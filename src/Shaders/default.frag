#version 460 core
out vec4 FragColor;
uniform vec4 color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
void main()
{
   FragColor = color;
}