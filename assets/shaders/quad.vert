#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 vUV;

uniform vec2 uPos;
uniform vec2 uSize;
uniform mat4 uProj;
uniform mat4 uView;
uniform vec4 uUV;

void main()
{
  vUV = vec2(
    mix(uUV.x, uUV.z, aUV.x), 
    mix(uUV.y, uUV.w, aUV.y)
  );

  vec2 worldPos = uPos + aPos.xy * uSize;
  gl_Position = uProj * uView * vec4(worldPos, aPos.z, 1.0);
}
