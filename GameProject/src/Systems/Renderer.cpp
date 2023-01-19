#include "glew.h"
#include "glfw3.h"
#include "../Game.h"
#include "Renderer.h"
#include "../ComponentTypes.h"
#include <fstream>
#include <sstream>
#include <iostream>

//temp
GLdouble vertices[] = {
    -1.0, -1.0, 0.0,
     1.0, -1.0, 0.0,
     1.0,  1.0, 0.0
};

Renderer::Renderer(Game* _game) {
    game = _game;
}

void GLAPIENTRY debugMessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam) {

    std::cout << message << std::endl;

}

void Renderer::init()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;


    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugMessageCallback, (const void*)0);

	glViewport(0, 0, 800, 600);

    genBuffers();
    createShaderPrograms();


}



void Renderer::update()
{
    glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < game->componentManager.getComponentCount(GRAPHICS); i++)
	{
		Graphics* graphicsComponent = game->componentManager.getComponent(GRAPHICS, i);
		glUseProgram(graphicsComponent->shaderID);
		glBindVertexArray(graphicsComponent->vaoID);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
    glfwSwapBuffers(game->windowManager.getWindow(0));
    glfwPollEvents();
}

void Renderer::deleteGraphicsComponent(int index)
{
    Graphics* graphicsComponent = game->componentManager.getComponent(GRAPHICS, index);
    glDeleteBuffers(1, &graphicsComponent->vboID);
    glDeleteVertexArrays(1, &graphicsComponent->vaoID);
}

void Renderer::createShaderPrograms()
{
	for (int i = 0; i < game->componentManager.getComponentCount(GRAPHICS); i++)
	{
		Graphics* graphicsComponent = game->componentManager.getComponent(GRAPHICS, i);
		const char* vertexPath = graphicsComponent->vertexPath;
		const char* fragmentPath = graphicsComponent->fragmentPath;

        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        //GLuint vertex, fragment;
        // vertex shader
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        graphicsComponent->shaderID = glCreateProgram();
        glAttachShader(graphicsComponent->shaderID, vertex);
        glAttachShader(graphicsComponent->shaderID, fragment);
        glLinkProgram(graphicsComponent->shaderID);
        checkCompileErrors(graphicsComponent->shaderID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        graphicsComponent = nullptr;
	}
}

void Renderer::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type == "PROGRAM")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

void Renderer::genBuffers()
{
    for (int i = 0; i < game->componentManager.getComponentCount(GRAPHICS); i++)
    {
        Graphics* graphicsComponent = game->componentManager.getComponent(GRAPHICS, i);
        glGenVertexArrays(1, &graphicsComponent->vaoID);
        glBindVertexArray(graphicsComponent->vaoID);
        glGenBuffers(1, &graphicsComponent->vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, graphicsComponent->vaoID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribLPointer(0, 3, GL_DOUBLE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        graphicsComponent = nullptr;
    }
}
