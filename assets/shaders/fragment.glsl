#version 330 core

layout (location = 0) out vec4 outColour;

in vec4 fragmentColour;
in vec2 fragmentTextureCoordinates;
in float fragmentTextureId;

void main() {
   int index = int(fragmentTextureId);
   outColour = fragmentColour; //REPLACE WITH THIS FOR TEXTURES outColor = texture(textures[index], fragmentTextureCoordinates) * fragmentColour
}