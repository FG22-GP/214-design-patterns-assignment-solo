// Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "tetris.h"
#include "renderer.h"

int main(int argc, char* args[])
{
	Renderer* renderer = new Renderer();
	if (renderer->Initialize() == EXIT_FAILURE)
	{
		// Pause so it doesn't close before you can read what went wrong
		system("pause");
		return -1;
	}

	Tetris* tetris = new Tetris();
	tetris->Initialize();
	tetris->SetRenderer(renderer);
	tetris->RegisterObserver(renderer);

	SDL_Event e; bool quit = false;
	Uint64 currentTick = SDL_GetTicks64();
	Uint64 previousTick = 0;
	float deltaTime = 0.0f;

	// While the user doesn't want to quit
	while (quit == false)
	{
		// Loop through all pending events from Windows (OS)
		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_QUIT) 
			{
				quit = true;
				break;
			}

			tetris->OnInput(e.key);
		}

		// Launching the game with a debugger and setting breakpoints breaks this. Otherwise it works fine
		previousTick = currentTick;
		currentTick = SDL_GetTicks64();
		deltaTime = (static_cast<float>(currentTick) - previousTick) / 1000;

		tetris->Tick(deltaTime);
		renderer->Render(tetris);

		// Run the game in 24 fps, no need to have it use over 50% cpu and gpu with 0 delay
		SDL_Delay(1000 / 24);
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}