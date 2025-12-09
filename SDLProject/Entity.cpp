#include "Entity.h"
#include <iostream>
#include <SDL_mixer.h>
using namespace std;

Mix_Chunk *death;

Entity::Entity()
{
    m_position = glm::vec3(0);
    m_movement = glm::vec3(0);
    m_acceleration = glm::vec3(0);
    m_velocity = glm::vec3(0);
    m_speed = 0;
    
    m_model_matrix = glm::mat4(1.0f);
}

bool Entity::CheckCollision(Entity *other) {
    if (get_activity_status() == false || other->get_activity_status() == false) return false;
    float xdist = fabs(m_position.x - other->m_position.x) - ((m_width + other->m_width) / 2.0f);
    float ydist = fabs(m_position.y - other->m_position.y) - ((m_height + other->m_height) / 2.0f);
    
    if (xdist < 0 && ydist < 0) return true;
    return false;
}

void Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
   for (int i = 0; i < objectCount; i++)
   {
       Entity *object = &objects[i];
       if (CheckCollision(object))
       {
           float ydist = fabs(m_position.y - object->m_position.y);
           float penetrationY = fabs(ydist - (m_height / 2.0f) - (object->m_height / 2.0f));
           if (m_velocity.y > 0) {
               m_position.y -= penetrationY;
               m_velocity.y = 0;
               m_collided_top = true;
               object->m_collided_bottom = true;
           }
           else if (m_velocity.y < 0) {
               m_position.y += penetrationY;
               m_velocity.y = 0;
               m_collided_bottom = true;
               object->m_collided_top = true;
} }
} }

void Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
   for (int i = 0; i < objectCount; i++)
   {
       Entity *object = &objects[i];
       if (CheckCollision(object))
       {
           float xdist = fabs(m_position.x - object->m_position.x);
           float penetrationX = fabs(xdist - (m_width / 2.0f) - (object->m_width / 2.0f));
           if (m_velocity.x > 0) {
               m_position.x -= penetrationX;
               m_velocity.x = 0;
               m_collided_right = true;
               object->m_collided_left = true;
           }
           else if (m_velocity.x < 0) {
               m_position.x += penetrationX;
               m_velocity.x = 0;
               m_collided_left = true;
               object->m_collided_right = true;
} }
} }

void Entity::CheckEnemyCollided(Entity *enemies, int enemyCount) {
    m_collided_left = false;
    m_collided_right = false;
    m_collided_top = false;
    m_collided_bottom = false;
    CheckCollisionsX(enemies, enemyCount);
    if (m_collided_left == true || m_collided_right == true) resetLocation = true;
    CheckCollisionsY(enemies, enemyCount);
    if (m_collided_top == true || m_collided_bottom == true) resetLocation = true;
    death = Mix_LoadWAV("bounce.wav");
    if (resetLocation) {
        Mix_PlayChannel(-1, death, 0);
    }
    
}

