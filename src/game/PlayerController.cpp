#include "playercontroller.h"

PlayerController::PlayerController(Vector2 startingPosition, float Speed, float DeadZone)
{
	position = startingPosition;
	speed = Speed;
    deadZone = DeadZone;
}

void PlayerController::update()
{
    HandleKeyboardInput();
	HandleControllerInput();
}

void PlayerController::HandleKeyboardInput()
{
    if (IsKeyDown(KEY_W)) {
        position.y -= speed;
    }
    if (IsKeyDown(KEY_S)) {
        position.y += speed;
    }
    if (IsKeyDown(KEY_A)) {
        position.x -= speed;
    }
    if (IsKeyDown(KEY_D)) {
        position.x += speed;
    }
}

void PlayerController::HandleControllerInput()
{
    if (IsGamepadAvailable(0))
    {
        // Use the left stick (Axis LeftX and LeftY)
        float moveX = 0.0f;
        float moveY = 0.0f;

        // Controller input for left stick X-axis, similarly:
        float rawX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        // Controller input for left stick Y-axis
        float rawY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        
        if (fabs(rawY) > deadZone)
        {
            moveY = rawY;  // Apply deadzone
        }
        
        if (fabs(rawX) > deadZone)
        {
            moveX = rawX;  // Apply deadzone
        }

        // Boost stick input a bit
        // NEEDS TO BE FIXED 
        // ISSUE: Player is being moved with no input is detected
        position.x += moveX * speed * 2.0f;
        position.y += moveY * speed * 2.0f;
    }
}
