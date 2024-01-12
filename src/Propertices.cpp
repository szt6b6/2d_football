#include "Properties.h"

const GLuint WINDOW_WIDTH = 800;
const GLuint WINDOW_HEIGHT = 600;

const GLfloat PLAYGROUND_WIDTH = 200.0f;
const GLfloat PLAYGROUND_HEIGHT = 150.0f;

const glm::vec2 GATE_SIZE_SCALE = glm::vec2(0.05f, 0.10f);

const GLuint PLAYER_MAX_NUM = 1;
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

const GLfloat PLAYER_SPEED = 20.0f;
const glm::vec2 PLAYER_SIZE = glm::vec2(10.0f, 10.0f);
const GLfloat PLAYER_WEIGHT = 60.0f;
const GLfloat BALL_RADIUS = 3.0f;
const GLfloat FONT_SIZE = 15.0f;
const GLfloat BALL_WEIGHT = 1.0f;