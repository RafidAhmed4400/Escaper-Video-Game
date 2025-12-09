//#include "Scene.h"
//
//class Main : public Scene {
//public:
//    void Initialize(Entity *player) override;
//    void Update(float delta_time) override;
//    void Render(ShaderProgram *g_shader_program) override;
//};



#include "Main.h"
#define MAIN_WIDTH 14
#define MAIN_HEIGHT 20

#define MAIN_ENEMY_COUNT 0
using namespace std;
  
unsigned int main_data[] =
{ 
    133, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134,
    181, 243, 243, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 182,
    181, 181, 181, 0, 0, 0, 0, 0, 0, 0, 0, 182, 182, 182,
    181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182,
    181, 181, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182,
    181, 243, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182,
    181, 243, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182,
    181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182, 182, 182,
    181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 182,
    181, 181, 181, 0, 0, 0, 0, 0, 0, 0, 0, 182, 182, 182,
    181, 243, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182,
    181, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182,
    181, 181, 181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182,
    181, 243, 243, 0, 0, 0, 0, 0, 0, 0, 0, 182, 182, 182,
    181, 181, 181, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 182,
    181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 182, 182, 182,
    181, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 182,
    181, 243, 181, 0, 0, 0, 0, 0, 0, 0, 0, 182, 182, 182,
    181, 243, 181, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 182,
    133, 134, 134, 134, 134, 135, 244, 246, 133, 134, 134, 134, 134, 135
};

/*
 {
     110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
     110, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 0, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 0, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 110, 110, 110, 110, 110, 2, 2, 110, 110, 110, 110, 110, 3
 };

 */

