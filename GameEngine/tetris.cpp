#include <stdio.h>
#include <ctime>
#include "tetris.h"
#include <SDL_ttf.h>
#include <string>
#include <format>

void Tetris::Initialize()
{
	// Add all the different blocks
	BlockTypes.push_back(new IBlock());
	BlockTypes.push_back(new JBlock());
	BlockTypes.push_back(new LBlock());
	BlockTypes.push_back(new OBlock());
	BlockTypes.push_back(new SBlock());
	BlockTypes.push_back(new TBlock());
	BlockTypes.push_back(new ZBlock());

	// Randomizes the seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Pick a random block and copy its data to the new active block
	CurrentActiveBlock = GetRandomBlock();
}

void Tetris::Restart()
{
	if (LinesCleared > LinesClearedHighScore)
	{
		LinesClearedHighScore = LinesCleared;
	}

	for (int col = 0; col < COLOUMNS; col++)
	{
		for (int row = 0; row < ROWS; row++)
		{
			Grid[col][row] = {};
		}
	}

	RandomBlocks.clear();
	CurrentActiveBlock = GetRandomBlock();

	MoveLeft = false;
	MoveRight = false;
	MoveDown = false;
	MoveDownHard = false;
	RotateClockwise = false;
	RotateCounterClockwise = false;

	TimeElapsedSinceLastDrop = 0.0f;
	TimeInSecondsToDrop = 1.0f;
	LinesCleared = 0;
}

void Tetris::Tick(const float deltaTime)
{
	if (IsGamePaused)
	{
		return;
	}

	TimeElapsedSinceLastDrop += deltaTime;

	if (TimeElapsedSinceLastDrop > TimeInSecondsToDrop || MoveDownHard || MoveDown)
	{
		TimeElapsedSinceLastDrop = 0.0f;
		MoveDown = false;

		// If we can move block down, move it down
		if (CanBlockMoveDown())
		{
			CurrentActiveBlock->Position.Y++;
		}
		else
		{
			// If we can't move it down, we either hit the bottom or another block
			for (int i = 0; i < NUM_BLOCKS; i++)
			{
				const auto position = CurrentActiveBlock->GetBlockPosition(i);
				Grid[position.X][position.Y] = CurrentActiveBlock->Color;
			}

			// The function is recursive and destroys full rows and increases the variable it got
			int rowsCleared = 0;
			DestoryFullRows(rowsCleared);

			LinesCleared += rowsCleared;
			MoveDownHard = false;
			CurrentActiveBlock = GetRandomBlock();

			// Checks if we have spawned on top of another block and restarts the game instantly if true
			for (int i = 0; i < NUM_BLOCKS; i++)
			{
				const auto position = CurrentActiveBlock->GetBlockPosition(i);
				if (Grid[position.X][position.Y].a != 0)
				{
					Restart();
					return;
				}
			}
		}
	}

	if (MoveLeft || MoveRight)
	{
		// Check if can move either directions. If we can't move it will be ignored
		if (CanBlockMoveHorizontally(MoveLeft))
		{
			CurrentActiveBlock->Position.X += (MoveLeft ? -1 : 1);
		}

		MoveLeft = false;
		MoveRight = false;
	}
	else if (RotateCounterClockwise || RotateClockwise)
	{
		// Same as checking horizontally move. If we can't rotate it will be ignored
		if (CanBlockRotate(RotateClockwise))
		{
			CurrentActiveBlock->Rotate(RotateClockwise);
		}

		RotateClockwise = false;
		RotateCounterClockwise = false;
	}
}

void Tetris::Render()
{
	// Draw the grid's vertical line
	for (int col = 0; col <= COLOUMNS; col++)
	{
		DrawLine(BLOCK_SIZE * col, 0, BLOCK_SIZE * col, BLOCK_SIZE * ROWS, GridColor);
	}

	// Draw the grid's horizontal line
	for (int row = 0; row <= ROWS; row++)
	{
		DrawLine(0, BLOCK_SIZE * row, BLOCK_SIZE * COLOUMNS, BLOCK_SIZE * row, GridColor);
	}

	// Draw the current block
	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		const auto position = CurrentActiveBlock->GetBlockPosition(i);
		DrawBlock(position.X, position.Y, CurrentActiveBlock->Color);
	}

	// Draw all blocks in the grid
	for (int col = 0; col < COLOUMNS; col++)
	{
		for (int row = 0; row < ROWS; row++)
		{
			if (Grid[col][row].a != 0)
			{
				DrawBlock(col, row, Grid[col][row]);
			}
		}
	}

	// Display the next 3 blocks to the right side
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < NUM_BLOCKS; j++)
		{
			const auto position = RandomBlocks[i]->GetBlockPosition(j);

			int x = COLOUMNS + position.X;
			int y = COLOUMNS + (i * NUM_BLOCKS) + position.Y;
			DrawBlock(x, y, RandomBlocks[i]->Color);
		}
	}
	
	static int x = COLOUMNS * BLOCK_SIZE + (BLOCK_SIZE * 3);
	if (IsGamePaused)
	{
		DrawText(x, BLOCK_SIZE * 1, "GAME PAUSED");
	}

	DrawText(x, BLOCK_SIZE * 3, std::format("Lines Cleared: {}", LinesCleared).c_str());
	DrawText(x, BLOCK_SIZE * 4, std::format("High Score: {}", LinesClearedHighScore).c_str());
}

