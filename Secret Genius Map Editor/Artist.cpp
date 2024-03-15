#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <time.h>
#include "Artist.h"
#include "Menus.h"
#include "Tile.h"
#include "Map.h"
#include "Object.h"
#include "Spawn.h"
#include "Editor.h"


//Screen dimension constants Windowed  1280x720  Fullscreen 1 1920x1080
int Artist::SCREEN_WIDTH = 1920;
int Artist::SCREEN_HEIGHT = 1080;
float Artist::SCREEN_SCALE = 1;
bool Artist::FULLSCREEN = true;

Artist::RGB Artist::tileSelecterRGB{ 125, 0, 0 };



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;





//Initialize textures in the header
SDL_Texture* Artist::gBackground = NULL;
SDL_Texture* Artist::gExit = NULL;
SDL_Texture* Artist::gTire = NULL;
SDL_Texture* Artist::gLoad = NULL;
SDL_Texture* Artist::gNew = NULL;
SDL_Texture* Artist::gOptions = NULL;
SDL_Texture* Artist::gStart = NULL;
SDL_Texture* Artist::gNameBackplate = NULL;
SDL_Texture* Artist::gTileHoverPiece = NULL;
SDL_Texture* Artist::gTileInfoBackdrop = NULL;
SDL_Texture* Artist::gCharInfoBackdrop = NULL;
SDL_Texture* Artist::gCharObjectInfoBackdrop = NULL;
SDL_Texture* Artist::gObjectInfoBackdrop = NULL;
SDL_Texture* Artist::gSliderBack = NULL;
SDL_Texture* Artist::gSliderKnob = NULL;
SDL_Texture* Artist::gVolumeIcon = NULL;
SDL_Texture* Artist::gVolumeCrossout = NULL;
SDL_Texture* Artist::gShittySword = NULL;
SDL_Texture* Artist::gHUDBackdrop = NULL;
SDL_Texture* Artist::gHUDBackplate = NULL;
SDL_Texture* Artist::gHUDBackplate2 = NULL;
SDL_Texture* Artist::gHUDBackplate3 = NULL;
SDL_Texture* Artist::gTabCorner = NULL;
SDL_Texture* Artist::gTabChunk = NULL;
SDL_Texture* Artist::gArrow = NULL;
SDL_Texture* Artist::gHome = NULL;
//spawn icons
SDL_Texture* Artist::gSpawn1 = NULL;
SDL_Texture* Artist::gSpawn2 = NULL;
SDL_Texture* Artist::gSpawn3 = NULL;
SDL_Texture* Artist::gSpawn4 = NULL;
SDL_Texture* Artist::gSpawn5 = NULL;
SDL_Texture* Artist::gSpawn6 = NULL;
SDL_Texture* Artist::gSpawn7 = NULL;
SDL_Texture* Artist::gSpawn8 = NULL;
SDL_Texture* Artist::gSpawn9 = NULL;
SDL_Texture* Artist::gSpawn10 = NULL;
SDL_Texture* Artist::gSpawn11 = NULL;
SDL_Texture* Artist::gSpawn12 = NULL;
SDL_Texture* Artist::gSpawn13 = NULL;
SDL_Texture* Artist::gSpawn14 = NULL;
SDL_Texture* Artist::gSpawn15 = NULL;
SDL_Texture* Artist::gSpawn16 = NULL;
SDL_Texture* Artist::gSpawn17 = NULL;
SDL_Texture* Artist::gSpawn18 = NULL;
SDL_Texture* Artist::gSpawn19 = NULL;
SDL_Texture* Artist::gSpawn20 = NULL;
SDL_Texture* Artist::gSpawn21 = NULL;
SDL_Texture* Artist::gSpawn22 = NULL;
SDL_Texture* Artist::gSpawn23 = NULL;
SDL_Texture* Artist::gSpawn24 = NULL;
SDL_Texture* Artist::gSpawn25 = NULL;
SDL_Texture* Artist::gSpawn26 = NULL;
SDL_Texture* Artist::gSpawn27 = NULL;
SDL_Texture* Artist::gSpawn28 = NULL;
SDL_Texture* Artist::gSpawn29 = NULL;
SDL_Texture* Artist::gSpawn30 = NULL;
//letters

Artist::fontTextureSet Artist::largeFont;
Artist::fontTextureSet Artist::smallFont;




