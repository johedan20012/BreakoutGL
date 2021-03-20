#version 330 core
layout (location = 0) in vec4 vertex;

out vec4 TexCoords;

uniform mat4 projection;
uniform vec2 offset;

void main(){
    float scale = 10.0f;
    TexCoords = vertex.zw;
    gl_Position = projection*vec4((vertex.xy*scale)+offset,0.0,1.0);
}

