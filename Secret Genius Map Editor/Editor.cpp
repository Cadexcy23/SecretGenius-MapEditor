#include <SDL.h>
#include "Editor.h"
#include "Menus.h"
#include "Spawn.h"
#include "Artist.h"
#include "Map.h"
#include "Controller.h"

int tilePageNumber = 0;
int objectPageNumber = 0;
int selectedTileID = 0;
int selectedObjectID = 0;
int displayTileID = 0;
int displayObjectID = 0;
int selectedSpawnTeam = 0;
int selectedSpawnNumber = 0;
int saveNumber = 1;
int loadNumber = 1;

void drawTab(int x, int y, std::string name)
{
	Artist artist;

	//start tab
	artist.drawImage(x, y, 6, 26, Artist::gTabCorner);
	//draw chunks behind letters
	int count = 0;
	while (count < name.length())
	{
		artist.drawImage(6 + x + count * 20, y, 20, 26, Artist::gTabChunk);
		count++;
	}
	artist.drawImage(6 + x + count * 20, y, 6, 26, Artist::gTabCorner, 0, NULL, SDL_FLIP_HORIZONTAL);

	artist.drawLetters(name, 6 + x, y + 4, Artist::smallFont);
}

void drawTilesInEditor()
{
	Artist artist;
	//draw backplates and if they are hovered/selected
	for (int i = 0; i < 11; i++)
	{
		if (Controller::mouseX >= 78 + 150 * i && Controller::mouseX <= 222 + 150 * i && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
		{
			if (i - 1 + tilePageNumber * 10 < Tile::tileList.size())
			{
				SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 150);
			}
		}
		if (i - 1 + tilePageNumber * 10 == selectedTileID)
		{
			SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 150, 150);
		}
		artist.drawImage(78 + 150 * i, 928, 144, 144, Artist::gHUDBackplate);
		SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 255);
	}
	//draw tiles and figure out what one is hovered
	for (int i = 0; i < 10; i++)
	{
		if (i + tilePageNumber * 10 < Tile::tileList.size())
		{
			if (Controller::mouseX >= 228 + 150 * i && Controller::mouseX <= 372 + 150 * i && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
			{
				displayTileID = i + tilePageNumber * 10;
			}
			artist.drawImage(240 + 150 * i, 940, 120, 120, Tile::tileList[i + tilePageNumber * 10].textureSet.variant1);
		}
	}
	//draw info
	artist.drawLetters(Tile::tileList[displayTileID].name, 80, 930, Artist::smallFont);
	if (Tile::tileList[displayTileID].walkable)
	{
		artist.drawLetters("true", 80, 951, Artist::smallFont);
	}
	else
	{
		artist.drawLetters("false", 80, 951, Artist::smallFont);
	}
	Tile::tileVariantList[displayTileID * 4].draw(162, 1012, 60, 60);
	displayTileID = selectedTileID;
	//draw up and down arrows
	if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(1748, 928, 50, 50, Artist::gArrow);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);
	if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(1748, 1022, 50, 50, Artist::gArrow, 0, 0, SDL_FLIP_VERTICAL);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);

	artist.drawLetters(std::to_string(tilePageNumber + 1), 1748, 990, Artist::smallFont);
}

void drawObjectsInEditor()
{
	Artist artist;
	//draw backplates and if they are hovered/selected
	for (int i = 0; i < 11; i++)
	{
		if (Controller::mouseX >= 78 + 150 * i && Controller::mouseX <= 222 + 150 * i && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
		{
			if (i - 1 + objectPageNumber * 10 < Object::objectList.size())
			{
				SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 150);
			}
		}
		if (i - 1 + objectPageNumber * 10 == selectedObjectID)
		{
			SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 150, 150);
		}
		artist.drawImage(78 + 150 * i, 928, 144, 144, Artist::gHUDBackplate);
		SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 255);
	}
	//draw tiles and figure out what one is hovered
	for (int i = 0; i < 10; i++)
	{
		if (i + objectPageNumber * 10 < Object::objectList.size())
		{
			if (Controller::mouseX >= 228 + 150 * i && Controller::mouseX <= 372 + 150 * i && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
			{
				displayObjectID = i + objectPageNumber * 10;
			}
			artist.drawImage(240 + 150 * i, 940, 120, 120, Object::objectList[i + objectPageNumber * 10].textureSet.variant1);
		}
	}
	//draw info
	artist.drawLetters(Object::objectList[displayObjectID].name, 80, 930, Artist::smallFont);
	if (Object::objectList[displayObjectID].walkable)
	{
		artist.drawLetters("true", 80, 951, Artist::smallFont);
	}
	else
	{
		artist.drawLetters("false", 80, 951, Artist::smallFont);
	}
	Object::objectVariantList[displayObjectID * 4].draw(162, 1012, 60, 60);
	displayObjectID = selectedObjectID;
	//draw up and down arrows
	if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(1748, 928, 50, 50, Artist::gArrow);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);
	if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(1748, 1022, 50, 50, Artist::gArrow, 0, 0, SDL_FLIP_VERTICAL);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);

	artist.drawLetters(std::to_string(objectPageNumber + 1), 1748, 990, Artist::smallFont);
}

