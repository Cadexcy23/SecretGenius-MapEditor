#include <vector>
#include "Spawn.h"



void Spawn::makeSpawnsRed()
{
	SDL_SetTextureColorMod(Artist::gSpawn1, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn2, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn3, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn4, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn5, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn6, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn7, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn8, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn9, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn10, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn11, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn12, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn13, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn14, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn15, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn16, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn17, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn18, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn19, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn20, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn21, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn22, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn23, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn24, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn25, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn26, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn27, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn28, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn29, 255, 0, 0);
	SDL_SetTextureColorMod(Artist::gSpawn30, 255, 0, 0);
}

void Spawn::makeSpawnsWhite()
{
	SDL_SetTextureColorMod(Artist::gSpawn1, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn2, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn3, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn4, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn5, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn6, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn7, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn8, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn9, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn10, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn11, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn12, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn13, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn14, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn15, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn16, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn17, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn18, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn19, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn20, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn21, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn22, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn23, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn24, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn25, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn26, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn27, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn28, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn29, 255, 255, 255);
	SDL_SetTextureColorMod(Artist::gSpawn30, 255, 255, 255);
}

std::vector<Spawn::spawn> Spawn::friendlySpawns;
std::vector<Spawn::spawn> Spawn::enemySpawns;