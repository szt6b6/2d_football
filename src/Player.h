#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Properties.h"

enum PLAYER_STATE {
    AI_PLAYER, // AI 玩家
    HUMAN_PLAYER // 人类玩家
};

// operation state
enum OPERATION_STATE { // idle -> move -> kick -> idle
    IDLE, // 空闲
    MOVE, // 移动
    KICK // 踢球
};

class Player : public Entity {
    public:
        glm::vec2 m_velocity; // 球的速度
        PLAYER_STATE m_state; // 玩家状态
        OPERATION_STATE m_operation_state; // 操作状态
        GLuint idle_time_step;
        GLuint kick_time_step;

        Player(Shader shader, Texture2D texture, glm::vec2 position = glm::vec2(100.0f, 75.0f), glm::vec2 size = glm::vec2(0.2f, 0.2f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(0.2f, 0.3f, 0.3f)) : 
            Entity(shader, texture, position, size, color), m_velocity(velocity), 
            m_state(AI_PLAYER), m_operation_state(IDLE), idle_time_step(IDEL_WAIT_TIME), kick_time_step(KICK_WAIT_TIME) { this->init(); }

        void set_velocity(GLfloat x, GLfloat y){ this->m_velocity.x = x; this->m_velocity.y = y;} // 设置球的速度
        void set_velocity(glm::vec2 v) { this->m_velocity = v;} // 设置球的速度

        void set_role(PLAYER_STATE state) { this->m_state = state; } // 设置玩家状态
        void set_operation_state(OPERATION_STATE state) { this->m_operation_state = state; } // 设置操作状态

        void update(GLfloat dt, GLuint window_width, GLuint window_height, glm::vec2 gate_position, glm::vec2 ball_position); // 更新球的位置
};

#endif