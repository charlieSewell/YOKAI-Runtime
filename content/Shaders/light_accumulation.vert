#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;
layout (location = 5) in ivec4 boneIDs;
layout (location = 6) in vec4 weights;

out VERTEX_OUT {
	vec3 fragmentPosition;
	vec2 textureCoordinates;
	mat3 TBN;
	vec3 tangentViewPosition;
	vec3 tangentFragmentPosition;
} vertex_out;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 boneTrans[MAX_BONES];
uniform bool isAnimated;

out vec3 Normal;
// Uniforms
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 viewPosition;

void main() {
	//Skeletal Animation
	mat4 BoneTransform = boneTrans[boneIDs[0]] * weights[0];
    BoneTransform += boneTrans[boneIDs[1]] * weights[1];
    BoneTransform += boneTrans[boneIDs[2]] * weights[2];
    BoneTransform += boneTrans[boneIDs[3]] * weights[3];
    vec4 PosL;
    if(isAnimated)
    {
        PosL = BoneTransform * vec4(position, 1.0);
    }
    else{
        PosL = vec4(position, 1.0);
    }

	gl_Position = projection * view * model * PosL;
	vertex_out.fragmentPosition = vec3(model * vec4(position, 1.0));
	vertex_out.textureCoordinates = texCoords;

	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 tan = normalize(normalMatrix * tangent);
	vec3 bitan = normalize(normalMatrix * bitangent);
	vec3 norm = normalize(normalMatrix * normal);

	// For tangent space normal mapping
	mat3 TBN = transpose(mat3(tan, bitan, norm));
	vertex_out.tangentViewPosition = TBN * viewPosition;
	vertex_out.tangentFragmentPosition = TBN * vertex_out.fragmentPosition;
	vertex_out.TBN = TBN;
	Normal = normal;
}