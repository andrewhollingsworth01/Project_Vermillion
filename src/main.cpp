// main.cpp : Defines the entry point for the application.
#include <iostream>
#include <vector>

#include "raylib.h"

#include "render/GameRenderer.h"
#include "render/MenuRenderer.h"
#include "game/PlayerController.h"
#include "game/GameState.h"
#include "game/MenuManager.h"
#include "Trackers/PerformanceTracking.h"


using namespace std;

// sets the size of the tiles in the tileset
const int tileSize = 16;

// sets the number of tiles vertically and horizontailly
const int tileset_Horizontal = 12;
const int tileset_Vertical = 11;

float tileScale = 2.0f;

Vector2 characterSize = { 66, 106 };

Vector2 playerPosition = { 0, 0 };
float playerSpeed = 2;
float deadZone = 0.1f;

// Test world map 
// numbers store the position of each tile needed
const std::vector<std::vector<int>> worldMap = {
    { 0, 0, 1, 1, 0, 0, 2, 2, 2, 0 },
    { 0, 1, 1, 0, 0, 2, 2, 1, 2, 0 },
    { 1, 1, 0, 0, 2, 2, 1, 1, 2, 0 },
    { 1, 0, 0, 2, 2, 1, 1, 0, 2, 0 },
    { 0, 0, 2, 2, 1, 1, 0, 0, 2, 0 },
    { 0, 2, 2, 1, 1, 0, 0, 1, 2, 0 },
    { 2, 2, 1, 1, 0, 0, 1, 1, 0, 0 },
    { 2, 1, 1, 0, 0, 1, 1, 0, 0, 0 }
};

// Sets the window Width and Height
int screenWidth = 1280;
int screenHeight = 720;

int main()
{
    ShowCursor();

    // Initialization
    // Initializes the window:
    InitWindow(screenWidth, screenHeight, "Project Vermillion");

    // load your assets
    Texture2D tileset = LoadTexture("assets/tilemap_packed.png");
    Texture2D characterTileset = LoadTexture("assets/placeholder_main_character_temp.png");

    // int tilesetColumns = (tileset_Horizontal * tileSize) / tileSize;

    // Sets the frame rate of the game to 60 frames-per-second
    SetTargetFPS(180);

    // Game State varible
    GameState currentState;
    // Menu Manager varible
    MenuManager currentMenu;
    // Performance Tracker Varible
    PerformanceTracking perf;

    // setting up player controller
    PlayerController player = PlayerController::PlayerController(playerPosition, playerSpeed, deadZone);

    // Proformance Tracking bool varible
    bool showStats = false;
    // Proformance Tracking size varibles 
    int x = 10;
    int y = 10;

    // Main game loop
	// Runs until exit button is pressed
	// Exits when the 'x' button on the window is pressed (needs to be added)
    // WindowShouldClose() = Detect window close button or ESC key (Needs to be re written)
    while (currentState.getStatus() != GameStatus::EXIT)
    {

        // Update
        // gets the positoion of the mouse for menus 
        Vector2 mousePoint = GetMousePosition();

        // checks if 'TAB' key is pressed
        if (currentState.getStatus() == GameStatus::GAMEPLAY)
        {
           
            // Press TAB to sends the User to the pause menu
            if (IsKeyPressed(KEY_TAB))
            {
                currentState.SetStatus(GameStatus::MENU);
				currentMenu.SetMenu(MenuState::PAUSEMENU);
            }

            // Press ESC to sends the User to the main menu
			// Will change when other menus are created
            if (IsKeyPressed(KEY_ESCAPE))
            {
                currentState.SetStatus(GameStatus::MENU);
				currentMenu.SetMenu(MenuState::MAINMENU);
			}

            if (IsGamepadAvailable(0))
            {
				// Press 'START' button to return to the menu
				// 15 is the 'START' button on an Xbox controller
				// 0 is the first connected gamepad
                if (IsGamepadButtonPressed(0, 15)) {
                    currentState.SetStatus(GameStatus::MENU);
                    currentMenu.SetMenu(MenuState::PAUSEMENU);
                }
				// Press 'Select' button to return to the main menu
				// 13 is the 'SELECT' button on an Xbox controller
				// 0 is the first connected gamepad
				// Will change when other menus are created
				if (IsGamepadButtonPressed(0, 13)) {
                    currentState.SetStatus(GameStatus::MENU);
                    currentMenu.SetMenu(MenuState::MAINMENU);
                }
            }

            player.update();

            perf.Update();
        }

        // Player Boundries
		// Keeps the player within the screen bounds
		// Curently for testing purposes will cange when world scrolling is added
        if (player.position.x < 0) player.position.x = 0;
        if (player.position.y < 0) player.position.y = 0;
        if (player.position.x + characterSize.x > screenWidth) player.position.x = screenWidth - characterSize.x;
        if (player.position.y + characterSize.y > screenHeight) player.position.y = screenHeight - characterSize.y;

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentState.getStatus() == GameStatus::MENU && currentMenu.GetCurrentMenu() == MenuState::MAINMENU)
        {
            MenuManager::UpadateMenu();
            MenuManager::DrawMainMenu();
            
        }

        if (currentState.getStatus() == GameStatus::MENU && currentMenu.GetCurrentMenu() == MenuState::PAUSEMENU)
        {
            MenuManager::UpadateMenu();
            MenuManager::DrawPauseMenu();
        }

        else if (currentState.getStatus() == GameStatus::GAMEPLAY)
        {
            // Renders the game world
            GameRenderer::RenderTileMap(tileset, tileSize, worldMap, tileScale);
			// Renders the player character
            GameRenderer::RenderCharacterTileMap(characterTileset, characterSize, player.position, 0, 1.0f);
        }

        // Proformance Tracking
        if (IsKeyPressed(KEY_F3)) showStats = !showStats;

        if (showStats) {
            perf.Draw(x, y);
        }


        // Clears the frame
        EndDrawing();
    }

    
    // De-Initialization
    // Unloading Texture
    UnloadTexture(tileset);
	UnloadTexture(characterTileset);

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}