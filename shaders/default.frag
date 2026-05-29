#version 330 core

out vec4 FragColor;

in vec3 currentPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() {
   vec3 lightVec = lightPos - currentPos;
   float dist = length(lightVec);
   float a = 1.04;
   float b = 0.04;
   float intensity = 1.0 / (a * pow(dist, 2) + b * dist + 1.0);
   
   float ambience = 0.2;
   vec3 lightDirn = normalize(lightVec);
   float diffuse = max(0.0, dot(Normal, lightDirn));
   
   float specularLight = 0.50;
   vec3 viewDirn = normalize(camPos - currentPos);
   vec3 reflectionDirn = reflect(-lightDirn, Normal);
   float specAmount = pow(max(0.0, dot(viewDirn, reflectionDirn)), 16);
   float specular = specAmount * specularLight;

   return (texture(diffuse0, texCoord) * (diffuse * intensity + ambience) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

vec4 direcLight() {
   float ambience = 0.2;
   vec3 lightDirn = normalize(vec3(1.0, 1.0, 0.0));
   float diffuse = max(0.0, dot(Normal, lightDirn));
   
   float specularLight = 0.50;
   vec3 viewDirn = normalize(camPos - currentPos);
   vec3 reflectionDirn = reflect(-lightDirn, Normal);
   float specAmount = pow(max(0.0, dot(viewDirn, reflectionDirn)), 16);
   float specular = specAmount * specularLight;

   return (texture(diffuse0, texCoord) * (diffuse + ambience) + texture(specular0, texCoord).r * specular) * lightColor;
}


vec4 spotLight() {
   float outerCone = 0.90;
   float innerCone = 0.95;

   float ambience = 0.2;
   vec3 lightDirn = normalize(lightPos - currentPos);
   float diffuse = max(0.0, dot(Normal, lightDirn));
   
   float specularLight = 0.50;
   vec3 viewDirn = normalize(camPos - currentPos);
   vec3 reflectionDirn = reflect(-lightDirn, Normal);
   float specAmount = pow(max(0.0, dot(viewDirn, reflectionDirn)), 16);
   float specular = specAmount * specularLight;

   float angle = dot(vec3(0.0, -1.0, 0.0), -lightDirn);
   float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0);

   return (texture(diffuse0, texCoord) * (diffuse * intensity + ambience) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

void main() {
   FragColor = direcLight();
}