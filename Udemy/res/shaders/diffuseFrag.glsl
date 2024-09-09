#version 330 core

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

struct DirectionalLight
{
   vec3 color;
   float ambientIntensity;
   vec3 direction;
   float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionLight;

void main(){

   vec4 ambientColor = vec4(directionLight.color, 1.0f) * directionLight.ambientIntensity; 

   float diffuseFactor = max(dot(normalize(Normal), normalize(directionLight.direction)),0) ;
   vec4 diffuseColor = vec4(directionLight.color, 1.0f) * directionLight.diffuseIntensity * diffuseFactor;

   vec4 texColor = texture(theTexture, TexCoord);
   color = texColor * (ambientColor + diffuseColor);
};