#include "Menu.h"

void Menu::Initialize(Entity *player) {
    m_game_state.nextScene = -1;
    m_game_state.player = player;
    m_game_state.player->set_position(glm::vec3(0));
}
void Menu::Update(float delta_time) {
    if (delta_time == -1) {
        m_game_state.nextScene = 2;
        m_game_state.player->set_position(glm::vec3(7, -10, 0));
    }
}
void Menu::Render(ShaderProgram *g_shader_program) {
    Utility::draw_text(g_shader_program, Utility::load_texture("font1.png"), "Welcome to", 1, -0.5, glm::vec3(-2.0f, 1.0f, 0));
    Utility::draw_text(g_shader_program, Utility::load_texture("font1.png"), "Escaper", 1, -0.5, glm::vec3(-3.25f, 0.0f, 0));
    Utility::draw_text(g_shader_program, Utility::load_texture("font1.png"), "Press Enter", 1, -0.5, glm::vec3(-2.25f, -2.0f, 0));
    Utility::draw_text(g_shader_program, Utility::load_texture("font1.png"), "to Start", 1, -0.5, glm::vec3(-1.75f, -3.0f, 0));
}

