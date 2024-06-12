/* #include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <sstream>
#include <vector>
#define GLFW_INCLUDE_NONE 
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <fstream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


-- base.vs 

#version 330 core

layout (location = 0) in vec3 _v_data;

uniform mat4 Projection;
void main()
{
  gl_Position = Projection * vec4(_v_data,1.0f);
}


-- base.fs 

#version 330 core

out vec4 FragColor;

uniform float time;
void main()
{
  float red = sin(time) * 0.5f + 0.5f;

  float green = sin(time + 2.0) * 0.5 + 0.5;

  float blue = sin(time + 4.0) * 0.5 + 0.5;

  vec3 finalColor = vec3(red, green, blue);

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


class Cube 
{
  GLuint ShaderID;
  GLuint VertexBuffer;
  GLuint VertexArray;
  GLuint IndexBuffer;
  private:

  std::vector<GLuint> IndexData;
  std::vector<float> VertexData;

  public:

  Cube()
  {

        VertexData = {
           -0.25,0.25,0.0,   // The left up front side
           0.25,0.25,0.0,   // The right up front side
           -0.25,0.0,0.0,  // The left down front side
           0.25,0.0,0.0, // the right down front side 


           0.25,0.25,-0.25, // The right up right side 
           0.25,0.0,-0.25, // The right down right side 

           -0.25,0.25,-0.25, // The left up left side 
           -0.25,0.0,-0.25, // The left down left side
        };

        IndexData = {
          0,1,2,2,3,1, // The front square 
          1,3,5,5,4,1, // The right square
          0,2,7,7,6,0, // The left square
          6,7,5,5,4,6, // The behind square
          0,6,1,1,4,6, // The top square
          2,7,5,5,3,2, // The down square
        };

        glGenBuffers(1,&VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,VertexData.size() * sizeof(float), VertexData.data(), GL_STATIC_DRAW);

        glGenBuffers(1,&IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,IndexData.size() * sizeof(GLuint), IndexData.data(), GL_STATIC_DRAW);

        glGenVertexArrays(1,&VertexArray);
        glBindVertexArray(VertexArray);

        glVertexAttribPointer(0,3,GL_FLOAT,false,3* sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        HelpersFunction _func;

        ShaderID = _func.LoadShader("base.vs", "base.fs");
        

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
  };

  float rotation = 0.0f;
  float speed = 0.5f;

  glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

  void render()
  {
    glUseProgram(ShaderID);


        if(rotation >= 360)
        {
            rotation = 0;
        }
        else  
        {
            rotation += speed * 0.1f;
        };

      ProjectionMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1.0f));

      glUniformMatrix4fv(glGetUniformLocation(ShaderID,"Projection"),1,false,glm::value_ptr(ProjectionMatrix));

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

  GLFWwindow* window = glfwCreateWindow(1000,1000,"[Cuboid] - [Animated]", NULL,NULL);


  glfwMakeContextCurrent(window);

  glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h){
    glViewport(0,0,w,h);
  });

  if(!gladLoadGL())
    return -1;

  Cube* cube = new Cube();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    cube->render();

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  delete cube;
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}; */