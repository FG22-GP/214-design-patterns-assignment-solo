#pragma once
#include <SDL.h>
#include "structs.h"

class Block
{
protected:
    static const int NUM_ROTATIONS = 4;
    static const int NUM_BLOCKS = 4;
    int CurrentRotation = 0;

public:
    SDL_Color Color = {};
    Vec2Int Position = { 4, 0 };
    Vec2Int LocalCoordinate[NUM_ROTATIONS][NUM_BLOCKS] = {};

    // Empty constructor
    Block() {};

    // Copy constructor
    Block(const Block& other)
    {
        Color = other.Color;
        Position = other.Position;

        for (int i = 0; i < NUM_ROTATIONS; i++)
        {
            for (int j = 0; j < NUM_BLOCKS; j++)
            {
                LocalCoordinate[i][j] = other.LocalCoordinate[i][j];
            }
        }
    }

    void Rotate(bool rotateClockwise);
    bool IsAnyBlockOutOfBounds();
    Vec2Int GetBlockPosition(int index);
};

class IBlock : public Block
{
public:
    IBlock()
    {
        Color = { 0, 255, 255, 128 };

        // First dimension is the rotation index
        // Second dimension is the block index with its position
        LocalCoordinate[0][0] = { 0, 1 };
        LocalCoordinate[0][1] = { 1, 1 };
        LocalCoordinate[0][2] = { 2, 1 };
        LocalCoordinate[0][3] = { 3, 1 };

        LocalCoordinate[1][0] = { 2, 0 };
        LocalCoordinate[1][1] = { 2, 1 };
        LocalCoordinate[1][2] = { 2, 2 };
        LocalCoordinate[1][3] = { 2, 3 };

        LocalCoordinate[2][0] = { 0, 2 };
        LocalCoordinate[2][1] = { 1, 2 };
        LocalCoordinate[2][2] = { 2, 2 };
        LocalCoordinate[2][3] = { 3, 2 };

        LocalCoordinate[3][0] = { 1, 0 };
        LocalCoordinate[3][1] = { 1, 1 };
        LocalCoordinate[3][2] = { 1, 2 };
        LocalCoordinate[3][3] = { 1, 3 };
    };
};

class JBlock : public Block
{
public:
    JBlock()
    {
        Color = { 0, 0, 255, 128 };

        LocalCoordinate[0][0] = { 1, 1 };
        LocalCoordinate[0][1] = { 1, 2 };
        LocalCoordinate[0][2] = { 2, 2 };
        LocalCoordinate[0][3] = { 3, 2 };

        LocalCoordinate[1][0] = { 1, 1 };
        LocalCoordinate[1][1] = { 2, 1 };
        LocalCoordinate[1][2] = { 1, 2 };
        LocalCoordinate[1][3] = { 1, 3 };

        LocalCoordinate[2][0] = { 1, 1 };
        LocalCoordinate[2][1] = { 2, 1 };
        LocalCoordinate[2][2] = { 3, 1 };
        LocalCoordinate[2][3] = { 3, 2 };

        LocalCoordinate[3][0] = { 1, 3 };
        LocalCoordinate[3][1] = { 2, 1 };
        LocalCoordinate[3][2] = { 2, 2 };
        LocalCoordinate[3][3] = { 2, 3 };
    };
};

class LBlock : public Block
{
public:
    LBlock()
    {
        Color = { 255, 170, 0, 128 };

        LocalCoordinate[0][0] = { 3, 1 };
        LocalCoordinate[0][1] = { 1, 2 };
        LocalCoordinate[0][2] = { 2, 2 };
        LocalCoordinate[0][3] = { 3, 2 };

        LocalCoordinate[1][0] = { 2, 1 };
        LocalCoordinate[1][1] = { 2, 2 };
        LocalCoordinate[1][2] = { 2, 3 };
        LocalCoordinate[1][3] = { 3, 3 };

        LocalCoordinate[2][0] = { 1, 2 };
        LocalCoordinate[2][1] = { 2, 2 };
        LocalCoordinate[2][2] = { 3, 2 };
        LocalCoordinate[2][3] = { 1, 3 };

        LocalCoordinate[3][0] = { 1, 1 };
        LocalCoordinate[3][1] = { 2, 1 };
        LocalCoordinate[3][2] = { 2, 2 };
        LocalCoordinate[3][3] = { 2, 3 };
    };
};

