# learn_opengl

教程链接：“[LearnOpenGL CN](https://learnopengl-cn.github.io/)”。

## `archlinux`环境配置

分别用到了`glfw`，`stb`，`glm`和`glad`，其中`glfw`和`stb`直接从`github`上克隆最新代码：

```
git clone https://github.com/glfw/glfw.git
git clone https://github.com/nothings/stb.git
```

`glm`是按照教程中的建议，选择了低于`0.9.9`的版本，下载地址：“[GLM 0.9.8.5](https://github.com/g-truc/glm/releases/tag/0.9.8.5)”。

`glad`用的好像是教程中提供的在线服务链接生成的“[Glad](https://glad.dav1d.de)”。

## 编译

编译及链接选项参考`.vscode`中的文件。