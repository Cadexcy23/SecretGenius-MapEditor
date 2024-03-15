#pragma once
#ifndef Character
#include "Spawn.h"
#endif
class Editor {
public:
	static int selectedCharID;


	void controlEditor(int input);

	void drawEditor();

};