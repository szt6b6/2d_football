#include "Game.h"

// player and ball boteh are circle, so we use circle collision detection
std::pair<GLboolean, glm::vec2> CheckCollision(Entity *a, Entity *b)
{
    glm::vec2 center_a = a->m_position + a->m_size / 2.0f;
    glm::vec2 center_b = b->m_position + b->m_size / 2.0f;
    GLfloat radius_a = a->m_size.x / 2.0f;
    GLfloat radius_b = b->m_size.x / 2.0f;
    GLfloat distance = glm::length(center_a - center_b);
    if(distance <= radius_a + radius_b) {
        return std::make_pair(GL_TRUE, glm::normalize(center_a - center_b) * (radius_a + radius_b - distance));
    } else {
        return std::make_pair(GL_FALSE, glm::vec2(0.0f, 0.0f));
    }
}

GLboolean CheckBallInRec(Entity* ball, Entity* rec) {
    glm::vec2 ball_left_top = ball->m_position + glm::vec2(0.0f, ball->m_size.y);
    glm::vec2 ball_right_bottom = ball->m_position + glm::vec2(ball->m_size.x, 0.0f);

    glm::vec2 rec_left_top = rec->m_position + glm::vec2(0.0f, rec->m_size.y);
    glm::vec2 rec_right_bottom = rec->m_position + glm::vec2(rec->m_size.x, 0.0f);

    return ball_left_top.x >= rec_left_top.x && ball_left_top.y <= rec_left_top.y 
            && ball_right_bottom.x <= rec_right_bottom.x && ball_right_bottom.y >= rec_right_bottom.y;
}

// from gpt
// correct velocities after collision
void correctVelocitiesAfterCollision(glm::vec2& velocity1, glm::vec2& velocity2,
                                      const glm::vec2& position1, const glm::vec2& position2,
                                      float mass1, float mass2) {
    // Calculate relative velocity
    glm::vec2 relativeVelocity = velocity1 - velocity2;

    // Calculate collision normal
    glm::vec2 collisionNormal = glm::normalize(position1 - position2);

    // Decompose relative velocity into normal and tangential components
    GLfloat normalVelocity = glm::dot(relativeVelocity, collisionNormal);

    // Recalculate velocities based on mass and momentum conservation
    velocity1 -= (2 * mass2) / (mass1 + mass2) * normalVelocity * collisionNormal;
    velocity2 += (2 * mass1) / (mass1 + mass2) * normalVelocity * collisionNormal;
}

