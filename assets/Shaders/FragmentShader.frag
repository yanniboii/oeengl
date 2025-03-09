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

	float castsShadows;

    vec3 lightDirection;

    float shadowType;

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
    };

layout(std430, binding = 0) readonly buffer LightBuffer {
    Light[] lights;
};


uniform Material material;

uniform int numLights;



vec4 CalculateAmbient(vec4 l_AmbientColor, float l_AmbientIntensity){
    return material.ambientColor * l_AmbientColor * material.ambientCoefficient * l_AmbientIntensity;
}

float CalculateDiffuseTerm( vec3 normal,
                            vec3 _lightDir, 
                            float _diffuseIntensity){
    return  _diffuseIntensity * 
            material.diffuseCoefficient *
            max(0,dot(normal,_lightDir));
}

vec3 CalculateReflection(vec3 _lightDir, vec3 norm){
    return reflect(-_lightDir,norm);
}

vec4 PointLightDiffuse(int i, vec3 norm, vec3 lightDist, vec3 lightDir){

    vec4 d_temp = vec4(0.0);

    float diff = CalculateDiffuseTerm(  norm, 
                                        lightDir, 
                                        lights[i].diffuseIntensity);

    d_temp = diff * 
        material.diffuseColor * 
        lights[i].diffuseColor;   

    float attenuationFactor =   1.0 / 
                    (lights[i].constant + 
                    lights[i].linear * length(lightDist) + 
                    lights[i].quadratic * pow(length(lightDist),2));

        d_temp *= attenuationFactor;
        
    return  d_temp;
}

vec4 PointLightSpecular(int i, vec3 norm, vec3 lightDist, vec3 lightDir){

    vec4 s_temp = vec4(0.0);
    vec3 reflection = CalculateReflection(lightDir, norm);
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

        s_temp *= attenuationFactor;

    return s_temp;
}

vec4 DirectionalLightDiffuse(int i, vec3 norm){

    vec4 d_temp = vec4(0.0);

    float diff = CalculateDiffuseTerm(  norm, 
                                        -lights[i].lightDirection, 
                                        lights[i].diffuseIntensity);

    d_temp = diff * 
        material.diffuseColor * 
        lights[i].diffuseColor;   
        
    return  d_temp;
}

vec4 DirectionalLightSpecular(int i, vec3 norm){

    vec4 s_temp = vec4(0.0);
    vec3 reflection = CalculateReflection(-normalize(lights[i].lightDirection), norm);
    vec3 viewDir = normalize(vViewPos - FragPos);

    float spec = (
    pow(max(0,dot(reflection,viewDir)), 
    material.specularShininess));

    s_temp = spec * 
        lights[i].specularColor * 
        material.specularColor * 
        material.specularCoefficient * 
        lights[i].specularIntensity;

    return s_temp;
}

vec4 SpotLightDiffuse(int i, vec3 norm, vec3 lightDist, vec3 lightDir){

    vec4 d_temp = vec4(0.0);

    float diff = CalculateDiffuseTerm(  norm, 
                                        lightDir, 
                                        lights[i].diffuseIntensity);

    d_temp = diff * 
        material.diffuseColor * 
        lights[i].diffuseColor;   

    float attenuationFactor =   1.0 / 
                    (lights[i].constant + 
                    lights[i].linear * length(lightDist) + 
                    lights[i].quadratic * pow(length(lightDist),2));

        d_temp *= attenuationFactor;
        
    return  d_temp;
}

vec4 SpotLightSpecular(int i, vec3 norm, vec3 lightDist, vec3 lightDir){

    vec4 s_temp = vec4(0.0);
    vec3 reflection = CalculateReflection(lightDir, norm);
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

        s_temp *= attenuationFactor;

    return s_temp;
}

void main()
{
    vec4 a = vec4(0.0);
    vec4 d = vec4(0.0);
    vec4 s = vec4(0.0);

    for(int i = 0; i < numLights; i++)
    {
        vec4 a_temp = vec4(0.0);
        vec4 d_temp = vec4(0.0);
        vec4 s_temp = vec4(0.0);

        a_temp = CalculateAmbient(lights[i].ambientColor,lights[i].ambientIntensity);
        
        //Point Light
        if(lights[i].lightType == 0)
        {
            vec3 norm = normalize(vNorm);
            vec3 lightDist = vec3(lights[i].lightPos - FragPos);
            vec3 lightDir = normalize(lightDist);

            d_temp = PointLightDiffuse(i, norm, lightDist, lightDir);
            s_temp = PointLightSpecular(i, norm, lightDist, lightDir);
        }
        //Directional Light
        if(lights[i].lightType == 1)
        {
            vec3 norm = normalize(vNorm);

            d_temp = DirectionalLightDiffuse(i, norm);
            s_temp = DirectionalLightSpecular(i, norm);
        }
        //Spot Light
        if(lights[i].lightType == 2)
        {
            vec3 norm = normalize(vNorm);
            vec3 lightDist = vec3(lights[i].lightPos - FragPos);
            vec3 lightDir = normalize(lightDist);

            float theta = dot(lightDir, normalize(-lights[i].lightDirection));
            float epsilon = lights[i].innerCutoff - lights[i].outerCutoff;
            float spotIntensity = clamp((theta - lights[i].outerCutoff) / epsilon, 0.0, 1.0);

            d_temp = SpotLightDiffuse(i, norm, lightDist, lightDir);
            s_temp = SpotLightSpecular(i, norm, lightDist, lightDir);
            
            d_temp *= spotIntensity;
            s_temp *= spotIntensity;
        }

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