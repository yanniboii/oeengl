#version 330 core
out vec4 FragColor;
in float vTime;
in vec3 vCol;
in vec3 vNorm;
in vec3 FragPos;
in vec3 vViewPos;

struct Material{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;

    float ambientCoefficient;
    float diffuseCoefficient;
    float specularCoefficient;

    float specularShininess;
};

struct Light{
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

uniform vec3 m_LightPos;


void main()
{
    vec4 a = material.ambientColor * light.ambientColor * material.ambientCoefficient * light.ambientIntensity;

    vec3 norm = normalize(vNorm);
    vec3 lightDist = vec3(m_LightPos - FragPos);
    vec3 lightDir = normalize(lightDist);

    float diff =    light.diffuseIntensity * 
                    material.diffuseCoefficient *
                    max(0,dot(norm,lightDir));

    vec4 d =    diff * 
                material.diffuseColor * 
                light.diffuseColor;

    vec3 reflection = reflect(-lightDir, norm);
    vec3 viewDir = normalize(vViewPos - FragPos);

    float spec = (
    pow(max(0,dot(reflection,viewDir)), 
    material.specularShininess));

    vec4 s =    spec * 
                light.specularColor * 
                material.specularColor * 
                material.specularCoefficient * 
                light.specularIntensity;

    vec4 ds = d + s;
    vec4 attenuation =  ds / 
                        (light.constant + 
                        light.linear * length(lightDist) + 
                        light.quadratic * pow(length(lightDist),2));
    vec4 ad = a + d;
    vec4 ads = a + attenuation;

    FragColor = ads;
} 