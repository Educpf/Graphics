
#version 330 core

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

const int MAX_POINT_LIGHT = 3;


struct Light
{
   vec3 color;
   float ambientIntensity;
   float diffuseIntensity;
};

struct DirectionalLight
{
    Light base;
    vec3 direction;
};

struct PointLight
{
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};


struct Material
{
   float specularIntensity;
   float shininess;
};

uniform int pointLightCount;

uniform DirectionalLight directionLight;
uniform PointLight pointLights[MAX_POINT_LIGHT];

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;



vec4 CalcLightByDirection(Light light, vec3 direction)
{
   vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity; 

   float diffuseFactor = max(dot(normalize(Normal), normalize(direction)),0) ;
   vec4 diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

   vec4 specularColor = vec4(0, 0, 0, 0);

   if (diffuseFactor > 0.0f)
   {
      vec3 fragToEye = normalize(eyePosition - FragPos);
      vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
      float specularFactor = dot(fragToEye, reflectedVertex);

      if (specularFactor > 0)
      {
         specularFactor = pow(specularFactor, material.shininess);
         specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
      }
   }

   return (ambientColor + diffuseColor + specularColor);
}

vec4 CalcDirectionalLight()
{
    return CalcLightByDirection(directionLight.base, directionLight.direction);
}

vec4 CalcPointLights()
{

    vec4 totalColor = vec4(0,0,0,0);

    for (int i = 0; i < pointLightCount; i++)
    {
        // Calculate the direction
        vec3 direction = FragPos - pointLights[i].position;
        float distance = length(direction);
        direction = normalize(direction);

        vec4 color = CalcLightByDirection(pointLights[i].base, direction);

        float attenuation = pointLights[i].exponent * distance * distance 
                            + pointLights[i].linear * distance + pointLights[i].constant;

        totalColor += (color / attenuation);
    }
    return totalColor;
}


void main(){

    vec4 finalColor = CalcDirectionalLight() + CalcPointLights();


   vec4 texColor = texture(theTexture, TexCoord);
   color = texColor * finalColor;
};