#version 330 core

uniform sampler2D u_Texture;
uniform vec4 u_LightColor;
uniform vec3 u_LightPosition;

in vec2 v_TextureCoord;
in vec3 v_Normal;
in vec3 v_Position;

layout(location = 0) out vec4 color;

void main() {

    float ambientStrength = 0.2;

    vec3 toLightDirection = u_LightPosition - v_Position;
    float diffuse = max(dot(v_Normal, toLightDirection), 0);
    color = texture(u_Texture, v_TextureCoord) * ((diffuse + ambientStrength) * u_LightColor);
} 