#ifndef GAME_TEXTGAME_LIB_SCROLLING_TEXT_TEXT_H_
#define GAME_TEXTGAME_LIB_SCROLLING_TEXT_TEXT_H_

#include <iostream>
#include <string>

using namespace std;

/*
This class is a wrapper for the string object,
used as a base class for ScrollingText 
(printing scrolling text).

I wrapped this class around a namespace because
this class's name conflicts with other class names
from std.

@author Rahul Kumar
*/
namespace game 
{
class Text 
{
	public:
		Text(string text);
		void OutputText();
		void ModifyText(string text);
	protected:
		string text_;
};
}
#endif //GAME_TEXTGAME_LIB_SCROLLING_TEXT_TEXT_H_