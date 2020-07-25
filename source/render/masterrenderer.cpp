#include <render/masterrenderer.h>

void Render::MasterRenderer::finish_render(SDL_Window* window) { SDL_UpdateWindowSurface(window); }

void Render::MasterRenderer::draw_characters() {}

void Render::MasterRenderer::draw_hud() {}

void Render::MasterRenderer::draw_points() {}

void Render::MasterRenderer::draw_walls() {}