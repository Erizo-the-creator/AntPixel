#include <SDL2/SDL.h>
#pragma once
class Game{

public:
    Game();
    ~Game();

    void loop();
    void update(double dt);
    void draw();

private:
    SDL_Window* m_window;
    SDL_Event e; 
    SDL_Renderer* m_renderer; 
   
    SDL_Rect m_ant_instance;
    SDL_Rect m_grid_cell;

    SDL_Color m_ant_color; 
    SDL_Color m_grid_background;
    SDL_Color m_grid_line_color;
};