// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

vec4 EdgeDetection(vec2 texCoord) {
	vec2 texel = 1.0f / textureSize(colourTarget, 0).xy;
	
	vec4 colourX = texture(colourTarget, texCoord) * 0;
	vec4 colourY = texture(colourTarget, texCoord) * 0;
	
	colourX += texture( colourTarget, texCoord + texel * vec2(-1, 1) ) * -1;
	colourX += texture( colourTarget, texCoord + texel * vec2(1, 1) ) * 1;
	colourX += texture( colourTarget, texCoord + texel * vec2(-1, 0) ) * -2;
	colourX += texture( colourTarget, texCoord + texel * vec2(1, 0) ) * 2;
	colourX += texture( colourTarget, texCoord + texel * vec2(-1, -1) ) * -1;
    colourX += texture( colourTarget, texCoord + texel * vec2(1, -1) ) * 1;
	
	colourY += texture( colourTarget, texCoord - texel * vec2(-1, 1) ) * -1;
	colourY += texture( colourTarget, texCoord - texel * vec2(0, 1) ) * -2;
	colourY += texture( colourTarget, texCoord - texel * vec2(1, 1) ) * -1;
	colourY += texture( colourTarget, texCoord - texel * vec2(-1, -1) ) * 1;
	colourY += texture( colourTarget, texCoord - texel * vec2(0, -1) ) * 2;
    colourY += texture( colourTarget, texCoord - texel * vec2(1, 1) ) * 1;
	
	vec4 colour = sqrt((colourX * colourX) + (colourY * colourY));

	colour.a = 1.0f;
		
	return colour;
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
	
	FragColour = EdgeDetection(texCoord);
}