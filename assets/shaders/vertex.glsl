#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 textureCoordinates;
layout (location = 3) in float textureId;

out vec4 fragmentColour;
out vec2 fragmentTextureCoordinates;
out float fragmentTextureId;

uniform mat4 projection;
uniform mat4 model;

void main() {
    //gl_Position = viewProjection * vec4(position, 1.0);
    gl_Position = projection * model * vec4(position, 1.0);

    fragmentColour = colour;
    fragmentTextureCoordinates = textureCoordinates;
    fragmentTextureId = textureId;
}