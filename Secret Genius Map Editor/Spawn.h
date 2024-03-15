#pragma once
#ifndef string
#include <string>
#endif
#ifndef Artist
#include "Artist.h"
#endif
#ifndef vector
#include <vector>
#endif
class Spawn {
public:
	struct spawn
	{
		int x;
		int y;
		
		void draw(int drawX, int drawY, int w, int h, int ID)
		{
			Artist artist;
			SDL_Texture* tempTex = Artist::gSpawn1;
			switch (ID)
			{
			case 0:
				tempTex = Artist::gSpawn1;
				break;
			case 1:
				tempTex = Artist::gSpawn2;
				break;
			case 2:
				tempTex = Artist::gSpawn3;
				break;
			case 3:
				tempTex = Artist::gSpawn4;
				break;
			case 4:
				tempTex = Artist::gSpawn5;
				break;
			case 5:
				tempTex = Artist::gSpawn6;
				break;
			case 6:
				tempTex = Artist::gSpawn7;
				break;
			case 7:
				tempTex = Artist::gSpawn8;
				break;
			case 8:
				tempTex = Artist::gSpawn9;
				break;
			case 9:
				tempTex = Artist::gSpawn10;
				break;
			case 10:
				tempTex = Artist::gSpawn11;
				break;
			case 11:
				tempTex = Artist::gSpawn12;
				break;
			case 12:
				tempTex = Artist::gSpawn13;
				break;
			case 13:
				tempTex = Artist::gSpawn14;
				break;
			case 14:
				tempTex = Artist::gSpawn15;
				break;
			case 15:
				tempTex = Artist::gSpawn16;
				break;
			case 16:
				tempTex = Artist::gSpawn17;
				break;
			case 17:
				tempTex = Artist::gSpawn18;
				break;
			case 18:
				tempTex = Artist::gSpawn19;
				break;
			case 19:
				tempTex = Artist::gSpawn20;
				break;
			case 20:
				tempTex = Artist::gSpawn21;
				break;
			case 21:
				tempTex = Artist::gSpawn22;
				break;
			case 22:
				tempTex = Artist::gSpawn23;
				break;
			case 23:
				tempTex = Artist::gSpawn24;
				break;
			case 24:
				tempTex = Artist::gSpawn25;
				break;
			case 25:
				tempTex = Artist::gSpawn26;
				break;
			case 26:
				tempTex = Artist::gSpawn27;
				break;
			case 27:
				tempTex = Artist::gSpawn28;
				break;
			case 28:
				tempTex = Artist::gSpawn29;
				break;
			case 29:
				tempTex = Artist::gSpawn30;
				break;
			}
			
			artist.drawImage(drawX, drawY, w, h, tempTex);
			
		}
	};

	

	static std::vector<spawn> friendlySpawns;
	static std::vector<spawn> enemySpawns;
	void makeSpawnsRed();
	void makeSpawnsWhite();
};