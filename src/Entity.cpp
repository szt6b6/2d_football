#include "Entity.h"

void Entity::init()
{
    GLuint VBO;
    GLfloat vertices[] = {
        // 位置     // 纹理
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->m_VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->m_position, 0.0f));
    model = glm::scale(model, glm::vec3(this->m_size, 1.0f));
    this->m_shader.Use().SetMatrix4("model", model);
    glm::mat4 view = glm::mat4(1.0f);
    this->m_shader.SetMatrix4("view", view);

    this->m_shader.SetVector3f("m_color", this->m_color);
    this->m_shader.SetInteger("m_texture", 0);
}

void Entity::render()
{
    this->m_shader.Use();
    this->m_texture.Bind();
    
    glBindVertexArray(this->m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}