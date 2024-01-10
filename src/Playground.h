#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "Entity.h"

// playground class

class Playground : public Entity {
    public:
        GLfloat m_friction_param; // 摩擦系数

        Playground(Shader shader, Texture2D texture2d, glm::vec2 position = glm::vec2(100.0f, 50.0f), glm::vec2 size = glm::vec2(200.0f, 150.0f), GLfloat friction_param = 0.1f, glm::vec3 color = glm::vec3(0.2f, 0.3f, 0.3f)) : 
            Entity(shader, texture2d, position, size, color), m_friction_param(friction_param) { this->init(); }
};
#endif