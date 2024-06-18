/*
#include <fstream>
#include <sstream>
#include <string>
#define GLFW_INCLUDE_NONE 
#include <GLFW/glfw3.h>
#include <glad/glad.h>

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


void main()
{
  
  vec2 uv =  gl_FragCoord.xy / resolution * 2 - 1; 

  vec3 finalColor = vec3(0.0f);

  uv = fract(uv * 1.5) - 0.5;

  float d = length(uv) * exp(length(uv));

  d = pow(d,1.2);

  finalColor.xy += d;



 FragColor = vec4(finalColor, 1.0f);
}

------------------------------------

int W = 800;
int H = 800;
class HelperFucntions 
{
  public:
 std::string LoadShaderFile(const std::string& data){

    std::string value = "D:\\GLFW\\assets\\" + data;

    std::ifstream file(value);
    std::stringstream ss;

    ss << file.rdbuf();

    return ss.str();
  };

  int LoadShader(const char* VertexShaderName = "base.vs", const char* FragShaderName = "base.fs"){
    GLuint ShaderID = glCreateProgram();

    std::string VertexShaderTempSource = LoadShaderFile(VertexShaderName), FragShaderTempSource = LoadShaderFile(FragShaderName);

    const char* VertexShaderSource = VertexShaderTempSource.c_str(), *FragShaderSource = FragShaderTempSource.c_str();

    GLuint VertexShader,FragShader;

   auto CreateShader = [](GLenum Mode,const char* ModeShaderSource) ->GLuint {
      GLuint ModeShader = glCreateShader(Mode);

      glShaderSource(ModeShader,1,&ModeShaderSource,NULL);

      glCompileShader(ModeShader);

      return ModeShader;
    };

    VertexShader = CreateShader(GL_VERTEX_SHADER, VertexShaderSource);
    FragShader = CreateShader(GL_FRAGMENT_SHADER, FragShaderSource);

    glAttachShader(ShaderID,VertexShader);
    glAttachShader(ShaderID,FragShader);

    glDeleteShader(VertexShader);
    glDeleteShader(FragShader);

    glLinkProgram(ShaderID);

    return ShaderID;
  };
};

class Background 
{
  GLuint VertexArray;
  GLuint VertexBuffer;
  GLuint IndexBuffer;

  GLuint ShaderID;

  std::vector<float> VertexData;
  std::vector<GLuint> IndexData;
  public:

  Background()
  {

    VertexData = {
      -1,1,
      1,1,
      1,-1,
      -1,-1,
    };

    IndexData = {
      0,1,2,
      0,3,2
    };

    glGenBuffers(1,&VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,VertexData.size() * sizeof(float), VertexData.data(),GL_STATIC_DRAW);

    glGenBuffers(1,&IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexData.size() * sizeof(GLuint), IndexData.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1,&VertexArray);

    glBindVertexArray(VertexArray);

    glVertexAttribPointer(0,2,GL_FLOAT,false, 2 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    HelperFucntions _funcs;

   ShaderID = _funcs.LoadShader();

   
    glUseProgram(ShaderID);

    glUniform2f(glGetUniformLocation(ShaderID,"resolution"),W,H);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

  };

  void render()
  {
    glUseProgram(ShaderID);
    glUniform1f(glGetUniformLocation(ShaderID,"time"),glfwGetTime());
    glBindVertexArray(VertexArray);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IndexBuffer);
    glDrawElements(GL_TRIANGLES,IndexData.size(),GL_UNSIGNED_INT,0);
  };
};

int main()
{
  if(!glfwInit())
    return -1;

  GLFWwindow* window = glfwCreateWindow(W,H, "Fractal Circle ",NULL,NULL);


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
};
*/
