#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 objectColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // Ambient light
    float ambiantStrength = 0.2f;
    vec3 ambiant = ambiantStrength * lightColor;

   // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm,lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular light
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = objectColor * (ambiant + diffuse + specular);

    FragColor = vec4(result, 1.0);
}
