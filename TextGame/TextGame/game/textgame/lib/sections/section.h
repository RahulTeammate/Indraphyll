#ifndef GAME_TEXTGAME_LIB_SECTIONS_SECTION_H_
#define GAME_TEXTGAME_LIB_SECTIONS_SECTION_H_

#include "..\\enums\\enum_result.h"

/*
This class is a base class for 
independent sections of the game.

All sections of this game first read their
dialogue from a txt file and then output their
dialogue when prompted by the Main Game Loop.

@author Rahul Kumar
*/
class Section 
{
	public:
		virtual ~Section() = 0;
		virtual void ReadFromTxtFile(const char * filename) = 0;
		virtual Result OutputText() = 0;
};
#endif //GAME_TEXTGAME_LIB_SECTIONS_SECTION_H_