//Update screen
void Artist::updateScreen()
{
	SDL_RenderPresent(gRenderer);
}

//Clear screen
void Artist::clearScreen()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

SDL_Texture* Artist::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

bool Artist::init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Secret Genius", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Artist::SCREEN_WIDTH, Artist::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		Artist artist;
		SDL_Surface* icon = IMG_Load("Resource/icon.png");
		SDL_SetWindowIcon(gWindow, icon);
		SDL_FreeSurface(icon);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void loadFontTextures(Artist::fontTextureSet* fontToLoad, std::string fontName)
{
	Artist artist;
	fontToLoad->LowerA = artist.loadTexture("Resource/fonts/" + fontName + "/a.png");
	fontToLoad->LowerB = artist.loadTexture("Resource/fonts/" + fontName + "/b.png");
	fontToLoad->LowerC = artist.loadTexture("Resource/fonts/" + fontName + "/c.png");
	fontToLoad->LowerD = artist.loadTexture("Resource/fonts/" + fontName + "/d.png");
	fontToLoad->LowerE = artist.loadTexture("Resource/fonts/" + fontName + "/e.png");
	fontToLoad->LowerF = artist.loadTexture("Resource/fonts/" + fontName + "/f.png");
	fontToLoad->LowerG = artist.loadTexture("Resource/fonts/" + fontName + "/g.png");
	fontToLoad->LowerH = artist.loadTexture("Resource/fonts/" + fontName + "/h.png");
	fontToLoad->LowerI = artist.loadTexture("Resource/fonts/" + fontName + "/i.png");
	fontToLoad->LowerJ = artist.loadTexture("Resource/fonts/" + fontName + "/j.png");
	fontToLoad->LowerK = artist.loadTexture("Resource/fonts/" + fontName + "/k.png");
	fontToLoad->LowerL = artist.loadTexture("Resource/fonts/" + fontName + "/l.png");
	fontToLoad->LowerM = artist.loadTexture("Resource/fonts/" + fontName + "/m.png");
	fontToLoad->LowerN = artist.loadTexture("Resource/fonts/" + fontName + "/n.png");
	fontToLoad->LowerO = artist.loadTexture("Resource/fonts/" + fontName + "/o.png");
	fontToLoad->LowerP = artist.loadTexture("Resource/fonts/" + fontName + "/p.png");
	fontToLoad->LowerQ = artist.loadTexture("Resource/fonts/" + fontName + "/q.png");
	fontToLoad->LowerR = artist.loadTexture("Resource/fonts/" + fontName + "/r.png");
	fontToLoad->LowerS = artist.loadTexture("Resource/fonts/" + fontName + "/s.png");
	fontToLoad->LowerT = artist.loadTexture("Resource/fonts/" + fontName + "/t.png");
	fontToLoad->LowerU = artist.loadTexture("Resource/fonts/" + fontName + "/u.png");
	fontToLoad->LowerV = artist.loadTexture("Resource/fonts/" + fontName + "/v.png");
	fontToLoad->LowerW = artist.loadTexture("Resource/fonts/" + fontName + "/w.png");
	fontToLoad->LowerX = artist.loadTexture("Resource/fonts/" + fontName + "/x.png");
	fontToLoad->LowerY = artist.loadTexture("Resource/fonts/" + fontName + "/y.png");
	fontToLoad->LowerZ = artist.loadTexture("Resource/fonts/" + fontName + "/z.png");
	fontToLoad->CapA = artist.loadTexture("Resource/fonts/" + fontName + "/capA.png");
	fontToLoad->CapB = artist.loadTexture("Resource/fonts/" + fontName + "/capB.png");
	fontToLoad->CapC = artist.loadTexture("Resource/fonts/" + fontName + "/capC.png");
	fontToLoad->CapD = artist.loadTexture("Resource/fonts/" + fontName + "/capD.png");
	fontToLoad->CapE = artist.loadTexture("Resource/fonts/" + fontName + "/capE.png");
	fontToLoad->CapF = artist.loadTexture("Resource/fonts/" + fontName + "/capF.png");
	fontToLoad->CapG = artist.loadTexture("Resource/fonts/" + fontName + "/capG.png");
	fontToLoad->CapH = artist.loadTexture("Resource/fonts/" + fontName + "/capH.png");
	fontToLoad->CapI = artist.loadTexture("Resource/fonts/" + fontName + "/capI.png");
	fontToLoad->CapJ = artist.loadTexture("Resource/fonts/" + fontName + "/capJ.png");
	fontToLoad->CapK = artist.loadTexture("Resource/fonts/" + fontName + "/capK.png");
	fontToLoad->CapL = artist.loadTexture("Resource/fonts/" + fontName + "/capL.png");
	fontToLoad->CapM = artist.loadTexture("Resource/fonts/" + fontName + "/capM.png");
	fontToLoad->CapN = artist.loadTexture("Resource/fonts/" + fontName + "/capN.png");
	fontToLoad->CapO = artist.loadTexture("Resource/fonts/" + fontName + "/capO.png");
	fontToLoad->CapP = artist.loadTexture("Resource/fonts/" + fontName + "/capP.png");
	fontToLoad->CapQ = artist.loadTexture("Resource/fonts/" + fontName + "/capQ.png");
	fontToLoad->CapR = artist.loadTexture("Resource/fonts/" + fontName + "/capR.png");
	fontToLoad->CapS = artist.loadTexture("Resource/fonts/" + fontName + "/capS.png");
	fontToLoad->CapT = artist.loadTexture("Resource/fonts/" + fontName + "/capT.png");
	fontToLoad->CapU = artist.loadTexture("Resource/fonts/" + fontName + "/capU.png");
	fontToLoad->CapV = artist.loadTexture("Resource/fonts/" + fontName + "/capV.png");
	fontToLoad->CapW = artist.loadTexture("Resource/fonts/" + fontName + "/capW.png");
	fontToLoad->CapX = artist.loadTexture("Resource/fonts/" + fontName + "/capX.png");
	fontToLoad->CapY = artist.loadTexture("Resource/fonts/" + fontName + "/capY.png");
	fontToLoad->CapZ = artist.loadTexture("Resource/fonts/" + fontName + "/capZ.png");
	fontToLoad->num1 = artist.loadTexture("Resource/fonts/" + fontName + "/1.png");
	fontToLoad->num2 = artist.loadTexture("Resource/fonts/" + fontName + "/2.png");
	fontToLoad->num3 = artist.loadTexture("Resource/fonts/" + fontName + "/3.png");
	fontToLoad->num4 = artist.loadTexture("Resource/fonts/" + fontName + "/4.png");
	fontToLoad->num5 = artist.loadTexture("Resource/fonts/" + fontName + "/5.png");
	fontToLoad->num6 = artist.loadTexture("Resource/fonts/" + fontName + "/6.png");
	fontToLoad->num7 = artist.loadTexture("Resource/fonts/" + fontName + "/7.png");
	fontToLoad->num8 = artist.loadTexture("Resource/fonts/" + fontName + "/8.png");
	fontToLoad->num9 = artist.loadTexture("Resource/fonts/" + fontName + "/9.png");
	fontToLoad->num0 = artist.loadTexture("Resource/fonts/" + fontName + "/0.png");
	fontToLoad->Pound = artist.loadTexture("Resource/fonts/" + fontName + "/#.png");
	fontToLoad->$ = artist.loadTexture("Resource/fonts/" + fontName + "/$.png");
	fontToLoad->Percent = artist.loadTexture("Resource/fonts/" + fontName + "/%.png");
	fontToLoad->Ampersand = artist.loadTexture("Resource/fonts/" + fontName + "/&.png");
	fontToLoad->LeftParentheses = artist.loadTexture("Resource/fonts/" + fontName + "/(.png");
	fontToLoad->RightParentheses = artist.loadTexture("Resource/fonts/" + fontName + "/).png");
	fontToLoad->Comma = artist.loadTexture("Resource/fonts/" + fontName + "/,.png");
	fontToLoad->Apostrophe = artist.loadTexture("Resource/fonts/" + fontName + "/'.png");
	fontToLoad->Minus = artist.loadTexture("Resource/fonts/" + fontName + "/-.png");
	fontToLoad->SemiColon = artist.loadTexture("Resource/fonts/" + fontName + "/;.png");
	fontToLoad->Colon = artist.loadTexture("Resource/fonts/" + fontName + "/colon.png");
	fontToLoad->At = artist.loadTexture("Resource/fonts/" + fontName + "/@.png");
	fontToLoad->LeftBracket = artist.loadTexture("Resource/fonts/" + fontName + "/[.png");
	fontToLoad->RightBracket = artist.loadTexture("Resource/fonts/" + fontName + "/].png");
	fontToLoad->Caret = artist.loadTexture("Resource/fonts/" + fontName + "/^.png");
	fontToLoad->UnderScore = artist.loadTexture("Resource/fonts/" + fontName + "/_.png");
	fontToLoad->Tilde = artist.loadTexture("Resource/fonts/" + fontName + "/~.png");
	fontToLoad->Acute = artist.loadTexture("Resource/fonts/" + fontName + "/`.png");
	fontToLoad->LeftBrace = artist.loadTexture("Resource/fonts/" + fontName + "/{.png");
	fontToLoad->RightBrace = artist.loadTexture("Resource/fonts/" + fontName + "/}.png");
	fontToLoad->Plus = artist.loadTexture("Resource/fonts/" + fontName + "/+.png");
	fontToLoad->Equals = artist.loadTexture("Resource/fonts/" + fontName + "/=.png");
	fontToLoad->Asterisk = artist.loadTexture("Resource/fonts/" + fontName + "/asterisk.png");
	fontToLoad->BackSlash = artist.loadTexture("Resource/fonts/" + fontName + "/backSlash.png");
	fontToLoad->ForwardSlash = artist.loadTexture("Resource/fonts/" + fontName + "/forwardSlash.png");
	fontToLoad->ExclamationMark = artist.loadTexture("Resource/fonts/" + fontName + "/exclamationMark.png");
	fontToLoad->QuestionMark = artist.loadTexture("Resource/fonts/" + fontName + "/questionMark.png");
	fontToLoad->GreaterThan = artist.loadTexture("Resource/fonts/" + fontName + "/greaterThan.png");
	fontToLoad->LessThan = artist.loadTexture("Resource/fonts/" + fontName + "/lessThan.png");
	fontToLoad->Period = artist.loadTexture("Resource/fonts/" + fontName + "/period.png");
	fontToLoad->QuotationMark = artist.loadTexture("Resource/fonts/" + fontName + "/quotationMark.png");
	fontToLoad->VerticalBar = artist.loadTexture("Resource/fonts/" + fontName + "/verticalBar.png");
}

