#version 400 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUVs;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uTransform;

out vec2 vUVs;

void main() {
    gl_Position = uProjection * uView * uTransform * vec4(aPosition, 1.0);
    vUVs = aUVs;
}