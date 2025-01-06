#version 330 core
out vec4 FragColor;
in float vTime;
in vec3 vCol;
in vec3 vNorm;
in vec3 FragPos;
in vec3 vViewPos;

vec3 m_LightPos = vec3(-4,5,0);
float m_LightIntensity = 0.5;

vec3 m_Ambient = vec3(0,1,0);
float m_AmbientIntensity = 0.4f;

vec3 m_Diffuse = vec3(1,0.9f,0.6f);
float m_DiffuseReflectionCoefficient = 0.7f;

vec3 m_Specular = vec3(0,0,1);
float m_SpecularShininess = 256;
float m_SpecularReflectifity = 0.8f;


void main()
{
    vec3 col = vCol+vec3(sin(vTime));
    vec3 a = m_Ambient * m_AmbientIntensity;

    vec3 norm = normalize(vNorm);
    vec3 lightDir = normalize(vec3(m_LightPos - FragPos))   ;

    float diffuseIntensity = m_DiffuseReflectionCoefficient * m_LightIntensity * max(0,dot(norm,lightDir));
    vec3 d = diffuseIntensity * m_Diffuse;

    vec3 reflection = reflect(-lightDir, norm);
    vec3 viewDir = normalize(vViewPos - FragPos);

    float specularIntesity = (
    pow(max(0,dot(reflection,viewDir)), 
    m_SpecularShininess));

    vec3 s = specularIntesity * m_Specular * m_SpecularReflectifity;

    vec3 ad = a + d;
    vec3 ads = a + d + s;

    FragColor = vec4(ads.xyz, 1.0f);
} 