#include "AntPixel_common.h"

int cell_Size;
int main(int argc, char* argv[]) {
	Game game;
	
	std::cout << "Cell size? (recommended 5)" << std::endl;
	std::cin >> cell_Size;

	game.loop();
	
	SDL_Quit();

	return 0;
}