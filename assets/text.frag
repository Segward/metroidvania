#version 330 core
in vec2 vUV;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec4 uColor;

void main()
{
  float a = texture(uTexture, vUV).r; // red channel is coverage
  FragColor = vec4(uColor.rgb, uColor.a * a);
}
