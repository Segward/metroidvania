#version 330 core

in vec2 vUV;

out vec4 FragColor;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main()
{
  vec4 texColor = texture(uTexture, vUV);
  FragColor = texColor * uColor;
}
