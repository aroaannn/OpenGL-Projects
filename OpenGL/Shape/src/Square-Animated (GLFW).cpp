/*
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

-- base.vs 

#version 330 core

layout (location = 0) in vec3 _v_data;
layout (location = 1) in vec3 _v_color;

out vec3 _r_color;
out vec2 _fragPos;
void main()
{
  gl_Position = vec4(_v_data,1.0f);
  _r_color = _v_color;
  _fragPos = _v_data.xy;
}

-- base.fs 

#version 330 core

out vec4 FragColor;

in vec2 _fragPos;
in vec3 _r_color;

uniform float time;
void main()
{
  float r = abs(sin(_fragPos.x * 10.0 + time));
  float g = abs(sin(_fragPos.y * 10.0 + time));
  float b = abs(sin(_fragPos.x * 10.0 + time));

  vec3 dynamicColor = vec3(r, g, b);

  vec3 finalColor = mix(_r_color, dynamicColor, 0.5);
  FragColor = vec4(finalColor,1.0f);
}

--



class HelpersFunctions {
public:
  std::string LoadShaderFile(const std::string &data) {
    std::ifstream value("D:\\GLFW\\assets\\" + data);
    std::stringstream ss;
    ss << value.rdbuf();
    return ss.str();
  };

  void LoadShader(GLuint &ShaderID, const char *VertexShaderFile,
                  const char *FragShaderFile) {
    ShaderID = glCreateProgram();
    const char *VertexShaderSource = 0;
    const char *FragShaderSource = 0;

    std::string vertexShaderSourceStr = this->LoadShaderFile(VertexShaderFile);
    std::string fragShaderSourceStr = this->LoadShaderFile(FragShaderFile);

    VertexShaderSource = vertexShaderSourceStr.c_str();
    FragShaderSource = fragShaderSourceStr.c_str();

    printf("%s \n | %s \n", VertexShaderSource, FragShaderSource);

    {
      GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
      glCompileShader(VertexShader);
      glAttachShader(ShaderID, VertexShader);
      glDeleteShader(VertexShader);
      // Work fine
    };

    {
      GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(FragShader, 1, &FragShaderSource, NULL);
      glCompileShader(FragShader);
      glAttachShader(ShaderID, FragShader);
      glDeleteShader(FragShader);
    };

    glLinkProgram(ShaderID);
  };
};

class Square : public HelpersFunctions {
  GLuint VertexArray;
  GLuint VertexBuffer;
  GLuint ShaderID;
  GLuint IndexBuffer;

  float time = 0;

public:
  Square() {
    float vertexData[] = {-0.25, 0.25, 0.0,  0.1,  0.6,  0.8,   -0.25, -0.25,
                          0.0,   0.9,  0.1,  0.5,  0.25, -0.25, 0.0,   0.3,
                          0.9,   0.3,  0.25, 0.25, 0.0,  0.9,   0.8,   0.1};

    GLuint indexData[] = {0, 1, 2, 3, 0, 2};

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
                 GL_STATIC_DRAW);

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData,
                 GL_STATIC_DRAW);

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)12);
    glEnableVertexAttribArray(1);

    this->LoadShader(ShaderID, "base.vs", "base.fs");
  };

  void Render() {
    glUseProgram(ShaderID);
    glUniform1f(glGetUniformLocation(ShaderID, "time"), glfwGetTime());
    glBindVertexArray(VertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  };
};

int main() {
  if (!glfwInit()) {
    return -1;
  }

  GLFWwindow *s_window = glfwCreateWindow(1280, 600, "[Square]", NULL, NULL);

  glfwMakeContextCurrent(s_window);

  glfwSetWindowSizeCallback(s_window, [](GLFWwindow* window, int w, int h){
    glViewport(0, 0, w, h);
  });

  if (!gladLoadGL()) {
    return -1;
  };

  Square *square = new Square();

  while (!glfwWindowShouldClose(s_window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 0.5, 1);

    square->Render();

    glfwSwapBuffers(s_window);
    glfwPollEvents();
  };

  delete square;
  glfwDestroyWindow(s_window);
  glfwTerminate();
  return 0;
};
*/