void Game::Init()
{
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->m_width), 
                                    0.0f, static_cast<GLfloat>(this->m_height), -1.0f, 1.0f);
                                
    // load playground
    ResourceManager::LoadTexture("resources/textures/fooball_playground.jpeg", GL_TRUE, "background");
    ResourceManager::LoadShader("src/shaders/playground.vs", "src/shaders/playground.fs", nullptr, "playground");
    ResourceManager::GetShader("playground").Use().SetMatrix4("projection", projection);
    this->m_playground = new Playground(ResourceManager::GetShader("playground"), 
                                        ResourceManager::GetTexture("background"),
                                        glm::vec2(0, 0), // 暂时考虑简单门的场地
                                        glm::vec2(this->m_width, this->m_height), 
                                        0.1f, glm::vec3(0.5f, 0.5f, 0.5f));

    // load ball
    ResourceManager::LoadShader("src/shaders/ball.vs", "src/shaders/ball.fs", nullptr, "ball");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", GL_TRUE, "ball");
    ResourceManager::GetShader("ball").Use().SetMatrix4("projection", projection);
    this->m_ball = new Ball(ResourceManager::GetShader("ball"),
                            ResourceManager::GetTexture("ball"),
                            glm::vec2(this->m_width * 0.5 - BALL_RADIUS, this->m_height * 0.5 - BALL_RADIUS), // position
                            glm::vec2(BALL_RADIUS * 2, BALL_RADIUS * 2), // size
                            glm::vec2(0, 0), // velocity
                            glm::vec3(0.0f, 1.0f, 0.0f)); // color
    this->m_ball->set_rotation_v(0.0f);

    // load player
    for(int i=0; i<PLAYER_MAX_NUM; i++) {
        std::string shader_name = "blue_player_" + std::to_string(i);
        ResourceManager::LoadShader("src/shaders/player.vs", "src/shaders/player.fs", nullptr, shader_name);
        ResourceManager::GetShader(shader_name).Use().SetMatrix4("projection", projection);
        Player* player = new Player(ResourceManager::GetShader(shader_name),
                                    ResourceManager::GetTexture("ball"),
                                    BLUE_TIME_INIT_POSITION + BLUE_TEAM_POSITION_OFFSET[i], // according to different player, add diff offset
                                    PLAYER_SIZE, 
                                    glm::vec2(0, 0), 
                                    glm::vec3(0.0f, 0.0f, 1.0f));
        player->set_operation_state(BLUE_TEAM_OPERATION_STATE[i]);
        this->m_players_blue.push_back(player);
    }
    for(int i=0; i<PLAYER_MAX_NUM; i++) {
        std::string shader_name = "red_player_" + std::to_string(i);
        ResourceManager::LoadShader("src/shaders/player.vs", "src/shaders/player.fs", nullptr, shader_name);
        ResourceManager::GetShader(shader_name).Use().SetMatrix4("projection", projection);
        Player* player = new Player(ResourceManager::GetShader(shader_name),
                                    ResourceManager::GetTexture("ball"),
                                    RED_TIME_INIT_POSITION + RED_TEAM_POSITION_OFFSET[i],
                                    PLAYER_SIZE, 
                                    glm::vec2(0, 0), // velocity control by AI
                                    glm::vec3(1.0f, 0.0f, 0.0f));
        player->set_operation_state(RED_TEAM_OPERATION_STATE[i]);
        this->m_players_red.push_back(player);
    }
    // set human player
    this->m_player_human = this->m_players_blue[0];
    this->m_player_human->set_role(HUMAN_PLAYER);
    this->m_player_human->set_velocity(0.0f, 0.0f);
    this->m_player_human->set_color(glm::vec3(1.0f, 1.0f, 0.0f));

    // load gate
    ResourceManager::LoadShader("src/shaders/gate.vs", "src/shaders/gate.fs", nullptr, "gate_blue");
    ResourceManager::LoadShader("src/shaders/gate.vs", "src/shaders/gate.fs", nullptr, "gate_red");
    ResourceManager::LoadTexture("resources/textures/block.png", GL_TRUE, "gate");
    ResourceManager::GetShader("gate_blue").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("gate_red").Use().SetMatrix4("projection", projection);
    this->m_gate_blue = new Entity(ResourceManager::GetShader("gate_blue"),
                                    ResourceManager::GetTexture("gate"),
                                    glm::vec2(0.0f, this->m_height * 0.5 - this->m_height * GATE_SIZE_SCALE.y * 0.5), 
                                    glm::vec2(this->m_width * GATE_SIZE_SCALE.x, this->m_height * GATE_SIZE_SCALE.y), 
                                    glm::vec3(0.0f, 0.0f, 1.0f));
    this->m_gate_blue->init();
    this->m_gate_red = new Entity(ResourceManager::GetShader("gate_red"),
                                    ResourceManager::GetTexture("gate"),
                                    glm::vec2(this->m_width - this->m_width * GATE_SIZE_SCALE.x, this->m_height * 0.5 - this->m_height * GATE_SIZE_SCALE.y * 0.5),
                                    glm::vec2(this->m_width * GATE_SIZE_SCALE.x, this->m_height * GATE_SIZE_SCALE.y),
                                    glm::vec3(1.0f, 0.0f, 0.0f));
    this->m_gate_red->init();

    // load text render
    this->m_text_render = new TextRender(this->m_width, this->m_height);
    this->m_text_render->Load("resources/fonts/VonwaonBitmap-16px.ttf", FONT_SIZE);
}

