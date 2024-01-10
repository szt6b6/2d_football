#include "Game.h"

void Game::Init()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->m_width), 
                                    0.0f, static_cast<GLfloat>(this->m_height), -1.0f, 1.0f);
                                
    // load playground
    ResourceManager::LoadTexture("resources/textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadShader("src/shaders/playground.vs", "src/shaders/playground.fs", nullptr, "playground");
    ResourceManager::GetShader("playground").Use().SetMatrix4("projection", projection);
    this->m_playground = new Playground(ResourceManager::GetShader("playground"), 
                                        ResourceManager::GetTexture("background"),
                                        glm::vec2(this->m_width * 0.05, this->m_height * 0.05), 
                                        glm::vec2(this->m_width * 0.9, this->m_height * 0.9), 
                                        0.1f, glm::vec3(0.5f, 0.5f, 0.5f));

    // load ball
    ResourceManager::LoadShader("src/shaders/ball.vs", "src/shaders/ball.fs", nullptr, "ball");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", GL_TRUE, "ball");
    ResourceManager::GetShader("ball").Use().SetMatrix4("projection", projection);
    this->m_ball = new Ball(ResourceManager::GetShader("ball"),
                            ResourceManager::GetTexture("ball"),
                            glm::vec2(this->m_width * 0.5, this->m_height * 0.5), 
                            glm::vec2(10.0f, 10.0f), 
                            glm::vec2(10.0f, 10.0f), 
                            glm::vec3(0.0f, 1.0f, 0.0f));
    this->m_ball->set_rotation_v(45.0f);

    // load player
    glm::vec2 player_size = glm::vec2(20.0f, 20.0f);
    for(int i=0; i<5; i++) {
        std::string shader_name = "blue_player_" + std::to_string(i);
        ResourceManager::LoadShader("src/shaders/player.vs", "src/shaders/player.fs", nullptr, shader_name);
        ResourceManager::GetShader(shader_name).Use().SetMatrix4("projection", projection);
        Player* player = new Player(ResourceManager::GetShader(shader_name),
                                    ResourceManager::GetTexture("ball"),
                                    glm::vec2(rand() % this->m_width, rand() %this->m_height), 
                                    player_size, 
                                    glm::vec2(rand() % 40, rand() % 40), 
                                    glm::vec3(0.0f, 0.0f, 1.0f));
        // player->set_state(AI_PLAYER); // default ai player
        this->m_players_blue.push_back(player);
    }
    for(int i=0; i<5; i++) {
        std::string shader_name = "red_player_" + std::to_string(i);
        ResourceManager::LoadShader("src/shaders/player.vs", "src/shaders/player.fs", nullptr, shader_name);
        ResourceManager::GetShader(shader_name).Use().SetMatrix4("projection", projection);
        Player* player = new Player(ResourceManager::GetShader(shader_name),
                                    ResourceManager::GetTexture("ball"),
                                    glm::vec2(rand() % this->m_width, rand() %this->m_height), 
                                    player_size, 
                                    glm::vec2(rand() % 40, rand() % 40), 
                                    glm::vec3(1.0f, 0.0f, 0.0f));
        this->m_players_red.push_back(player);
    }
}

void Game::Update(GLfloat dt)
{
    this->m_ball->update(dt, this->m_width, this->m_height);
    for(auto player : this->m_players_blue) {
        player->update(dt, this->m_width, this->m_height);
    }
    for(auto player : this->m_players_red) {
        player->update(dt, this->m_width, this->m_height);
    }
}

void Game::Render()
{
    glDisable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

    // make sure we clear the framebuffer's content
    glEnable(GL_BLEND);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->m_playground->render();
    this->m_ball->render();
    for(auto player : this->m_players_blue) {
        player->render();
    }
    for(auto player : this->m_players_red) {
        player->render();
    }
}
