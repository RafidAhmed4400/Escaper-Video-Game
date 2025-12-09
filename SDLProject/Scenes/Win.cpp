#include "Win.h"
#include "Utility.h"
#include <SDL_mixer.h>


Mix_Chunk *win_sfx;



void Win::Initialize(Entity *player) {
    
    win_sfx = Mix_LoadWAV("win.mp3");
    
    Mix_VolumeChunk(
            win_sfx,
            MIX_MAX_VOLUME / 2  
            );

    m_game_state.nextScene = -1;
    m_game_state.player = player;
    m_game_state.player->set_position(glm::vec3(0));
    
}
void Win::Update(float delta_time) {
    
}
void Win::Render(ShaderProgram *g_shader_program) {
    Mix_PlayChannel(-1,win_sfx,0 );
                     
    Utility::draw_text(g_shader_program, Utility::load_texture("font1.png"), "You Win!", 1, -0.5, glm::vec3(-2.0f, 0, 0));
}
