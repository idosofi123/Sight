#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoord;

uniform mat4 u_MVP;

out vec2 v_TextureCoord;

void main() {
    gl_Position = position * u_MVP;
    v_TextureCoord = textureCoord;
}