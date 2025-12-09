/**
* Author: [Rafid Ahmed]
* Assignment: [Escaper]
* Date due: [05/02], 2:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/


#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include <SDL_mixer.h>

#include "Entity.h"
#include "Map.h"

#include <iostream>
#include <vector>

#include "Utility.h"

#include "Scenes/Scene.h"
#include "Scenes/Menu.h"
#include "Scenes/Main.h"
#include "Scenes/Dungeon.h"
#include "Scenes/Lose.h"
#include "Scenes/Win.h"

using namespace std;

// ————— CONSTANTS ————— //
constexpr int WINDOW_WIDTH  = 640 * 2,
              WINDOW_HEIGHT = 480 * 2;

constexpr float BG_RED     = 0.1922f,
            BG_BLUE    = 0.549f,
            BG_GREEN   = 0.9059f,
            BG_OPACITY = 1.0f;

constexpr int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH  = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

constexpr char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

constexpr float MILLISECONDS_IN_SECOND = 1000.0;

// BGM
constexpr int CD_QUAL_FREQ = 44100,  // CD quality
          AUDIO_CHAN_AMT  = 2,      // Stereo
          AUDIO_BUFF_SIZE = 4096;

// SFX
constexpr int PLAY_ONCE   =  0,
          NEXT_CHNL   = -1,  // next available channel
          MUTE_VOL    =  0,
          MILS_IN_SEC =  1000,
          ALL_SFX_CHN = -1;


constexpr int   m_LEFT  = 0,
                m_RIGHT = 1,
                m_UP    = 2,
                m_DOWN  = 3;



int player_walking_animation[4][4] =
{
    {4, 5, 6, 7 }, // for George to move to the left,
    { 8, 9, 10, 11 }, // for George to move to the right,
    {12, 13, 14, 15}, // for George to move upwards,
    {0, 1, 2, 3}  // for George to move downwards
};

enum AppStatus { RUNNING, TERMINATED };


SDL_Window* g_display_window;
AppStatus g_app_status = RUNNING;

ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

Mix_Music *g_music;
Mix_Chunk *die;

Scene *g_current_scene;
Scene *sceneList[14];

void SwitchToScene(Scene *scene) {
    Entity *player;
    if (g_current_scene == nullptr) {
        player = new Entity();
        player->set_entity_type(PLAYER);
        player->set_position(glm::vec3(7, -10, 0));
        player->set_movement(glm::vec3(0));
        player->set_acceleration(glm::vec3(0, 0, 0));
        player->set_speed(3.0f);
        player->set_texture_id(Utility::load_texture("red.png"));
        

        
        player->m_animation_indices = player_walking_animation[m_RIGHT];
        player->set_animation_frames(4);
        player->set_animation_index(0);
        player->set_animation_time(0);
        player->set_animation_cols(4);
        player->set_animation_rows(4);
        
        player->set_num_lives(3);
        
        player->set_height(0.8f);
        player->set_width(0.8f);
        player->set_num_of_dun_cleared(0);
        
    } else {
        player = g_current_scene->m_game_state.player;
    }
    g_current_scene = scene;
    g_current_scene->Initialize(player);
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("Project 6!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    g_shader_program.load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    g_view_matrix = glm::mat4(1.0f);
    //g_model_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    
    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    Mix_OpenAudio(CD_QUAL_FREQ, MIX_DEFAULT_FORMAT, AUDIO_CHAN_AMT, AUDIO_BUFF_SIZE);
    g_music = Mix_LoadMUS("Great Little Challenge.mp3");
    Mix_PlayMusic(g_music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    
    die = Mix_LoadWAV("bounce.wav");

    

    sceneList[0] = new Lose();
    sceneList[1] = new Win();
    sceneList[2] = new Main();
    for (int i = 3; i < 13; ++i) {
        sceneList[i] = new Dungeon();
    }
    sceneList[13] = new Menu();
    SwitchToScene(sceneList[13]);
}

void ProcessInput() {
    
    g_current_scene->m_game_state.player->set_movement(glm::vec3(0));
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_app_status = TERMINATED;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
   
                        break;
                        
                    case SDLK_RIGHT:
       
                        break;
                        
                    case SDLK_SPACE:
   
                        break;
                    case SDLK_RETURN:
                        if (g_current_scene == sceneList[13]) {
                            g_current_scene->Update(-1);
                        }
                }
                break;
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        g_current_scene->m_game_state.player->m_movement.x = -1.0f;
        g_current_scene->m_game_state.player->m_animation_indices = player_walking_animation[m_LEFT];
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        g_current_scene->m_game_state.player->m_movement.x = 1.0f;
        g_current_scene->m_game_state.player->m_animation_indices = player_walking_animation[m_RIGHT];
    }
    else if (keys[SDL_SCANCODE_UP]) {
        g_current_scene->m_game_state.player->m_movement.y = 1.0f;
        g_current_scene->m_game_state.player->m_animation_indices = player_walking_animation[m_UP];
    }
    else if (keys[SDL_SCANCODE_DOWN]) {
        g_current_scene->m_game_state.player->m_movement.y = -1.0f;
        g_current_scene->m_game_state.player->m_animation_indices = player_walking_animation[m_DOWN];
    }
    

    if (glm::length(g_current_scene->m_game_state.player->m_movement) > 1.0f) {
        g_current_scene->m_game_state.player->m_movement = glm::normalize(g_current_scene->m_game_state.player->m_movement);
    }

}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;
void Update() {
   float ticks = (float)SDL_GetTicks() / 1000.0f;
   float delta_time = ticks - lastTicks;
   lastTicks = ticks;
    delta_time += accumulator;
   if (delta_time < FIXED_TIMESTEP) {
       accumulator = delta_time;
       return;
   }
   while (delta_time >= FIXED_TIMESTEP) {
       g_current_scene->Update(FIXED_TIMESTEP);
       
       delta_time -= FIXED_TIMESTEP;
   }
   accumulator = delta_time;
    
    g_view_matrix = glm::mat4(1.0f);
    float x = 0;
    float y = 0;

    x = -g_current_scene->m_game_state.player->m_position.x;
    y = -g_current_scene->m_game_state.player->m_position.y;

    g_view_matrix = glm::translate(g_view_matrix, glm::vec3(x, y, 0));
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    g_shader_program.set_view_matrix(g_view_matrix);
    
    g_current_scene->Render(&g_shader_program);
    
    SDL_GL_SwapWindow(g_display_window);
}


void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (g_app_status == RUNNING) {
        ProcessInput();
        Update();
        
        if (g_current_scene->m_game_state.nextScene >= 0) SwitchToScene(sceneList[g_current_scene->m_game_state.nextScene]);
        
        Render();
    }
    
    Shutdown();
    return 0;
}
