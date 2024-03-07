#include "renderer.h"
#include "tetris.h"

int Renderer::Initialize()
{
	// Initialize SDL_ttf for font loading
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

	// Start up SDL and create window
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	// Create Window and Renderer
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &Window, &Renderer);
	if (!Window)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // Make the scaled rendering look smoother
	SDL_RenderSetLogicalSize(Renderer, 1024, 768);
	SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);

	// Load font
	Font = TTF_OpenFont(FontPath.c_str(), FontSize);
	if (Font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

	SDL_SetWindowTitle(Window, "Tetris");
	return EXIT_SUCCESS;
}

void Renderer::Render(Tetris* tetris)
{
	// Clear the screen
	SDL_SetRenderDrawColor(Renderer, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
	SDL_RenderClear(Renderer);

	tetris->OnRender();

	// Present screen (switch buffers)
	SDL_RenderPresent(Renderer);
}

void Renderer::DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
}

void Renderer::DrawRectangle(const int x, const int y, const int width, const int height, const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { x, y, width, height };
	SDL_RenderDrawRect(Renderer, &rect);
}

void Renderer::DrawFilledRectangle(const int x, const int y, const int width, const int height, const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { x, y, width, height };
	SDL_RenderFillRect(Renderer, &rect);
}

void Renderer::DrawBlock(const int x, const int y, const SDL_Color color)
{
	DrawFilledRectangle(x * Tetris::BLOCK_SIZE, y * Tetris::BLOCK_SIZE, Tetris::BLOCK_SIZE, Tetris::BLOCK_SIZE, color);
}

void Renderer::DrawText(const int x, const int y, const char* text)
{
	SDL_Surface* surface = TTF_RenderText_Shaded(Font, text, { 255, 255, 255 }, { 0, 0, 0 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);
	SDL_Rect rect = { x, y, surface->w, surface->h };

	SDL_RenderCopy(Renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
