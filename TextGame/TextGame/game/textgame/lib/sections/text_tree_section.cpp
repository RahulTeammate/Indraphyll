#include "text_tree_section.h"

/*
Constructor

Sends the filename containing this objects's
dialogue to the ReadFromTxtFile function.

@param filename - filename containing this object's dialgoue.
*/
TextTreeSection::TextTreeSection(const char * filename)
{
	ReadFromTxtFile(filename);
}
/*
Destructor

Calls a helper function to recursively
destruct root_.
*/
TextTreeSection::~TextTreeSection()
{
	delete_tree(root_);
}
/*
This function begins to read in this object's dialogue
by creating the root of this object (i.e. root of the Conversation Tree).
The recursive nature of the TextTreeNode constructor gathers 
all of this object's dialogue.

@param filename - filename containing this object's dialgoue.
@return Nothing
*/
void TextTreeSection::ReadFromTxtFile(const char * filename)
{
	root_ = new TextTreeNode(filename);
}
/*
This function outputs this object's dialogue (as
a Conversation Tree) by starting at the root of
this object (i.e. root of the Conversation Tree).

After reaching a leaf (of the Conversation Tree), 
this function returns the Result of that leaf,
which affects how the Main Game Loop continues.

@return Result - Makes the Main Game Loop continue to the next Section,
                 redo this Section, or terminate itself.
*/
Result TextTreeSection::OutputText()
{
	return root_->OutputText();
}
/*
This helper function deletes all the
heap allocated memory associated with
a TextTreeNode.

@param curr_node - current node this function is deleting.
@return Nothing.
*/
void TextTreeSection::delete_tree(TextTreeNode * curr_node)
{
	TextTreeNode * indra = curr_node->get_indra_child();
	TextTreeNode * phil = curr_node->get_phil_child();
	//delete indra recursively.
	if (indra != nullptr)
		delete_tree(indra);
	//delete phil recursively.
	if (phil != nullptr)
		delete_tree(phil);
	//delete curr_node.
	delete curr_node;
	curr_node = nullptr;
}
