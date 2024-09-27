#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
  // amibent
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;

  // diffuse
  // 因为只关心方向向量的方向，所以这里先进行标准化，即 normalize
  // norm 是书中所说的法向量，垂直于立面体表面
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);

  // 将法向量和方向向量进行点乘，会得到它们之前夹角的余弦值
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * objectColor;
  FragColor = vec4(result, 1.0);
}
