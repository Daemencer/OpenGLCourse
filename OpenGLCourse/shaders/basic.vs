#version 430

/*layout (location=0)*/ in vec4 a_position;
/*layout (location=1)*/ in vec2 a_texcoords;
/*layout (location=2)*/ in vec3 a_normal;

uniform vec3 u_viewPos;

layout (std140, binding=0) uniform WorldMatrices
{
	mat4 translate;
	mat4 rotate;
	mat4 scale;
};

//uniform mat4 u_worldMatrix;

layout (std140, binding=1) uniform CameraMatrices
{
	mat4 u_viewMatrix;
	mat4 u_projectMatrix;
};

out VS_OUTPUT
{
	vec3 v_pos;
	vec3 v_normal;
	vec4 v_fragmentColor;
	vec2 v_texCoords;
	
	vec3 v_viewPos;
} OUT;

out vec3 FragmentPosition;

void main(void)
{
	mat4 model = scale * rotate * translate;

	// for hemisphere lighting
	//mix(U, V, factor);
	
	//vec3 N = (mat4(transpose(inverse(u_worldMatrix))) * vec4(a_normal, 1.0)).xyz;
	vec3 N = (mat4(transpose(inverse(model))) * vec4(a_normal, 1.0)).xyz;
	N = normalize(N);
	
	OUT.v_normal = N;
	OUT.v_texCoords = a_texcoords;
	OUT.v_fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
	
	//OUT.v_pos = (u_worldMatrix * a_position).xyz;
	OUT.v_pos = (model * a_position).xyz;
	
	//OUT.v_viewPos = (u_worldMatrix * vec4(u_viewPos, 0.0)).xyz;
	OUT.v_viewPos = (model * vec4(u_viewPos, 0.0)).xyz;
	
	//gl_Position = u_projectMatrix * u_viewMatrix * u_worldMatrix * a_position;
	gl_Position = u_projectMatrix * u_viewMatrix * model * a_position;
}


// tan(a) = sin(a) / cos(a) car tan = oppose / adjacent
// donc
// adjacent = oppose / tangent

// Dans notre cas: a = FOVy / 2

// H = max.y - min.y			// hauteur de la bounding box
// H / 2 = (max.y - min.y) / 2	// demi hauteur (half extent)

// distance = (H/2) / tan(a) => (H/2) * cotan(a)

// CAMERA.z = (H/2) / cotan(FOVy/2)