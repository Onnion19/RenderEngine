#version 420 core
out vec4 FragColor;
in vec3 o_color;
void main()
{
   FragColor = vec4(o_color, 1.0f);
};
