#version 400 core

in vec2 vUVs;

uniform sampler2D uColorTexture;

uniform vec4 uColor;

layout(location = 0) out vec4 outColor;
layout(location = 1) out int outID;

void main() {
    outColor = uColor * texture2D(uColorTexture, vUVs);

    outID = 42069;
}