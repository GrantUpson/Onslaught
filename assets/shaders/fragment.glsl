#version 330 core

layout (location = 0) out vec4 outColour;

in vec4 fragmentColour;
in vec2 fragmentTextureCoordinates;
in float fragmentTextureId;

//uniform sampler2D textures[16];
//uniform sampler2D ourTexture;

void main() {
   //int index = int(fragmentTextureId);
   outColour = fragmentColour;
   //outColour = texture(textures[index], fragmentTextureCoordinates) * fragmentColour;
}