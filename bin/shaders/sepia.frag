// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

vec4 Sepia(vec2 texCoord) {
	vec4 colour = texture(colourTarget, texCoord);
	
	colour.a = 1.0f;
	
	float grey = (colour.r + colour.g + colour.b) / 3.0f;
	
	vec4 sephiaScale = vec4(grey, grey, grey, 1) * vec4(1.2f, 1.0f, 0.8f, 1);
	
	return sephiaScale;
}

void main() {
	// calculate texel size
	vec2 texSize = textureSize( colourTarget, 0 );
	vec2 texelSize = 1.0f / texSize;
	
	// adjust texture coordinate
	vec2 scale = (texSize - texelSize) / texSize;
	vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;
	
	// sample post effect
	vec2 texel = 1.0f / textureSize(colourTarget, 0).xy;
	FragColour = Sepia(texCoord);
}