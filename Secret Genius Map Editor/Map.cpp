#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Map.h"
#include "Tile.h"
#include "Artist.h"
#include "Menus.h"
#include "Object.h"
#include "Spawn.h"
#include "Controller.h"
#include "Editor.h"


int Map::mapSizeX = 10, Map::mapSizeY = 10;
int cameraPosX = 0, cameraPosY = 0;
float cameraZoom = 1;

int Editor::selectedCharID = -1;




//The maps tiles
std::vector<std::vector<Tile::tileVariant*>> currentMapTiles;
//the maps objects
std::vector<std::vector<Object::objectVariant*>> currentMapObjects;

Map::pos Map::getGridPosUnderMouse()
{
	Map::pos returnPos;

	int scale = 60 * cameraZoom;

	returnPos.x = (Controller::mouseX + cameraPosX) / scale;
	returnPos.y = (Controller::mouseY + cameraPosY) / scale;

	return returnPos;
}

Spawn::spawn Map::getCharUnderMouse()
{
	

	for (int a = 0; Spawn::friendlySpawns.size() > a; a++)
	{
		if (Spawn::friendlySpawns[a].x == getGridPosUnderMouse().x && Spawn::friendlySpawns[a].y == getGridPosUnderMouse().y)
		{
			return Spawn::friendlySpawns[a];
		}
	}

	//return Spawn::none;
}

Tile::tile Map::getTileUnderMouse()
{
	if (getGridPosUnderMouse().x >= 0 && getGridPosUnderMouse().x < mapSizeX && getGridPosUnderMouse().y >= 0 && getGridPosUnderMouse().y < mapSizeY)
		return *currentMapTiles[getGridPosUnderMouse().x][getGridPosUnderMouse().y]->tileType;

	return Tile::tileList[0];
}

void Map::setTileUnderMouse(int x, int y, Tile::tileVariant* tile)
{
	if (x >= 0 && x < mapSizeX && y >= 0 && y < mapSizeY)
		currentMapTiles[x][y] = tile;
}

Object::object Map::getObjectUnderMouse()
{
	if (getGridPosUnderMouse().x >= 0 && getGridPosUnderMouse().x < mapSizeX && getGridPosUnderMouse().y >= 0 && getGridPosUnderMouse().y < mapSizeY)
		return *currentMapObjects[getGridPosUnderMouse().x][getGridPosUnderMouse().y]->objectType;

	return Object::objectList[0];
}

void Map::setObjectUnderMouse(int x, int y, Object::objectVariant* obj)
{
	if (x >= 0 && x < mapSizeX && y >= 0 && y < mapSizeY)
		currentMapObjects[x][y] = obj;
}

int Map::getCharIDUnderMouse()
{
	for (int a = 0; Spawn::friendlySpawns.size() > a; a++)
	{
		if (Spawn::friendlySpawns[a].x == getGridPosUnderMouse().x && Spawn::friendlySpawns[a].y == getGridPosUnderMouse().y)
		{
			return a;
		}
	}

	return -1;
}

int Map::getEnemyCharIDUnderMouse()
{
	for (int a = 0; Spawn::enemySpawns.size() > a; a++)
	{
		if (Spawn::enemySpawns[a].x == getGridPosUnderMouse().x && Spawn::enemySpawns[a].y == getGridPosUnderMouse().y)
		{
			return a;
		}
	}

	return -1;
}

bool Map::isSpaceWalkable(int x, int y)
{
	bool walkable = true;
	if (!currentMapTiles[x][y]->tileType->walkable)
		walkable = false;
	if (!currentMapObjects[x][y]->objectType->walkable)
		walkable = false;
	for (int a = 0; Spawn::friendlySpawns.size() > a; a++)
	{
		if (Spawn::friendlySpawns[a].x == x && Spawn::friendlySpawns[a].y == y)
		{
			walkable = false;
		}
	}
	return walkable;
}

void drawTileSelection()
{
	Artist artist;
	int scale = 60 * cameraZoom;

	int moveOffset = clock() % 1500 / 150;
	if (moveOffset > 5)
	{
		moveOffset = 10 - moveOffset;
	}
	moveOffset = moveOffset * cameraZoom;

	int camOffsetX = cameraPosX % scale;
	int camOffsetY = cameraPosY % scale;

	int xPos = (Controller::mouseX + camOffsetX) / scale * scale;
	int yPos = (Controller::mouseY + camOffsetY) / scale * scale;

	artist.drawImage(xPos - moveOffset - camOffsetX, yPos - moveOffset - camOffsetY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece);
	artist.drawImage(xPos + 40 * cameraZoom + moveOffset - camOffsetX, yPos - moveOffset - camOffsetY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_HORIZONTAL);
	artist.drawImage(xPos - moveOffset - camOffsetX, yPos + 40 * cameraZoom + moveOffset - camOffsetY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_VERTICAL);
	artist.drawImage(xPos + 40 * cameraZoom + moveOffset - camOffsetX, yPos + 40 * cameraZoom + moveOffset - camOffsetY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece, 180);
}

