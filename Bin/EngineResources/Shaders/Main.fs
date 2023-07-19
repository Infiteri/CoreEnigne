#version 400 core

uniform vec4 uColor;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = uColor;
}