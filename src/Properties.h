#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// 游戏世界行为属性值

extern const GLuint WINDOW_WIDTH; // 窗口宽度    
extern const GLuint WINDOW_HEIGHT; // 窗口高度

extern const GLfloat PLAYGROUND_WIDTH; // 游戏场地宽度
extern const GLfloat PLAYGROUND_HEIGHT; // 游戏场地高度

extern const glm::vec2 GATE_SIZE_SCALE; // 球门大小比例

extern const GLuint PLAYER_MAX_NUM; // 每队队员数量
extern const glm::vec2 RED_TIME_INIT_POSITION; // 红队初始位置
extern const glm::vec2 BLUE_TIME_INIT_POSITION; // 蓝队初始位置
extern const glm::vec2 RED_TEAM_POSITION_OFFSET[]; // 红队队员位置偏移
extern const glm::vec2 BLUE_TEAM_POSITION_OFFSET[]; // 蓝队队员位置偏移

extern const GLfloat PLAYER_SPEED; // 玩家移动速度
extern const glm::vec2 PLAYER_SIZE; // 玩家大小
extern const GLuint IDEL_WAIT_TIME; // 玩家踢球后空闲等待帧数
extern const GLuint KICK_WAIT_TIME; // 玩家踢球状态持续帧数
extern const GLfloat BALL_SPEED; // 球的速度
extern const GLfloat BALL_RADIUS; // 球的半径
extern const GLfloat FONT_SIZE; // 字体大小

#endif