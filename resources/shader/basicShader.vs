#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texcoord;
layout(location = 3) in vec3 vertex_color;

out VS_OUT {
	vec3	position;
	vec3	normal;
	vec2	texcoord;
	vec3	color;
}	vs_out;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
    vs_out.position = vertex_position;
    vs_out.normal = mat3(transpose(inverse(ModelMatrix))) * vertex_normal;
	vs_out.texcoord = vertex_texcoord;
	vs_out.color = vertex_color;
}
