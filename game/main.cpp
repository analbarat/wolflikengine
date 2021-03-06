#include "render.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(sdl.window.width, sdl.window.height, SDL_WINDOW_SHOWN, &sdl.w, &sdl.r);

	//create a map and set a spawnpoint
	map_data = loadMap();
	player.setSpawnPoint(map_data);

	while (sdl.event.type != SDL_QUIT) { //main game loop
		/* TODO: game states, eg menu, map drawing etc*/
		SDL_PollEvent(&sdl.event);
		for (int x = 0; x < sdl.window.width; x++) { //rendering loop
			renderScene(x, map_data, sdl.window.width, sdl.window.height); //yup, its the whole rendering function
		}

		/* input handling*/

		if (sdl.event.type == SDL_KEYDOWN) {
			if (sdl.event.key.keysym.sym == SDLK_UP) { 
				player.moveFwd(); 
				if (player.isPlayerColliding(map_data)) player.moveRwd();
			}
			if (sdl.event.key.keysym.sym == SDLK_DOWN) {
				player.moveRwd();
				if (player.isPlayerColliding(map_data)) player.moveFwd();
			}
			if (sdl.event.key.keysym.sym == SDLK_PAGEDOWN) {
				player.moveRight();
				if (player.isPlayerColliding(map_data)) player.moveLeft();
			}
			if (sdl.event.key.keysym.sym == SDLK_DELETE) {
				player.moveLeft();
				if (player.isPlayerColliding(map_data)) player.moveRight();
			}
			if (sdl.event.key.keysym.sym == SDLK_LEFT)	player.angle -= 0.1;
			if (sdl.event.key.keysym.sym == SDLK_RIGHT) player.angle += 0.1; 
			if (sdl.event.key.keysym.sym == SDLK_SPACE) player.openCurrDoor();

		}
		SDL_RenderPresent(sdl.r);
	}

	SDL_Quit();
	return 0;
}