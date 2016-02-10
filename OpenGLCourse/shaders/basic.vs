#version 430

//in vec4 a_color;
/*layout (location=0)*/ in vec4 a_position;
/*layout (location=1)*/ in vec2 a_texcoords;
/*layout (location=2)*/ in vec3 a_normal;
/*layout (location=3)*/ in vec4 a_color;

//layout (location=0) uniform float u_time;
//layout (location=1) uniform mat4 u_modelMatrix;

//layout(std140, binding=42)
/*uniform Matrices {
	mat4 u_viewMatrix;
	mat4 u_projectionMatrix;
};*/

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

const vec3 L = vec3(0.0, 0.0, 1.0);

out VS_OUTPUT
{
	vec3 v_normal;
	vec4 v_fragmentColor;
	vec2 v_texCoords;
} OUT;

//struct Light
//{
//	vec3	direction;
//	vec3 	la;
//};
//uniform Light	u_directionalLight;

void main(void)
{
	//mix(U, V, factor);

	//vec3 N = (mat3)model * a_normal;
	vec3 N = (model * vec4(a_normal, 0.0)).xyz;
	N = normalize(N);
	
	OUT.v_normal = N;
	OUT.v_texCoords = a_texcoords;
	
	vec4 Kd = a_color;
	OUT.v_fragmentColor = max(dot(N, L), 0.0) * Kd;
	
	gl_Position = project * view * model * a_position;
}