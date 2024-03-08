#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "tetris.h"
#include "observer.h"

class Tetris;

class Renderer : public Observer
{
public:
    /// <summary>Initializes SDL and TTF</summary>
    /// <returns>1 on failure, 0 on success</returns>
    int Initialize();
    void Render(Tetris* tetris);

    void DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color color);
    void DrawRectangle(const int x, const int y, const int width, const int height, const SDL_Color color);
    void DrawFilledRectangle(const int x, const int y, const int width, const int height, const SDL_Color color);
    void DrawBlock(const int x, const int y, const SDL_Color color);
    void DrawText(const int x, const int y, const char* text);

private:
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    SDL_Window* Window = {};
    SDL_Renderer* Renderer;

    SDL_Color BackgroundColor = { 0, 0, 0, 255 };
    std::vector<SDL_Color> BackgroundColors;

    TTF_Font* Font = {};
    std::string FontPath = "C:\\Windows\\Fonts\\verdana.ttf";
    uint8_t FontSize = 24;

    void OnNotify(uint8_t level);
    void SetupBackgroundColors();
};

