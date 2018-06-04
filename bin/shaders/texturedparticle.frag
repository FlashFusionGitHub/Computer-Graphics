// FRAGMENT SHADER
#version 410

in vec4 vPosition;
in vec4 vColour;
in vec2 vTexCoord;

uniform sampler2D diffuseTexture;

out vec4 FragColour;

void main() {
	FragColour = texture( diffuseTexture, vTexCoord);
}
