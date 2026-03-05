#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec2 iOffset;

uniform vec2 uSize;
uniform mat4 uProj;
uniform mat4 uView;

out vec2 vUV;

void main()
{
  vec2 world = iOffset + aPos * uSize;
  gl_Position = uProj * uView * vec4(world, 0.0, 1.0);
  vUV = aUV;
}
