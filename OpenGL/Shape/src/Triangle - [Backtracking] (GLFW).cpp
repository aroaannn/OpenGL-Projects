/* #include <iostream>
#include <sstream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <fstream>
#include <glad/glad.h>
#include <string>
#include <vector>

-- base.vs 

#version 330 core

layout (location = 0) in vec2 _v_data;

void main()
{
  gl_Position = vec4(_v_data,0.0f,1.0f);
}

-- base.fs 

#version 330 core

out vec4 FragColor;

void main()
{

  vec3 finalColor = vec3(0.74, 0.42, 0.74);

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

    std::string VertexShaderTemp = LoadShaderFile(VertexShadeFile);
    std::string FragShaderTemp = LoadShaderFile(FragShaderFile);

    const char *VertexShaderSource = VertexShaderTemp.c_str();
    const char *FragShaderSource = FragShaderTemp.c_str();

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

class Triangle {
  GLuint ShaderID;
  GLuint VertexArray;
  GLuint VertexBuffer;
  GLuint IndexBuffer;

private:
  std::vector<GLuint> IndexData;
  std::vector<float> VertexData;
  int cnt = 3;

public:
  void recursive(float x1, float y1, float x2, float y2, float x3, float y3,
                 int depth, std::vector<float> &VertexData,
                 std::vector<GLuint> &IndexData) {
    if (depth == 0) {
      return;
    }

    float midX1 = (x1 + x2) * 1.111f;
    float midY1 = (y1 + y2) * 1.111f;
    float midX2 = (x2 + x3) * 1.111f;
    float midY2 = (y2 + y3) * 1.111f;
    float midX3 = (x1 + x3) * 1.111f;
    float midY3 = (y1 + y3) * 1.111f;

    VertexData.insert(VertexData.end(), {midX1, midY1, midX2, midY2, midX3, midY3});


    recursive(x1, y1, midX1, midY1, midX3, midY3, depth - 1, VertexData, IndexData);
    recursive(midX1, midY1, x2, y2, midX2, midY2, depth - 1, VertexData, IndexData);
    recursive(midX3, midY3, midX2, midY2, x3, y3, depth - 1, VertexData, IndexData);
}

  Triangle(){

    VertexData = {
      -0.25,-0.15,
          0.0, -0.0,
        0.25, -0.15,
    };

    recursive(VertexData[0], VertexData[1], VertexData[2], VertexData[3],
              VertexData[4], VertexData[5], 2, VertexData, IndexData);

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, VertexData.size() * sizeof(float),
                 VertexData.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexData.size() * sizeof(GLuint),
                 IndexData.data(), GL_STATIC_DRAW); 

    glGenVertexArrays(1, &VertexArray);
    glBindVertexArray(VertexArray);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    HelpersFunction _func;

    ShaderID = _func.LoadShader("base.vs", "base.fs");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
      int _cnt = 2;
    for(auto a : VertexData)
    {
      std::cout << a << ' ';
        if(_cnt == 3)
      {
        std::cout << '\n';
        _cnt = 1;

      };
        _cnt += 1;

    };
    std::cout << "\nVertex Buffer END\n  \nIndex Buffer Start\n";
    for(auto a : IndexData)
      std::cout << a << ' ';

  };

  void render() {
    glUseProgram(ShaderID);
    glBindVertexArray(VertexArray);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer); 
    glDrawArrays(GL_TRIANGLES,0,VertexData.size() / 2);
  };
};

int main() {
  if (!glfwInit())
    return -1;

  GLFWwindow *window =
      glfwCreateWindow(1000, 1000, "[Triangle] - [Backtracking method]", NULL, NULL);

  glfwMakeContextCurrent(window);

  glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h){
    glViewport(0, 0, w, h);
  });

  if (!gladLoadGL())
    return -1;

  Triangle *triangle = new Triangle();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    triangle->render();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  delete triangle;
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
};
 */