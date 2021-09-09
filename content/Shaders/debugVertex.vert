#version 330 core
// In variables
layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in uint vertexColor;


// Uniform variables
uniform mat4 model;        // Local-space to world-space matrix
uniform mat4 view;       // World-space to camera-space matrix
uniform mat4 projection;          // Projection matrix

// Out variables
out vec4 vertexColorOut;

void main() {

    gl_Position = projection * view * vertexPosition;

    // Transfer the vertex color to the fragment shader
    vertexColorOut = vec4((vertexColor & 0xFF0000u) >> 16, (vertexColor & 0x00FF00u) >> 8, vertexColor & 0x0000FFu, 0xFF);
}