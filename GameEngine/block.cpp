#include "block.h"
#include "tetris.h"

void Block::Rotate(bool rotateClockwise)
{
    if (rotateClockwise)
    {
        CurrentRotation = (CurrentRotation + 1) % NUM_ROTATIONS;
    }
    else
    {
        CurrentRotation--;
        if (CurrentRotation < 0) 
        {
            CurrentRotation = NUM_ROTATIONS - 1;
        }
    }
}

bool Block::IsAnyBlockOutOfBounds()
{
    for (int i = 0; i < NUM_BLOCKS; i++)
    {
        auto position = GetBlockPosition(i);
        if (position.X < 0 || position.X >= Tetris::COLOUMNS || position.Y >= Tetris::ROWS)
        {
            return true;
        }
    }

    return false;
}

Coordinate Block::GetBlockPosition(int index)
{
    return Coordinate 
    (
        Position.X + LocalCoordinate[CurrentRotation][index].X - 1,
        Position.Y + LocalCoordinate[CurrentRotation][index].Y - 1
    );
}
