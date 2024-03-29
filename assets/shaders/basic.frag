#version 330 core

uniform sampler2D u_Texture;
uniform vec4 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

in vec2 v_TextureCoord;
in vec3 v_Normal;
in vec3 v_Position;

layout(location = 0) out vec4 color;

void main() {

    float ambientStrength = 0.2;
    float specularStrength = 0.5;
    float shininess = 32;

    vec3 toLightDirection = normalize(u_LightPosition - v_Position);
    float diffuse = max(dot(v_Normal, toLightDirection), 0);
    vec3 reflectionDirection = reflect(-toLightDirection, v_Normal);
    vec3 viewDirection = normalize(u_CameraPosition - v_Position);
    float specular = pow(max(dot(viewDirection, reflectionDirection), 0), shininess);

    color = texture(u_Texture, v_TextureCoord) * ((diffuse + ambientStrength + specularStrength * specular) * u_LightColor);
} 