#ifndef GAME_TEXTGAME_LIB_MAIN_GAME_GAME_H_
#define GAME_TEXTGAME_LIB_MAIN_GAME_GAME_H_


#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "..\\enums\\enum_result.h"
#include "..\\sections\\section.h"
#include "..\\sections\\text_tree_section.h"
#include "..\\sections\\text_seq_section.h"

using namespace std;

/*
This class contains the main game.
Users should only use this class to play the game.

@author Rahul Kumar
*/
class Game
{
	public:
		Game();
		~Game();
		void OutputText();
	private:
		static const int kMaxStreamSize = 100;
		vector<Section*> scenes_;
};
#endif //GAME_TEXTGAME_LIB_MAIN_GAME_GAME_H_
