#include "Ball.h"

void Ball::update(GLfloat dt, GLuint window_width, GLuint window_height, GLfloat slow_down_strength)
{
    // 球的位置更新 v越快旋转越快
    this->m_rotation_v = this->m_velocity.x * 2.0f;
    this->m_rotation += this->m_rotation_v * dt;
    this->m_position += this->m_velocity * dt;
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

    // slow down because of friction
    glm::vec2 slow_delta_v = this->m_velocity / glm::length(this->m_velocity) * slow_down_strength * dt;
    if(glm::length(this->m_velocity) > glm::length(slow_delta_v)) {
        this->m_velocity -= slow_delta_v;
    } else {
        this->m_velocity = glm::vec2(0.0f, 0.0f);
    }
}

void Ball::render()
{
    this->m_shader.Use();
    this->m_texture.Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->m_position, 0.0f));

    // if rotate, first move triangle to origin, then rotate, then move back
    model = glm::translate(model, glm::vec3(0.5f * this->m_size.x, 0.5f * this->m_size.y, 0.0f)); 
    model = glm::rotate(model, this->m_rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * this->m_size.x, -0.5f * this->m_size.y, 0.0f));

    model = glm::scale(model, glm::vec3(this->m_size, 1.0f));
    this->m_shader.Use().SetMatrix4("model", model);
    
    glBindVertexArray(this->m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
