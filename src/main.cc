#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#define GRID_CELL_SIZE 36
#define GRID_WIDTH 29
#define GRID_HEIGHT 23
#define MOVE_SPEED 0.01f
#define UPDATES_PER_SECOND 100

#undef main
int main(int argc, char* argv[]) {
	srand(time(NULL));
	int window_width = (GRID_WIDTH * GRID_CELL_SIZE) + 1;
	int window_height = (GRID_HEIGHT * GRID_CELL_SIZE) + 1;

	SDL_Rect antInstance = {
		(GRID_WIDTH - 1) / 2 * GRID_CELL_SIZE,
		(GRID_HEIGHT - 1) / 2 * GRID_CELL_SIZE,
		GRID_CELL_SIZE,
		GRID_CELL_SIZE,
	};

	SDL_Color grid_background = {27, 33, 70, 255}; 
	SDL_Color grid_line_color = {13, 12, 25, 255}; 

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL video: %s\n", SDL_GetError());
		return -2;
	}

	SDL_Window* window = SDL_CreateWindow("AntPixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_OPENGL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	bool quit = false;

	while (!quit){
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a);
		for (int x = 0; x < 1 + GRID_WIDTH * GRID_CELL_SIZE; x += GRID_CELL_SIZE) {
			SDL_RenderDrawLine(renderer, x, 0, x, window_height);
		}

		for (int y = 0; y < 1 + GRID_HEIGHT * GRID_CELL_SIZE; y += GRID_CELL_SIZE) {
			SDL_RenderDrawLine(renderer, 0, y, window_width, y);
		}

		SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g, grid_line_color.b, grid_line_color.a);
		SDL_RenderFillRect(renderer, &antInstance);
		
		SDL_RenderPresent(renderer);
	}
		
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}