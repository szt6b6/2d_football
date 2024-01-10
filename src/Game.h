#ifndef GAME_H
#define GAME_H

#include "utils/ResourceManager.h"
#include "utils/Log.h"
#include "utils/Shader.h"
#include "Playground.h"
#include "Ball.h"
#include "Player.h"

#include <vector>


class Game {
    public:
        GLuint m_width, m_height;
        Playground* m_playground;
        Ball* m_ball;
        std::vector<Player*> m_players_blue;
        std::vector<Player*> m_players_red;
        
        Game(GLuint width, GLuint height) : m_width(width), m_height(height) {}
        ~Game(){ delete m_playground; }

        void Init();
        // void ProcessInput(GLfloat dt);
        void Update(GLfloat dt);
        void Render();
};

#endif