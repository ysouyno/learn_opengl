# version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  FragPos = vec3(model * vec4(aPos, 1.0));

  // 因为例子中没有对立方体进行不等比缩放，所以这里的法线矩阵（Normal Matrix）没有必要
  // Normal = mat3(transpose(inverse(model))) *aNormal;
  Normal = aNormal;

  gl_Position = projection * view * vec4(aPos, 1.0);
}
