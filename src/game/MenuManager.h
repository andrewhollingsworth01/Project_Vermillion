#pragma once

#include "raylib.h"
#include "../render/MenuRenderer.h"

enum class MenuState
{
	NONE = 0,
	MAINMENU = 1,
	PAUSEMENU = 2
};

class MenuManager
{
public:
	static void SetMenu(MenuState menu);
	static MenuState GetCurrentMenu();
	static bool IsMenuOpen();
	static void UpadateMenu();
	static void DrawMainMenu();

private:
	static MenuState currentMenu;
	static int selectedButton;
	static const int buttonCount;
	static float stickCooldown;
	static float stickTimer;
	static Rectangle buttons[2];
};