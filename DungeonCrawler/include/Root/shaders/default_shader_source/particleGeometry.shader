#version 460 core

layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

out vec2 FragIn_TexCoords;

vec2 offsets[] = {
	vec2( 0.5, 0.5),
	vec2( 0.5,-0.5),
	vec2(-0.5, 0.5),
	vec2( 0.5,-0.5),
	vec2(-0.5,-0.5),
	vec2(-0.5, 0.5)
};

void main()
{
	for (int i = 0; i < 6; i++)
	{
		FragIn_TexCoords = offsets[i] + vec2(0.5, 0.5);
		gl_Position = gl_in[0].gl_Position + vec4(offsets[i], 0.0f, 0.0f) * 0.04;
		EmitVertex();
		if (i == 2 || i == 5)
		{
			EndPrimitive();
		}
	}
}