void drawSpawnTab()
{
	Artist artist;
	Spawn spawn;
	//draw team 1 stuff
	if (Controller::mouseX >= 78 && Controller::mouseX <= 222 && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 150);
	}
	if (selectedSpawnTeam == 0)
	{
		SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 150, 150);
	}
	artist.drawImage(78, 928, 144, 144, Artist::gHUDBackplate);
	SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 255);

	Spawn::friendlySpawns[selectedSpawnNumber].draw(80, 930, 140, 140, selectedSpawnNumber);

	//draw team 2 stuff
	if (Controller::mouseX >= 228 && Controller::mouseX <= 372 && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 150);
	}
	if (selectedSpawnTeam == 1)
	{
		SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 150, 150);
	}
	artist.drawImage(228, 928, 144, 144, Artist::gHUDBackplate);
	SDL_SetTextureColorMod(Artist::gHUDBackplate, 255, 255, 255);

	spawn.makeSpawnsRed();
	Spawn::friendlySpawns[selectedSpawnNumber].draw(230, 930, 140, 140, selectedSpawnNumber);
	spawn.makeSpawnsWhite();

	//draw up and down arrow for spawn number
	if (Controller::mouseX >= 375 && Controller::mouseX <= 425 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(375, 928, 50, 50, Artist::gArrow);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);
	if (Controller::mouseX >= 375 && Controller::mouseX <= 425 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(375, 1022, 50, 50, Artist::gArrow, 0, 0, SDL_FLIP_VERTICAL);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);

	artist.drawLetters(std::to_string(selectedSpawnNumber + 1), 375, 990, Artist::smallFont);

	//draw amount of players and arrows
	artist.drawLetters("Players:", 1630, 990, Artist::smallFont);
	if (Controller::mouseX >= 1790 && Controller::mouseX <= 1840 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(1790, 928, 50, 50, Artist::gArrow);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);
	if (Controller::mouseX >= 1790 && Controller::mouseX <= 1840 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(1790, 1022, 50, 50, Artist::gArrow, 0, 0, SDL_FLIP_VERTICAL);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);

	artist.drawLetters(std::to_string(Spawn::enemySpawns.size()), 1790, 990, Artist::smallFont);
}

