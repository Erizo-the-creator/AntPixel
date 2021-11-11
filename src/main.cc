#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>	
#include <stdio.h>

#define MOVE_SPEED 0.01f
#undef main

#define RGBA(col) col.r, col.b, col.b, col.a

#define DEF_WND_W 900
#define DEF_WND_H 900

static const SDL_Color ANT_COLOR = {255,255,255,255};
static const SDL_Color BG_COLOR = {27, 33, 70, 255};
static const SDL_Color GRID_COLOR = {13, 12, 50, 255};

static SDL_Window *window;
static SDL_Renderer *renderer;

static int cell_size;
static int wnd_w, wnd_h;

static SDL_Rect ant_rect;

/* Clears the entire screen with BG_COLOR. */
static void draw_bg(void) {
	SDL_SetRenderDrawColor(renderer, RGBA(BG_COLOR));
        SDL_RenderClear(renderer);
}

static void draw_grid(void) {
        SDL_SetRenderDrawColor(renderer, RGBA(GRID_COLOR));

        for(unsigned int x = 0; x < wnd_w; x += cell_size) {
                SDL_RenderDrawLine(renderer, x, 0, x, wnd_h);
        }

        for(unsigned int y = 0; y < wnd_h; y += cell_size) {
                SDL_RenderDrawLine(renderer, 0, y, wnd_w, y);
        }
}

static void draw_ant(void) {
        SDL_SetRenderDrawColor(renderer, RGBA(ANT_COLOR));
        SDL_RenderFillRect(renderer, &ant_rect);
}

int main(int argc, char **argv) {
	std::cout << "Cell size? (recommended 15)" << std::endl;
	std::cin >> cell_size;

	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                std::cerr << "Failed to initialize SDL video: " << SDL_GetError();
		return -1;
	}

	window = SDL_CreateWindow("AntPixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEF_WND_W, DEF_WND_H, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        wnd_w = DEF_WND_W;
        wnd_h = DEF_WND_H;

	ant_rect = {
		(DEF_WND_W + 1) / 2,
		(DEF_WND_H + 1) / 2,
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

                                case SDL_WINDOWEVENT:
                                        switch(ev.window.event) {
                                                case SDL_WINDOWEVENT_RESIZED:
                                                        wnd_w = ev.window.data1;
                                                        wnd_h = ev.window.data2;
                                                        break;
                                        }
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
