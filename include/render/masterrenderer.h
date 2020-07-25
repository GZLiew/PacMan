#pragma once
#include <SDL.h>

namespace Render{
class MasterRenderer {
public:
    void draw_characters();
    void draw_hud();
    void draw_points();
    void draw_walls();
    void finish_render(SDL_Window &window);
private:
    
};
}