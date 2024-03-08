#version 330 core

layout (location = 0) out vec4 outColour;

in vec4 fragmentColour;
in vec2 fragmentTextureCoordinates;
in float fragmentTextureId;

uniform sampler2D textures;

void main() {
   //int index = int(fragmentTextureId);
   //outColour = fragmentColour;
   //outColour = texture(textures[index], fragmentTextureCoordinates) * fragmentColour;

   outColour = texture(textures, fragmentTextureCoordinates);
}