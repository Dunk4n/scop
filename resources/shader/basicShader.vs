#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texcoord;

out vec3 vs_position;
out vec3 vs_normal;
out vec2 vs_texcoord;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
    vs_position = vec3(ModelMatrix * vec4(vertex_position, 1.0f));
	vs_normal = vertex_normal;
	vs_texcoord = vertex_texcoord;
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.0f);
}
