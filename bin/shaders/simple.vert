#version 410

layout( location = 0 ) in vec4 Position;
layout( location = 1 ) in vec4 Colour;

out vec4 vPosition;
out vec4 vColour;

uniform mat4 ProjectionViewModel;

// We need this matrix to transform the position
uniform mat4 ModelMatrix;

void main() {
	vPosition = ModelMatrix * Position;
	vColour = Colour;
	gl_Position = ProjectionViewModel * Position;
}
