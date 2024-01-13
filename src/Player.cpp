#include "Player.h"

// 计算点 P 在直线上的投影点
/*
params:
    pointA, pointB 为线段端点
    pointP 为点 P
return:
    是否在线段中间和p在直线上投影点
*/
std::pair<GLboolean, glm::vec2> cal_line_point_dis(glm::vec2 pointA, glm::vec2 pointB, glm::vec2 pointP)
{
    // 计算直线的方向向量
    glm::vec2 lineDirection = glm::normalize(pointB - pointA);

    // 计算直线上的投影点 P'
    GLfloat t = glm::dot(pointP - pointA, lineDirection);
    glm::vec2 projection = pointA + t * lineDirection;

    if(t < 0.0f || t > glm::length(pointB - pointA)) {
        return std::make_pair(GL_FALSE, projection);
    }
    return std::make_pair(GL_TRUE, projection);
}

void Player::update(GLfloat dt, GLuint window_width, GLuint window_height, glm::vec2 oppo_gate_position, glm::vec2 self_gate_position, glm::vec2 ball_position)
{
    // AI control, make dicision and set velocity
    // logic: move to back of the ball and kick the ball
    glm::vec2 player_center = this->m_position + this->m_size / 2.0f;
    GLfloat dis_from_ball = glm::length(ball_position - player_center);

    switch(this->m_operation_state) {
        case IDLE:
            {   if(this->idle_time_step-- == IDEL_WAIT_TIME) {
                    GLfloat direction = rand() % 360 / 180.0f * 3.1415926f;
                    this->m_velocity = glm::vec2(cos(direction), sin(direction)) * PLAYER_SPEED;
                }
                if(dis_from_ball < window_width / 4.0f) { // if ball is near the player, go to attack
                    this->m_operation_state = ATTACK;
                    this->idle_time_step = IDEL_WAIT_TIME;
                }
                if(this->idle_time_step <= 0) idle_time_step = IDEL_WAIT_TIME;
            }
            break;
        case ATTACK:
            {
                if(dis_from_ball > window_width / 4.0f) {
                    this->m_operation_state = IDLE;
                    break;
                }
                /*
                想法实现：
                    先跑到球后面一个目的点 然后在踢出去
                    跑到球后面是 若球在路线上则绕一下改变一下目的点
                    绕路实现：
                        球员去往目的点直线附近有球且球在目的点和球员之间 则球员将目的点修改为球附近一个点（根据映射点计算得来）
                        如果球在球员和目的球门中间 则不进行绕路
                */
                glm::vec2 dis_position = glm::normalize(ball_position - oppo_gate_position) * this->m_size.x * 1.5f + ball_position;
                GLfloat dis = glm::length(dis_position - player_center);
                // judge the ball in near the line between the player and the gate
                std::pair<GLboolean, glm::vec2> info_ball_between_playerAndGate = cal_line_point_dis(this->m_position, oppo_gate_position, ball_position);

                // judge ball is near the line and between player and its dis_position
                std::pair<GLboolean, glm::vec2> info_ball_between_playerAndDis = cal_line_point_dis(this->m_position, dis_position, ball_position);
                
                if(!info_ball_between_playerAndGate.first && info_ball_between_playerAndDis.first && glm::length(info_ball_between_playerAndDis.second - ball_position) <= BALL_RADIUS + PLAYER_SIZE.x / 2.0f) {
                    dis_position = ball_position + glm::normalize(info_ball_between_playerAndDis.second - ball_position) * (PLAYER_SIZE.x * 1.5f + BALL_RADIUS);
                    this->m_velocity = glm::normalize(dis_position - player_center) * PLAYER_SPEED;
                } else {
                    if(dis > 0.5f && (dis_position.x > this->m_size.x && dis_position.x < window_width - this->m_size.x) && (dis_position.y > this->m_size.y && dis_position.y < window_height - this->m_size.y)) {
                        this->m_velocity = glm::normalize(dis_position - player_center) * PLAYER_SPEED;
                    } else {
                        this->m_operation_state = KICK;
                    }
                }
            }
            break;
        case KICK:
            {
                this->m_velocity = glm::normalize(ball_position - player_center) * PLAYER_SPEED * 2.0f;
                // kick the ball and change the state to idle, go to collision and write codes

                // kick state keep frames
                if(this->kick_time_step-- <= 0) {
                    this->m_operation_state = IDLE;
                    this->kick_time_step = KICK_WAIT_TIME;
                }
            }
            break;
        case DEFEND:
        /*
            想法：
                移动到球和己方球门中间, 球距离近 就把他踢走
        */
        {
            GLfloat dis_from_ball = glm::length(ball_position - player_center);
            if(dis_from_ball < PLAYER_SIZE.x) {
                // kick ball to away from the gate
                // 对球的一角踢
                GLuint up_or_bottom = rand() % 2;
                if(up_or_bottom)
                    this->m_velocity = glm::normalize(ball_position + glm::vec2(0.0f, BALL_RADIUS) - player_center) * PLAYER_SPEED * 2.0f;
                else
                    this->m_velocity = glm::normalize(ball_position + glm::vec2(0.0f, -BALL_RADIUS) - player_center) * PLAYER_SPEED * 2.0f;
            } else {
                glm::vec2 dis_position_defend = (ball_position + self_gate_position) / 2.0f;
                this->m_velocity = glm::normalize(dis_position_defend - player_center) * PLAYER_SPEED;
            }

        }
        break;
    }


    // do decision, m_velocity got by AI logic
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

void Player::update_by_controller(GLfloat dt, GLuint window_width, GLuint window_height, glm::vec2 ball_position, glm::vec2 mouse_position)
{
    // according to mouse position, set v
    this->m_velocity = glm::normalize(mouse_position - this->m_position) * PLAYER_SPEED * 2.0f;
    // if dis from ball < 0.5f, kick the ball, double speed
    if(glm::length(this->m_position - ball_position) < PLAYER_SIZE.x + BALL_RADIUS) 
        this->m_velocity *= 2.0f;

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
