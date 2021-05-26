#version 330 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

in vec2 TexCoords;

uniform sampler2D image;
uniform sampler2D brightMap;

uniform vec3 tileCount; 

uniform float ambientStrength;

void main(){    
    vec4 textColor = texture(image, TexCoords);

    vec3 ambient = ambientStrength * vec3(1.0,1.0,1.0);

    FragColor = textColor*vec4(ambient,1.0);
    BrightColor = vec4(texture(brightMap, TexCoords).rgb*10,1.0);
}