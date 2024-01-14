#version 420 core
out vec4 FragColor;

in vec4 o_color;
in vec2 o_worldPos;
in vec3 o_sdf;

void main()
{
	vec2 center = o_sdf.xy;
	float radius = o_sdf.z;
	float d = distance(center,o_worldPos);
	
	float t = clamp((d - radius * 0.25)/ radius ,0.0,1.0);
	
	float alpha = smoothstep(1.0,0.0, t);
	
	FragColor = vec4(alpha);
};
