#ifndef GAME_TEXTGAME_LIB_SECTIONS_TEXT_SEQ_SECTION_H_
#define GAME_TEXTGAME_LIB_SECTIONS_TEXT_SEQ_SECTION_H_


#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "..\\enums\\enum_result.h"
#include "..\\scrolling_text\\scrolling_text.h"
#include "..\\section_transitions\\checkpoint.h"
#include "section.h"

using namespace std;

/*
This class is used as a Section of the Game,
therefore it is a derived class of Section.

This class is effectively a list of scrolling texts, 
where each scrolling text has different text scroll lag.

This class simulates a Wall of Text where the player
doesn't give any input.

@author Rahul Kumar
*/
class TextSeqSection : public Section 
{
	public:
		TextSeqSection(const char * filename, bool allow_checkpoint);
		TextSeqSection(ifstream & file, bool allow_checkpoint);
		virtual ~TextSeqSection();

		virtual void ReadFromTxtFile(const char * filename);
		virtual void ReadFromTxtFile(ifstream & file);
		virtual Result OutputText();
	protected:
		static const int kMaxStreamSize = 1000;
		vector<ScrollingText*> dialogue_;
		Checkpoint * checkpoint_;
};
#endif //GAME_TEXTGAME_LIB_SECTIONS_TEXT_SEQ_SECTION_H_
