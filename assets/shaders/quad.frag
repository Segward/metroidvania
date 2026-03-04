#version 410 core

in vec2 vUV;

out vec4 FragColor;

uniform vec4 uColor;
uniform sampler2D uTex;

void main()
{
  vec4 texColor = texture(uTex, vUV);
  FragColor = texColor * uColor;
}
