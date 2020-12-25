#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

out vec3 ourColor;
uniform float offset;

void main()
{
    gl_Position = vec4(pos.x + offset, pos.y, pos.z, 1.0);
    ourColor = vec3(pos.x, pos.y, pos.z);
}
