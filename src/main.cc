#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>	
#include <stdio.h>

#define GRID_CELL_SIZE cell_Size
#define GRID_WIDTH 900
#define GRID_HEIGHT 900

#define MOVE_SPEED 0.01f
#undef main

int main(int argc, char* argv[]) {
	std::cout << "Cell size? (recommended 15)" << std::endl;
	int cell_Size;
	std::cin >> cell_Size;
	srand(time(NULL));

	SDL_Rect antInstance = {
		(GRID_WIDTH + 1) / 2 ,
		(GRID_HEIGHT + 1) / 2 ,
		GRID_CELL_SIZE,
		GRID_CELL_SIZE,
	};
	SDL_Rect grid_cell = {
		(GRID_WIDTH - 1),
		(GRID_HEIGHT - 1),
		GRID_CELL_SIZE,
		GRID_CELL_SIZE,
	};

	SDL_Color ant_color = {255,255,255,255};
	SDL_Color grid_background = {27, 33, 70, 255};
	SDL_Color grid_line_color = {13, 12, 50, 255};

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL video: %s\n", SDL_GetError());
		return -2;
	}

	SDL_Window* window = SDL_CreateWindow("AntPixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	bool quit = false;
	
	float counter = 0;

	while(!quit){
		SDL_Event e;
		float start = SDL_GetPerformanceCounter();
		while (SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}
		}


		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g, grid_line_color.b, grid_line_color.a);
		for (int x = 0; x < GRID_WIDTH * GRID_CELL_SIZE; x += GRID_CELL_SIZE) {
			SDL_RenderDrawLine(renderer, x, 0, x, 900);
		}

		for (int y = 0; y < GRID_HEIGHT * GRID_CELL_SIZE; y += GRID_CELL_SIZE) {
			SDL_RenderDrawLine(renderer, 0, y, 900, y);
		}
		SDL_SetRenderDrawColor(renderer, ant_color.r, ant_color.g, ant_color.b, ant_color.a);
		SDL_RenderFillRect(renderer, &antInstance);
		
		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);
		SDL_RenderFillRect(renderer, &grid_cell);

		
		
		float end = SDL_GetPerformanceCounter();
		float dt = (end - start) / (float)SDL_GetPerformanceFrequency();	
		
		counter += dt / 10;
		//printf("dt: %f\n counter: %f \n",dt,counter);	
		}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
