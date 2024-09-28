# version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emission;
  float shininess;
};

struct Light {
  vec3 position;
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
  vec3 lightDir = normalize(light.position - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

  // 镜面光（specular）
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

  // 放射光贴图（Emission Map）
  vec3 emission = vec3(0.1) * vec3(texture(material.emission, TexCoords));

  vec3 result = ambient + diffuse + specular + emission;
  FragColor = vec4(result, 1.0);
}
