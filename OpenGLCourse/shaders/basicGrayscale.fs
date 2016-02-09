#version 430

in VS_OUTPUT
{
	vec4 v_fragmentColor;
	vec2 v_texCoords;
} IN;

uniform sampler2D texSampler;

out vec4 Fragment;

vec4 color;

void main(void)
{
	color = IN.v_fragmentColor * texture(texSampler, IN.v_texCoords);
    float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
    Fragment = vec4(average, average, average, 1.0);
}