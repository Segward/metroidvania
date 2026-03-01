#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 vUV;

uniform mat4 uModel;
uniform mat4 uProj;
uniform vec4 uFrameUV;

void main()
{
  vUV = vec2(mix(uFrameUV.x, uFrameUV.z, aUV.x), mix(uFrameUV.y, uFrameUV.w, aUV.y));
  gl_Position = uProj * uModel * vec4(aPos, 1.0);
}
