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
    // Runs until eiither the exit button is press or the 'x' button on the window or 'ESC' key is pressed
    // WindowShouldClose() = Detect window close button or ESC key (Needs to be re written)
    while (!WindowShouldClose() && currentState.getStatus() != GameStatus::EXIT)
    {

        // Update
        // gets the positoion of the mouse for menus 
        Vector2 mousePoint = GetMousePosition();

        if (IsGamepadAvailable(0))
        {
            const char* gamepadName = GetGamepadName(0);
            DrawText(TextFormat("Gamepad detected: %s", gamepadName), 10, 10, 20, DARKGREEN);
        }
        else
        {
            DrawText("No gamepad detected!", 10, 10, 20, RED);
        }

        // checks if 'TAB' key is pressed
        if (currentState.getStatus() == GameStatus::GAMEPLAY)
        {
           
            // Example: Press TAB to return to the menu
            if (IsKeyPressed(KEY_TAB))
            {
                currentState.SetStatus(GameStatus::MENU);
				currentMenu.SetMenu(MenuState::PAUSEMENU);
            }

            if (IsGamepadAvailable(0))
            {
                const char* gamepadName = GetGamepadName(0);
                if (IsGamepadButtonDown(0, 15)) {
                    currentState.SetStatus(GameStatus::MENU);
                    currentMenu.SetMenu(MenuState::PAUSEMENU);
                }
            }

            player.update();

            perf.Update();
        }

        // Player Boundries
        /*
        if (player.position.x < 0) player.position.x = 0;
        if (player.position.y < 0) player.position.y = 0;
        if (player.position.x + characterSize.x > GetScreenWidth()) player.position.x = GetScreenWidth() - characterSize.x;
        if (player.position.y + characterSize.y > GetScreenHeight()) player.position.y = GetScreenHeight() - characterSize.y;
        */

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
    // Close window and OpenGL context
    CloseWindow();

    return 0;
}