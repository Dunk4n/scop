#version 440

struct Material
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	float	shininess;
	float	transparency;
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
uniform sampler2D tex;

void main()
{
	//vec4(1.f, 0.5f, 0.32f, 1.f)
	vec3 color = vec3(texture(tex, vs_texcoord) * transition +
	vec4(vs_color, 1.f) * (1.f - transition));

	vec3 ambient = color * material.ambient;
	
	vec3 norm = normalize(vs_normal);
	vec3 lightDir = normalize(lightPos - vs_position);;
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = color * (diff * material.diffuse);

	vec3 viewDir = normalize(cameraPos - vs_position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = color * (spec * material.specular);

	fs_color = vec4(ambient + diffuse + specular, material.transparency);
}