void loadTileData(std::string tileName, bool walkable, int bonusType, int bonusAmount, std::string textureName)
{
	Artist artist;

	
	//make temp tile to fill with data
	Tile::tile tempTile;
	// add tiletype to vector, add name and other info
	tempTile = { tileName, walkable, bonusType, bonusAmount };

	//load textures for all varients
	 tempTile.textureSet.variant1 = artist.loadTexture("Resource/tiles/" + textureName + "1.png");
	 tempTile.textureSet.variant2 = artist.loadTexture("Resource/tiles/" + textureName + "2.png");
	 tempTile.textureSet.variant3 = artist.loadTexture("Resource/tiles/" + textureName + "3.png");
	 tempTile.textureSet.variant4 = artist.loadTexture("Resource/tiles/" + textureName + "4.png");

	//add slot on vector for new tile with tempTiles data
	Tile::tileList.push_back(tempTile);
}

void loadTileVariantData()
{
	Tile::tileVariantList.resize(Tile::tileList.size() * 4);

	for (int a = 0; a < Tile::tileList.size(); a++)
	{
		for (int b = 0; b < 4; b++)
		{
			Tile::tileVariantList[a * 4 + b].tileType = &Tile::tileList[a];
			Tile::tileVariantList[a * 4 + b].textureID = b;
		}
	}
}

