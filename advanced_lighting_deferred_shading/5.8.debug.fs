# version 330 core

out vec4 PosColor;
out vec4 NormalColor;
in vec2 TexCoords;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;

void main() {
  vec3 color = texture(positionTexture, TexCoords).rgb;
  PosColor = vec4(color, 1.0f);
  float highlight = texture(normalTexture, TexCoords).a;
  NormalColor = vec4(highlight, highlight, highlight, 1.0f);
}
