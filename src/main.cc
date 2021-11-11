#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>	
#include <stdio.h>

#define GRID_WIDTH 900
#define GRID_HEIGHT 900

#define MOVE_SPEED 0.01f
#undef main

#define RGBA(col) col.r, col.b, col.b, col.a

static const SDL_Color ANT_COLOR = {255,255,255,255};
static const SDL_Color BG_COLOR = {27, 33, 70, 255};
static const SDL_Color GRID_COLOR = {13, 12, 50, 255};

static SDL_Window *window;
static SDL_Renderer *renderer;
static int cell_size;

static SDL_Rect ant_rect;

/* Clears the entire screen with BG_COLOR. */
static void draw_bg(void) {
	SDL_SetRenderDrawColor(renderer, RGBA(BG_COLOR));
        SDL_RenderClear(renderer);
}

static void draw_grid(void) {
        SDL_SetRenderDrawColor(renderer, RGBA(GRID_COLOR));

        for(unsigned int x = 0; x < GRID_WIDTH; x += cell_size) {
                SDL_RenderDrawLine(renderer, x, 0, x, GRID_HEIGHT);
        }

        for(unsigned int y = 0; y < GRID_HEIGHT; y += cell_size) {
                SDL_RenderDrawLine(renderer, 0, y, GRID_WIDTH, y);
        }
}

static void draw_ant(void) {
        SDL_SetRenderDrawColor(renderer, RGBA(ANT_COLOR));
        SDL_RenderFillRect(renderer, &ant_rect);
}

int main(int argc, char* argv[]) {
	std::cout << "Cell size? (recommended 15)" << std::endl;
	std::cin >> cell_size;

	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                std::cerr << "Failed to initialize SDL video: " << SDL_GetError();
		return -1;
	}

	window = SDL_CreateWindow("AntPixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	ant_rect = {
		(GRID_WIDTH + 1) / 2,
		(GRID_HEIGHT + 1) / 2,
		cell_size,
		cell_size,
	};

	bool quit = false;
        float t_start, t_end, dt;

	SDL_Event ev;
	while(!quit){
		t_start = SDL_GetPerformanceCounter();
		dt = (t_end - t_start) / SDL_GetPerformanceFrequency();	
                t_end = t_start;

		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}
		}


                draw_bg();
                draw_grid();		
                draw_ant();

		SDL_RenderPresent(renderer);
        }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
