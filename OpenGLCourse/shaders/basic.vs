#version 430

/*layout (location=0)*/ in vec4 a_position;
/*layout (location=1)*/ in vec2 a_texcoords;
/*layout (location=2)*/ in vec3 a_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

out VS_OUTPUT
{
	vec3 v_pos;
	vec3 v_normal;
	vec4 v_fragmentColor;
	vec2 v_texCoords;
} OUT;

out vec3 FragmentPosition;

void main(void)
{
	// for hemisphere lighting
	//mix(U, V, factor);
	
	//vec3 N = (model * vec4(a_normal, 0.0)).xyz;
	vec3 N = (mat4(transpose(inverse(model))) * vec4(a_normal, 1.0)).xyz;
	N = normalize(N);
	
	OUT.v_normal = N;
	OUT.v_texCoords = a_texcoords;
	OUT.v_fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
	
	OUT.v_pos = (model * a_position).xyz;
	
	gl_Position = project * view * model * a_position;
}