void loadObjectData(std::string objectName, bool walkable, int bonusType, int bonusAmount, std::string textureName)
{
	Artist artist;


	//make temp tile to fill with data
	Object::object tempObject;
	// add tiletype to vector, add name and other info
	tempObject = { objectName, walkable, bonusType, bonusAmount };

	//load textures for all varients
	tempObject.textureSet.variant1 = artist.loadTexture("Resource/objects/" + textureName + "1.png");
	tempObject.textureSet.variant2 = artist.loadTexture("Resource/objects/" + textureName + "2.png");
	tempObject.textureSet.variant3 = artist.loadTexture("Resource/objects/" + textureName + "3.png");
	tempObject.textureSet.variant4 = artist.loadTexture("Resource/objects/" + textureName + "4.png");

	//add slot on vector for new tile with tempTiles data
	Object::objectList.push_back(tempObject);
}

void loadObjectVariantData()
{
	Object::objectVariantList.resize(Object::objectList.size() * 4);

	for (int a = 0; a < Object::objectList.size(); a++)
	{
		for (int b = 0; b < 4; b++)
		{
			Object::objectVariantList[a * 4 + b].objectType = &Object::objectList[a];
			Object::objectVariantList[a * 4 + b].textureID = b;
		}
	}
}

bool Artist::loadMedia()
{
	Artist Artist;
	//Loading success flag
	bool success = true;

	//load data for tiles/objects
	loadTileData("Dirt", true, 0, 0, "dirt");
	loadTileData("Grass", true, 0, 0, "grass");
	loadTileData("Blue", true, 0, 0, "blue");
	loadTileData("Green", true, 0, 0, "green");
	loadTileData("Grey", true, 0, 0, "grey");
	loadTileData("Orange", true, 0, 0, "orange");
	loadTileData("Pink", true, 0, 0, "pink");
	loadTileData("Purple", true, 0, 0, "purple");
	loadTileData("Red", false, 0, 0, "red");
	loadTileData("White", true, 0, 0, "white");
	loadTileData("Yellow", true, 0, 0, "yellow");

	loadObjectData("Empty", true, 0, 0, "empty");
	loadObjectData("Wall", false, 0, 0, "wall");
	loadObjectData("Fort", true, 0, 0, "fort");
	

	

	//Load texture
	Artist::gBackground = loadTexture("Resource/mainMenu/background.png");
	Artist::gExit = loadTexture("Resource/exit.png");
	Artist::gTire = loadTexture("Resource/tire.png");
	Artist::gLoad = loadTexture("Resource/mainMenu/load.png");
	Artist::gNew = loadTexture("Resource/mainMenu/new.png");
	Artist::gOptions = loadTexture("Resource/mainMenu/options.png");
	Artist::gStart = loadTexture("Resource/mainMenu/start.png");
	Artist::gNameBackplate = loadTexture("Resource/mainMenu/nameBackplate.png");
	Artist::gTileHoverPiece = loadTexture("Resource/tiles/tileHoverPiece.png");
	//Change to change tile selection thing's color
	SDL_SetTextureColorMod(Artist::gTileHoverPiece, tileSelecterRGB.r, tileSelecterRGB.g, tileSelecterRGB.b);
	Artist::gTileInfoBackdrop = loadTexture("Resource/hud/tileInfoBackdrop.png");
	Artist::gCharInfoBackdrop = loadTexture("Resource/hud/charInfoBackdrop.png");
	Artist::gCharObjectInfoBackdrop = loadTexture("Resource/hud/charObjectInfoBackdrop.png");
	Artist::gObjectInfoBackdrop = loadTexture("Resource/hud/objectInfoBackdrop.png");
	Artist::gSliderBack = loadTexture("Resource/mainMenu/sliderBack.png");
	Artist::gSliderKnob = loadTexture("Resource/mainMenu/sliderKnob.png");
	Artist::gVolumeIcon = loadTexture("Resource/mainMenu/volumeIcon.png");
	Artist::gVolumeCrossout = loadTexture("Resource/mainMenu/volumeCrossout.png");
	Artist::gShittySword = loadTexture("Resource/mainMenu/shittySword.png");
	Artist::gHUDBackdrop = loadTexture("Resource/editor/hud/backdrop.png");
	Artist::gHUDBackplate = loadTexture("Resource/editor/hud/backplate.png");
	Artist::gHUDBackplate2 = loadTexture("Resource/editor/hud/backplate2.png");
	Artist::gHUDBackplate3 = loadTexture("Resource/editor/hud/backplate3.png");
	Artist::gTabCorner = loadTexture("Resource/editor/hud/tabCorner.png");
	Artist::gTabChunk = loadTexture("Resource/editor/hud/tabChunk.png");
	Artist::gArrow = loadTexture("Resource/editor/hud/arrow.png");
	Artist::gHome = loadTexture("Resource/editor/hud/home.png");
	//spawn icons
	Artist::gSpawn1 = loadTexture("Resource/editor/spawns/spawn1.png");
	Artist::gSpawn2 = loadTexture("Resource/editor/spawns/spawn2.png");
	Artist::gSpawn3 = loadTexture("Resource/editor/spawns/spawn3.png");
	Artist::gSpawn4 = loadTexture("Resource/editor/spawns/spawn4.png");
	Artist::gSpawn5 = loadTexture("Resource/editor/spawns/spawn5.png");
	Artist::gSpawn6 = loadTexture("Resource/editor/spawns/spawn6.png");
	Artist::gSpawn7 = loadTexture("Resource/editor/spawns/spawn7.png");
	Artist::gSpawn8 = loadTexture("Resource/editor/spawns/spawn8.png");
	Artist::gSpawn9 = loadTexture("Resource/editor/spawns/spawn9.png");
	Artist::gSpawn10 = loadTexture("Resource/editor/spawns/spawn10.png");
	Artist::gSpawn11 = loadTexture("Resource/editor/spawns/spawn11.png");
	Artist::gSpawn12 = loadTexture("Resource/editor/spawns/spawn12.png");
	Artist::gSpawn13 = loadTexture("Resource/editor/spawns/spawn13.png");
	Artist::gSpawn14 = loadTexture("Resource/editor/spawns/spawn14.png");
	Artist::gSpawn15 = loadTexture("Resource/editor/spawns/spawn15.png");
	Artist::gSpawn16 = loadTexture("Resource/editor/spawns/spawn16.png");
	Artist::gSpawn17 = loadTexture("Resource/editor/spawns/spawn17.png");
	Artist::gSpawn18 = loadTexture("Resource/editor/spawns/spawn18.png");
	Artist::gSpawn19 = loadTexture("Resource/editor/spawns/spawn19.png");
	Artist::gSpawn20 = loadTexture("Resource/editor/spawns/spawn20.png");
	Artist::gSpawn21 = loadTexture("Resource/editor/spawns/spawn21.png");
	Artist::gSpawn22 = loadTexture("Resource/editor/spawns/spawn22.png");
	Artist::gSpawn23 = loadTexture("Resource/editor/spawns/spawn23.png");
	Artist::gSpawn24 = loadTexture("Resource/editor/spawns/spawn24.png");
	Artist::gSpawn25 = loadTexture("Resource/editor/spawns/spawn25.png");
	Artist::gSpawn26 = loadTexture("Resource/editor/spawns/spawn26.png");
	Artist::gSpawn27 = loadTexture("Resource/editor/spawns/spawn27.png");
	Artist::gSpawn28 = loadTexture("Resource/editor/spawns/spawn28.png");
	Artist::gSpawn29 = loadTexture("Resource/editor/spawns/spawn29.png");
	Artist::gSpawn30 = loadTexture("Resource/editor/spawns/spawn30.png");
	//letters
	loadFontTextures(&Artist::largeFont, "large");
	loadFontTextures(&Artist::smallFont, "small");

	
	loadTileVariantData();
	loadObjectVariantData();

	return success;
}

