#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aSdf;

out vec4 o_color;
out vec2 o_worldPos;
out vec3 o_sdf;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	o_worldPos = (model * vec4(aPos, 1.0)).xy;
	o_color = vec4(0.85,0.15,0.03,1.0);
	o_sdf = aSdf;
};