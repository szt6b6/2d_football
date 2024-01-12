#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Properties.h"

enum PLAYER_STATE {
    AI_PLAYER, // AI 玩家
    HUMAN_PLAYER // 人类玩家
};


class Player : public Entity {
    public:
        glm::vec2 m_velocity; // 玩家速度
        PLAYER_STATE m_state; // 玩家状态

        Player(Shader shader, Texture2D texture, glm::vec2 position = glm::vec2(100.0f, 75.0f), glm::vec2 size = glm::vec2(0.2f, 0.2f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(0.2f, 0.3f, 0.3f)) : 
            Entity(shader, texture, position, size, color), m_velocity(velocity), m_state(AI_PLAYER) { this->init(); }

        void set_velocity(GLfloat x, GLfloat y){ this->m_velocity.x = x; this->m_velocity.y = y;} // 设置玩家的速度
        void set_velocity(glm::vec2 v) { this->m_velocity = v;} // 设置玩家的速度
        void set_texture(Texture2D texture) { this->m_texture = texture; } // 设置玩家的纹理 不同回合选中出现不同的纹理
        void set_role(PLAYER_STATE state) { this->m_state = state; } // 设置玩家的状态

        void update(GLfloat dt, GLuint window_width, GLuint window_height, GLfloat slow_down_strength); // 更新玩家的位置

        
};

#endif