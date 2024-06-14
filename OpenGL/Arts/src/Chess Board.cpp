/* #define GLFW_INCLUDE_NONE 
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <sstream>
#include <string>
#include <fstream>


int WIDTH = 1000;
int HEIGHT = 1000;

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

uniform vec2 resolution; 

#define PI 3.14

float f(float t)
{
  float p0 = 0.5;
  float p1 = 0.25;
  float p2 = 0.1;
  return pow(1 - t,2)*p0 + 2*(1 - t)*t*p1+pow(t,2)*p2;
}

vec3 checkerboard(vec2 uv, float scale) {
    vec2 p = floor(uv * scale);
    float checker = mod(p.x - p.y, 2.0);
    return vec3(checker);
}

void main()
{
  
  vec2 uv =  gl_FragCoord.xy - resolution.xy / 2;

  
  vec3 final =checkerboard(uv,0.015);

  FragColor = vec4(final, 1.0f);
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

class Background 
{
  private:
  GLuint ShaderID;
  GLuint VertexBuffer;
  GLuint IndexBuffer;
  GLuint VertexArray;

  std::vector<float> VertexData;
  std::vector<GLuint> IndexData;
  public:

  Background()
  {

    VertexData = {
      -1,-1,
      -1,1,
      1,1,
      1,-1
    };

    IndexData = {
      0,1,2,
      0,3,2
    };
    glGenBuffers(1,&VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, VertexData.size() * sizeof(float), VertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1,&IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexData.size() * sizeof(GLuint), IndexData.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1,& VertexArray);
    glBindVertexArray(VertexArray);
    
    glVertexAttribPointer(0,2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    HelpersFunction _func;

   ShaderID =  _func.LoadShader("base.vs", "base.fs");

   glUseProgram(ShaderID);

   glUniform2f(glGetUniformLocation(ShaderID,"resolution"),WIDTH,HEIGHT);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  };

  void render()
  {
    glUseProgram(ShaderID);
    glBindVertexArray(VertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glDrawElements(GL_TRIANGLES,IndexData.size(), GL_UNSIGNED_INT,0);
  };
};

int main()
{
    if(!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1000,1000,"[ChessBoard]",NULL,NULL);

    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h){
      glViewport(0,0,w,h);
    });

    if(!gladLoadGL())
        return -1;

      Background* background = new Background();


    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        background->render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    };

    delete background;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}; */