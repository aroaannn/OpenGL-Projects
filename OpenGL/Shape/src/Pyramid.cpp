/* #include <cstddef>
#include <cstdio>
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <sstream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>

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

void main()
{

  vec3 finalColor = vec3(0.34, 0.26, 0.21);

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

class Pyramid   
{
    GLuint ShaderId;
    GLuint VertexBuffer;
    GLuint VertexArray;
    GLuint IndexBuffer;

    private:

    std::vector<GLuint> IndexData;
    std::vector<float> VertexData;

    public:
    Pyramid()
    {

        VertexData = {
            -0.25,0.0,-0.25, // Left side
            0.0,0.5,0.0,    // Top center
            0.0,-0.0,0.25,     // Down center
            0.25,0.0 ,-0.25, // Right side
        };

        IndexData = {
            1,0,2, // left triangle
            1,3,2, // right triangle 
            3,1,0, // behind triangle 
            0,2,3, // down triangle
        };
        glGenBuffers(1,&VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER,VertexData.size() * sizeof(float), VertexData.data(), GL_STATIC_DRAW);

        glGenBuffers(1,&IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexData.size() * sizeof(GLuint), IndexData.data(), GL_STATIC_DRAW);

        glGenVertexArrays(1,&VertexArray);
        glBindVertexArray(VertexArray);
        
        glVertexAttribPointer(0,3,GL_FLOAT,false,3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);

        HelpersFunction _func;
       ShaderId =  _func.LoadShader("base.vs", "base.fs");

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    };

    glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

    float rotation = 0;
    float speed = 0.05f;
    void render()
    {
        glUseProgram(ShaderId);

        if(rotation >= 360)
        {
            rotation = 0;
        }
        else  
        {
            rotation += speed;
        };

        ProjectionMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(1));

        glUniformMatrix4fv(glGetUniformLocation(ShaderId,"Projection"),1,false,glm::value_ptr(ProjectionMatrix));

        glBindVertexArray(VertexArray);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IndexBuffer);
        glDrawElements(GL_TRIANGLES, IndexData.size(), GL_UNSIGNED_INT, NULL);
    };
};


int main()
{
    if(!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "[Pyramid]", NULL, NULL);
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window,[](GLFWwindow* window, int w, int h){
        glViewport(0,0,w,h);
    });


    if(!gladLoadGL())
        return -1;

    Pyramid* pyramid = new Pyramid();

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1, 0.25, 1, 1);

        pyramid->render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    };

    delete pyramid;

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
};

 */