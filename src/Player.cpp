#include "Player.h"

void Player::update(GLfloat dt, GLuint window_width, GLuint window_height, glm::vec2 gate_position, glm::vec2 ball_position)
{
    // AI control
    // logic: move to back of the ball and kick the ball
    glm::vec2 player_center = this->m_position + this->m_size / 2.0f;
    if(this->m_operation_state == IDLE) {
        this->m_velocity = glm::vec2(0.0f, 0.0f);
        if(this->idle_time_step-- <= 0) {
            this->m_operation_state = MOVE;
            this->idle_time_step = IDEL_WAIT_TIME;
        }
    } 
    else if(this->m_operation_state == MOVE) {
        glm::vec2 dis_position = glm::normalize(ball_position - gate_position) * this->m_size.x * 1.5f + ball_position;
        GLfloat dis = glm::length(dis_position - player_center);
        if(dis > 0.5f && (dis_position.x > this->m_size.x && dis_position.x < window_width - this->m_size.x) && (dis_position.y > this->m_size.y && dis_position.y < window_height - this->m_size.y)) {
            this->m_velocity = glm::normalize(dis_position - player_center) * PLAYER_SPEED;
        } else {
            this->m_operation_state = KICK;
        }
    } 
    else if(this->m_operation_state == KICK) {
        this->m_velocity = glm::normalize(ball_position - player_center) * PLAYER_SPEED * 2.0f;
        // kick the ball and change the state to idle, go to collision and write codes

        // kick state keep frames
        if(this->kick_time_step-- <= 0) {
            this->m_operation_state = IDLE;
            this->kick_time_step = KICK_WAIT_TIME;
        }
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