#ifndef GAME_TEXTGAME_LIB_SCROLLING_TEXT_SCROLLING_TEXT_H_
#define GAME_TEXTGAME_LIB_SCROLLING_TEXT_SCROLLING_TEXT_H_

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include "text.h"

using namespace game;
using namespace std;

/*
This class is used to implement scrolling
text (printing scrolling text).

Because most of this class's functionality
is handled by the Text class, this class
is a derived class of Text.

@author Rahul Kumar
*/
class ScrollingText : public Text 
{
	public:
		ScrollingText(string text, int text_lag_in_ms);
	
		void modify_text_lag(int text_lag_in_ms);
		void OutputText();
		void ModifyText(string text);
	protected:
		int text_lag_in_ms_;
		int text_length_;
};
#endif //GAME_TEXTGAME_LIB_SCROLLING_TEXT_SCROLLING_TEXT_H_