void drawCharSelection()
{
	if (Editor::selectedCharID == -1)
		return;

	Artist artist;
	int scale = 60 * cameraZoom;

	int moveOffset = clock() % 1500 / 150;
	if (moveOffset > 5)
	{
		moveOffset = 10 - moveOffset;
	}
	moveOffset = moveOffset * cameraZoom;

	int camOffsetX = cameraPosX % scale;
	int camOffsetY = cameraPosY % scale;

	int xPos = Spawn::friendlySpawns[Editor::selectedCharID].x * scale;
	int yPos = Spawn::friendlySpawns[Editor::selectedCharID].y * scale;

	SDL_SetTextureColorMod(Artist::gTileHoverPiece, 200, 200, 0);
	artist.drawImage(xPos - moveOffset - cameraPosX, yPos - moveOffset - cameraPosY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece);
	artist.drawImage(xPos + 40 * cameraZoom + moveOffset - cameraPosX, yPos - moveOffset - cameraPosY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_HORIZONTAL);
	artist.drawImage(xPos - moveOffset - cameraPosX, yPos + 40 * cameraZoom + moveOffset - cameraPosY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece, 0, NULL, SDL_FLIP_VERTICAL);
	artist.drawImage(xPos + 40 * cameraZoom + moveOffset - cameraPosX, yPos + 40 * cameraZoom + moveOffset - cameraPosY, 20 * cameraZoom, 20 * cameraZoom, Artist::gTileHoverPiece, 180);
	SDL_SetTextureColorMod(Artist::gTileHoverPiece, Artist::tileSelecterRGB.r, Artist::tileSelecterRGB.g, Artist::tileSelecterRGB.b);
}

void moveMapWithMouse()
{
	cameraPosX = -1 * (Controller::mouseX - Controller::lastMousePos.x) + cameraPosX;
	cameraPosY = -1 * (Controller::mouseY - Controller::lastMousePos.y) + cameraPosY;

	Controller::lastMousePos.x = Controller::mouseX;
	Controller::lastMousePos.y = Controller::mouseY;
}

void drawTiles()
{
	Spawn spawn;
	Artist artist;
	//make sure we are culling extra tiles
	int maxDistX = 33, maxDistY = 19;
	if (cameraZoom == 2.0)
	{
		maxDistX = 17;
		maxDistY = 10;
	}
	if (cameraZoom == .5)
	{
		maxDistX = 65;
		maxDistY = 37;
	}
	for (int x = 0; x <= maxDistX; x++)
	{
		for (int y = 0; y <= maxDistY; y++)
		{
			int offsetX, offsetY, camOffsetX, camOffsetY;
			offsetX = int (cameraPosX / (60 * cameraZoom)) + x - 1;
			offsetY = int (cameraPosY / (60 * cameraZoom)) + y - 1;
			camOffsetX = cameraPosX % int(60 * cameraZoom);
			camOffsetY = cameraPosY % int(60 * cameraZoom);
			if (offsetX < Map::mapSizeX && offsetX >= 0 && offsetY < Map::mapSizeY && offsetY >= 0)
			{
				currentMapTiles[offsetX][offsetY]->draw(x * (60 * cameraZoom) - camOffsetX - 60 * cameraZoom, y * (60 * cameraZoom) - camOffsetY - 60 * cameraZoom, 60 * cameraZoom, 60 * cameraZoom);

				//draw players here and make a class for players, enemys and a general struct for chars holding what team they are on 2
				for (int a = 0; Spawn::friendlySpawns.size() > a; a++)
				{
					if (Spawn::friendlySpawns[a].x == offsetX && Spawn::friendlySpawns[a].y == offsetY)
						Spawn::friendlySpawns[a].draw(x * (60 * cameraZoom) - camOffsetX - 5 * cameraZoom - 60 * cameraZoom, y * (60 * cameraZoom) - camOffsetY - 5 * cameraZoom - 60 * cameraZoom, 70 * cameraZoom, 70 * cameraZoom, a);

					spawn.makeSpawnsRed();
					if (Spawn::enemySpawns[a].x == offsetX && Spawn::enemySpawns[a].y == offsetY)
						Spawn::enemySpawns[a].draw(x * (60 * cameraZoom) - camOffsetX - 5 * cameraZoom - 60 * cameraZoom, y * (60 * cameraZoom) - camOffsetY - 5 * cameraZoom - 60 * cameraZoom, 70 * cameraZoom, 70 * cameraZoom, a);
					spawn.makeSpawnsWhite();
				}
				

				currentMapObjects[offsetX][offsetY]->draw(x * (60 * cameraZoom) - camOffsetX - 5 * cameraZoom - 60 * cameraZoom, y * (60 * cameraZoom) - camOffsetY - 5 * cameraZoom - 60 * cameraZoom, 70 * cameraZoom, 70 * cameraZoom);
			}
			else
				artist.drawImage(x * (60 * cameraZoom) - camOffsetX - 60 * cameraZoom, y * (60 * cameraZoom) - camOffsetY - 60 * cameraZoom, 60 * cameraZoom, 60 * cameraZoom, Artist::gTire);

		}
	}
	drawTileSelection();
	drawCharSelection();
}

