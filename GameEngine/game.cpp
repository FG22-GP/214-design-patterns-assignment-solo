// Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "tetris.h"

// Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main(int argc, char* args[])
{
	SDL_Window* window = {};	// The window we'll be rendering to
	SDL_Renderer* renderer;		// The window's rendering surface

	// Initialize SDL_ttf for font loading
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	// Start up SDL and create window
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	// Create Window and Renderer
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
	if (!window)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // Make the scaled rendering look smoother
	SDL_RenderSetLogicalSize(renderer, 1024, 768);

	// Load font
	auto font = TTF_OpenFont("C:\\Windows\\Fonts\\verdana.ttf", 24);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return -1;
	}

	SDL_SetWindowTitle(window, "Tetris");

	Tetris* tetris = new Tetris();
	tetris->SetRenderer(renderer);
	tetris->SetFont(font);
	tetris->Initialize();

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

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		tetris->Render();

		// Present screen (switch buffers)
		SDL_RenderPresent(renderer);

		// Run the game in 24 fps, no need to have it use over 50% cpu and gpu with 0 delay
		SDL_Delay(1000 / 24);
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}