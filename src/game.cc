#include "game.h"
#include "AntPixel_common.h"
#define RGBA(c) c.r, c.g, c.b, c.a
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900
uint64_t now, last_frame;
bool quit = false;
float counter = 0;
float dt;
int cell_size = 5;
uint16_t GRID_WIDTH = 900, GRID_HEIGHT = 900;
float accumulator;
Game::Game(){
    srand(time(NULL));
    //std::cout << "Cell size? (recommended 5)" << std::endl;
    //std::cin >> cell_size;
    m_window = SDL_CreateWindow("AntPixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    m_ant_color = {255, 255, 255, 255};
    m_grid_background = {27, 33, 70, 255};
    m_grid_line_color = {13, 12, 50, 255};

    m_ant_instance.x = GRID_WIDTH / 3;
    m_ant_instance.y = GRID_HEIGHT / 2;
    m_ant_instance.w = cell_size;
    m_ant_instance.h = cell_size;
    
    m_grid_cell.x = GRID_WIDTH;
    m_grid_cell.y = GRID_HEIGHT;
    m_grid_cell.w = cell_size;
    m_grid_cell.h = cell_size;

    m_ant_color = {255, 255, 255, 255};
    m_grid_background = {27, 33, 70, 255};
    m_grid_line_color = {13, 12, 50, 255};
    
    loop();
}

Game::~Game(){
    SDL_DestroyRenderer(m_renderer);    
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::loop(){
    while (!quit){
        now = SDL_GetPerformanceCounter();
        dt = (float)(now - last_frame) / SDL_GetPerformanceCounter();
        last_frame = now;
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            switch (e.type){
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                }
                if(e.key.keysym.sym == SDLK_KP_PLUS){
                    cell_size++;
                }
                if(e.key.keysym.sym == SDLK_KP_MINUS){
                    cell_size--;
                }
                break;
            }
        }
        update();
        draw();
    }   
}

void Game::draw(){
    SDL_SetRenderDrawColor(m_renderer, RGBA(m_grid_background));
    
    SDL_RenderClear(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, RGBA(m_grid_line_color));
    for (int x = 0; x < GRID_WIDTH / cell_size; x++){
        float nx = x * cell_size;
        
        SDL_RenderDrawLine(m_renderer, nx, 0, nx, GRID_HEIGHT);
    }

    for (int y = 0; y < GRID_HEIGHT / cell_size; y++){
        float ny = y * cell_size;        
        
        SDL_RenderDrawLine(m_renderer, 0, ny, GRID_WIDTH, ny);
    }
   
    SDL_SetRenderDrawColor(m_renderer, RGBA(m_ant_color));
    SDL_RenderFillRect(m_renderer, &m_ant_instance);

    SDL_RenderPresent(m_renderer);
    printf("dt: %f \n", dt);
}

void Game::update(){
    m_ant_instance.w = cell_size;
    m_ant_instance.h = cell_size;
    
    int direction = rand() % 10;
    
    switch (direction){
    
    case 1: m_ant_instance.x += cell_size; break;
          
    case 2: m_ant_instance.x -= cell_size; break;
        
    case 3: m_ant_instance.y += cell_size; break;
    
    case 4: m_ant_instance.y -= cell_size; break;
    }
}