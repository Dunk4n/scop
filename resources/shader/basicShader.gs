#version 440

layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
	vec3	position;
	vec3	normal;
	vec2	texcoord;
	vec3	color;
}	gs_in[];

out VS_OUT {
	vec3	position;
	vec3	normal;
	vec2	texcoord;
	vec3	color;
}	gs_out;

uniform float explosion;

vec3	GetNormal()
{
	vec3 a = vec3(gs_in[0].position) - vec3(gs_in[1].position);
	vec3 b = vec3(gs_in[2].position) - vec3(gs_in[1].position);
	return (normalize(cross(a, b)));
}

vec3	GetDirection()
{
	if (explosion == -1)
		return (vec3(0));
	vec3 normal = GetNormal();
	vec3	direction = normal * ((sin(explosion) + 1.0) / 2.0) * 2.0;
	return (direction);
}

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void	main()
{
	vec3 direction = -GetDirection();

	gs_out.position = vec3(ModelMatrix * vec4(gs_in[0].position + direction, 1));
	gs_out.normal = gs_in[0].normal;
	gs_out.texcoord = gs_in[0].texcoord;
	gs_out.color = gs_in[0].color;
	gl_Position = ProjectionMatrix * ViewMatrix * vec4(gs_out.position, 1);
	EmitVertex();
	gs_out.position = vec3(ModelMatrix * vec4(gs_in[1].position + direction, 1));
	gs_out.normal = gs_in[1].normal;
	gs_out.texcoord = gs_in[1].texcoord;
	gs_out.color = gs_in[1].color;
	gl_Position = ProjectionMatrix * ViewMatrix * vec4(gs_out.position, 1);
	EmitVertex();
	gs_out.position = vec3(ModelMatrix * vec4(gs_in[2].position + direction, 1));
	gs_out.normal = gs_in[2].normal;
	gs_out.texcoord = gs_in[2].texcoord;
	gs_out.color = gs_in[2].color;
	gl_Position = ProjectionMatrix * ViewMatrix * vec4(gs_out.position, 1);
	EmitVertex();
	EndPrimitive();
}