void Main::Initialize(Entity *player) {
    
    m_game_state.nextScene = -1;
    
    GLuint map_texture_id = Utility::load_texture("medieval_tilesheet_2X.png");
    m_game_state.map = new Map(MAIN_WIDTH, MAIN_HEIGHT, main_data, map_texture_id, 1.0f, 24, 14);
    m_game_state.player = player;
    
    /*m_game_state.enemies = new Entity[MAIN_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ctg.png");
    
    m_game_state.enemies[0].entityType = ENEMY;
    m_game_state.enemies[0].textureID = enemyTextureID;
    m_game_state.enemies[0].position = glm::vec3(5, -5.0f, 0);
    m_game_state.enemies[0].speed = 1;
    m_game_state.enemies[0].aiType = WAITANDGO;
    m_game_state.enemies[0].aiState = IDLE;
    //m_game_state.enemies[0].jumpPower = 5.0f;
    m_game_state.enemies[0].acceleration = glm::vec3(0, 0, 0);
        
    m_game_state.enemies[1].entityType = ENEMY;
    m_game_state.enemies[1].textureID = enemyTextureID;
    m_game_state.enemies[1].position = glm::vec3(11, 0.0f, 0);
    m_game_state.enemies[1].speed = 1;
    m_game_state.enemies[1].aiType = WAITANDGO;
    m_game_state.enemies[1].aiState = IDLE;
    //m_game_state.enemies[1].jumpPower = 5.0f;
    m_game_state.enemies[1].acceleration = glm::vec3(0, 0, 0);
    
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        m_game_state.enemies[i].isActive = true;
    }*/
}
void Main::Update(float delta_time) {
    m_game_state.player->Update(delta_time, m_game_state.player, m_game_state.enemies, MAIN_ENEMY_COUNT, m_game_state.map);
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        m_game_state.enemies[i].Update(delta_time, m_game_state.player, m_game_state.enemies, MAIN_ENEMY_COUNT, m_game_state.map);
    }
    if (m_game_state.player->get_num_lives() == 0) {
        m_game_state.nextScene = 4;
        m_game_state.player->set_position(glm::vec3(0,0,0));
    }
    bool anyAlive = false;
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        if (m_game_state.enemies[i].get_activity_status() == true) {
            anyAlive = true;
            break;
        }
    }
    //cout << "X: " << m_game_state.player->position.x << endl;
    //cout << "Y: " << m_game_state.player->position.y << endl;
    // open doors for exit
    if (m_game_state.player->get_num_of_dun_cleared() == 10) {
        main_data[272] = 0;
        main_data[273] = 0;
        m_game_state.nextScene = 2;
    }
    // exited building
    if ((m_game_state.player->m_position.x >= 5 && m_game_state.player->m_position.x <= 8) && (m_game_state.player->m_position.y <= -18.5 && m_game_state.player->m_position.y >= -20)) {
        m_game_state.nextScene = 1;
        m_game_state.player->set_scene_id(1);
    }
    // entered dungeon 1
    if ((m_game_state.player->get_position().x >= 0 && m_game_state.player->get_position().x <= 2) && (m_game_state.player->get_position().y <= 0 && m_game_state.player->get_position().y >= -2)) {
        m_game_state.nextScene = 3;
        m_game_state.player->set_scene_id(3);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(2.5f, -0.5f, 0));
    }
    // entered dungeon 2
    if ((m_game_state.player->get_position().x >= 0 && m_game_state.player->get_position().x <= 2) && (m_game_state.player->get_position().y <= -4 && m_game_state.player->get_position().y >= -6)) {
        m_game_state.nextScene = 4;
        m_game_state.player->set_scene_id(4);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(1.0f, -6.5f, 0));
    }

    // entered dungeon 3
    if ((m_game_state.player->get_position().x >= 0 && m_game_state.player->get_position().x <= 2) && (m_game_state.player->get_position().y <= -11.5 && m_game_state.player->get_position().y >= -13.5)) {
        m_game_state.nextScene = 5;
        m_game_state.player->set_scene_id(5);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(2.5f, -12.5f, 0));
    }

    // entered dungeon 4
    if ((m_game_state.player->get_position().x >= 0 && m_game_state.player->get_position().x <= 2) && (m_game_state.player->get_position().y <= -16.5 && m_game_state.player->get_position().y >= -18)) {
        m_game_state.nextScene = 6;
        m_game_state.player->set_scene_id(6);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(1.0f, -15.5f, 0));
    }

    // entered dungeon 5
    if ((m_game_state.player->get_position().x >= 11 && m_game_state.player->get_position().x <= 13) && (m_game_state.player->get_position().y <= 0 && m_game_state.player->get_position().y >= -2)) {
        m_game_state.nextScene = 7;
        m_game_state.player->set_scene_id(7);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(10.5f, -0.5f, 0));
    }
    
    // entered dungeon 6
    if ((m_game_state.player->get_position().x >= 11 && m_game_state.player->get_position().x <= 13) && (m_game_state.player->get_position().y <= -6.5 && m_game_state.player->get_position().y >= -8.5)) {
        m_game_state.nextScene = 8;
        m_game_state.player->set_scene_id(8);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(10.5f, -7.5f, 0));
    }

    // entered dungeon 7
    if ((m_game_state.player->get_position().x >= 11 && m_game_state.player->get_position().x <= 13) && (m_game_state.player->get_position().y <= -12.5 && m_game_state.player->get_position().y >= -14.5)) {
        m_game_state.nextScene = 9;
        m_game_state.player->set_scene_id(9);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(10.5f, -13.5f, 0));
    }

    // entered dungeon 8
    if ((m_game_state.player->get_position().x >= 11 && m_game_state.player->get_position().x <= 13) && (m_game_state.player->get_position().y <= -14.5 && m_game_state.player->get_position().y >= -16.5)) {
        m_game_state.nextScene = 10;
        m_game_state.player->set_scene_id(10);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(10.5f, -15.5f, 0));
    }


    // entered dungeon 9
    if ((m_game_state.player->get_position().x >= 0 && m_game_state.player->get_position().x <= 2) && (m_game_state.player->get_position().y <= -9 && m_game_state.player->get_position().y >= -10)) {
        m_game_state.nextScene = 11;
        m_game_state.player->set_scene_id(11);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(1.5f, -10.5f, 0));
    }

    // entered dungeon 10
    if ((m_game_state.player->get_position().x >= 11 && m_game_state.player->get_position().x <= 13) && (m_game_state.player->get_position().y <= -16.5 && m_game_state.player->get_position().y >= -18.5)) {
        m_game_state.nextScene = 12;
        m_game_state.player->set_scene_id(12);
        m_game_state.player->m_position.x = 4.5f;
        m_game_state.player->m_position.y = -7.0f;
        m_game_state.player->set_new_position(glm::vec3(10.5f, -17.5f, 0));
    }


}
void Main::Render(ShaderProgram *g_shader_program) {
    bool all_keys_collected = (m_game_state.player->get_num_of_dun_cleared() >= 10);
        g_shader_program->set_all_keys_collected(all_keys_collected);
    
    
    m_game_state.map->Render(g_shader_program);
    m_game_state.player->Render(g_shader_program);
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        m_game_state.enemies[i].Render(g_shader_program);
    }
}
