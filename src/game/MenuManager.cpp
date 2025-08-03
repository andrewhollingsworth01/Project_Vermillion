#include "MenuManager.h"

MenuState MenuManager::currentMenu = MenuState::MAINMENU;

int MenuManager::selectedButton = 0;
const int MenuManager::buttonCount = 2;

Rectangle MenuManager::buttons[2] = {
    { 1280 / 2.0f - 100, 720 / 2 - 75, 200, 50 },
    { 1280 / 2.0f - 100, 720 / 2, 200, 50 }
};

// Timing value for stick input timing
float MenuManager::stickCooldown = 0.2f;
float MenuManager::stickTimer = 0.0f;

void MenuManager::SetMenu(MenuState menu)
{
	currentMenu = menu;
}

MenuState MenuManager::GetCurrentMenu()
{
	return currentMenu;
}

bool MenuManager::IsMenuOpen()
{
	if (currentMenu == MenuState::NONE)
	{
		return false;
	}
	return true;
}

void MenuManager::UpadateMenu()
{
    float delta = GetFrameTime();
    stickTimer -= delta;

    // -------- LEFT STICK NAVIGATION --------
    float stickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    if (stickTimer <= 0.0f)
    {
        if (stickY > 0.5f) // Down
        {
            selectedButton = (selectedButton + 1) % buttonCount;
            stickTimer = stickCooldown;
        }
        else if (stickY < -0.5f) // Up
        {
            selectedButton = (selectedButton - 1 + buttonCount) % buttonCount;
            stickTimer = stickCooldown;
        }
    }

    // -------- D-PAD OR KEYBOARD NAVIGATION --------
    if (IsKeyPressed(KEY_S) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
        selectedButton = (selectedButton + 1) % buttonCount;

    if (IsKeyPressed(KEY_W) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP))
        selectedButton = (selectedButton - 1 + buttonCount) % buttonCount;

    // -------- MOUSE HOVER --------
    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < buttonCount; i++)
    {
        if (CheckCollisionPointRec(mousePos, buttons[i]))
        {
            selectedButton = i;
        }
    }

    // -------- SELECT --------
    bool selectPressed =
        IsKeyPressed(KEY_ENTER) ||
        IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || // A ON XBOX CONTORLLER
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (selectPressed)
    {
        switch (selectedButton)
        {
        case 0: GameState::SetStatus(GameStatus::GAMEPLAY); break;
        
        // ADD OTHER MENU FEATURES HERE

        case 1: GameState::SetStatus(GameStatus::EXIT); break;
        }
    }
}

void MenuManager::DrawMainMenu()
{
	MenuRenderer::DrawMainMenu(selectedButton);
}
