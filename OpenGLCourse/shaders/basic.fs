#version 430

struct Light
{
	vec3	direction;
	vec3 	la;
	vec3	ld;
	vec3	ls;
};
uniform Light	u_directionalLight;

struct Material
{
	vec3 Ke;
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float shininess;
};
uniform Material u_material;

in VS_OUTPUT
{
	vec3 v_normal;
	vec4 v_fragmentColor;
	vec2 v_texCoords;
} IN;

const vec4 Kd = vec4(1.0, 1.0, 1.0, 1.0);
const vec3 L = vec3(0.0, 0.0, 1.0);

uniform sampler2D texSampler;

out vec4 Fragment;

void main(void)
{
	//OUT.v_fragmentColor = max(dot(N, L), 0.0) * Kd;
	Fragment = IN.v_fragmentColor * texture(texSampler, IN.v_texCoords);
}