void Map::updateMapSize()
{
	currentMapTiles.resize(mapSizeX);
	for (int i = 0; i < mapSizeX; i++)
		currentMapTiles[i].resize(mapSizeY);

	currentMapObjects.resize(mapSizeX);
	for (int i = 0; i < mapSizeX; i++)
		currentMapObjects[i].resize(mapSizeY);
}

void Map::resetMap()
{
	for (int y = 0; y <= mapSizeY - 1; y++)
	{
		for (int x = 0; x <= mapSizeX - 1; x++)
		{
			currentMapTiles[x][y] = &Tile::tileVariantList[0 + rand() % 4];
			currentMapObjects[x][y] = &Object::objectVariantList[0 + rand() % 4];
		}
	}
}

void Map::saveMap(std::string mapName)
{
	std::ofstream myFile;
	myFile.open("Resource/maps/" + mapName + ".SGM");
	if (myFile.is_open())
	{
		//myFile << 2;
		
		int counter = 1;


		if (counter == 1)
		{
			myFile << mapSizeX;
			myFile << " ";
			myFile << mapSizeY;
			myFile << "\n";

			counter++;
		}
		if (counter == 2)
		{
			myFile << Spawn::friendlySpawns.size();
			myFile << "\n";

			counter++;
		}
		if (counter == 3)
		{
			for (int a = 0; a < Spawn::friendlySpawns.size(); a++)
			{
				myFile << Spawn::friendlySpawns[a].x;
				myFile << " ";
				myFile << Spawn::friendlySpawns[a].y;
				myFile << " ";
			}
			myFile << "\n";
			
			counter++;
		}
		if (counter == 4)
		{
			for (int a = 0; a < Spawn::enemySpawns.size(); a++)
			{
				myFile << Spawn::enemySpawns[a].x;
				myFile << " ";
				myFile << Spawn::enemySpawns[a].y;
				myFile << " ";
			}
			myFile << "\n";

			counter++;
		}
		if (counter == 5)
		{
			for (int y = 0; y <= mapSizeY - 1; y++)
			{
				for (int x = 0; x <= mapSizeX - 1; x++)
				{
					for (int i = 0; i < Tile::tileList.size(); i++)
					{
						if (currentMapTiles[x][y]->tileType->name == Tile::tileList[i].name)
						{
							myFile << i;
							break;
						}
					}
					myFile << " ";
					myFile << currentMapTiles[x][y]->textureID;
					myFile << " ";
				}
				myFile << "\n";
			}
			counter++;
		}
		if (counter == 6)
		{
			for (int y = 0; y <= mapSizeY - 1; y++)
			{
				for (int x = 0; x <= mapSizeX - 1; x++)
				{
					for (int i = 0; i < Object::objectList.size(); i++)
					{
						if (currentMapObjects[x][y]->objectType->name == Object::objectList[i].name)
						{
							myFile << i;
							break;
						}
					}
					myFile << " ";
					myFile << currentMapObjects[x][y]->textureID;
					myFile << " ";
				}
				myFile << "\n";
			}
			counter++;
		};

		myFile.close();
	}
	else
	{
		printf("Unable to save File\n");
	}
}