void Entity::CheckCollisionsY(Map *map)
{
    // Probes for tiles
    glm::vec3 top = glm::vec3(m_position.x, m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_left = glm::vec3(m_position.x - (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 top_right = glm::vec3(m_position.x + (m_width / 2), m_position.y + (m_height / 2), m_position.z);
    glm::vec3 bottom = glm::vec3(m_position.x, m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_left = glm::vec3(m_position.x - (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    glm::vec3 bottom_right = glm::vec3(m_position.x + (m_width / 2), m_position.y - (m_height / 2), m_position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    if (map->is_solid(top, &penetration_x, &penetration_y) && m_velocity.y > 0) {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_left, &penetration_x, &penetration_y) && m_velocity.y > 0) {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    else if (map->is_solid(top_right, &penetration_x, &penetration_y) && m_velocity.y > 0) {
        m_position.y -= penetration_y;
        m_velocity.y = 0;
        m_collided_top = true;
    }
    if (map->is_solid(bottom, &penetration_x, &penetration_y) && m_velocity.y < 0) {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_left, &penetration_x, &penetration_y) && m_velocity.y < 0) {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
    else if (map->is_solid(bottom_right, &penetration_x, &penetration_y) && m_velocity.y < 0) {
        m_position.y += penetration_y;
        m_velocity.y = 0;
        m_collided_bottom = true;
    }
}

void Entity::CheckCollisionsX(Map *map)
{
    // Probes for tiles
    glm::vec3 left = glm::vec3(m_position.x - (m_width / 2), m_position.y, m_position.z);
    glm::vec3 right = glm::vec3(m_position.x + (m_width / 2), m_position.y, m_position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    if (map->is_solid(left, &penetration_x, &penetration_y) && m_velocity.x < 0) {
        m_position.x += penetration_x;
        m_velocity.x = 0;
        m_collided_left = true;
}
    if (map->is_solid(right, &penetration_x, &penetration_y) && m_velocity.x > 0) {
        m_position.x -= penetration_x;
        m_velocity.x = 0;
        m_collided_right = true;
} }

void Entity::ai_activate(Entity *player, Map *map) {
    switch (m_ai_type) {
        case WAITANDGO:
            AIWaitAndGo(player);
            break;
        case GUARD:
 
            break;
        case WALKER:
            AIWalker(map);
            break;
    }
}

void Entity::AIWaitAndGo(Entity *player) {
    switch(m_ai_state) {
        case IDLE:
            if (glm::distance(m_position, player->m_position) < 3.0f) {
                m_ai_state = WALKING;
            }
            break;
            
        case WALKING:
            float x = 0;
            float y = 0;
            if (player->m_position.x < m_position.x) {
                x = -1;
            }
            else {
                x = 1;
            }
            if (player->m_position.y < m_position.y) {
                y = -1;
            }
            else {
                y = 1;
            }
            m_movement = glm::vec3(x, y, 0);
            break;
    }
}

void Entity::AIWalker(Map *map) {
    static float walk_distance = 0.0f;
    const float max_distance = 6.0f;
    

    if (walk_distance <= -max_distance) {
        m_movement = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else if (walk_distance >= max_distance) {
        m_movement = glm::vec3(-1.0f, 0.0f, 0.0f);
    }
    else if (glm::length(m_movement) < 0.1f) {
        m_movement = glm::vec3(-1.0f, 0.0f, 0.0f);
    }
    
    walk_distance += m_movement.x * m_speed * 0.016f;
    
}

void Entity::Update(float delta_time, Entity *player, Entity *objects, int objectCount, Map *map)
{
    if (get_activity_status() == false) {
        return;
    }
    m_collided_top = false;
    m_collided_bottom = false;
    m_collided_left = false;
    m_collided_right = false;
    
    if (m_entity_type == ENEMY) {
        ai_activate(player, map);
    }
    
    if (m_entity_type == ENEMY && m_ai_type == WALKER) {
            ai_activate(player, map);
        }
    
    if (m_animation_indices != NULL) {
        if (glm::length(m_movement) != 0) {
            m_animation_time += delta_time;

            if (m_animation_time >= 0.25f)
            {
                m_animation_time = 0.0f;
                m_animation_index++;
                if (m_animation_index >= m_animation_frames)
                {
                    m_animation_index = 0;
                }
            }
        } else {
            m_animation_index = 0;
        }
    }
    
    m_velocity.x = m_movement.x * m_speed;
    m_velocity.y = m_movement.y * m_speed;
    m_velocity += m_acceleration * delta_time;
    
    m_position.y += m_velocity.y * delta_time;
    CheckCollisionsY(map);
    
    m_position.x += m_velocity.x * delta_time;
    CheckCollisionsX(map);
    
    
    if(m_entity_type == PLAYER) {
        CheckEnemyCollided(objects, objectCount);
    }
    
    m_model_matrix = glm::mat4(1.0f);
    m_model_matrix = glm::translate(m_model_matrix, m_position);
}

void Entity::draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index)
{
    float u_coord = (float)(index % m_animation_cols) / (float)m_animation_cols;
    float v_coord = (float)(index / m_animation_cols) / (float)m_animation_rows;

    float width = 1.0f / (float)m_animation_cols;
    float height = 1.0f / (float)m_animation_rows;

    float tex_coords[] =
    {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };

    float vertices[] =
    {
        -0.5, -0.5, 0.5, -0.5,  0.5, 0.5,
        -0.5, -0.5, 0.5,  0.5, -0.5, 0.5
    };

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());

    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

void Entity::Render(ShaderProgram *g_shader_program) {
    if (get_activity_status() == false) {
        return;
    }
    
    g_shader_program->set_model_matrix(m_model_matrix);
    
    if (m_animation_indices != NULL) {
        draw_sprite_from_texture_atlas(g_shader_program, m_texture_id, m_animation_indices[m_animation_index]);
        return;
    }
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    
    glVertexAttribPointer(g_shader_program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(g_shader_program->get_position_attribute());
    
    glVertexAttribPointer(g_shader_program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(g_shader_program->get_position_attribute());
    glDisableVertexAttribArray(g_shader_program->get_tex_coordinate_attribute());
}
