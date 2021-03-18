#version 330 core
in vec3 FragPos;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1; //Para la textura , puede ser sampler1D,sampler2D o sampler3D
uniform sampler2D texture2;

void main(){
    /*
    vec3 color = FragPos;
    /*transform color to color values {0.0,0.5,1.0}*//*
    float division = 20;
    color.x = floor(color.x*division)/division;
    color.y = floor(color.y*division)/division;
    color.z = floor(color.z*division)/division; */

    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}


