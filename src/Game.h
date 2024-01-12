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
#include <iomanip>
#include <sstream>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum GameTurn {
    BLUE_TURN,
    RED_TURN
};


class Game {
    public:
        GameState m_state;
        GameTurn m_turn;

        GLfloat m_width, m_height;
        Playground* m_playground;
        Ball* m_ball;
        std::vector<Player*> m_players_blue;
        GLuint m_score_blue;
        std::vector<Player*> m_players_red;
        GLuint m_score_red;
        Entity *m_gate_blue, *m_gate_red;

        Player* m_player_human_blue; // human control blue player pointer
        Player* m_player_human_red; // human control red player pointer

        TextRender* m_text_render; // text render pointer

        GLboolean  Keys[1024]; // key pressed state
        GLboolean  Keys_hold[1024]; // key hold state
        GLboolean  Mouse_hold; // mouse hold state
        glm::vec2  Mouse_position; // mouse position

        GLfloat Mouse_click_time; // mouse click time
        GLfloat Mouse_release_time; // mouse release time

        Game(GLfloat width, GLfloat height) : m_width(width), m_height(height), m_score_blue(0), 
                                            m_score_red(0), m_state(GAME_MENU), m_turn(BLUE_TURN), Mouse_hold(GL_FALSE) {}
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
        // set mouse position
        void SetMousePosition(GLfloat x, GLfloat y) { this->Mouse_position.x = x; this->Mouse_position.y = y; }
        // receive mouse click, ready for shot
        void MouseRelease();

        // reset game
        void Reset();

        // inc mouse hold time
        void set_mouseClickTime() { this->Mouse_click_time = glfwGetTime(); }
        void set_mouseReleaseTime() { this->Mouse_release_time = glfwGetTime(); }
    
        
};

#endif