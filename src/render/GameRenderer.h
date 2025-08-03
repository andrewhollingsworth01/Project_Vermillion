#pragma once

#include "raylib.h"
#include <vector>

using namespace std;

namespace GameRenderer
{
	void RenderTileMap(Texture2D tileset, int tileSize, const std::vector<std::vector<int>>& WorldMap, float scale);

	void RenderCharacterTileMap(Texture2D Tileset, Vector2 CharacterSize, Vector2 SpawnPoint, int PlayerTileIndex, float Scale);
};