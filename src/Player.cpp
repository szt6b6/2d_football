#include "Player.h"

void Player::update(GLfloat dt, GLuint window_width, GLuint window_height, glm::vec2 gate_position, glm::vec2 ball_position)
{
    // AI control
    // logic: move to back of the ball and kick the ball
    glm::vec2 dis_position = glm::normalize(ball_position - gate_position) * this->m_size.x * 1.5f + ball_position;
    GLfloat dis = glm::length(dis_position - this->m_position);
    if(dis > 1.0f) {
        this->m_velocity = glm::normalize(dis_position - this->m_position) * 20.0f;
    } else {
        this->m_velocity = glm::normalize(ball_position - gate_position) * 40.0f;
    }

    this->m_position += this->m_velocity * dt;
    // boundary check
    if(this->m_position.x <= 0.0f) {
        this->m_position.x = 0.0f;
    }
    if(this->m_position.x + this->m_size.x >= window_width) {
        this->m_position.x = window_width - this->m_size.x;
    }
    if(this->m_position.y <= 0.0f) {
        this->m_position.y = 0.0f;
    }
    if(this->m_position.y + this->m_size.y >= window_height) {
        this->m_position.y = window_height - this->m_size.y;
    }
}