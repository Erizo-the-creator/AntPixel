#include "game.h"

double start;
double end;
double counter = 0;
double dt;

Game::Game(){

    m_window = SDL_CreateWindow("AntPixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GRID_WIDTH, GRID_HEIGHT, SDL_WINDOW_OPENGL);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    m_ant_color = {255, 255, 255, 255};
    m_grid_background = {27, 33, 70, 255};
    m_grid_line_color = {13, 12, 50, 255};

    m_ant_instance.x = 0;
    m_ant_instance.y = (GRID_HEIGHT - cell_Size) / 2;
    m_ant_instance.w = cell_Size;
    m_ant_instance.h = cell_Size;
    
    m_grid_cell.x = GRID_WIDTH;
    m_grid_cell.y = GRID_HEIGHT;
    m_grid_cell.w = cell_Size;
    m_grid_cell.h = cell_Size;

    m_ant_color = {255, 255, 255, 255};
    m_grid_background = {27, 33, 70, 255};
    m_grid_line_color = {13, 12, 50, 255};
}

Game::~Game(){
    SDL_DestroyRenderer(m_renderer);    
    SDL_DestroyWindow(m_window);
}

void Game::loop(){
    bool quit = false;
    while (!quit){
    double start = SDL_GetPerformanceCounter();
        SDL_Event e;
        start = SDL_GetPerformanceCounter();
        while (SDL_PollEvent(&e)){
            switch (e.type){
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        update(1.0/60.0);
        draw();
        end = SDL_GetPerformanceCounter();
    }   
}

void Game::draw(){
    
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, m_grid_line_color.r, m_grid_line_color.g, m_grid_line_color.b, m_grid_line_color.a);
    for (int x = 0; x < GRID_WIDTH * cell_Size; x += cell_Size)
    {
        SDL_RenderDrawLine(m_renderer, x, 0, x, 900);
    }

    for (int y = 0; y < GRID_HEIGHT * cell_Size; y += cell_Size)
    {
        SDL_RenderDrawLine(m_renderer, 0, y, 900, y);
    }
    SDL_SetRenderDrawColor(m_renderer, m_ant_color.r, m_ant_color.g, m_ant_color.b, m_ant_color.a);
    SDL_RenderFillRect(m_renderer, &m_ant_instance);

    SDL_RenderPresent(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, m_grid_background.r, m_grid_background.g, m_grid_background.b, m_grid_background.a);
    SDL_RenderFillRect(m_renderer, &m_grid_cell);

    printf("dt: %f\n counter: %f \n", dt, counter);
}

void Game::update(double dt){
    
    //m_ant_instance.x += 1;
  
    dt = (end - start) / (double)SDL_GetPerformanceFrequency();
    counter += dt / 10;
}