void Tetris::OnInput(const SDL_KeyboardEvent input)
{
	if (input.type != SDL_KEYDOWN)
	{
		return;
	}

	if (input.repeat > 0)
	{
		return;
	}

	if (IsGamePaused)
	{
		if (input.keysym.sym == SDLK_p || input.keysym.sym == SDLK_ESCAPE)
		{
			IsGamePaused = false;
		}
		return;
	}

	switch (input.keysym.sym)
	{
		case SDLK_p:
		case SDLK_ESCAPE:
			IsGamePaused = true;
			break;
		case SDLK_r:
			Restart();
			break;
		case SDLK_x:
			RotateCounterClockwise = true;
			break;
		case SDLK_c:
			RotateClockwise = true;
			break;
		case SDLK_LEFT:
			MoveLeft = true;
			break;
		case SDLK_DOWN:
			MoveDown = true;
			break;
		case SDLK_RIGHT:
			MoveRight = true;
			break;
		case SDLK_SPACE:
			MoveDownHard = true;
			break;
		default:
			break;
	}
}

Block* Tetris::GetRandomBlock()
{
	if (RandomBlocks.size() < 4)
	{
		do
		{
			int randomIndex = std::rand() % BlockTypes.size();
			RandomBlocks.push_back(new Block(*BlockTypes[randomIndex]));
		} while (RandomBlocks.size() < 7);
	}
	
	auto newBlock = new Block(*RandomBlocks[0]);
	RandomBlocks.erase(RandomBlocks.begin());

	return newBlock;
}

bool Tetris::CanBlockMoveDown()
{
	CurrentActiveBlock->Position.Y++;
	if (CurrentActiveBlock->IsAnyBlockOutOfBounds())
	{
		CurrentActiveBlock->Position.Y--;
		return false;
	}

	CurrentActiveBlock->Position.Y--;

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		auto position = CurrentActiveBlock->GetBlockPosition(i);
		if (position.Y + 1 > ROWS)
		{
			return false;
		}

		if (Grid[position.X][position.Y + 1].a != 0)
		{
			return false;
		}
	}

	return true;
}

bool Tetris::CanBlockMoveHorizontally(const bool moveLeft)
{
	int direction = moveLeft ? -1 : 1;

	// Change X position in the direction we're going to check
	CurrentActiveBlock->Position.X += direction;
	if (CurrentActiveBlock->IsAnyBlockOutOfBounds())
	{
		// Out of bounds, undo the x position change
		CurrentActiveBlock->Position.X += direction > 0 ? -1 : 1;
		return false;
	}

	// Undo move here instead of doing it if it's going to be false
	CurrentActiveBlock->Position.X += direction > 0 ? -1 : 1;

	// Check each block if we can do the move
	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		auto position = CurrentActiveBlock->GetBlockPosition(i);
		if (position.X + direction > COLOUMNS || position.X + direction < 0)
		{
			return false;
		}

		if (Grid[position.X + direction][position.Y].a != 0)
		{
			return false;
		}
	}

	return true;
}

bool Tetris::CanBlockRotate(const bool clockwise)
{
	CurrentActiveBlock->Rotate(clockwise);
	if (CurrentActiveBlock->IsAnyBlockOutOfBounds())
	{
		CurrentActiveBlock->Rotate(!clockwise);
		return false;
	}

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		auto position = CurrentActiveBlock->GetBlockPosition(i);
		if (Grid[position.X][position.Y].a != 0)
		{
			CurrentActiveBlock->Rotate(!clockwise);
			return false;
		}
	}

	CurrentActiveBlock->Rotate(!clockwise);
	return true;
}

void Tetris::DestoryFullRows(int &rowsCleared)
{
	for (int row = ROWS - 1; row >= 0; row--)
	{
		int amountOfBlocksFound = 0;
		for (int col = 0; col < COLOUMNS; col++)
		{
			if (Grid[col][row].a != 0)
			{
				amountOfBlocksFound++;
			}
		}

		if (amountOfBlocksFound == 0)
		{
			return;
		}

		if (amountOfBlocksFound == COLOUMNS)
		{
			rowsCleared++;

			// Clear current row
			for (int i = 0; i < COLOUMNS; i++)
			{
				Grid[i][row] = {};
			}

			// Move down all blocks above current row
			for (int i = row; i > 0; i--)
			{
				for (int j = 0; j < COLOUMNS; j++)
				{
					Grid[j][i] = Grid[j][i - 1];
					Grid[j][i - 1] = {};
				}
			}

			DestoryFullRows(rowsCleared);
		}
	}
}

void Tetris::DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
}

void Tetris::DrawRectangle(const int x, const int y, const int width, const int height, const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { x, y, width, height };
	SDL_RenderDrawRect(Renderer, &rect);
}

void Tetris::DrawFilledRectangle(const int x, const int y, const int width, const int height, const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_Rect rect = { x, y, width, height };
	SDL_RenderFillRect(Renderer, &rect);
}

void Tetris::DrawBlock(const int x, const int y, const SDL_Color color)
{
	DrawFilledRectangle(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, color);
}

void Tetris::DrawText(const int x, const int y, const char* text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(Font, text, { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);
	SDL_Rect rect = { x, y, surface->w, surface->h };

	SDL_RenderCopy(Renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}