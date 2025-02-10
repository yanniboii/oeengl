#version 330 core
out vec4 FragColor;
in float vTime;
in vec3 vCol;
in vec3 vNorm;
in vec3 FragPos;
in vec3 vViewPos;

uniform vec3 m_LightPos;
float m_LightIntensity = 0.5;

uniform vec3 m_Ambient;
float m_AmbientIntensity = 0.4f;

uniform vec3 m_Diffuse;
float m_DiffuseReflectionCoefficient = 0.7f;

vec3 m_Specular = vec3(0,0,1);
float m_SpecularShininess = 8;
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