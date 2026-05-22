#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;

float ambience = 0.2;

void main() {
   vec3 lightDirn = normalize(lightPos - currentPos);
   float diffuse = max(0.0, dot(Normal, lightDirn));

   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambience);
}