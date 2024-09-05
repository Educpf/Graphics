#version 330 core

in vec4 vCol;
in vec2 TexCoord;

out vec4 color;

struct DirectionalLight
{
   vec3 color;
   float ambientIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionLight;

void main(){

   vec4 ambientColor = vec4(directionLight.color, 1.0f) * directionLight.ambientIntensity; 

   vec4 texColor = texture(theTexture, TexCoord);
   color = texColor * ambientColor;
};