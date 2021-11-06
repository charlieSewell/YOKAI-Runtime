#version 430 core

in vec2 TextureCoordinates;

//framebuffer in
uniform sampler2D hdrBuffer;

//exposure level of image
uniform float exposure;

out vec4 fragColor;

// Uses Reinhard tonemapping https://www.cs.utah.edu/~reinhard/cdrom/tonemap.pdf

void main() {
	vec3 color = texture(hdrBuffer, TextureCoordinates).rgb;
	vec3 result = vec3(1.0) - exp(-color * exposure);

	// Minor gamma correction. Need to expand on it
	const float gamma = 2.2;
	result = pow(result, vec3(1.0 / gamma));
	fragColor = vec4(result, 1.0);
}
