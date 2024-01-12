#ifndef GAME_H
#define GAME_H

#include "utils/ResourceManager.h"
#include "utils/Log.h"
#include "utils/Shader.h"
#include "utils/Text.h"
#include "Properties.h"
#include "Playground.h"
#include "Ball.h"
#include "Player.h"

#include <vector>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};


class Game {
    public:
        GameState m_state;

        GLfloat m_width, m_height;
        Playground* m_playground;
        Ball* m_ball;
        std::vector<Player*> m_players_blue;
        GLuint m_score_blue;
        std::vector<Player*> m_players_red;
        GLuint m_score_red;
        Entity *m_gate_blue, *m_gate_red;

        Player* m_player_human; // human control player pointer
        TextRender* m_text_render; // text render pointer

        GLboolean  Keys[1024]; // key pressed state
        GLboolean  Keys_hold[1024]; // key hold state
        
        Game(GLfloat width, GLfloat height) : m_width(width), m_height(height), m_score_blue(0), m_score_red(0), m_state(GAME_MENU) {}
        ~Game(){ delete m_playground; }

        void Init();

        // collision detection
        void DoCollision();

        // check if the ball is in the gate
        void CheckBallInGate();

        void Update(GLfloat dt);

        void Render();

        // process key event
        void ProcessInput(GLfloat dt);

        // reset game
        void Reset();

};

#endif