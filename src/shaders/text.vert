#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

uniform mat4 uProjection;

out vec2 TexCoords;

void main()
{
    gl_Position = uProjection * vec4(vertex.xy, -0.5, 1.0);
    TexCoords = vertex.zw;
}
