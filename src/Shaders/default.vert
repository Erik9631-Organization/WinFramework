#version 460 core
layout (location = 0) in vec3 aPos;
uniform mat4 transform = mat4(1);
uniform mat4 view = mat4(1);
void main()
{
   vec4 pos =  view * transform * vec4(aPos, 1.0f);
   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}