# version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light {
  // vec3 position; // 使用定向光（Directional Light）就不需要它了
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
in vec2 TexCoords;

void main()
{
  // 环境光（amibent）
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

  // 漫反射（diffuse）
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

  // 镜面光（specular）
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0);
}
