#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Properties.h"

class Ball : public Entity {
    public:
        glm::vec2 m_velocity; // 球的速度
        GLfloat m_radius; // 球的半径
        GLfloat m_rotation, m_rotation_v; // 球的旋转角度, 旋转速度

        Ball(Shader shader, Texture2D texture, glm::vec2 position = glm::vec2(400.0f, 300.0f), glm::vec2 size = glm::vec2(10.0f, 10.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(0.2f, 0.3f, 0.3f)) : 
            Entity(shader, texture, position, size, color), m_velocity(velocity), m_radius(size.x / 2), m_rotation_v(0) { this->init(); }

        void set_velocity(GLfloat x, GLfloat y){ this->m_velocity.x = x; this->m_velocity.y = y;} // 设置球的速度
        void set_velocity(glm::vec2 v) { this->m_velocity = v;} // 设置球的速度

        void set_rotation_v(GLfloat v) { this->m_rotation_v = v; } // 设置球的旋转角度

        void update(GLfloat dt, GLuint window_width, GLuint window_height, GLfloat slow_down_strength); // 更新球的位置

        void render();
};

#endif