#version 330 core
#extension GL_ARB_shading_language_420pack: enable

layout (binding = 0) uniform sampler2D tex_composite;

layout (location = 0) out vec4 color;

void main(void)
{
	color = texelFetch(tex_composite, ivec2(gl_FragCoord.xy), 0);
	//color = vec4(0.0,0.0,1.0,1.0);
}

