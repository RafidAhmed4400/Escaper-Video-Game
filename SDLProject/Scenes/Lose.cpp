#include "Lose.h"




void Lose::Initialize(Entity *player) {
    m_game_state.nextScene = -1;
    m_game_state.player = player;
    m_game_state.player->set_position(glm::vec3(0));
    


}
void Lose::Update(float delta_time) {
    
}
void Lose::Render(ShaderProgram *g_shader_program) {
    

    Utility::draw_text(g_shader_program, Utility::load_texture("font1.png"), "You Lose!", 1, -0.5, glm::vec3(-2.0f, 0, 0));
}
