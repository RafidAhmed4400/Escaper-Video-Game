#include "Scene.h"

class Main : public Scene {
public:
    void Initialize(Entity *player) override;
    void Update(float delta_time) override;
    void Render(ShaderProgram *g_shader_program) override;
};
