#pragma once

enum class GameStatus
{
	EXIT = 0,
	MENU = 1,
	GAMEPLAY = 2,
	PAUSE = 3
};

class GameState
{
public:
	static void SetStatus(GameStatus status);
	static GameStatus getStatus();
	static bool isPaused();

private:
	static GameStatus Status;
};