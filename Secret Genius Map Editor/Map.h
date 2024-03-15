#pragma once
#ifndef string
#include <string>
#endif
#ifndef Character
#include "Spawn.h"
#endif
#ifndef Tile
#include "Tile.h"
#endif
#ifndef Object
#include "Object.h"
#endif
class Map {
public:

	struct pos {
		int x;
		int y;
	};

	static int mapSizeX, mapSizeY;

	static pos lastMousePos;

	void loadMap(std::string mapName);
	Map::pos getGridPosUnderMouse();
	Spawn::spawn getCharUnderMouse();
	int getCharIDUnderMouse();
	int getEnemyCharIDUnderMouse();
	bool isSpaceWalkable(int x, int y);
	Tile::tile getTileUnderMouse();
	void setTileUnderMouse(int x, int y, Tile::tileVariant* tile);
	Object::object getObjectUnderMouse();
	void setObjectUnderMouse(int x, int y, Object::objectVariant* obj);
	void updateMapSize();
	void resetMap();
	void saveMap(std::string mapName);
	void controlMap(int input);
	void drawMap();

};