void drawOptionsTab()
{
	Artist artist;
	//save button
	if (Controller::mouseX >= 78 && Controller::mouseX <= 334 && Controller::mouseY >= 928 && Controller::mouseY <= 996)
	{
		SDL_SetTextureColorMod(Artist::gHUDBackplate2, 255, 255, 150);
	}
	artist.drawImage(78, 928, 256, 68, Artist::gHUDBackplate2);
	SDL_SetTextureColorMod(Artist::gHUDBackplate2, 255, 255, 255);
	artist.drawLetters("Save", 80, 930, Artist::largeFont);
	//save 1-3
	for (int i = 0; i < 3; i++)
	{
		if (Controller::mouseX >= 334 + 68 * i && Controller::mouseX <= 401 + 68 * i && Controller::mouseY >= 928 && Controller::mouseY <= 996)
		{
			SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 255, 150);
		}
		if (saveNumber == i + 1)
		{
			SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 150, 150);
		}
		artist.drawImage(334 + 68 * i, 928, 68, 68, Artist::gHUDBackplate3);
		SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 255, 255);
		artist.drawLetters(std::to_string(i + 1), 336 + 68 * i, 930, Artist::largeFont);
	}
	//load button
	if (Controller::mouseX >= 78 && Controller::mouseX <= 334 && Controller::mouseY >= 1004 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gHUDBackplate2, 255, 255, 150);
	}
	artist.drawImage(78, 1004, 256, 68, Artist::gHUDBackplate2);
	SDL_SetTextureColorMod(Artist::gHUDBackplate2, 255, 255, 255);
	artist.drawLetters("Load", 80, 1006, Artist::largeFont);
	//load 1-3
	for (int i = 0; i < 3; i++)
	{
		if (Controller::mouseX >= 334 + 68 * i && Controller::mouseX <= 401 + 68 * i && Controller::mouseY >= 1004 && Controller::mouseY <= 1072)
		{
			SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 255, 150);
		}
		if (loadNumber == i + 1)
		{
			SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 150, 150);
		}
		artist.drawImage(334 + 68 * i, 1004, 68, 68, Artist::gHUDBackplate3);
		SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 255, 255);
		artist.drawLetters(std::to_string(i + 1), 336 + 68 * i, 1006, Artist::largeFont);
	}
	//X size arrows
	if (Controller::mouseX >= 540 && Controller::mouseX <= 590 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(540, 928, 50, 50, Artist::gArrow);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);
	if (Controller::mouseX >= 540 && Controller::mouseX <= 590 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(540, 1022, 50, 50, Artist::gArrow, 0, 0, SDL_FLIP_VERTICAL);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);

	artist.drawLetters(std::to_string(Map::mapSizeX), 540, 990, Artist::smallFont);
	//Y size arrows
	if (Controller::mouseX >= 600 && Controller::mouseX <= 650 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(600, 928, 50, 50, Artist::gArrow);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);
	if (Controller::mouseX >= 600 && Controller::mouseX <= 650 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 150);
	}
	artist.drawImage(600, 1022, 50, 50, Artist::gArrow, 0, 0, SDL_FLIP_VERTICAL);
	SDL_SetTextureColorMod(Artist::gArrow, 255, 255, 255);
	artist.drawLetters(std::to_string(Map::mapSizeY), 600, 990, Artist::smallFont);
	//reset button
	if (Controller::mouseX >= 1670 && Controller::mouseX <= 1738 && Controller::mouseY >= 1004 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 255, 150);
	}
	artist.drawImage(1670, 1004, 68, 68, Artist::gHUDBackplate3);
	SDL_SetTextureColorMod(Artist::gHUDBackplate3, 255, 255, 255);
	artist.drawLetters("R", 1670, 1006, Artist::largeFont);
	
	//home button
	if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
	{
		SDL_SetTextureColorMod(Artist::gHome, 255, 255, 150);
	}
	artist.drawImage(1748, 1022, 50, 50, Artist::gHome);
	SDL_SetTextureColorMod(Artist::gHome, 255, 255, 255);
}

void drawHUD()
{
	Artist artist;
	
	if (Menus::gameIndex != 0)
	{
		artist.drawImage(70, 920, 1780, 160, Artist::gHUDBackdrop);

		if (Menus::gameIndex == 1)
		{
			drawTab(70, 896, "Tiles");
		}
		else
		{
			drawTab(70, 894, "Tiles");
		}
		if (Menus::gameIndex == 2)
		{
			drawTab(183, 896, "Objects");
		}
		else
		{
			drawTab(183, 894, "Objects");
		}
		if (Menus::gameIndex == 3)
		{
			drawTab(336, 896, "Spawns");
		}
		else
		{
			drawTab(336, 894, "Spawns");
		}
		if (Menus::gameIndex == 4)
		{
			drawTab(1665, 896, "Options");
		}
		else
		{
			drawTab(1665, 894, "Options");
		}
		drawTab(1818, 896, "X");
	}
	else
	{
		
		drawTab(70, 1054, "Tiles");
		drawTab(183, 1054, "Objects");
		drawTab(336, 1054, "Spawns");
		drawTab(1665, 1054, "Options");

		drawTab(1818, 1054, "X");
	}


	switch (Menus::gameIndex)
	{
	case 1:
		drawTilesInEditor();
		break;
	case 2:
		drawObjectsInEditor();
		break;
	case 3:
		drawSpawnTab();
		break;
	case 4:
		drawOptionsTab();
		break;

	}
}

