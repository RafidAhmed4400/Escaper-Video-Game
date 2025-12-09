#include "Scene.h"
 
class Dungeon : public Scene {
    unsigned int dungeon_data[100] =
    {
        181,134, 134, 134, 134, 134, 134,134 , 135
        , 182,
        181, 0, 0, 0, 0, 0, 0, 0, 0, 182,
        181, 0, 0, 0, 209, 209, 0, 0, 0, 182,
        181, 0, 0, 0, 0, 0, 0, 0, 0, 182,
        181, 0, 0, 0, 0, 0, 0, 0, 0, 182,
        181, 0, 0, 0, 0, 0, 0, 0, 0, 182,
        181, 0, 0, 0, 0, 0, 0, 0, 0, 182,
        181, 0, 0, 0, 0, 0, 0, 0, 0, 182,
        181, 0, 0, 0, 0, 0, 0, 0, 0, 182,
        181, 133, 134, 135, 243, 243, 133,134 , 135, 182
    };
public:
    void Initialize(Entity *player) override;
    void Update(float delta_time) override;
    void Render(ShaderProgram *g_shader_program) override;

};
  
