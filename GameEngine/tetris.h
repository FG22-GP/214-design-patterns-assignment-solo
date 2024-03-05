#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "block.h"
#include "structs.h"

class Tetris
{
public:
    static const int COLOUMNS = 10;
    static const int ROWS = 20;
    static const int NUM_BLOCKS = 4;
    static const int BLOCK_SIZE = 32;

    void Initialize();
    void Restart();
    void Tick(const float deltaTime);
    void Render();
    void OnInput(const SDL_KeyboardEvent input);

    void SetRenderer(SDL_Renderer* renderer) { Renderer = renderer; }
    void SetFont(TTF_Font* font) { Font = font; }

    Block* GetRandomBlock();
    bool CanBlockMoveDown();
    bool CanBlockMoveHorizontally(const bool moveLeft);
    bool CanBlockRotate(const bool clockwise);
    void DestoryFullRows(int &rowsCleared);

    void DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color color);
    void DrawRectangle(const int x, const int y, const int width, const int height, const SDL_Color color);
    void DrawFilledRectangle(const int x, const int y, const int width, const int height, const SDL_Color color);
    void DrawBlock(const int x, const int y, const SDL_Color color);
    void DrawText(const int x, const int y, const char* text);

private:
    TTF_Font* Font = {};
    SDL_Renderer* Renderer = {};

    SDL_Color Grid[COLOUMNS][ROWS] = {};
    const SDL_Color GridColor = { 128, 128, 128, 255 };

    bool IsGamePaused = false;
    bool DrawGhostBlock = true;

    float TimeElapsedSinceLastDrop = 0.0f;
    float TimeInSecondsToDrop = 1.0f;
    int LinesCleared = 0;
    int LinesClearedHighScore = 0;

    Block* CurrentActiveBlock = {};
    std::vector<Block*> BlockTypes = {};    // Holds all block types (I, J, L, O, S, T, and Z)
    std::vector<Block*> RandomBlocks = {};  // Picks the first block from the list and adds more once there are less than 4 in the list

    // Input requests
    bool MoveLeft = false;
    bool MoveRight = false;
    bool MoveDown = false;
    bool MoveDownHard = false;
    bool RotateClockwise = false;
    bool RotateCounterClockwise = false;
};
