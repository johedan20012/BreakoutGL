#version 330 core

layout(location = 0)out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

in vec2 TexCoords;

uniform sampler2D image;
uniform sampler2D brightMap;
uniform vec4 spriteColor;

void main(){
    FragColor = spriteColor * texture(image,TexCoords);
    BrightColor = texture(brightMap,TexCoords);
}