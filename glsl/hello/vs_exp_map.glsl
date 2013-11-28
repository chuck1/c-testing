#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 triangle_ID;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

// explosion map sphere
uniform vec3 center;
uniform float radius;

out vec4 color;


void main(void)
{
	mat4 modelview = view_matrix * model_matrix;

        // Calculate view-space coordinate
        vec4 P = modelview * position;

        // Calculate normal in view-space
        vs_out.N = mat3(modelview) * normal;

        // Calculate view vector
        vs_out.V = -P.xyz;

	vec3 R = reflect(P,N);

	float s = r/2 * ( 1 + ( R.x / sqrt( 2*(R.z+1) ) ) );
	float t = r/2 * ( 1 + ( R.y / sqrt( 2*(R.z+1) ) ) );
	
	
        gl_Position = vec3(s, t, -1.0);

	color = triangle_ID;
}



