#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

#include "Properties.h"
#include "Playground.h"
#include "utils/ResourceManager.h"
#include "Game.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mode);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);


Game* game = new Game(PLAYGROUND_WIDTH, PLAYGROUND_HEIGHT);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2d_football", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 初始化 GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        return -1;
    }
    game->Init();

    // 设置键盘回调函数
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_click_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    
    // render loop
    // -----------
    GLfloat lastFrame = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        // input
        // -----
        game->ProcessInput(currentFrame - lastFrame);
        
        // logic
        game->Update(currentFrame - lastFrame);
        lastFrame = currentFrame;

        // draw
        game->Render();
        
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{   

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS) // if pressed all the time, run all the time
        {
            game->Keys[key] = GL_TRUE;
        }
        else if(action == GLFW_RELEASE)
        {
            game->Keys[key] = GL_FALSE;
            game->Keys_hold[key] = GL_FALSE; // hold state reset
        }
    }
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mode) {
    // if release, change turn
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        game->set_mouseClickTime();
        game->Mouse_hold = GL_TRUE;
    }
    // if hold, inc hold frames, max 100, symbol of shot power
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        game->set_mouseReleaseTime();
        game->Mouse_hold = GL_FALSE;
        game->MouseRelease();
    }
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
    // get mouse position according to window size
    xpos = xpos / WINDOW_WIDTH * game->m_width;
    ypos = WINDOW_HEIGHT - ypos; // left bottom is (0, 0), need to convert
    ypos = ypos / WINDOW_HEIGHT * game->m_height;
    
    game->SetMousePosition(xpos, ypos);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}