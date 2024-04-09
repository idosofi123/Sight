#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

out vec3 v_Position;

void main() {
    v_Position = vec3(position);
    gl_Position = (u_MVP * position).xyww;
}