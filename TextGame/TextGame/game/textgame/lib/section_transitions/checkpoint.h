#ifndef GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_CHECKPOINT_H_
#define GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_CHECKPOINT_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include "..\\enums\\enum_result.h"
#include "..\\scrolling_text\\scrolling_text.h"

using namespace std;

/*
This class is used to display
Checkpoint messages to the player.

@author Rahul Kumar
*/
class Checkpoint 
{
	public:
		Checkpoint();
		~Checkpoint();
		Result OutputText();
		
	private:
		static const int kMaxStreamSize = 700;
		ScrollingText * checkpoint_msg_;
};
#endif //GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_CHECKPOINT_H_