#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main() {
   float ambience = 0.2;
   vec3 lightDirn = normalize(lightPos - currentPos);
   float diffuse = max(0.0, dot(Normal, lightDirn));
   
   float specularLight = 0.50;
   vec3 viewDirn = normalize(camPos - currentPos);
   vec3 reflectionDirn = reflect(-lightDirn, Normal);
   float specAmount = pow(max(0.0, dot(viewDirn, reflectionDirn)), 8);
   float specular = specAmount * specularLight;

   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambience + specular);
}