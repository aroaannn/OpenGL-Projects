 #include <sstream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <string>

#include <fstream>


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

    ShaderProgram = glCreateProgram();

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

class Star {
private:
  GLuint ShaderID;
  GLuint VertexArray;
  GLuint VertexBuffer;
  GLuint IndexBuffer;

private:
  std::vector<float> VertexData;
  std::vector<GLuint> IndexData;

public:
  Star() {

    VertexData = {
        -0.2,   0.2, // Vertex 0: Left up
        0.0,    0.4, // Vertex 1: Up up
        0.2,    0.2, // Vertex 2: Right up

        0.4,    0.2, // Vertex 3: Up right
        0.25,   0.0, // Vertex 4: Right right

        0.275,  -0.2,  // Vertex 5: Down left
        0.0,    -0.15, // Vertex 6: Down down

        -0.275, -0.2, // Vertex 7: Down right

        -0.25,  0.0, // Vertex 8: Left left

        -0.4,   0.2 // Vertex 9: Left right
    };

    IndexData = {0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 0,

                 // Coloring....

                 0, 2, 4, 4, 6, 8, 4, 6, 0, 8, 10, 0};

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, VertexData.size() * sizeof(float),
                 VertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexData.size() * sizeof(GLuint),
                 IndexData.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &VertexArray); // Gen vertex array
    glBindVertexArray(VertexArray);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    HelpersFunction _func;

    ShaderID = _func.LoadShader("base.vs", "base.fs");

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  };

  void render() {
    glUseProgram(ShaderID);
    glBindVertexArray(VertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glDrawElements(GL_TRIANGLES, IndexData.size(), GL_UNSIGNED_INT, NULL);
  };
};

int main() {
  if (!glfwInit())
    return -1;

  GLFWwindow *window = glfwCreateWindow(1000, 1000, "[Star]", nullptr, nullptr);

  glfwMakeContextCurrent(window);

  glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h){
    glViewport(0,0,w,h);
  });

  if (!gladLoadGL())
    return -1;

  Star *star = new Star();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    star->render();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  delete star;
  glfwDestroyWindow(window);
  glfwTerminate();
}; 