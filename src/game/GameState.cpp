#include "gamestate.h"

GameStatus GameState::Status = GameStatus::MENU;

void GameState::SetStatus(GameStatus status)
{
	Status = status;
}

GameStatus GameState::getStatus()
{
	return Status;
}

bool GameState::isPaused()
{
	if (Status != GameStatus::MENU) 
	{
		return false;
	}
	return true;
}
