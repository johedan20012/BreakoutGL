#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D textImage;
uniform vec4 textColor;

void main(){    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textImage, TexCoords).r);
    color = textColor * sampled;
}  