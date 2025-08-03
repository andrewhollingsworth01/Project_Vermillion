#pragma once

#include "raylib.h"
#include <cmath>

class PlayerController
{
public:
	Vector2 position;

	PlayerController(Vector2 startingPosition, float Speed, float DeadZone);
	void update();

private:
	float speed;
	float deadZone;

	void HandleKeyboardInput();
	void HandleControllerInput();
};