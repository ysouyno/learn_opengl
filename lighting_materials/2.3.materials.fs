# version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material material;

void main()
{
  // 环境光（amibent）
  vec3 ambient = lightColor * material.ambient;

  // 漫反射（diffuse）
  // 因为只关心方向向量的方向，所以这里先进行标准化，即 normalize
  // norm 是书中所说的法向量，垂直于立方体表面
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  // 将法向量和方向向量进行点乘，会得到它们之前夹角的余弦值
  // 角度越大，余弦值越小
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = lightColor * (diff * material.diffuse);

  // 镜面光（specular）
  // FragPos 即光线入射点，viewDir 相当于光线入射方向
  vec3 viewDir = normalize(viewPos - FragPos);
  // reflectDir 即光线的反射方向
  vec3 reflectDir = reflect(-lightDir, norm);
  // 将观察向量和反射向量进行点乘，会得到它们之前夹角的余弦值
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = lightColor * (spec * material.specular);

  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0);
}
