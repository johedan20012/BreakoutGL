#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec3 FragPos;
out vec2 TexCoord;

void main(){
    //Saluda del vertex shader
    gl_Position = vec4(aPos,1.0);
    FragPos = aPos;
    TexCoord = aTexCoord;
}
