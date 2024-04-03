#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 textureCoord;
layout(location = 3) in uint textureIndex;

uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_ModelTi;

out vec2 v_TextureCoord;
out vec3 v_Normal;
out vec3 v_Position;
flat out uint v_TextureIndex;

void main() {
    gl_Position = u_MVP * position;
    v_TextureCoord = textureCoord;
    v_Normal = normalize(vec3(u_ModelTi * normal));
    v_Position = vec3(u_Model * position);
    v_TextureIndex = textureIndex;
}