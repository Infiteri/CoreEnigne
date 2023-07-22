#version 400 core

in vec2 vUVs;

uniform sampler2D uST;
uniform sampler2D uColorTexture;

uniform vec4 uColor;

out vec4 outColor;

void main() {
    outColor = uColor * texture2D(uColorTexture, vUVs);
}