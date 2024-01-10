#include "Player.h"

void Player::update(GLfloat dt, GLuint window_width, GLuint window_height)
{
    this->m_position += this->m_velocity * dt;
    // boundary check
    if(this->m_position.x <= 0.0f) {
        this->m_position.x = 0.0f;
        this->m_velocity.x = -this->m_velocity.x;
    }
    if(this->m_position.x + this->m_size.x >= window_width) {
        this->m_position.x = window_width - this->m_size.x;
        this->m_velocity.x = -this->m_velocity.x;
    }
    if(this->m_position.y <= 0.0f) {
        this->m_position.y = 0.0f;
        this->m_velocity.y = -this->m_velocity.y;
    }
    if(this->m_position.y + this->m_size.y >= window_height) {
        this->m_position.y = window_height - this->m_size.y;
        this->m_velocity.y = -this->m_velocity.y;
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->m_position, 0.0f));
    model = glm::scale(model, glm::vec3(this->m_size, 1.0f));
    this->m_shader.Use().SetMatrix4("model", model);
}