#version 330 core

in vec2 texCoord;

out vec4 fragColor;

uniform mat4 transform;
uniform sampler2D tex;
uniform sampler2D tex2;

void main() {
  vec4 color1 = texture(tex, texCoord);
  vec4 color2 = texture(tex2, texCoord);

  vec4 result = color1 * (1.0 - color2.a) + color2 * color2.a;
  result.a = 1.0;

  fragColor = result;
}