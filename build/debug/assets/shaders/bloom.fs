#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;

const float exposure = 4.0;
const float gamma = 0.1;

void main(){             
    vec3 hdrColor = texture(scene, TexCoords).rgb;      
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    
    hdrColor += bloomColor;
    
    //Mapeo de tonos
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    //Corrección gamma (esto hace que la luz sea mas realista)    
    result = pow(result, vec3(1.0 / gamma));

    FragColor = vec4(result, 1.0);
}