/* #include <cstdio>
#include <fstream>
#include <minwindef.h>
#include <sstream>
#include <string>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glad/glad.h>

-- base.vs

#version 330 core

layout (location = 0) in vec3 _v_data;

void main()
{
  gl_Position = vec4(_v_data,1.0f);
}

-- base.fs

#version 330 core

out vec4 FragColor;

uniform float time;

void main()
{
  float r = sin(time);
  float g = cos(time);
  float b = tan(time);

  vec3 finalColor = vec3(r,b,g);

  FragColor = vec4(finalColor,1.0f);
}

--


class HelpersFunction {
public:
  std::string LoadShaderFile(const std::string &data) {

    std::string full = "D:/GLFW/assets/" + data;
    std::ifstream _file(full);
    std::stringstream ss;

    ss << _file.rdbuf();

    return ss.str();
  };

  GLuint LoadShader(const char *VertexShadeFile, const char *FragShaderFile) {
    GLuint ShaderProgram;

    // Create Program

    ShaderProgram = glCreateProgram();

    // Do stuffs

    std::string VertexShaderTemp = LoadShaderFile("base.vs");
    std::string FragShaderTemp = LoadShaderFile("base.fs");

    const char *VertexShaderSource = VertexShaderTemp.c_str();
    const char *FragShaderSource = FragShaderTemp.c_str();

    printf("%s \n", FragShaderSource);

    auto CreateShader = [ShaderProgram](GLenum type, const char *src) -> void {
      GLuint Shader = glCreateShader(type);
      glShaderSource(Shader, 1, &src, NULL);
      glCompileShader(Shader);
      glAttachShader(ShaderProgram, Shader);
      glDeleteShader(Shader);
    };

    CreateShader(GL_VERTEX_SHADER, VertexShaderSource);
    CreateShader(GL_FRAGMENT_SHADER, FragShaderSource);

    glLinkProgram(ShaderProgram);

    return ShaderProgram;
  };
};

class Circle : public HelpersFunction {
  GLuint ShaderProgram;
  std::vector<float> VertexData;
  std::vector<GLuint> IndexData;

  struct Core {
    GLuint VertexBuffer;
    GLuint VertexArray;
    GLuint IndexBuffer;
    GLuint ShaderProgram;
  };

  Core core;

public:
  Circle(float centerX, float centerY, float radius, int points) {

    for (int i = 0; i <= points; i += 1) {
      float theta = 4 * M_PI * radius * float(i) / points;
      float px = radius * cos(theta);
      float py = radius * sin(theta);

      VertexData.push_back(px + centerX);
      VertexData.push_back(py + centerY);
      VertexData.push_back(0.0f);

      if (i > 0)
        IndexData.push_back(i);
    };

    GLuint VertexBuffer;
    GLuint IndexBuffer;
    GLuint ShaderProgram;
    GLuint VertexArray;

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, VertexData.size() * sizeof(float),
                 VertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexData.size() * sizeof(GLuint),
                 IndexData.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    ShaderProgram = this->LoadShader("base.vs", "base.fs");

    core.ShaderProgram = ShaderProgram;
    core.VertexArray = VertexArray;
    core.IndexBuffer = IndexBuffer;
    core.VertexBuffer = VertexBuffer;
    // Debug...
    printf("ShaderProgram - VertexArray - IndexBuffer - VertexBuffer (%d - %d "
           "- %d - %d)",
           ShaderProgram, VertexArray, IndexBuffer, VertexBuffer);
  };

  void Update() {
    glUseProgram(core.ShaderProgram);

    glUniform1f(glGetUniformLocation(core.ShaderProgram, "time"),
                glfwGetTime());

    glBindVertexArray(core.VertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, core.IndexBuffer);
    glDrawElements(GL_TRIANGLE_FAN, IndexData.size(), GL_UNSIGNED_INT, NULL);
  };
};

int main() {
  if (!glfwInit()) {
    return -1;
  }

  GLFWwindow *window =
      glfwCreateWindow(1000, 1000, "[Circle] - [Animated]", NULL, NULL);

  glfwMakeContextCurrent(window);

  if (!gladLoadGL()) {
    return -1;
  }

  Circle *circle = new Circle(0, 0, 0.5, 36);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5, 1, 0.5, 1);

    circle->Update();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  delete circle;
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}; */