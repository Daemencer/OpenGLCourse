#version 430

attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texcoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;

out VS_OUTPUT
{
	vec4 v_fragmentColor;
	vec2 v_texCoords;
} OUT;

void main(void)
{
	OUT.v_fragmentColor = a_color;
	OUT.v_texCoords = a_texcoords;
	
	gl_Position = /*project * view * model **/ a_position;
}