void Editor::controlEditor(int input)
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_NONE:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		break;
	case Menus::GAME_STATE_IN_EDITOR:
		bool clickedInHud = false;
		if (Controller::mouseX >= 70 && Controller::mouseX <= 1850 && Controller::mouseY > 920)
		{
			clickedInHud = true;
		}

		if (Menus::gameIndex != 0)
		{
			if (Controller::mouseX >= 1818 && Controller::mouseX <= 1850 && Controller::mouseY >= 896 && Controller::mouseY <= 922)
			{
				clickedInHud = true;
				Menus::gameIndex = 0;
			}
			if (Controller::mouseX >= 70 && Controller::mouseX <= 182 && Controller::mouseY >= 896 && Controller::mouseY <= 922)
			{
				clickedInHud = true;
				Menus::gameIndex = 1;
			}
			if (Controller::mouseX >= 183 && Controller::mouseX <= 335 && Controller::mouseY >= 896 && Controller::mouseY <= 922)
			{
				clickedInHud = true;
				Menus::gameIndex = 2;
			}
			if (Controller::mouseX >= 336 && Controller::mouseX <= 468 && Controller::mouseY >= 896 && Controller::mouseY <= 922)
			{
				clickedInHud = true;
				Menus::gameIndex = 3;
			}
			if (Controller::mouseX >= 1665 && Controller::mouseX <= 1817 && Controller::mouseY >= 896 && Controller::mouseY <= 922)
			{
				clickedInHud = true;
				Menus::gameIndex = 4;
			}
		}
		//Left Mouse Click
		if (input == 1)
		{
			Map map;

			
			switch (Menus::gameIndex)
			{
			case 0:
				//tab closed
				if (Controller::mouseX >= 70 && Controller::mouseX <= 182 && Controller::mouseY >= 1054)
				{
					Menus::gameIndex = 1;
				}
				if (Controller::mouseX >= 183 && Controller::mouseX <= 335 && Controller::mouseY >= 1054)
				{
					Menus::gameIndex = 2;
				}
				if (Controller::mouseX >= 336 && Controller::mouseX <= 468 && Controller::mouseY >= 1054)
				{
					Menus::gameIndex = 3;
				}
				if (Controller::mouseX >= 1665 && Controller::mouseX <= 1817 && Controller::mouseY >= 1054)
				{
					Menus::gameIndex = 4;
				}
				break;
			case 1:
				//tiles
				
				//tile selcetion
				for (int i = 0; i < 10; i++)
				{
					if (Controller::mouseX >= 228 + 150 * i && Controller::mouseX <= 372 + 150 * i && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
					{
						if (i + tilePageNumber * 10 < Tile::tileList.size())
						{
							selectedTileID = i + tilePageNumber * 10;
						}
					}
				}
				//up arrow
				if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
				{
					tilePageNumber += 1;
					
					if (tilePageNumber > Tile::tileList.size() / 10)
					{
						tilePageNumber = 0;
					}
					
				}
				//down arrow
				if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
				{
					tilePageNumber -= 1;

					if (tilePageNumber < 0)
					{
						tilePageNumber = Tile::tileList.size() / 10;
					}
					
				}
				//set tile
				if (!clickedInHud)
				{
					map.setTileUnderMouse(map.getGridPosUnderMouse().x, map.getGridPosUnderMouse().y, &Tile::tileVariantList[selectedTileID * 4 + rand() % 4]);
				}
				//MAKE IT SO YOU DONT CLICK THRU THE TABS STUFF
				break;
			case 2:
				//objects
				//object selection
				for (int i = 0; i < 10; i++)
				{
					if (Controller::mouseX >= 228 + 150 * i && Controller::mouseX <= 372 + 150 * i && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
					{
						if (i + objectPageNumber * 10 < Object::objectList.size())
						{
							selectedObjectID = i + objectPageNumber * 10;
						}
					}
				}
				//up arrow
				if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
				{
					objectPageNumber += 1;

					if (objectPageNumber > Object::objectList.size() / 10)
					{
						objectPageNumber = 0;
					}

				}
				//down arrow
				if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
				{
					objectPageNumber -= 1;

					if (objectPageNumber < 0)
					{
						objectPageNumber = Object::objectList.size() / 10;
					}

				}
				//set object
				if (!clickedInHud)
				{
					map.setObjectUnderMouse(map.getGridPosUnderMouse().x, map.getGridPosUnderMouse().y, &Object::objectVariantList[selectedObjectID * 4 + rand() % 4]);
				}
				break;
			case 3:
				//spawns
				// team 1 select
				if (Controller::mouseX >= 78 && Controller::mouseX <= 222 && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
				{
					selectedSpawnTeam = 0;
				}
				//team 2 select
				if (Controller::mouseX >= 228 && Controller::mouseX <= 372 && Controller::mouseY >= 928 && Controller::mouseY <= 1072)
				{
					selectedSpawnTeam = 1;
				}
				//up arrow for selected player
				if (Controller::mouseX >= 375 && Controller::mouseX <= 425 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
				{
					selectedSpawnNumber++;
					if (selectedSpawnNumber >= Spawn::friendlySpawns.size())
					{
						selectedSpawnNumber = 0;
					}
				}
				//down arrow
				if (Controller::mouseX >= 375 && Controller::mouseX <= 425 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
				{
					selectedSpawnNumber--;
					if (selectedSpawnNumber < 0)
					{
						selectedSpawnNumber = Spawn::friendlySpawns.size() - 1;
					}
				}
				//up arrow for player count
				if (Controller::mouseX >= 1790 && Controller::mouseX <= 1840 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
				{
					if (Spawn::friendlySpawns.size() + 1 <= 30)
					{
						Spawn::friendlySpawns.resize(Spawn::friendlySpawns.size() + 1);
						Spawn::enemySpawns.resize(Spawn::enemySpawns.size() + 1);
					}
				}
				//down arrow
				if (Controller::mouseX >= 1790 && Controller::mouseX <= 1840 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
				{
					if (Spawn::friendlySpawns.size() - 1 > 0)
					{
						Spawn::friendlySpawns.resize(Spawn::friendlySpawns.size() - 1);
						Spawn::enemySpawns.resize(Spawn::enemySpawns.size() - 1);
						if (selectedSpawnNumber > Spawn::friendlySpawns.size() - 1)
						{
							selectedSpawnNumber = Spawn::friendlySpawns.size() - 1;
						}
					}
				}
				if (!clickedInHud)
				{
					if (map.getCharIDUnderMouse() == -1 && map.getEnemyCharIDUnderMouse() == -1)
					{
						switch (selectedSpawnTeam)
						{
						case 0:
							Spawn::friendlySpawns[selectedSpawnNumber].x = map.getGridPosUnderMouse().x;
							Spawn::friendlySpawns[selectedSpawnNumber].y = map.getGridPosUnderMouse().y;
							break;
						case 1:
							Spawn::enemySpawns[selectedSpawnNumber].x = map.getGridPosUnderMouse().x;
							Spawn::enemySpawns[selectedSpawnNumber].y = map.getGridPosUnderMouse().y;
							break;
						}
					}
				}
				break;
			case 4:
				//options
				//save button
				if (Controller::mouseX >= 78 && Controller::mouseX <= 334 && Controller::mouseY >= 928 && Controller::mouseY <= 996)
				{
					Map map;
					
					map.saveMap("map" + std::to_string(saveNumber));
				}
				
				//save 1-3
				for (int i = 0; i < 3; i++)
				{
					if (Controller::mouseX >= 334 + 68 * i && Controller::mouseX <= 401 + 68 * i && Controller::mouseY >= 928 && Controller::mouseY <= 996)
					{
						saveNumber = i + 1;
					}
				}
				//load button
				if (Controller::mouseX >= 78 && Controller::mouseX <= 334 && Controller::mouseY >= 1004 && Controller::mouseY <= 1072)
				{
					Map map;
					
					map.loadMap("map" + std::to_string(loadNumber));
				}
				//load 1-3
				for (int i = 0; i < 3; i++)
				{
					if (Controller::mouseX >= 334 + 68 * i && Controller::mouseX <= 401 + 68 * i && Controller::mouseY >= 1004 && Controller::mouseY <= 1072)
					{
						loadNumber = i + 1;
					}
				}
				//X size arrows
				if (Controller::mouseX >= 540 && Controller::mouseX <= 590 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
				{
					//make it so it cant go negative
					Map map;
					
					Map::mapSizeX++;
					if (Map::mapSizeX > 10)
					{
						map.updateMapSize();
						for (int i = 0; i < Map::mapSizeY; i++)
						{
							map.setObjectUnderMouse(Map::mapSizeX - 1, i, &Object::objectVariantList[0 + rand() % 4]);
							map.setTileUnderMouse(Map::mapSizeX - 1, i, &Tile::tileVariantList[0 + rand() % 4]);
						}
					}
					else
					{
						Map::mapSizeX--;
					}
				}
				if (Controller::mouseX >= 540 && Controller::mouseX <= 590 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
				{
					Map map;
					Map::mapSizeX--;
					map.updateMapSize();
				}
				//Y size arrows
				if (Controller::mouseX >= 600 && Controller::mouseX <= 650 && Controller::mouseY >= 928 && Controller::mouseY <= 978)
				{
					//make it so it cant go negative
					Map map;

					Map::mapSizeY++;
					if (Map::mapSizeY > 10)
					{
						map.updateMapSize();
						for (int i = 0; i < Map::mapSizeX; i++)
						{
							map.setObjectUnderMouse(i, Map::mapSizeY - 1, &Object::objectVariantList[0 + rand() % 4]);
							map.setTileUnderMouse(i, Map::mapSizeY - 1, &Tile::tileVariantList[0 + rand() % 4]);
						}
					}
					else
					{
						Map::mapSizeY--;
					}
				}
				if (Controller::mouseX >= 600 && Controller::mouseX <= 650 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
				{
					Map map;
					Map::mapSizeY--;
					map.updateMapSize();
				}
				//reset button
				if (Controller::mouseX >= 1670 && Controller::mouseX <= 1738 && Controller::mouseY >= 1004 && Controller::mouseY <= 1072)
				{
					Map map;
					map.resetMap();
				}
				


				if (Controller::mouseX >= 1748 && Controller::mouseX <= 1798 && Controller::mouseY >= 1022 && Controller::mouseY <= 1072)
				{
					Menus::gameState = Menus::GAME_STATE_MAIN_MENU;
					Menus::gameIndex = 0;
				}
				break;
			}
		}

		//Right Mouse Click
		if (input == 2)
		{
			Map map;
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				//objects
				if (!clickedInHud)
				{
					map.setObjectUnderMouse(map.getGridPosUnderMouse().x, map.getGridPosUnderMouse().y, &Object::objectVariantList[0]);
				}
				break;
			}
		}

		//Keyboard Input
		if (input == 3)
		{
			//KEYBOARD
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			switch (Menus::gameIndex)
			{
			case 0:
				if (state[SDL_SCANCODE_ESCAPE])
				{
					
				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}

		//left drag
		if (input == 11)
		{
			Map map;
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			case 1:
				//tiles
				if (!clickedInHud)
				{
					map.setTileUnderMouse(map.getGridPosUnderMouse().x, map.getGridPosUnderMouse().y, &Tile::tileVariantList[selectedTileID * 4 + rand() % 4]);
				}
				break;
			case 2:
				//objects
				if (!clickedInHud)
				{
					map.setObjectUnderMouse(map.getGridPosUnderMouse().x, map.getGridPosUnderMouse().y, &Object::objectVariantList[selectedObjectID * 4 + rand() % 4]);
				}
				break;
			}
		}

		//Right drag
		if (input == 12)
		{
			Map map;
			switch (Menus::gameIndex)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				//objects
				if (!clickedInHud)
				{
					map.setObjectUnderMouse(map.getGridPosUnderMouse().x, map.getGridPosUnderMouse().y, &Object::objectVariantList[0]);
				}
				break;
			}
		}
		break;
	}
}

void Editor::drawEditor()
{
	switch (Menus::gameState)
	{
	case Menus::GAME_STATE_NONE:
		break;
	case Menus::GAME_STATE_MAIN_MENU:
		break;
	case Menus::GAME_STATE_IN_EDITOR:
		drawHUD();
		break;
	}
}