#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

out VS_OUT {
	vec3	normal;
}	vs_out;

uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
	gl_Position = ViewMatrix * ModelMatrix * vec4(vertex_position, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(ViewMatrix * ModelMatrix)));
    vs_out.normal = normalize(vec3(vec4(normalMatrix * vertex_normal, 0.0)));
}
