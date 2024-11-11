#include <iostream>
#include <string>
#include "./window/Window.h"
#include "./renderer/Renderer.h"
#include "./model/Model.h"
#include "./shader/Shader.h"
#include "./texture/Texture.h"
#include "./vendor/glm/glm.hpp"
#include "./vendor/glm/gtc/matrix_transform.hpp"
#include "./vendor/glm/gtc/type_ptr.hpp"
#include "./vendor/glm/glm.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Orthographic projection
glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -7.0f, 7.0f, 0.1f, 100.0f);
glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));

// glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
// glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

glm::vec3 positions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(3.0f, 2.0f, -12.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f)
    };

int main()
{
    Window window("Vjezba4", SCR_WIDTH, SCR_HEIGHT);

     glEnable(GL_DEPTH_TEST);

    Model model("res/models/rectangle.obj");
    Shader shader("res/shaders/vShader.glsl", "res/shaders/fShader.glsl");
    Texture tex("res/textures/Logo_audi.jpg");

    Renderer render;

    glm::vec3 color(1.0f, 1.0f, 1.0f);

    while (!window.isClosed())
    {
        window.ProcessInput();
        render.Clear();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        shader.SetUniformVec3("color", color);
        shader.SetUniform4x4("projection", projection);
        shader.SetUniform4x4("view", view);

        for (unsigned int i = 0; i < 3; i++)
        {
            glm::mat4 Model = glm::mat4(1.0f);
            Model = glm::translate(Model, positions[i]);
            float angle = 90.0f * i;
            Model = glm::rotate(Model, glm::radians(angle), glm::vec3(0.5f, 0.5f, 0.5f));
            shader.SetUniform4x4("model", Model);
            
            model.Draw(shader, tex);
        }


        window.SwapAndPoll();
    }

    window.CloseWindow();

    return 0;
}