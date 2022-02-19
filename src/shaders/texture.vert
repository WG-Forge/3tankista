 #version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec4 aColor;
uniform mat4 aModelTransform;

out vec4 ourColor;
out vec2 texCoord;

void main() {
    gl_Position = aModelTransform * vec4(aPos, 1.0f);
    ourColor = aColor;
    texCoord = aTexCoord;
}