class OBlock : public Block
{
public:
    OBlock()
    {
        Color = { 255, 255, 0, 128 };

        for (int i = 0; i < NUM_BLOCKS; i++)
        {
            LocalCoordinate[i][0] = { 1, 1 };
            LocalCoordinate[i][1] = { 1, 2 };
            LocalCoordinate[i][2] = { 2, 1 };
            LocalCoordinate[i][3] = { 2, 2 };
        }
    };
};

class SBlock : public Block
{
public:
    SBlock()
    {
        Color = { 0, 255, 0, 128 };

        LocalCoordinate[0][0] = { 2, 1 };
        LocalCoordinate[0][1] = { 3, 1 };
        LocalCoordinate[0][2] = { 1, 2 };
        LocalCoordinate[0][3] = { 2, 2 };

        LocalCoordinate[1][0] = { 2, 1 };
        LocalCoordinate[1][1] = { 2, 2 };
        LocalCoordinate[1][2] = { 3, 2 };
        LocalCoordinate[1][3] = { 3, 3 };

        LocalCoordinate[2][0] = { 2, 2 };
        LocalCoordinate[2][1] = { 3, 2 };
        LocalCoordinate[2][2] = { 1, 3 };
        LocalCoordinate[2][3] = { 2, 3 };

        LocalCoordinate[3][0] = { 1, 1 };
        LocalCoordinate[3][1] = { 1, 2 };
        LocalCoordinate[3][2] = { 2, 2 };
        LocalCoordinate[3][3] = { 2, 3 };
    };
};

class TBlock : public Block
{
public:
    TBlock()
    {
        Color = { 153, 0, 255, 128 };

        LocalCoordinate[0][0] = { 2, 1 };
        LocalCoordinate[0][1] = { 1, 2 };
        LocalCoordinate[0][2] = { 2, 2 };
        LocalCoordinate[0][3] = { 3, 2 };

        LocalCoordinate[1][0] = { 2, 1 };
        LocalCoordinate[1][1] = { 2, 2 };
        LocalCoordinate[1][2] = { 3, 2 };
        LocalCoordinate[1][3] = { 2, 3 };

        LocalCoordinate[2][0] = { 1, 2 };
        LocalCoordinate[2][1] = { 2, 2 };
        LocalCoordinate[2][2] = { 3, 2 };
        LocalCoordinate[2][3] = { 2, 3 };

        LocalCoordinate[3][0] = { 2, 1 };
        LocalCoordinate[3][1] = { 1, 2 };
        LocalCoordinate[3][2] = { 2, 2 };
        LocalCoordinate[3][3] = { 2, 3 };
    };
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        Color = { 255, 0, 0, 128 };

        LocalCoordinate[0][0] = { 1, 1 };
        LocalCoordinate[0][1] = { 2, 1 };
        LocalCoordinate[0][2] = { 2, 2 };
        LocalCoordinate[0][3] = { 3, 2 };

        LocalCoordinate[1][0] = { 3, 1 };
        LocalCoordinate[1][1] = { 2, 2 };
        LocalCoordinate[1][2] = { 3, 2 };
        LocalCoordinate[1][3] = { 2, 3 };

        LocalCoordinate[2][0] = { 1, 2 };
        LocalCoordinate[2][1] = { 2, 2 };
        LocalCoordinate[2][2] = { 2, 3 };
        LocalCoordinate[2][3] = { 3, 3 };

        LocalCoordinate[3][0] = { 2, 1 };
        LocalCoordinate[3][1] = { 1, 2 };
        LocalCoordinate[3][2] = { 2, 2 };
        LocalCoordinate[3][3] = { 1, 3 };
    };
};