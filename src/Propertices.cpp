#include "Properties.h"

const GLuint WINDOW_WIDTH = 800;
const GLuint WINDOW_HEIGHT = 600;

const GLfloat PLAYGROUND_WIDTH = 200.0f;
const GLfloat PLAYGROUND_HEIGHT = 150.0f;

const glm::vec2 GATE_SIZE_SCALE = glm::vec2(0.05f, 0.25f);

const GLuint PLAYER_MAX_NUM = 3;
const glm::vec2 RED_TIME_INIT_POSITION = glm::vec2(150.0f, 75.0f);
const glm::vec2 BLUE_TIME_INIT_POSITION = glm::vec2(50.0f, 75.0f);
const glm::vec2 RED_TEAM_POSITION_OFFSET[] = { 
                                        glm::vec2(0.0f, 0.0f),
                                        glm::vec2(20.0f, 20.0f),
                                        glm::vec2(20.0f, -20.0f),};
const glm::vec2 BLUE_TEAM_POSITION_OFFSET[] = { 
                                        glm::vec2(0.0f, 0.0f),
                                        glm::vec2(-20.0f, -20.0f),
                                        glm::vec2(-20.0f, 20.0f),};

const GLfloat PLAYER_SPEED = 20;
const glm::vec2 PLAYER_SIZE = glm::vec2(5.0f, 5.0f);
const GLuint IDEL_WAIT_TIME = 10;
const GLuint KICK_WAIT_TIME = 100;
const GLfloat BALL_SPEED = 30.0f;
const GLfloat BALL_RADIUS = 2.0f;
const GLfloat FONT_SIZE = 15.0f;