#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

enum PLAYER_STATE {
    AI_PLAYER, // AI 玩家
    HUMAN_PLAYER // 人类玩家
};

class Player : public Entity {
    public:
        glm::vec2 m_velocity; // 球的速度
        PLAYER_STATE m_state; // 玩家状态

        Player(Shader shader, Texture2D texture, glm::vec2 position = glm::vec2(100.0f, 75.0f), glm::vec2 size = glm::vec2(0.2f, 0.2f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(0.2f, 0.3f, 0.3f)) : 
            Entity(shader, texture, position, size, color), m_velocity(velocity), m_state(AI_PLAYER) { this->init(); }

        void set_velocity(GLfloat x, GLfloat y){ this->m_velocity.x = x; this->m_velocity.y = y;} // 设置球的速度
        void set_velocity(glm::vec2 v) { this->m_velocity = v;} // 设置球的速度

        void set_state(PLAYER_STATE state) { this->m_state = state; } // 设置玩家状态

        void update(GLfloat dt, GLuint window_width, GLuint window_height); // 更新球的位置
};

#endif