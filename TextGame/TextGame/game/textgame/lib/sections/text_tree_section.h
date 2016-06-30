#ifndef GAME_TEXTGAME_LIB_SECTIONS_TEXT_TREE_SECTION_H_
#define GAME_TEXTGAME_LIB_SECTIONS_TEXT_TREE_SECTION_H_

#include "..\\enums\\enum_result.h"
#include "section.h"
#include "text_tree_node.h"

/*
This class is used as a Section of the Game,
therefore it is a derived class of Section.

This class simulates a Conversation Tree, where 
the player goes down the Tree by choosing if
Indra or Phil responds.

@author Rahul Kumar
*/
class TextTreeSection : public Section 
{
	public:
		TextTreeSection(const char * filename);
		virtual ~TextTreeSection();
		virtual void ReadFromTxtFile(const char * filename);
		virtual Result OutputText();
		virtual void delete_tree(TextTreeNode * curr_node);
	protected:
		TextTreeNode * root_;
};
#endif //GAME_TEXTGAME_LIB_SECTIONS_TEXT_TREE_SECTION_H_
