#ifndef GAME_TEXTGAME_LIB_SECTIONS_TEXT_TREE_NODE_H_
#define GAME_TEXTGAME_LIB_SECTIONS_TEXT_TREE_NODE_H_

#include "..\\section_transitions\\checkpoint.h"
#include "..\\section_transitions\\game_over.h"
#include "..\\section_transitions\\question.h"
#include "..\\scrolling_text\\scrolling_text.h"
#include "text_seq_section.h"

/*
This class is used as a Node of a TextTreeSection (i.e. Conversation Tree).

This class will first output the dialogue stored within itself. 
Then, if this class is a non-leaf TextTreeNode, it will ask the player 
if Indra or Phil responds to the dialogue.

If the player chooses Indra, then this class goes to the child TextTreeNode
pertaining to Indra. Similarly, if the player chooses Phil, 
then this class goes to the child TextTreeNode pertaining to Phil.

If this class is a leaf TextTreeNode, it will contain either a GameOver
or Checkpoint object. Those two will be used to notify the player
if the path they chose down the TextTreeSection (i.e. Conversation Tree)
results in a Game Over or Checkpoint.

@author Rahul Kumar
*/
class TextTreeNode {
	public:
		TextTreeNode(ifstream & file);
		TextTreeNode(const char * filename);
		~TextTreeNode();

		virtual void ReadFromTxtFile(const char * filename);
		virtual void ReadFromTxtFile(ifstream & file);
		virtual Result OutputText();

		virtual TextTreeNode * get_indra_child();
		virtual TextTreeNode * get_phil_child();
	private:
		static const int kMaxStreamSize = 700;

		GameOver * game_over_;
		Question * question_;
		Checkpoint * checkpoint_;
		TextTreeNode * indra_child_;
		TextTreeNode * phil_child_;
		TextSeqSection * conversation_;
};
#endif //GAME_TEXTGAME_LIB_SECTIONS_TEXT_TREE_NODE_H_
