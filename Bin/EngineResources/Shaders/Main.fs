#version 400 core

in vec2 vUVs;

uniform vec4 uColor;
uniform sampler2D uColorTexture;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = uColor * texture2D(uColorTexture, vUVs);
}