
/*
#define GLFW_INCLUDE_NONE
#include <fstream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <string>

-- triangle.vs 

#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 _temp;

out vec3 color;

void main(){
  gl_Position = vec4(vertex,1.0f);
  color = _temp;
}


---------------------------------

-- triangle.fs

#version 330 core 

out vec4 fragColor;
in vec3 color;

void main(){
    fragColor = vec4(color, 1.0f);
}


---------------------------------

class Shader  
{
  public:
  std::string LoadShaderFile(const std::string& file)
  {
    std::string filepath = "D:\\GLFW\\assets\\" + file;
    std::ifstream _file(filepath);
    
    std::stringstream ss;
    ss << _file.rdbuf();
    
    return ss.str();
  }

  void LoadShader(GLuint& ShaderID, const char* VertexShaderFile, const char* FragShaderFile)
  {
      ShaderID = glCreateProgram();

      {
          GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
          glShaderSource(VertexShader, 1, &VertexShaderFile, NULL);
          glCompileShader(VertexShader);
          glAttachShader(ShaderID, VertexShader);
      }

      {
          GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
          glShaderSource(FragShader, 1, &FragShaderFile, NULL);
          glCompileShader(FragShader);
          glAttachShader(ShaderID, FragShader);
      }

      glLinkProgram(ShaderID);
  }
};

class Triangle : public Shader
{
  GLuint VertexBuffer;
  GLuint VertexArray;
  GLuint ShaderID;
  public:
  Triangle()
  {
    float vertexData[] = {
      -0.5f, 0.0f, 0.0f, 0,0,1,
      0.0f, 0.5f, 0.0f, 0,1,0,
      0.5f, 0.0f, 0,  1,0,0
    };

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)12);
    glEnableVertexAttribArray(1);

    LoadShader(ShaderID, LoadShaderFile("triangle.vs").c_str(), LoadShaderFile("triangle.fs").c_str());
  }

  void Render()
  {
    glUseProgram(ShaderID);
    glBindVertexArray(VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }
};

int main()
{
  if (!glfwInit()) {
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(1000, 1000, "[Triangle]", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSetWindowSizeCallback(window,[](GLFWwindow*window,int w,int h){
    glViewport(0, 0, w, h);
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    return -1;
  }

  Triangle* triangle = new Triangle();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(1, 0.5f, 0.25f, 1.0f);

    triangle->Render();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
*/