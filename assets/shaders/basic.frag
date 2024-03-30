#version 330 core

uniform sampler2D u_Texture;
uniform sampler2D u_SpecularMap;
uniform vec4 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

uniform float u_innerConeCos;
uniform float u_outerConeCos;

uniform vec3 u_SpotLightDirection;

in vec2 v_TextureCoord;
in vec3 v_Normal;
in vec3 v_Position;

layout(location = 0) out vec4 color;

vec4 directionalLight(float fragmentShininess) {

    float ambientStrength = 0.2;
    float specularStrength = 2;
    float shininess = 16;

    vec3 toLightDirection = vec3(0.0, 1.0, 0.0);
    float diffuse = max(dot(v_Normal, toLightDirection), 0);
    vec3 reflectionDirection = reflect(-toLightDirection, v_Normal);
    vec3 viewDirection = normalize(u_CameraPosition - v_Position);
    float specular = pow(max(dot(viewDirection, reflectionDirection), 0), shininess);

    return (ambientStrength + diffuse + fragmentShininess * specularStrength * specular) * u_LightColor;
}

vec4 pointLight(float fragmentShininess) {

    float ambientStrength = 0.2;
    float specularStrength = 2;
    float shininess = 16;

    vec3 toLightVector = u_LightPosition - v_Position;
    float distance = length(toLightVector);
    float a = 0.05;
    float b = 0.05;
    float attenuation = 1 / (a * distance * distance + b * distance + 1.0);

    vec3 toLightDirection = normalize(toLightVector);
    float diffuse = max(dot(v_Normal, toLightDirection), 0);
    vec3 reflectionDirection = reflect(-toLightDirection, v_Normal);
    vec3 viewDirection = normalize(u_CameraPosition - v_Position);
    float specular = pow(max(dot(viewDirection, reflectionDirection), 0), shininess);

    return (ambientStrength + diffuse * attenuation + fragmentShininess * specularStrength * specular * attenuation) * u_LightColor;
}

vec4 pointLightNonAmb(float fragmentShininess) {

    float specularStrength = 2;
    float shininess = 16;

    vec3 toLightVector = u_LightPosition - v_Position;
    float distance = length(toLightVector);
    float a = 0.05;
    float b = 0.05;
    float attenuation = 1 / (a * distance * distance + b * distance + 1.0);

    vec3 toLightDirection = normalize(toLightVector);
    float diffuse = max(dot(v_Normal, toLightDirection), 0);
    vec3 reflectionDirection = reflect(-toLightDirection, v_Normal);
    vec3 viewDirection = normalize(u_CameraPosition - v_Position);
    float specular = pow(max(dot(viewDirection, reflectionDirection), 0), shininess);

    return (diffuse * attenuation + fragmentShininess * specularStrength * specular * attenuation) * u_LightColor;
}

vec4 spotLight(float fragmentShininess) {

    float ambientStrength = 0.2;
    vec3 lightToFragDirection = normalize(v_Position - u_LightPosition);
    float inten = clamp((dot(lightToFragDirection, u_SpotLightDirection) - u_outerConeCos) / (u_innerConeCos - u_outerConeCos), 0.0, 1.0);

    return (inten + ambientStrength) * pointLightNonAmb(fragmentShininess);
}

void main() {
    color = texture(u_Texture, v_TextureCoord) * spotLight(texture(u_SpecularMap, v_TextureCoord).r);
} 