# version 330 core

out vec4 FragColor;

in VS_OUT {
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
} fs_in;

struct Light {
  vec3 Position;
  vec3 Color;
};

uniform Light lights[16];
uniform sampler2D diffuseTexture;
uniform vec3 viewPos;

void main() {
  vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
  FragColor = vec4(color, 1.0);
}
