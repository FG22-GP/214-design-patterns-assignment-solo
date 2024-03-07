#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "block.h"
#include "structs.h"
#include "renderer.h"

class Renderer;

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
    void OnRender();
    void OnInput(const SDL_KeyboardEvent input);

    void SetRenderer(Renderer* renderer) { Renderer = renderer; }

    Block* GetRandomBlock();
    bool CanBlockMoveDown();
    bool CanBlockMoveHorizontally(const bool moveLeft);
    bool CanBlockRotate(const bool clockwise);

    void DestoryFullRows(int &rowsCleared);
    int GetScore(const int rowsCleared);

private:
    Renderer* Renderer = {};

    SDL_Color Grid[COLOUMNS][ROWS] = {};
    const SDL_Color GridColor = { 128, 128, 128, 255 };

    bool IsGamePaused = false;
    bool DrawGhostBlock = true;

    float TimeElapsed = 0.0f;
    float TimeElapsedSinceLastDrop = 0.0f;
    float InititalTimeInSecondsToDrop = 1.0f;
    float TimeInSecondsToDrop = 1.0f;
    int LinesCleared = 0;
    int LinesClearedAtLevel = 0;
    int Score = 0;
    int HighScore = 0;
    int Level = 0;
    const int RowsClearedToAdvanceToNextLevel = 10;
    float LastTimeRotated = 0.0f;
    const float RotationDelay = 0.2f;

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
