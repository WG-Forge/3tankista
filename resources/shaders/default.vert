#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

uniform vec4 uColor;
uniform mat4 uTransform;
uniform mat4 uProjection;

out vec4 varColor;
out vec3 varNormal;
out vec2 varTexCoord;

void main()
{
    varNormal   = aNormal;
    varTexCoord = aTexCoord;
    varColor    = uColor;

    gl_Position = uProjection * uTransform * vec4(aPos, 1.0);

}
