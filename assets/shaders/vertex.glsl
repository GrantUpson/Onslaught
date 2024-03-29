#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 textureCoordinates;
layout (location = 3) in float textureIndex;

uniform mat4 viewProjection;

out vec4 fragmentColour;
out vec2 fragmentTextureCoordinates;
out float fragmentTextureIndex;


void main() {
    gl_Position = viewProjection * vec4(position, 1.0);

    fragmentColour = colour;
    fragmentTextureCoordinates = textureCoordinates;
    fragmentTextureIndex = textureIndex;
}