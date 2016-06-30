#ifndef GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_QUESTION_H_
#define GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_QUESTION_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include "..\\enums\\enum_choose.h"
#include "..\\scrolling_text\\scrolling_text.h"

using namespace std;

/*
This class is used to implement a Question to the player.

It asks whether the player wants Indra or Phil to continue
the conversation in a TextTreeSection (Conversation Tree).

@author Rahul Kumar
*/
class Question 
{
	public:
		Question();
		~Question();
		Choose OutputText();
		
	private:
		static const int kMaxStreamSize = 700;
		static const int kPlayerInputSize = 100;
		ScrollingText * question_msg_;
		ScrollingText * bad_input_msg_;
};
#endif //GAME_TEXTGAME_LIB_SECTION_TRANSITIONS_QUESTION_H_