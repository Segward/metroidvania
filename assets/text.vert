#version 330 core
layout (location = 0) in vec4 aVertex; // x,y,u,v

out vec2 vUV;

uniform mat4 uProj;

void main()
{
  gl_Position = uProj * vec4(aVertex.xy, 0.0, 1.0);
  vUV = aVertex.zw;
}
