#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum PLAYER_STATE {
    AI_PLAYER, // AI 玩家
    HUMAN_PLAYER // 人类玩家
};

// operation state
enum OPERATION_STATE { // idle -> move -> kick -> idle
    IDLE, // 空闲
    ATTACK, // 移动进攻
    KICK, // 踢球
    DEFEND, // 防守
};

// 游戏世界行为属性值

const GLuint WINDOW_WIDTH = 800; // 窗口宽度
const GLuint WINDOW_HEIGHT = 600;  // 窗口高度

const GLfloat PLAYGROUND_WIDTH = 200.0f; // 游戏场地宽度
const GLfloat PLAYGROUND_HEIGHT = 150.0f; // 游戏场地高度

const glm::vec2 GATE_SIZE_SCALE = glm::vec2(0.05f, 0.10f); // 球门大小比例
const GLuint GAME_SCORE_TURN = 3; // 几分制游戏 比如1 3 5

const GLuint PLAYER_MAX_NUM = 5; // 每队队员数量
const glm::vec2 RED_TIME_INIT_POSITION = glm::vec2(150.0f, 75.0f); // 红队初始位置
const glm::vec2 BLUE_TIME_INIT_POSITION = glm::vec2(50.0f, 75.0f); // 蓝队初始位置
const glm::vec2 RED_TEAM_POSITION_OFFSET[] = {  // 红队队员初始位置偏移
                                        glm::vec2(0.0f, 0.0f),
                                        glm::vec2(20.0f, 20.0f),
                                        glm::vec2(20.0f, -20.0f),
                                        glm::vec2(40.0f, 40.0f),
                                        glm::vec2(40.0f, -40.0f),
                                        };
const glm::vec2 BLUE_TEAM_POSITION_OFFSET[] = {  // 蓝队队员初始位置偏移
                                        glm::vec2(0.0f, 0.0f),
                                        glm::vec2(-20.0f, -20.0f),
                                        glm::vec2(-20.0f, 20.0f),
                                        glm::vec2(-40.0f, -40.0f),
                                        glm::vec2(-40.0f, 40.0f),
                                        };
const OPERATION_STATE RED_TEAM_OPERATION_STATE[] = { IDLE, DEFEND, ATTACK, IDLE, IDLE }; // 红队队员初始操作状态
const OPERATION_STATE BLUE_TEAM_OPERATION_STATE[] = { IDLE, DEFEND, ATTACK, IDLE, IDLE }; // 蓝队队员初始操作状态

const GLfloat PLAYER_SPEED = 20; // 玩家移动速度
const glm::vec2 PLAYER_SIZE = glm::vec2(6.0f, 6.0f); // 玩家大小
const GLuint IDEL_WAIT_TIME = 100; // 玩家踢球后空闲等待帧数
const GLuint KICK_WAIT_TIME = 100; // 玩家踢球状态持续帧数
const GLfloat PLAYER_WEIGHT = 5.0f; // 玩家质量
const GLfloat BALL_SPEED = 30.0f; // 球的速度
const GLfloat BALL_RADIUS = 2.0f; // 球的半径
const GLfloat FONT_SIZE = 15.0f; // 字体大小
const GLfloat BALL_WEIGHT = 1.0f; // 球质量

#endif