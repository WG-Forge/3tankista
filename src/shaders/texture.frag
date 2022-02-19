#version 330 core

out vec4 FragColor;

in vec4 ourColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main() {
    vec4  texColor = texture(ourTexture, texCoord);
    if(texColor.a < 0.1){
        discard;
    }
    FragColor = texColor;
}
