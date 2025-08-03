#include "GameRenderer.h"

// namespace used because there are no objects in this class
namespace GameRenderer
{
    void GameRenderer::RenderTileMap(Texture2D Tileset, int TileSize, const std::vector<std::vector<int>>& WorldMap, float scale)
    {
        // gets the amount of columns in the tileset
        int tilesetColumns = Tileset.width / TileSize;

        // gets the number of vertical and horizontial tiles needed
        int TilesetVertical = WorldMap.size();
        int TilesetHorizontal = WorldMap[0].size();

        // runs through the number of rows in the tile set
        for (int y = 0; y < TilesetVertical; y++) {
            // runs through each tile
            for (int x = 0; x < TilesetHorizontal; x++)
            {
                // sets the tile needed in the tile set
                int tileIndex = WorldMap[y][x];

                // Position of the tile
                int tileX = (tileIndex % tilesetColumns) * TileSize;
                int tileY = (tileIndex / tilesetColumns) * TileSize;

                // creates the objects needed to put the tiles on screen
                Rectangle sourceRec = { (float)tileX, (float)tileY, (float)TileSize, (float)TileSize };
                Rectangle destRec = {
                    (float)(x * TileSize * scale),
                    (float)(y * TileSize * scale),
                    (float)TileSize * scale,
                    (float)TileSize * scale
                };
                Vector2 origin = { 0, 0 };

                // function to put the title on screen 
                DrawTexturePro(Tileset, sourceRec, destRec, origin, 0.0f, WHITE);
            }
        }

    }

    void GameRenderer::RenderCharacterTileMap(Texture2D Tileset, Vector2 CharacterSize, Vector2 SpawnPoint, int PlayerTileIndex, float Scale)
    {
        // creates the objects needed to put the tiles on screen
        // sourceRec Needs to be fixed
        // Note: Might need more info on the tile map to fix
        Rectangle sourceRec = { (float)PlayerTileIndex, (float)0, (float)CharacterSize.x, (float)CharacterSize.y };
        Rectangle destRec =
        { SpawnPoint.x,
            SpawnPoint.y,
            (float)CharacterSize.x * Scale,
            (float)CharacterSize.y * Scale
        };

        // function to put the title on screen 
        DrawTexturePro(Tileset, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
    }
}