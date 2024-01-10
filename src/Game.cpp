#include "Game.h"

void Game::Init()
{
    // load shader
    ResourceManager::LoadShader("src/shaders/playground.vs", "src/shaders/playground.fs", nullptr, "playground");glCheckError();
    // // configure shader
    // glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
    // ResourceManager::GetShader("playground").Use().SetInteger("image", 0);
    // ResourceManager::GetShader("playground").SetMatrix4("projection", projection);
    // // load texture
    // ResourceManager::LoadTexture("src/textures/playground.png", GL_FALSE, "playground");
    // set render-specific controls
    // configure global opengl state
    // initialize game objects
    this->playground = new Playground(ResourceManager::GetShader("playground"));glCheckError();
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
    glDisable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

    // make sure we clear the framebuffer's content
    glEnable(GL_BLEND);
    glClearColor(0.8f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->playground->render();
}
