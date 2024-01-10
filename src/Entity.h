#ifndef ENTITY_H
#define ENTITY_H

#include "utils/Shader.h"
#include "utils/Texture2d.h"

// entity parent class

class Entity {
    public:
        glm::vec2 m_size, m_position; // playground size
        glm::vec3 m_color; // playground color
        Shader m_shader; // shader
        Texture2D m_texture; // texture
        GLuint m_VAO; // VAO

        Entity(Shader shader, Texture2D texture2d, glm::vec2 position = glm::vec2(200.0f, 100.0f), glm::vec2 size = glm::vec2(200.0f, 100.0f), glm::vec3 color = glm::vec3(0.2f, 0.3f, 0.3f))
            : m_shader(shader), m_texture(texture2d), m_position(position), m_size(size), m_color(color) { }
        
        void init(); // buffer init
        void render(); // draw
};
#endif