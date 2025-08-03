#include "MenuRenderer.h"

namespace MenuRenderer
{
    // FIGURE OUT HOW TO DYNAMICAL LINK SCREEN RESOLUTION
    Rectangle MainMenuButton[] = {
        { 1280 / 2.0f - 100, 720 / 2 - 75, 200, 50 },
        { 1280 / 2.0f - 100, 720 / 2, 200, 50 }
    };

    void DrawMainMenu(int selectedButton)
    {
        DrawText("Project Vermillion", 720 / 2 + MeasureText("Project Vermillion", 40) / 2 - 75, 150, 40, WHITE);


        const char* buttonTexts[] = { "Play Game", "Exit" };

        // FIGURE OUT HOW TO DYNAMICALLY GET THE SIZE OF BUTTON ARRAYS
        for (int i = 0; i < 2; i++)
        {
            Color buttonColor = (i == selectedButton) ? LIGHTGRAY : GRAY;
            DrawRectangleRec(MainMenuButton[i], buttonColor);
            DrawText(
                buttonTexts[i],
                (int)(MainMenuButton[i].x + 20),
                (int)(MainMenuButton[i].y + 10),
                20,
                BLACK);
        }
    }
}