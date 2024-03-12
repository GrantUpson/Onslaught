#version 330 core

layout (location = 0) out vec4 outputColour;

in vec4 fragmentColour;
in vec2 fragmentTextureCoordinates;
in float fragmentTextureIndex;

uniform sampler2DArray textureAtlas;


void main() {
   outputColour = texelFetch(textureAtlas, ivec3(fragmentTextureCoordinates, int(fragmentTextureIndex)), 0) * fragmentColour;
}