void Map::loadMap(std::string mapName)
{
	
	
	std::ifstream myFile;
	myFile.open("Resource/maps/" + mapName + ".SGM");
	//myFile.open("Resource/maps/map.SGM");
	if (myFile.is_open())
	{
		std::string dataS;
		int dataI = 1;
		int counter = 1;

		
		if (counter == 1)
			{
				getline(myFile, dataS);
				std::istringstream iss(dataS);
				std::string subS;

				iss >> subS;
				dataI = std::stoi(subS);
				mapSizeX = dataI;
				//printf("Map X: %i \n", mapSizeX);

				iss >> subS;
				dataI = std::stoi(subS);
				mapSizeY = dataI;
				//printf("Map Y: %i \n", mapSizeY);

				updateMapSize();
				resetMap();

				counter++;
			}
		if (counter == 2)
		{
			getline(myFile, dataS);
			dataI = std::stoi(dataS);

			
			Spawn::friendlySpawns.resize(dataI);
			//printf("Friendly team size: %i\n", Spawn::friendlySpawns.size());

			
			Spawn::enemySpawns.resize(dataI);
			//printf("Enemy team size: %i\n", Spawn::friendlySpawns.size());


			counter++;
		}
		if (counter == 3)
			{
				getline(myFile, dataS);
				std::istringstream iss(dataS);
				std::string subS;

				for (int a = 0; a < Spawn::friendlySpawns.size(); a++)
				{
					
					iss >> subS;
					dataI = std::stoi(subS);
					Spawn::friendlySpawns[a].x = dataI;
					//printf("Player%i", a);
					//printf("Spawn X: %i ", dataI);

					iss >> subS;
					dataI = std::stoi(subS);
					Spawn::friendlySpawns[a].y = dataI;
					//printf("Spawn Y: %i \n", dataI);
				}
				counter++;
			}
		if (counter == 4)
			{
			getline(myFile, dataS);
			std::istringstream iss(dataS);
			std::string subS;

			for (int a = 0; a < Spawn::enemySpawns.size(); a++)
			{

				iss >> subS;
				dataI = std::stoi(subS);
				Spawn::enemySpawns[a].x = dataI;
				//printf("Enemy%i", a);
				//printf("Spawn X: %i ", dataI);

				iss >> subS;
				dataI = std::stoi(subS);
				Spawn::enemySpawns[a].y = dataI;
				//printf("Spawn Y: %i \n", dataI);
			}
			counter++;
			}
		if (counter == 5)
			{
				std::string subS;
				for (int y = 0; y <= mapSizeY - 1; y++)
				{
					getline(myFile, dataS);
					std::istringstream iss(dataS);
					for (int x = 0; x <= mapSizeX - 1; x++)
					{
						iss >> subS;
						int tileType = std::stoi(subS);
						iss >> subS;
						dataI = std::stoi(subS);
						//printf("Type: %i Variant %i \n", tileType, dataI);
						currentMapTiles[x][y] = &Tile::tileVariantList[tileType * 4 + dataI];
					}
				}
				counter++;
			}
		if (counter == 6)
		{
			std::string subS;
			for (int y = 0; y <= mapSizeY - 1; y++)
			{
				getline(myFile, dataS);
				std::istringstream iss(dataS);
				for (int x = 0; x <= mapSizeX - 1; x++)
				{
					iss >> subS;
					int objectType = std::stoi(subS);
					iss >> subS;
					dataI = std::stoi(subS);
					//printf("Type: %i Variant %i \n", tileType, dataI);
					currentMapObjects[x][y] = &Object::objectVariantList[objectType * 4 + dataI];
				}
			}
			counter++;

		};
		myFile.close();
	}
	else
	{
		printf("Unable to open File\n");
	}

}



void Map::controlMap(int input)
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_NONE:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		break;
	case Menus::GAME_STATE_IN_EDITOR:
		//Left Mouse Click
		if (input == 1)
		{
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}

		//Right Mouse Click
		if (input == 2)
		{
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			}
		}

		//Middle Mouse Click
		if (input == 4)
		{
			Controller::lastMousePos.x = Controller::mouseX;
			Controller::lastMousePos.y = Controller::mouseY;
				
			
		}

		//Keyboard Input
		if (input == 3)
		{
			//KEYBOARD
			const Uint8 *state = SDL_GetKeyboardState(NULL);

			if (state[SDL_SCANCODE_A])
			{
				cameraPosX -= 10;
			}
			if (state[SDL_SCANCODE_D])
			{
				cameraPosX += 10;
			}
			if (state[SDL_SCANCODE_W])
			{
				cameraPosY -= 10;
			}
			if (state[SDL_SCANCODE_S])
			{
				cameraPosY += 10;
			}
			if (state[SDL_SCANCODE_Z])
			{
				if (cameraZoom == .5)
				{
					cameraZoom = 2;
				}
				else if (cameraZoom == 2)
				{
					cameraZoom = 1;
				}
				else if (cameraZoom == 1)
				{
					cameraZoom = .5;
				}
			}

			switch (Menus::gameIndex)
			{
			case 0:
				
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}

		//Middle clicke dragged
		if (input == 14)
		{
			moveMapWithMouse();
		}
		break;
	}
}

void Map::drawMap()
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_NONE:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		break;
	case Menus::GAME_STATE_IN_EDITOR:
		drawTiles();
		break;
	}
}