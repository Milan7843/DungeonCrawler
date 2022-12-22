#include "TileMapCreator.h"

void TileMapCreator::createTileSets()
{
	std::vector<Tile> tiles
	{
		// Tile for top left
		TileSet::createTile(
			'g',
			glm::ivec2(0,2),
			'~','-','~',
			'-',    '+',
			'~','+','+'
		),

		// Tile for top middle
		TileSet::createTile(
			'g',
			glm::ivec2(1,2),
			'~','-','~',
			'+',    '+',
			'~','+','~'
		),

		// Tile for top right
		TileSet::createTile(
			'g',
			glm::ivec2(2,2),
			'~','-','~',
			'+',    '-',
			'~','+','~'
		),

		// Tile for middle right
		TileSet::createTile(
			'g',
			glm::ivec2(2,1),
			'~','+','~',
			'+',    '-',
			'~','+','~'
		),

		// Tile for bottom right
		TileSet::createTile(
			'g',
			glm::ivec2(2,0),
			'~','+','~',
			'+',    '-',
			'~','-','~'
		),

		// Tile for bottom middle
		TileSet::createTile(
			'g',
			glm::ivec2(1,0),
			'~','+','~',
			'+',    '+',
			'~','-','~'
		),

		// Tile for bottom left
		TileSet::createTile(
			'g',
			glm::ivec2(0,0),
			'~','+','~',
			'-',    '+',
			'~','-','~'
		),

		// Tile for middle left
		TileSet::createTile(
			'g',
			glm::ivec2(0,1),
			'~','+','~',
			'-',    '+',
			'~','+','~'
		),

		// Tile for full middle
		TileSet::createTile(
			'g',
			glm::ivec2(1,1),
			'~','~','~',
			'~',    '~',
			'~','~','~'
		),

		// Tile for animated water
		TileSet::createTile(
			'w',
			std::vector<glm::ivec2> { glm::ivec2(3,2), glm::ivec2(4,2), glm::ivec2(5,2) },
			'~','~','~',
			'~',    '~',
			'~','~','~',
			0,
			MultipleTextureIndexUsage::ANIMATION,
			0.5f,
			true
		)
	};

	TileSet::create(tiles, "ground", 1.0f);

	// Dungeon tileset
	std::vector<Tile> dungeonTiles {

		/* ====== CORNER WALL PIECES ====== */

		// Bottom left corner for top of walls
		TileSet::createTile(
			't', // t for top
			glm::ivec2(0,1),
			'-','-','-',
			'+',    '-',
			'~','+','-'
		),
		// Bottom right corner for top of walls
		TileSet::createTile(
			't', // t for top
			glm::ivec2(1,1),
			'-','-','-',
			'-',    '+',
			'-','+','~'
		),
		// Top left corner for top of walls
		TileSet::createTile(
			't', // t for top
			glm::ivec2(0, 2),
			'~','+','-',
			'+',    '-',
			'-','-','-'
		),
		// Top right corner for top of walls
		TileSet::createTile(
			't', // t for top
			glm::ivec2(1,2),
			'-','+','~',
			'-',    '+',
			'-','-','-'
		),

		/* ====== MAIN WALL PIECES ====== */

		// Top left corner for top of walls
		TileSet::createTile(
			't', // t for top
			glm::ivec2(1,2),
			'-','-','-',
			'-',    '+',
			'-','+','-'
		),
	};
}
