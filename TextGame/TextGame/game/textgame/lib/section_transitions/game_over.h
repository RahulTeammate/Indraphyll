#ifndef GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_GAME_OVER_H_
#define GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_GAME_OVER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include "..\\scrolling_text\\scrolling_text.h"
#include "..\\enums\\enum_result.h"

using namespace std;

/*
This class is used to implement a Game Over.

First, a continue message is shown. Then, the 
player can choose to continue from the last 
checkpoint (Continue) or stop the game (Game Over).

@author Rahul Kumar
*/
class GameOver 
{
	public:
		GameOver();
		~GameOver();
		Result OutputText();
		
	private:
		static const int kMaxStreamSize = 700;
		static const int kPlayerInputSize = 100;
		ScrollingText * continue_msg_;
		ScrollingText * select_yes_;
		ScrollingText * select_no_;
		ScrollingText * gameover_msg_;
		ScrollingText * bad_input_msg_;
};
#endif //GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_GAME_OVER_H_