// a simple textured shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

void main() {
	FragColour = texture( colourTarget, vTexCoord );
}