#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D tex;
uniform sampler2D tex2;

void main() {
  vec4 color1 = texture(tex, texCoord);
  vec4 color2 = texture(tex2, texCoord);

  fragColor = color2.a != 1.0 ? color1 : color2;
}