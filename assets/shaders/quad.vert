#version 410 core

layout(location=0) in vec2 aPos;
layout(location=1) in vec2 aUV;

layout(location=2) in vec2 iOffset;
layout(location=3) in vec2 iSize;
layout(location=4) in vec4 iColor;

uniform mat4 uProj;
uniform mat4 uView;

out vec2 vUV;
out vec4 vColor;

void main()
{
  vec2 world = iOffset + aPos * iSize;
  gl_Position = uProj * uView * vec4(world, 0.0, 1.0);

  vUV = aUV;
  vColor = iColor;
}
