#include "Dungeon.h"
#define DUNGEON_WIDTH 10
#define DUNGEON_HEIGHT 10

#define DUNGEON_ENEMY_COUNT 4
#define GUARD_COUNT 4
#include <SDL_mixer.h>


Mix_Chunk *key_sfx;


using namespace std;

void Dungeon::Initialize(Entity *player) {
    
    key_sfx = Mix_LoadWAV("key.mp3");
    
     
    m_game_state.nextScene = -1;
    
    GLuint map_texture_id = Utility::load_texture("medieval_tilesheet_2X.png");
    m_game_state.map = new Map(DUNGEON_WIDTH, DUNGEON_HEIGHT, dungeon_data, map_texture_id, 1.0f, 24, 14);
    m_game_state.player = player;
    
    m_game_state.enemies = new Entity[DUNGEON_ENEMY_COUNT];
    GLuint enemyTextureID = Utility::load_texture("knight.png");
    
    m_game_state.enemies[0].set_entity_type(ENEMY);
    m_game_state.enemies[0].set_texture_id(enemyTextureID);
    m_game_state.enemies[0].set_position(glm::vec3(5, -3.0f, 0));
    m_game_state.enemies[0].set_speed(1);
    m_game_state.enemies[0].set_ai_type(WAITANDGO);
    m_game_state.enemies[0].set_ai_state(IDLE);
    
    if (m_game_state.player->get_scene_id() == 3) {
            GLuint guardTextureID = Utility::load_texture("knight.png");
        for (int i = 0; i < GUARD_COUNT; ++i) {
            m_game_state.enemies[i].set_entity_type(ENEMY);
            m_game_state.enemies[i].set_texture_id(guardTextureID);
            m_game_state.enemies[i].set_ai_type(GUARD);
            m_game_state.enemies[i].activate();

        }
        m_game_state.enemies[0].set_position(glm::vec3(6, -2.0f, 0));
        m_game_state.enemies[1].set_position(glm::vec3(5, -5.0f, 0));
        m_game_state.enemies[2].set_position(glm::vec3(4, -1.0f, 0));
        m_game_state.enemies[3].set_position(glm::vec3(3, -3.0f, 0));

        }
    
    if (m_game_state.player->get_scene_id() == 4) {
            GLuint walkerTextureID = Utility::load_texture("knight.png");
            
        
            m_game_state.enemies[0].set_entity_type(ENEMY);
            m_game_state.enemies[0].set_texture_id(walkerTextureID);
            m_game_state.enemies[0].set_position(glm::vec3(4.5f, -5.0f, 0.0f));
            m_game_state.enemies[0].set_ai_type(WALKER);
            m_game_state.enemies[0].set_speed(1.0f);
            m_game_state.enemies[0].activate();
        }
    

    
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        m_game_state.enemies[i].activate();
    }
    
}
void Dungeon::Update(float delta_time) {
    m_game_state.player->Update(delta_time, m_game_state.player, m_game_state.enemies, DUNGEON_ENEMY_COUNT, m_game_state.map);
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        m_game_state.enemies[i].Update(delta_time, m_game_state.player, m_game_state.enemies, DUNGEON_ENEMY_COUNT, m_game_state.map);
    }
    if (m_game_state.player->get_reset() == true) {
        m_game_state.player->set_reset(false);
        m_game_state.player->set_num_lives(m_game_state.player->get_num_lives() - 1);
        m_game_state.nextScene = 2;
        m_game_state.player->set_position(glm::vec3(7, -10, 0));
    }
    if (m_game_state.player->get_num_lives() == 0) {
        m_game_state.nextScene = 0;
    }
    bool anyAlive = false;
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        if (m_game_state.enemies[i].get_activity_status() == true) {
            anyAlive = true;
            break;
        }
    }

    if (dungeon_data[25] != 208 && (m_game_state.player->m_position.x >= 4 && m_game_state.player->m_position.x < 6) && (m_game_state.player->m_position.y <= -1 && m_game_state.player->m_position.y >= -3)) {
        m_game_state.player->set_num_of_dun_cleared(m_game_state.player->get_num_of_dun_cleared() + 1);

        Mix_PlayChannel(-1,key_sfx,0 );

        dungeon_data[24] = 208;
        dungeon_data[25] = 208;
        m_game_state.enemies[0].set_new_position(m_game_state.enemies[0].m_position);
        m_game_state.nextScene = m_game_state.player->get_scene_id();
        m_game_state.enemies[0].m_position = m_game_state.enemies[0].get_new_position();
        
    }
    if ((m_game_state.player->m_position.x >= 4 && m_game_state.player->m_position.x <= 7) && (m_game_state.player->m_position.y <= -8 && m_game_state.player->m_position.y >= -10)) {
        m_game_state.nextScene = 2;
        m_game_state.player->m_position.x = m_game_state.player->get_new_position().x;
        m_game_state.player->m_position.y = m_game_state.player->get_new_position().y;
    }
}
void Dungeon::Render(ShaderProgram *g_shader_program) {
    m_game_state.map->Render(g_shader_program);
    m_game_state.player->Render(g_shader_program);
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        m_game_state.enemies[i].Render(g_shader_program);
    }
}
