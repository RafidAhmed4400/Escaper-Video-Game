#pragma once
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
#include "Map.h"

enum EntityType {PLAYER, PLATFORM, ENEMY};
enum AnimationDirection { LEFT, RIGHT, UP, DOWN };


enum AIType {WAITANDGO, GUARD, WALKER};
enum AIState {IDLE, WALKING, TURNING};

class Entity {
public:
    glm::vec3 m_position;
    glm::vec3 m_movement;
    int *m_animation_indices = NULL;
private:
    
    float m_walk_speed = 1.0f;  
    int m_direction = 1;
    
    EntityType m_entity_type;
    AIType m_ai_type;
    AIState m_ai_state;
    glm::vec3 m_acceleration;
    glm::vec3 m_velocity;
    glm::vec3 m_scale;
    int m_walking[4][4];
    glm::vec3 newPosition;
    float m_width = 1;
    float m_height = 1;
    float m_speed;
    float m_jumping_power;
    float m_animation_time = 0.0f;
    GLuint m_texture_id;
    glm::mat4 m_model_matrix;
    int m_animation_frames = 0;
    int m_animation_index = 0;
    int m_animation_cols = 0;
    int m_animation_rows = 0;
    bool m_collided_top    = false;
    bool m_collided_bottom = false;
    bool m_collided_left   = false;
    bool m_collided_right  = false;
    int num_lives;
    bool is_active = true;
    int numDungeonsCleared = 0;
    int scene_num = -1;
    bool resetLocation = false;
public:
    static constexpr int SECONDS_PER_FRAME = 4;

    Entity();
    Entity(GLuint texture_id, float speed, glm::vec3 acceleration, float jump_power, int walking[4][4], float animation_time,
        int animation_frames, int animation_index, int animation_cols,
           int animation_rows, float width, float height, EntityType EntityType);
    Entity(GLuint texture_id, float speed, float width, float height, EntityType EntityType);
    Entity(GLuint texture_id, float speed, float width, float height, EntityType EntityType, AIType AIType, AIState AIState);
    
    bool CheckCollision(Entity *other);
    void CheckCollisionsY(Entity *objects, int objectsCount);
    void CheckCollisionsX(Entity *objects, int objectsCount);
    void CheckEnemyCollided(Entity *enemies, int enemyCount);
    void CheckPit(Entity *platforms, int platformCount);
    void CheckCollisionsX(Map *map);
    void CheckCollisionsY(Map *map);
    
    void Update(float delta_time, Entity *player, Entity *collidable_entities, int collidable_entity_count, Map *map);
    void Render(ShaderProgram *g_shader_program);
    void draw_sprite_from_texture_atlas(ShaderProgram* g_shader_program, GLuint texture_id, int index);

    void ai_activate(Entity *player, Map *map);
    void AIWalker(Map *map);
    void AIWaitAndGo(Entity *player);
    
    void normalise_movement() { m_movement = glm::normalize(m_movement); }
    


    
    const void set_position(glm::vec3 pos) {m_position = pos;}
    
    glm::vec3 get_new_position() const {return newPosition;}
    const void set_new_position(glm::vec3 pos) {newPosition = pos;}
    
    int get_num_of_dun_cleared() const {return numDungeonsCleared;}
    const void set_num_of_dun_cleared(int num) {numDungeonsCleared = num;}
    
    const void set_scene_id(int num) {scene_num = num;}
    
    void activate()                             { is_active = true;  };
    void deactivate()                           { is_active = false; };
        EntityType const get_entity_type()    const { return m_entity_type;   };
    AIType     const get_ai_type()        const { return m_ai_type;       };
    AIState    const get_ai_state()       const { return m_ai_state;      };
    float const get_jumping_power()       const { return m_jumping_power; }
    glm::vec3 const get_position()        const { return m_position; }

    glm::vec3 const get_velocity()        const { return m_velocity; }
    glm::vec3 const get_acceleration()    const { return m_acceleration; }
    glm::vec3 const get_movement()        const { return m_movement; }
    glm::vec3 const get_scale()           const { return m_scale; }
    GLuint    const get_texture_id()      const { return m_texture_id; }
    float     const get_speed()           const { return m_speed; }

    bool      const get_collided_top()    const { return m_collided_top; }
    bool      const get_collided_bottom() const { return m_collided_bottom; }
    bool      const get_collided_right()  const { return m_collided_right; }
    bool      const get_collided_left()   const { return m_collided_left; }
    int       const get_num_of_dun()        const { return numDungeonsCleared; }
    bool      const get_activity_status() const { return is_active; }
    int       const get_scene_id()        const { return scene_num; }
    bool      const get_reset_location() const {return resetLocation;}
    int       const get_num_lives()     const {return num_lives;}
    bool       const get_reset()     const {return resetLocation;}

    
    
    void const set_entity_type(EntityType new_entity_type)  { m_entity_type = new_entity_type;};
    void const set_ai_type(AIType new_ai_type){ m_ai_type = new_ai_type;};
    void const set_ai_state(AIState new_state){ m_ai_state = new_state;};
    void const set_velocity(glm::vec3 new_velocity) { m_velocity = new_velocity; }
    void const set_acceleration(glm::vec3 new_acceleration) { m_acceleration = new_acceleration; }
    void const set_movement(glm::vec3 new_movement) { m_movement = new_movement; }
    void const set_scale(glm::vec3 new_scale) { m_scale = new_scale; }
    void const set_texture_id(GLuint new_texture_id) { m_texture_id = new_texture_id; }
    void const set_height(float num){m_height = num;}
    void const set_width(float num){m_width = num;}
    void const set_speed(float new_speed) { m_speed = new_speed; }
    void const set_animation_cols(int new_cols) { m_animation_cols = new_cols; }
    void const set_animation_rows(int new_rows) { m_animation_rows = new_rows; }
    void const set_animation_frames(int new_frames) { m_animation_frames = new_frames; }
    void const set_animation_index(int new_index) { m_animation_index = new_index; }
    void const set_animation_time(float new_time) { m_animation_time = new_time; }
    void const set_reset(bool new_res) { resetLocation = new_res; }
    void const set_num_lives(int num) { num_lives = num; }

    

    
    
    
    
    void set_walking(int walking[4][4])
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                m_walking[i][j] = walking[i][j];
            }
        }
    }
    
    
};
