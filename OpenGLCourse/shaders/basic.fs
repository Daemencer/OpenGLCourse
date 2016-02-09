#version 430

in VS_OUTPUT
{
	vec3 v_normal;
	vec4 v_fragmentColor;
	vec2 v_texCoords;
} IN;

uniform sampler2D texSampler;

out vec4 Fragment;

void main(void)
{
	Fragment = IN.v_fragmentColor * texture(texSampler, IN.v_texCoords);
}