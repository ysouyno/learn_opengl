#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void process_input(GLFWwindow *window);

// settings
const unsigned int SCR_W = 600;
const unsigned int SCR_H = 400;

int main() {
  // glfw: initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  GLFWwindow *window = glfwCreateWindow(SCR_W, SCR_H, "t_gl", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  Shader our_shader("coordinate_systems.vs", "coordinate_systems.fs");
  glEnable(GL_DEPTH_TEST);

  float vertices[] = {
      // positions         // texture coords
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
      0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, // top left
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bottom left
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, // bottom right
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, // top left
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bottom left

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, // bottom right
      -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, // top right
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, // bottom right

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom right
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, // top left
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, // top left
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, // bottom left
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom right

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left
      0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, // top right
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, // bottom right
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bottom left
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, // top left
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom right
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom right
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, // bottom left
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f  // top left
  };

  glm::vec3 cube_positions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int texture1, texture2;

  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int w, h, ch;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("container.jpg", &w, &h, &ch, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture\n";
  }
  stbi_image_free(data);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  data = stbi_load("awesomeface.png", &w, &h, &ch, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture\n";
  }
  stbi_image_free(data);

  our_shader.use();
  our_shader.set_int("texture1", 0);
  our_shader.set_int("texture2", 1);

  // render loop
  while (!glfwWindowShouldClose(window)) {
    // input
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    our_shader.use();

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f),
                                  (float)SCR_W / (float)SCR_H, 1.0f, 100.0f);

    our_shader.set_mat4("projection", projection);
    our_shader.set_mat4("view", view);

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; ++i) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cube_positions[i]);
      float angle = 20.0f * (i + 1);
      model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle),
                          glm::vec3(1.0f, 0.3f, 0.5f));
      our_shader.set_mat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}