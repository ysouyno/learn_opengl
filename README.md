# learn_opengl

教程链接：“[LearnOpenGL CN](https://learnopengl-cn.github.io/)”。

## `archlinux`环境配置

分别用到了`glfw`，`stb`，`glm`和`glad`，其中`glfw`和`stb`直接从`github`上克隆最新代码：

``` shellsession
$ git clone https://github.com/glfw/glfw.git
$ git clone https://github.com/nothings/stb.git
```

其中`glfw`需要编译一下才能使用，很简单：

``` shellsession
$ cd glfw
$ mkdir build
$ cd build
$ cmake ..
$ make
```

`glm`是按照教程中的建议，选择了低于`0.9.9`的版本，下载地址：“[GLM 0.9.8.5](https://github.com/g-truc/glm/releases/tag/0.9.8.5)”。

`glad`用的好像是教程中提供的在线服务链接生成的“[Glad](https://glad.dav1d.de)”，另项目中的`glad.c`是指向本机电脑中的一个软链接。

## 编译

编译及链接选项参考项目的`.vscode`中的文件。另因为使用`clang-format`格式化代码，头文件的顺序会影响编译，所以我在`~/.clang-format`中关闭了这项功能。

``` shellsession
$ cat ~/.clang-format
Language: Cpp
SortIncludes: false
```

## 其它

### “坐标系统”中代码说明

在“坐标系统”的“更多立方体”中提供的代码，文章中提到这十个立方体都能自主旋转，其实不然。我稍微修改了他的代码实现了，见：“[more cubes](https://github.com/ysouyno/learn_opengl/commit/b49247b5f9e1dd5e5b92809fe2235b948185767a)”，主要是这两处修改：

``` c++
float angle = 20.0f * (i + 1);
model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle),
                    glm::vec3(1.0f, 0.3f, 0.5f));
```

原代码中`angle = 20.0f * i`会导致最中间的那个立方体不旋转。