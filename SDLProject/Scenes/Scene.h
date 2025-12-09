#pragma once
#define GL_SILENCE_DEPRECATION
#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "../glm/mat4x4.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "../Utility.h"
#include "../Entity.h"
#include "../Map.h"

struct GameState {
    Map *map;
    Entity *player;
    Entity *enemies;
    int nextScene;
};
class Scene {
public:
    GameState m_game_state;
    virtual void Initialize(Entity *player) = 0;
    virtual void Update(float delta_time) = 0;
    virtual void Render(ShaderProgram *g_shader_program) = 0;
};
