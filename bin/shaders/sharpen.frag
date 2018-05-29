// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

vec4 Sharpen(vec2 texCoord) {
	vec2 texel = 1.0f / textureSize(colourTarget, 0).xy;
	
	vec4 colour = texture(colourTarget, texCoord) * (11 / 3);
	
	colour += texture( colourTarget, texCoord + vec2( 0, texel.y ) ) * (-2 / 3);
	colour += texture( colourTarget, texCoord - vec2( 0, texel.y ) ) * (-2 / 3);
	colour += texture( colourTarget, texCoord + vec2( texel.x, 0 ) ) * (-2 / 3);
	colour += texture( colourTarget, texCoord - vec2( texel.x, 0 ) ) * (-2 / 3);
	
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
	FragColour = Sharpen(texCoord);
}