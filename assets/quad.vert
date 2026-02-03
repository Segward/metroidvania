#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 vUV;

uniform vec3 uPos;
uniform vec2 uScale;

void main()
{
  vUV = aUV;
  vec2 p = aPos.xy * uScale + uPos.xy;
  gl_Position = vec4(p, uPos.z + aPos.z, 1.0);
}

