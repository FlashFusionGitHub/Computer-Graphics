// a simple textured shader
#version 410

in vec2 vTexCoord;

uniform sampler2D diffuseTexture;

out vec4 FragColour;

void main() {
	FragColour = texture( diffuseTexture, vTexCoord );
	//FragColour = vec4(0, 0, 1, 1);
}
