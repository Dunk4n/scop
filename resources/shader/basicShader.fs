#version 440

struct Material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
	float	transparency;
	sampler2D diffuse_tex;
	sampler2D specular_tex;
};

in vec3 vs_position;
in vec3 vs_normal;
in vec2 vs_texcoord;
in vec3 vs_color;

out vec4 fs_color;

uniform Material material;
uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform float transition;
uniform int use_material;

void main()
{
	vec3 color;

	if (use_material == 1)
		color = vec3(1.f);
	else
	{
		color = vec3(texture(material.diffuse_tex, vs_texcoord) * transition +
		vec4(vs_color, 1.f) * (1.f - transition));
	}
	if (use_material == 2)
	{
		fs_color = vec4(color, 1.f);
		return ;
	}

	vec3 ambient = color * material.ambient;
	
	vec3 norm = normalize(vs_normal);
	vec3 lightDir = normalize(lightPos - vs_position);;
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = color * diff * material.diffuse;

	vec3 viewDir = normalize(cameraPos - vs_position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 specular = spec * material.specular;
	if (textureSize(material.specular_tex, 1) != ivec2(0, 0))
		specular *= vec3(texture(material.specular_tex, vs_texcoord));

	fs_color = vec4(ambient + diffuse + specular, material.transparency);
}