void Artist::close()
{
	//Free loaded image
	//SDL_DestroyTexture(gBackground);
	//gBackground = NULL;






	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Artist::drawImage(int x, int y, int w, int h, SDL_Texture* tex, double r, SDL_Point* center, SDL_RendererFlip flip, bool scaled)
{
	SDL_Rect img;
	img.x = x * Artist::SCREEN_SCALE;
	img.y = y * Artist::SCREEN_SCALE;
	if (scaled)
		img.w = w * Artist::SCREEN_SCALE;
	else
		img.w = w;
	if (scaled)
		img.h = h * Artist::SCREEN_SCALE;
	else
		img.h = h;
	SDL_RenderCopyEx(gRenderer, tex, NULL, &img, r, center, flip);
}

void Artist::drawLetters(std::string string, int x, int y, Artist::fontTextureSet font)
{
	std::string letterS;
	SDL_Texture* letterT = NULL;
	int count = 0;
	int offset = 0;
	//std::cout << string << std::endl;
	while (count < string.length())
	{
		letterS = string[count];
		if (letterS == "a")
		{
			letterT = font.LowerA;
		}
		else if (letterS == "b")
		{
			letterT = font.LowerB;
		}
		else if (letterS == "c")
		{
			letterT = font.LowerC;
		}
		else if (letterS == "d")
		{
			letterT = font.LowerD;
		}
		else if (letterS == "e")
		{
			letterT = font.LowerE;
		}
		else if (letterS == "f")
		{
			letterT = font.LowerF;
		}
		else if (letterS == "g")
		{
			letterT = font.LowerG;
		}
		else if (letterS == "h")
		{
			letterT = font.LowerH;
		}
		else if (letterS == "i")
		{
			letterT = font.LowerI;
		}
		else if (letterS == "j")
		{
			letterT = font.LowerJ;
		}
		else if (letterS == "k")
		{
			letterT = font.LowerK;
		}
		else if (letterS == "l")
		{
			letterT = font.LowerL;
		}
		else if (letterS == "m")
		{
			letterT = font.LowerM;
		}
		else if (letterS == "n")
		{
			letterT = font.LowerN;
		}
		else if (letterS == "o")
		{
			letterT = font.LowerO;
		}
		else if (letterS == "p")
		{
			letterT = font.LowerP;
		}
		else if (letterS == "q")
		{
			letterT = font.LowerQ;
		}
		else if (letterS == "r")
		{
			letterT = font.LowerR;
		}
		else if (letterS == "s")
		{
			letterT = font.LowerS;
		}
		else if (letterS == "t")
		{
			letterT = font.LowerT;
		}
		else if (letterS == "u")
		{
			letterT = font.LowerU;
		}
		else if (letterS == "v")
		{
			letterT = font.LowerV;
		}
		else if (letterS == "w")
		{
			letterT = font.LowerW;
		}
		else if (letterS == "x")
		{
			letterT = font.LowerX;
		}
		else if (letterS == "y")
		{
			letterT = font.LowerY;
		}
		else if (letterS == "z")
		{
			letterT = font.LowerZ;
		}
		else if (letterS == "A")
		{
			letterT = font.CapA;
		}
		else if (letterS == "B")
		{
			letterT = font.CapB;
		}
		else if (letterS == "C")
		{
			letterT = font.CapC;
		}
		else if (letterS == "D")
		{
			letterT = font.CapD;
		}
		else if (letterS == "E")
		{
			letterT = font.CapE;
		}
		else if (letterS == "F")
		{
			letterT = font.CapF;
		}
		else if (letterS == "G")
		{
			letterT = font.CapG;
		}
		else if (letterS == "H")
		{
			letterT = font.CapH;
		}
		else if (letterS == "I")
		{
			letterT = font.CapI;
		}
		else if (letterS == "J")
		{
			letterT = font.CapJ;
		}
		else if (letterS == "K")
		{
			letterT = font.CapK;
		}
		else if (letterS == "L")
		{
			letterT = font.CapL;
		}
		else if (letterS == "M")
		{
			letterT = font.CapM;
		}
		else if (letterS == "N")
		{
			letterT = font.CapN;
		}
		else if (letterS == "O")
		{
			letterT = font.CapO;
		}
		else if (letterS == "P")
		{
			letterT = font.CapP;
		}
		else if (letterS == "Q")
		{
			letterT = font.CapQ;
		}
		else if (letterS == "R")
		{
			letterT = font.CapR;
		}
		else if (letterS == "S")
		{
			letterT = font.CapS;
		}
		else if (letterS == "T")
		{
			letterT = font.CapT;
		}
		else if (letterS == "U")
		{
			letterT = font.CapU;
		}
		else if (letterS == "V")
		{
			letterT = font.CapV;
		}
		else if (letterS == "W")
		{
			letterT = font.CapW;
		}
		else if (letterS == "X")
		{
			letterT = font.CapX;
		}
		else if (letterS == "Y")
		{
			letterT = font.CapY;
		}
		else if (letterS == "Z")
		{
			letterT = font.CapZ;
		}
		else if (letterS == " ")
		{
			letterT = NULL;
		}
		else if (letterS == "1")
		{
			letterT = font.num1;
		}
		else if (letterS == "2")
		{
			letterT = font.num2;
		}
		else if (letterS == "3")
		{
			letterT = font.num3;
		}
		else if (letterS == "4")
		{
			letterT = font.num4;
		}
		else if (letterS == "5")
		{
			letterT = font.num5;
		}
		else if (letterS == "6")
		{
			letterT = font.num6;
		}
		else if (letterS == "7")
		{
			letterT = font.num7;
		}
		else if (letterS == "8")
		{
			letterT = font.num8;
		}
		else if (letterS == "9")
		{
			letterT = font.num9;
		}
		else if (letterS == "0")
		{
			letterT = font.num0;
		}
		else if (letterS == "`")
		{
			letterT = font.Acute;
		}
		else if (letterS == "~")
		{
			letterT = font.Tilde;
		}
		else if (letterS == "!")
		{
			letterT = font.ExclamationMark;
		}
		else if (letterS == "?")
		{
			letterT = font.QuestionMark;
		}
		else if (letterS == "#")
		{
			letterT = font.Pound;
		}
		else if (letterS == "$")
		{
			letterT = font.$;
		}
		else if (letterS == "%")
		{
			letterT = font.Percent;
		}
		else if (letterS == "^")
		{
			letterT = font.Caret;
		}
		else if (letterS == "&")
		{
			letterT = font.Ampersand;
		}
		else if (letterS == "*")
		{
			letterT = font.Asterisk;
		}
		else if (letterS == "(")
		{
			letterT = font.LeftParentheses;
		}
		else if (letterS == ")")
		{
			letterT = font.RightParentheses;
		}
		else if (letterS == "-")
		{
			letterT = font.Minus;
		}
		else if (letterS == "_")
		{
			letterT = font.UnderScore;
		}
		else if (letterS == "=")
		{
			letterT = font.Equals;
		}
		else if (letterS == "+")
		{
			letterT = font.Plus;
		}
		else if (letterS == "[")
		{
			letterT = font.LeftBracket;
		}
		else if (letterS == "]")
		{
			letterT = font.RightBracket;
		}
		else if (letterS == "{")
		{
			letterT = font.LeftBrace;
		}
		else if (letterS == "}")
		{
			letterT = font.RightBrace;
		}
		else if (letterS == "\\")
		{
			letterT = font.BackSlash;
		}
		else if (letterS == "|")
		{
			letterT = font.VerticalBar;
		}
		else if (letterS == ";")
		{
			letterT = font.SemiColon;
		}
		else if (letterS == ":")
		{
			letterT = font.Colon;
		}
		else if (letterS == "'")
		{
			letterT = font.Apostrophe;
		}
		else if (letterS == "\"")
		{
			letterT = font.QuotationMark;
		}
		else if (letterS == ",")
		{
			letterT = font.Comma;
		}
		else if (letterS == "<")
		{
			letterT = font.LessThan;
		}
		else if (letterS == ".")
		{
			letterT = font.Period;
		}
		else if (letterS == ">")
		{
			letterT = font.GreaterThan;
		}
		else if (letterS == "/")
		{
			letterT = font.ForwardSlash;
		}
		else if (letterS == "@")
		{
			letterT = font.At;
		}
		else
		{
			letterT = gTire;
		}
		int w, h;
		//Make it sized based on width but adding the count and TO the count each time
		SDL_QueryTexture(letterT, NULL, NULL, &w, &h);
		drawImage(offset + x, y, w, h, letterT);
		offset += w;
		//std::cout << count << std::endl;
		//std::cout << letterS << std::endl;
		count++;
	}


}














void Artist::draw()
{
	Menus menus;
	Map map;
	Editor combat;

	menus.drawMenus();
	map.drawMap();
	combat.drawEditor();


	//TEMP
	/*drawImage(0, 0, 120, 120, Tile::tileList[0].textureSet.variant1);
	Tile::tileVariantList[0].draw(120, 0, 120, 120);
	Tile::tileVariantList[1].draw(240, 0, 120, 120);
	Tile::tileVariantList[2].draw(360, 0, 120, 120);
	Tile::tileVariantList[3].draw(480, 0, 120, 120);
	drawImage(0, 120, 120, 120, Tile::tileList[1].textureSet.variant1);
	Tile::tileVariantList[4].draw(120, 120, 120, 120);
	Tile::tileVariantList[5].draw(240, 120, 120, 120);
	Tile::tileVariantList[6].draw(360, 120, 120, 120);
	Tile::tileVariantList[7].draw(480, 120, 120, 120);*/

	
}
