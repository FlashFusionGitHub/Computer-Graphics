// a normal map fragment shader
#version 410

#define DIR 0
#define DIF 1
#define SPEC 2

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition;

out vec4 FragColour;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

uniform vec3 Ka; // material ambient
uniform vec3 Kd; // material diffuse
uniform vec3 Ks; // material specular

uniform float specularPower;

uniform vec3 Ia; // light ambient

uniform mat3 lights[2];

uniform vec3 cameraPosition;

uniform float roughness;
uniform float reflectionCoefficient;

void main() {

	vec3 N = normalize(vNormal);
	vec3 T = normalize(vTangent);
	vec3 B = normalize(vBiTangent);		
	vec3 E = normalize(cameraPosition - vPosition.xyz);		
	
	mat3 TBN = mat3(T,B,N);
	
	vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;	
	vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb;
	vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
	
	N = TBN * (texNormal * 2 - 1);
	vec3 ambient = Ia * Ka;
	FragColour = vec4(ambient, 1);
	
	for(int i = 0 ;i < 2; i++) {
		
		vec3 L = normalize(lights[i][DIR]);
		
		float NdL = max( 0.0f, dot( N, L ) );
		float NdE = max( 0.0f, dot( N, E ) );
		float R2 = roughness * roughness;
	
		// Oren-Nayar Diffuse Term
		float AX = 1.0f - 0.5f * R2 / (R2 + 0.33f);
		float BX = 0.45f * R2 / (R2 + 0.09f);
	
		// CX = Max(0, cos(l,e))
		vec3 lightProjected = normalize( L - N * NdL );
		vec3 viewProjected = normalize( E - N * NdE);
		float CX = max( 0.0f, dot( lightProjected, viewProjected ) );
	
		// DX = sin(alpha) * tan(beta)
		float alpha = sin( max( acos( NdE ), acos( NdL ) ) );
		float beta = tan( min( acos( NdE ), acos( NdL ) ) );
		float DX = alpha * beta;
	
	
		// Calculate Oren-Nayar, replaces the Phong Lambertian Term
		float OrenNayar = NdL * (AX + BX * CX * DX);	
	
		// calculate view vector and reflection vector
		vec3 V = normalize(cameraPosition - vPosition.xyz);
		vec3 R = reflect( L, N );
		vec3 H = (L + E) / 2;
	
		float NdH = max( 0.0f, dot( N, H ) );
		float NdH2 = NdH * NdH;
		float e = 2.71828182845904523536028747135f;
		float pi = 3.1415926535897932384626433832f;
	
		// Beckman's Distribution Function D
		float exponent = -(1 - NdH2) / (NdH2 * R2);
		float D = pow( e, exponent ) / (R2 * NdH2 * NdH2);
	
		// Fresnel Term F
		float F = reflectionCoefficient + (1 - reflectionCoefficient) * pow( 1 - NdE, 5 );
	
		// Geometric Attenuation Factor G
		float X = 2.0f * NdH / dot( E, H );
		float G = min(1, min(X * NdL, X * NdE));
	
		// Calculate Cook-Torrance
		float CookTorrance = max( (D*G*F) / (NdE * pi), 0.0f );
	
		// calculate each light property
		vec3 diffuse = lights[i][DIF] * Kd * texDiffuse * OrenNayar;
		vec3 specular = lights[i][SPEC] * Ks * texSpecular * CookTorrance;
	
		FragColour += vec4(diffuse + specular, 0);
	}
}