void Game::Update(GLfloat dt)
{
    this->DoCollision();

    this->CheckBallInGate(); // check ball in gate and update score

    this->m_ball->update(dt, this->m_width, this->m_height, this->m_playground->m_friction_param * 100);
    glm::vec2 ball_center = this->m_ball->m_position + this->m_ball->m_size / 2.0f;
    glm::vec2 red_gate_center = this->m_gate_red->m_position + this->m_gate_red->m_size / 2.0f;
    glm::vec2 blue_gate_center = this->m_gate_blue->m_position + this->m_gate_blue->m_size / 2.0f;

    for(auto player : this->m_players_blue) {
        if(player->m_state == HUMAN_PLAYER) {
            player->update_by_controller(dt, this->m_width, this->m_height, ball_center, this->m_mouse_position); // human player position update
            continue;
        }
        player->update(dt, this->m_width, this->m_height, red_gate_center, blue_gate_center, ball_center);
    }
    for(auto player : this->m_players_red) {
        player->update(dt, this->m_width, this->m_height, blue_gate_center, red_gate_center, ball_center);
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
    this->m_gate_blue->render();
    this->m_gate_red->render();
    this->m_ball->render();

    // render score
    std::string score = std::to_string(this->m_score_blue) + ":" + std::to_string(this->m_score_red);;
    this->m_text_render->RenderText(score, this->m_width / 2 - FONT_SIZE, this->m_height - FONT_SIZE, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    
    if(this->m_state == GAME_WIN) {
        std::string win = this->m_score_blue > this->m_score_red ? "Blue Win!" : "Red Win!";
        this->m_text_render->RenderText(win, this->m_width / 2 - FONT_SIZE / 2 * win.size() / 2 , this->m_height / 2 + FONT_SIZE, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
    if(this->m_state == GAME_MENU || this->m_state == GAME_WIN) {
        std::string menu = "Press Enter to Start";
        this->m_text_render->RenderText(menu, this->m_width / 2 - FONT_SIZE * menu.size() / 4 , this->m_height / 2, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
    
    for(auto player : this->m_players_blue) {
        player->render();
    }
    for(auto player : this->m_players_red) {
        player->render();
    }
}

// human player update according to key event
void Game::ProcessInput(GLfloat dt)
{
    if((this->m_state == GAME_MENU || this->m_state == GAME_WIN) && this->Keys[GLFW_KEY_ENTER] && !this->Keys_hold[GLFW_KEY_ENTER]) {
        this->m_state = GAME_ACTIVE;
        this->Keys_hold[GLFW_KEY_ENTER] = GL_TRUE;
        this->Reset();
    }
}

// after win and restart game
void Game::Reset()
{
    this->m_score_blue = 0;
    this->m_score_red = 0;
    this->m_ball->m_position = glm::vec2(this->m_width * 0.5 - this->m_ball->m_radius, this->m_height * 0.5 - this->m_ball->m_radius);
    this->m_ball->m_velocity = glm::vec2(0.0f, 0.0f);

    for(int i=0; i<PLAYER_MAX_NUM; i++) {
        this->m_players_blue[i]->m_position = BLUE_TIME_INIT_POSITION + BLUE_TEAM_POSITION_OFFSET[i];
        this->m_players_blue[i]->m_velocity = glm::vec2(0.0f, 0.0f);
        this->m_players_blue[i]->m_operation_state = BLUE_TEAM_OPERATION_STATE[i];
        this->m_players_blue[i]->kick_time_step = KICK_WAIT_TIME;

        this->m_players_red[i]->m_position = RED_TIME_INIT_POSITION + RED_TEAM_POSITION_OFFSET[i];
        this->m_players_red[i]->m_velocity = glm::vec2(0.0f, 0.0f);
        this->m_players_red[i]->m_operation_state = RED_TEAM_OPERATION_STATE[i];
        this->m_players_red[i]->kick_time_step = KICK_WAIT_TIME;
    }
}

void Game::CheckBallInGate()
{
    // blue gate
    if(this->m_state == GAME_ACTIVE && CheckBallInRec(this->m_ball, this->m_gate_blue)) {
        this->m_score_red++;
        // 进球播放音效...ing 重置球的位置
        this->m_ball->m_position = glm::vec2(this->m_width * 0.5, this->m_height * 0.5);
        this->m_ball->m_velocity = glm::vec2(0.0f, 0.0f);
    }
    // red gate
    if(this->m_state == GAME_ACTIVE && CheckBallInRec(this->m_ball, this->m_gate_red)) {
        this->m_score_blue++;
        this->m_ball->m_position = glm::vec2(this->m_width * 0.5, this->m_height * 0.5);
        this->m_ball->m_velocity = glm::vec2(0.0f, 0.0f);
    }

    if(this->m_score_blue >= GAME_SCORE_TURN || this->m_score_red >= GAME_SCORE_TURN) {
        this->m_state = GAME_WIN;
    }
}

void Game::DoCollision()
{
    // collision between players
    for(int i=0; i<this->m_players_blue.size(); i++) {
        Player* player = this->m_players_blue[i];
        for(int j=i+1; j<this->m_players_blue.size(); j++) {
            Player* player2 = this->m_players_blue[j];
            auto c = CheckCollision(player, player2);
            if(c.first) {
                // velocity correction
                glm::vec2 p1_center = player->m_position + player->m_size / 2.0f;
                glm::vec2 p2_center = player2->m_position + player2->m_size / 2.0f;
                correctVelocitiesAfterCollision(player->m_velocity, player2->m_velocity, p1_center, p2_center, PLAYER_WEIGHT, PLAYER_WEIGHT);

                // position correction
                player->m_position += c.second;
                player2->m_position -= c.second;
            }
        }
    }
    for(int i=0; i<this->m_players_red.size(); i++) {
        Player* player = this->m_players_red[i];
        for(int j=i+1; j<this->m_players_red.size(); j++) {
            Player* player2 = this->m_players_red[j];
            auto c = CheckCollision(player, player2);
            if(c.first) {
                // velocity correction
                glm::vec2 p1_center = player->m_position + player->m_size / 2.0f;
                glm::vec2 p2_center = player2->m_position + player2->m_size / 2.0f;
                correctVelocitiesAfterCollision(player->m_velocity, player2->m_velocity, p1_center, p2_center, PLAYER_WEIGHT, PLAYER_WEIGHT);

                // position correction
                player->m_position += c.second;
                player2->m_position -= c.second;
            }
        }
    }
    for(int i=0; i<this->m_players_blue.size(); i++) {
        Player* player = this->m_players_blue[i];
        for(int j=0; j<this->m_players_red.size(); j++) {
            Player* player2 = this->m_players_red[j];
            auto c = CheckCollision(player, player2);
            if(c.first) {
                // velocity correction
                glm::vec2 p1_center = player->m_position + player->m_size / 2.0f;
                glm::vec2 p2_center = player2->m_position + player2->m_size / 2.0f;
                correctVelocitiesAfterCollision(player->m_velocity, player2->m_velocity, p1_center, p2_center, PLAYER_WEIGHT, PLAYER_WEIGHT);

                // position correction
                player->m_position += c.second;
                player2->m_position -= c.second;
            }
        }
    }

    // collision between ball and players
    for(auto player : this->m_players_blue) {
        auto c = CheckCollision(this->m_ball, player);
        if(c.first) {
            glm::vec2 ball_center = this->m_ball->m_position + this->m_ball->m_size / 2.0f;
            glm::vec2 player_center = player->m_position + player->m_size / 2.0f;
            correctVelocitiesAfterCollision(this->m_ball->m_velocity, player->m_velocity, ball_center, player_center, BALL_WEIGHT, PLAYER_WEIGHT);

            // position correction
            this->m_ball->m_position += c.second;
            player->m_position -= c.second;

            if(player->m_state == AI_PLAYER &&player->m_operation_state == KICK) {
                player->m_operation_state = IDLE;
                player->kick_time_step = KICK_WAIT_TIME;
            }
        }
    }
    for(auto player : this->m_players_red) {
        auto c = CheckCollision(this->m_ball, player);
        if(c.first) {
            glm::vec2 ball_center = this->m_ball->m_position + this->m_ball->m_size / 2.0f;
            glm::vec2 player_center = player->m_position + player->m_size / 2.0f;
            correctVelocitiesAfterCollision(this->m_ball->m_velocity, player->m_velocity, ball_center, player_center, BALL_WEIGHT, PLAYER_WEIGHT);

            // position correction
            this->m_ball->m_position += c.second;
            player->m_position -= c.second;

            if(player->m_state == AI_PLAYER && player->m_operation_state == KICK) {
                player->m_operation_state = IDLE;
                player->kick_time_step = KICK_WAIT_TIME;
            }
        }
    }

}


