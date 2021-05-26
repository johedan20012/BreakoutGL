#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec2 TexCoords;

void main() {    
    gl_Position = gl_in[0].gl_Position;
    TexCoords = vec2(0.5);
    EmitVertex();   

    gl_Position = gl_in[1].gl_Position;
    TexCoords = (gl_in[1].gl_Position.x == gl_in[0].gl_Position.x)? vec2(0.5,1.5) : vec2(1.5,0.5);
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    TexCoords = vec2(1.5);
    EmitVertex();
    EndPrimitive();
} 