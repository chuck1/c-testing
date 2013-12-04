#version 330 core

struct Light
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 spot_direction;
	float spot_cutoff;
	float atten_const;
	float atten_linear;
	float atten_quad;
	float spot_exponent;
	float spot_light_cos_cutoff;
};

struct Material
{
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
	vec4 emission;
	float shininess;
};

struct VS_OUT
{
	vec3 P;
	vec3 L;
	vec2 texcoor;
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texcoor;

out VS_OUT vs_out;

void main(void)
{
	mat4 modelview = view * model;
	
	// Calculate view-space coordinate
	vs_out.P = modelview * position;
	
	// Calculate normal in view-space
	vs_out.N = normalize(mat3(modelview) * normal);

	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_out.P;

	// texture coordinate
	vs_out.texcoor = texcoor;
}



