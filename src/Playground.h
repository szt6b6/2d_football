#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include "utils/Shader.h"

// playground class

class Playground {
    public:
        glm::vec2 size; // playground size
        glm::vec3 color; // playground color
        GLfloat friction_param; // 摩擦系数
        Shader shader; // shader
        GLuint VAO; // VAO

        Playground(Shader shader, glm::vec2 size = glm::vec2(800.0f, 600.0f), GLfloat friction_param = 0.1f);
        
        void init(); // buffer init
        void render(); // draw playground
};
#endif