#version 440

in vec3 vs_position;
in vec3 vs_normal;
in vec2 vs_texcoord;

out vec4 fs_color;

uniform float transition;
uniform sampler2D tex;

void main()
{
	fs_color = texture(tex, vs_texcoord) * transition + vec4(vs_normal, 1.f) * (1.f - transition);
}
