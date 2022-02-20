#version 330 core
out vec4 FragColor;

in vec4 varColor;
in vec3 varNormal;
in vec2 varTexCoord;

uniform float     uMixValue;
uniform sampler2D uTexSampler;

void main()
{
    vec4  texColor = texture(uTexSampler, varTexCoord);
    if(texColor.a < 0.1){
        discard;
    }
    FragColor = mix(texColor, varColor, uMixValue);
}
