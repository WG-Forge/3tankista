#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec4 aColor;
uniform mat4 aModelTransform;
//uniform vec4 projection;

out vec4 ourColor;

void main()
{
    gl_Position = aModelTransform * vec4(aPos, 1.0);
    ourColor = aColor;
}
