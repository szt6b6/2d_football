#ifndef GAME_H
#define GAME_H

#include "utils/ResourceManager.h"
#include "utils/Log.h"
#include "utils/Shader.h"
#include "Playground.h"


class Game {
    public:
        GLuint width, height;
        Playground* playground;
        
        Game(GLuint width, GLuint height) : width(width), height(height) {}
        ~Game(){ delete playground; }

        void Init();
        // void ProcessInput(GLfloat dt);
        void Update(GLfloat dt);
        void Render();
};

#endif