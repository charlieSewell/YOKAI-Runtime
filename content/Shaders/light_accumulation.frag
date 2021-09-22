#version 430

in VERTEX_OUT{
	vec3 fragmentPosition;
	vec2 textureCoordinates;
	mat3 TBN;
	vec3 tangentViewPosition;
	vec3 tangentFragmentPosition;
} fragment_in;

struct PointLight {
	vec4 color;
	vec4 position;
	vec4 paddingAndRadius;
};
struct LightGrid{
    uint offset;
    uint count;
};
// Shader storage buffer objects
layout (std430, binding = 2) buffer screenToView{
    mat4 inverseProjection;
    uvec4 tileSizes;
    uvec2 screenDimensions;
    float scale;
    float bias;
} screen2View;
layout (std430, binding = 3) buffer lightSSBO{
    PointLight data[];
} lightBuffer;

layout (std430, binding = 4) buffer lightIndexSSBO{
    uint data[];
} visibleLightIndicesBuffer;

layout (std430, binding = 5) buffer lightGridSSBO{
    LightGrid lightGrid[];
} lightGrid;

vec3 colors[8] = vec3[](
   vec3(0, 0, 0),    vec3( 0,  0,  1), vec3( 0, 1, 0),  vec3(0, 1,  1),
   vec3(1,  0,  0),  vec3( 1,  0,  1), vec3( 1, 1, 0),  vec3(1, 1, 1)
);

// Uniforms
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform float zNear;
uniform float zFar;

out vec4 fragColor;

// Attenuate the point light intensity
float attenuate(vec3 lightDirection, float radius) {
	float cutoff = 0.5;
	float attenuation = dot(lightDirection, lightDirection) / (100.0 * radius);
	attenuation = 1.0 / (attenuation * 15.0 + 1.0);
	attenuation = (attenuation - cutoff) / (1.0 - cutoff);

	return clamp(attenuation, 0.0, 1.0);
}
float linearDepth(float depthSample){
    float depthRange = 2.0 * depthSample - 1.0;
    // Near... Far... wherever you are...
    float linear = 2.0 * zNear * zFar / (zFar + zNear - depthRange * (zFar - zNear));
    return linear;
}

void main() {
	// Determine which tile this pixel belongs to
	//Locating which cluster you are a part of
    uint zTile     = uint(max(log2(linearDepth(gl_FragCoord.z)) * screen2View.scale + screen2View.bias, 0.0));
    uvec3 tiles    = uvec3( uvec2( gl_FragCoord.xy / screen2View.tileSizes[3] ), zTile);
    uint tileIndex = tiles.x +
                     screen2View.tileSizes.x * tiles.y +
                     (screen2View.tileSizes.x * screen2View.tileSizes.y) * tiles.z;  

	// Get color and normal components from texture maps
	vec4 base_diffuse = texture(texture_diffuse1, fragment_in.textureCoordinates);
	vec4 base_specular = texture(texture_specular1, fragment_in.textureCoordinates);
	vec3 normal = texture(texture_normal1, fragment_in.textureCoordinates).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	vec4 color = vec4(0.0, 0.0, 0.0, 1.0);

	vec3 viewDirection = normalize(fragment_in.tangentViewPosition - fragment_in.tangentFragmentPosition);

	// The offset is this tile's position in the global array of valid light indices.
	// Loop through all these indices until we hit max number of lights or the end (indicated by an index of -1)
	// Calculate the lighting contribution from each visible point light
	uint lightCount       = lightGrid.lightGrid[tileIndex].count;
    uint lightIndexOffset = lightGrid.lightGrid[tileIndex].offset;
	
	for (uint i = 0; i < lightCount; i++) {
		uint lightIndex = visibleLightIndicesBuffer.data[lightIndexOffset + i];
		PointLight light = lightBuffer.data[lightIndex];
		
		vec4 lightColor = light.color;
		vec3 tangentLightPosition = fragment_in.TBN * light.position.xyz;
		float lightRadius = light.paddingAndRadius.w;

		// Calculate the light attenuation on the pre-normalized lightDirection
		vec3 lightDirection = tangentLightPosition - fragment_in.tangentFragmentPosition;
		float attenuation = attenuate(lightDirection, lightRadius);

		// Normalize the light direction and calculate the halfway vector
		lightDirection = normalize(lightDirection);
		vec3 halfway = normalize(lightDirection + viewDirection);

		// Calculate the diffuse and specular components of the irradiance, then irradiance, and accumulate onto color
		float diffuse = max(dot(lightDirection, normal), 0.0);
		// How do I change the material propery for the spec exponent? is it the alpha of the spec texture?
		float specular = pow(max(dot(normal, halfway), 0.0), 32.0);

		// Hacky fix to handle issue where specular light still effects scene once point light has passed into an object
		if (diffuse == 0.0) {
			specular = 0.0;
		}

		vec3 irradiance = lightColor.rgb * ((base_diffuse.rgb * diffuse) + (base_specular.rgb * vec3(specular))) * attenuation;
		color.rgb += irradiance;
	}
	color.rgb += base_diffuse.rgb * 0.08;

	// Use the mask to discard any fragments that are transparent
	if (base_diffuse.a <= 0.2) {
		discard;
	}
	
	fragColor = color;
}