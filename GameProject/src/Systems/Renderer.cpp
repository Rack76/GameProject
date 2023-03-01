#include "glew.h"
#include "WindowManager.h"
#include "glfw3.h"
#include "../Game.h"
#include "ComponentManager.h"
#include "Renderer.h"
#include "../ComponentTypes.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/gtc/matrix_access.hpp"

//temp
GLdouble vertices[] = {
    -1.0, -1.0, -1.5,
     1.0, -1.0, -1.5,
     1.0,  1.0, -1.5
};

Renderer::Renderer(Game* _game) {
    game = _game;
}

void Renderer::init()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	glViewport(0, 0, 800, 600);

    loadGraphicsComponents();
    createShaderPrograms();
}



void Renderer::update()
{
    glm::mat4 view = glm::mat4(1.0);
    glm::mat4 viewPerspective = glm::mat4(1.0);
    Camera* camera = nullptr;
    if (game->componentManager->getComponentCount(CAMERA))
    {
        camera = (Camera*)game->componentManager->getComponent(CAMERA);
        //glm::vec3 newColumn = -glm::column(camera->orientation, 2);
        //camera->orientation = glm::column(camera->orientation, 2, newColumn);
        camera->position += camera->velocity * 0.001f;
        view = glm::mat4(camera->orientation);
        glm::mat4 translationMat = glm::translate(glm::mat4(1.0), -camera->position);
        view = glm::transpose(view) * translationMat;
        viewPerspective = camera->perspective * view;
    }

    glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < game->componentManager->getComponentCount(GRAPHICS); i++)
	{
        Graphics* graphicsComponent = (Graphics*)game->componentManager->getComponent(GRAPHICS, i);
		glUseProgram(graphicsComponent->shaderID);
		glBindVertexArray(graphicsComponent->vaoID);
        GLuint location = glGetUniformLocation(graphicsComponent->shaderID, "worldViewPerspective");
        glUniformMatrix4fv(location, 1, GL_TRUE, &viewPerspective[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
    glfwSwapBuffers(game->windowManager->getWindow(0));
}


void Renderer::createShaderPrograms()
{
	for (int i = 0; i < game->componentManager->getComponentCount(GRAPHICS); i++)
	{
		Graphics* graphicsComponent = (Graphics*)game->componentManager->getComponent(GRAPHICS, i);
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

void Renderer::loadGraphicsComponents()
{
    for (int i = 0; i < game->componentManager->getComponentCount(GRAPHICS); i++)
    {
        loadGraphicsComponent(i);
    }
}

void Renderer::loadGraphicsComponent(int i)
{
    Graphics* graphicsComponent = (Graphics*)game->componentManager->getComponent(GRAPHICS, i);
    glGenVertexArrays(1, &graphicsComponent->vaoID);
    glBindVertexArray(graphicsComponent->vaoID);
    glGenBuffers(1, &graphicsComponent->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, graphicsComponent->vaoID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribLPointer(0, 3, GL_DOUBLE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::rotateCamera(GLFWwindow* window, double x, double y)
{
    x -= 400;
    y -= 300;
    static float xAngle = 0;
    static float yAngle = 0;
    xAngle += y;
    yAngle -= x;
    if (xAngle <= -450)
    {
        y = 0;
        xAngle = -450;
    }
    if (xAngle >= 450)
    {
        y = 0;
        xAngle = 450;
    }
    Camera* camera = (Camera*)game->componentManager->getComponent(CAMERA);
    glm::vec3 orientation = glm::vec3(sin(yAngle / 1000.0) * cos(xAngle / 1000.0), sin(xAngle / 1000.0), cos(xAngle / 1000.0) * cos(yAngle / 1000.0));
    glm::vec3 yAxis = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 localXAxis = glm::normalize(glm::cross(yAxis, orientation));
    glm::vec3 localYAxis = glm::normalize(glm::cross(orientation, localXAxis));
    camera->orientation[0] = localXAxis;
    camera->orientation[1] = localYAxis;
    camera->orientation[2] = orientation;
    glfwSetCursorPos(window, 400, 300);
}

void Renderer::translateCamera(GLFWwindow* window, int key, int action)
{
    Camera* camera = (Camera*)game->componentManager->getComponent(CAMERA);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->velocity = glm::normalize(glm::vec3(camera->orientation[2].x, 0, camera->orientation[2].z));
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->velocity = camera->orientation[0];
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->velocity = -camera->orientation[0];
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->velocity = -glm::normalize(glm::vec3(camera->orientation[2].x, 0, camera->orientation[2].z));
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->velocity = -glm::vec3(0.0, 1.0, 0.0);
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->velocity = glm::vec3(0.0, 1.0, 0.0);
    else
        camera->velocity = glm::vec3(0.0, 0.0, 0.0);
}