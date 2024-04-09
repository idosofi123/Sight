#version 330 core

uniform samplerCube u_Texture;
in vec3 v_Position;

layout(location = 0) out vec4 color;

void main() {
    color = texture(u_Texture, v_Position);
} 