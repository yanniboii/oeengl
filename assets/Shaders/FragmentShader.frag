#version 460 core
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

    vec3 lightPos;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;

	float innerCutoff;
	float outerCutoff;

	float shadowBias;
	float maximumLightDistance;

	float timeOffset;
	float lightFlickerIntensity;
	float lightMovementSpeed;

	float lightTemperature;
	float intensityScale;

	float lightType;

	float castsShadows;
    };

layout(std430, binding = 0) readonly buffer LightBuffer {
    Light[] lights;
};


uniform Material material;

uniform int numLights;


void main()
{
vec4 a = vec4(0.0);
vec4 d = vec4(0.0);
vec4 s = vec4(0.0);

vec4 a_temp = vec4(0.0);
vec4 d_temp = vec4(0.0);
vec4 s_temp = vec4(0.0);

for(int i = 0; i < numLights; i++){

    a_temp = material.ambientColor * lights[i].ambientColor * material.ambientCoefficient * lights[i].ambientIntensity;
    
    vec3 norm = normalize(vNorm);
    vec3 lightDist = vec3(lights[i].lightPos - FragPos);
    vec3 lightDir = normalize(lightDist);

    float diff =    lights[i].diffuseIntensity * 
                    material.diffuseCoefficient *
                    max(0,dot(norm,lightDir));

    d_temp = diff * 
        material.diffuseColor * 
        lights[i].diffuseColor;
   

    vec3 reflection = reflect(-lightDir, norm);
    vec3 viewDir = normalize(vViewPos - FragPos);

    float spec = (
    pow(max(0,dot(reflection,viewDir)), 
    material.specularShininess));



    s_temp = spec * 
        lights[i].specularColor * 
        material.specularColor * 
        material.specularCoefficient * 
        lights[i].specularIntensity;
   

    float attenuationFactor =   1.0 / 
                    (lights[i].constant + 
                    lights[i].linear * length(lightDist) + 
                    lights[i].quadratic * pow(length(lightDist),2));

        d_temp *= attenuationFactor;
        s_temp *= attenuationFactor;

        a += a_temp;
        d += d_temp;
        s += s_temp;
    }

    

    vec4 ad = a + d;
    vec4 ds = d + s;
    vec4 as = a + s;
    vec4 ads = a + d + s;

    FragColor = ads;
} 