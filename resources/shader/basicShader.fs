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

in VS_OUT {
	vec3	position;
	vec3	normal;
	vec2	texcoord;
	vec3	color;
}	fs_in;

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
		color = vec3(texture(material.diffuse_tex, fs_in.texcoord) * transition +
		vec4(fs_in.color, 1.f) * (1.f - transition));
	}
	if (use_material == 2)
	{
		fs_color = vec4(color, 1.f);
		return ;
	}

	vec3 ambient = color * material.ambient;
	
	vec3 norm = normalize(fs_in.normal);
	if (!gl_FrontFacing)
		norm *= -1;
	vec3 lightDir = normalize(lightPos - fs_in.position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = color * diff * material.diffuse;

	vec3 viewDir = normalize(cameraPos - fs_in.position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 specular = spec * material.specular;
	if (textureSize(material.specular_tex, 1) != ivec2(0, 0))
		specular *= vec3(texture(material.specular_tex, fs_in.texcoord));

	fs_color = vec4(ambient + diffuse + specular, material.transparency);
}
