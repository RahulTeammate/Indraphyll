#include "text_tree_node.h"

/*
Constructor
This constructor will be called for
non-root TextTreeNodes.

Sends the file reader (ifstream reference) 
to the ReadFromTxtFile function.

@param file - file reader (ifstream reference) reading the dialogue
              of the TextTreeSection (i.e. Conversation Tree) this
			  TextTreeNode is a part of.
*/
TextTreeNode::TextTreeNode(ifstream & file)
{
	question_ = nullptr; //will not initialize for leaves.
	indra_child_ = nullptr; //will not initialize for leaves.
	phil_child_ = nullptr; //will not initialize for leaves.
	conversation_ = nullptr;
	game_over_ = nullptr; //will only initialize if this is a game over leaf.
	checkpoint_ = nullptr; //will only initialize if this is a checkpoint leaf.
	ReadFromTxtFile(file);
}
/*
Constructor
This constructor will be called only
for root TextTreeNodes.

Sends the filename to the ReadFromTxtFile function.

@param filename - filename of the file containing the dialogue
                  of the TextTreeSection (i.e. Conversation Tree)
                  this TextTreeNode is a part of.
*/
TextTreeNode::TextTreeNode(const char * filename)
{
	question_ = nullptr; //will not initialize for leaves.
	indra_child_ = nullptr; //will not initialize for leaves.
	phil_child_ = nullptr; //will not initialize for leaves.
	conversation_ = nullptr;
	game_over_ = nullptr; //will only initialize if this is a game over leaf.
	checkpoint_ = nullptr; //will only initialize if this is a checkpoint leaf.
	ReadFromTxtFile(filename);
}
/*
Destructor
*/
TextTreeNode::~TextTreeNode()
{
	delete game_over_;
	delete question_;
	delete checkpoint_;
	delete conversation_;

	game_over_ = nullptr;
	question_ = nullptr;
	checkpoint_ = nullptr;
	conversation_ = nullptr;
}

/*
This function only activates if this object is a
non-root TextTreeNode.
This function takes a file reader (ifstream reference)
to initialize this object's members.

@param file - file reader (ifstream reference) reading the dialogue
              of the TextTreeSection (i.e. Conversation Tree) this
			  TextTreeNode is a part of.
@return Nothing
*/
void TextTreeNode::ReadFromTxtFile(ifstream & file) 
{
	//used for file.get() calls.
	char stream[kMaxStreamSize];
	//escape out of "[ ]" that file is in.
	file.get(stream, kMaxStreamSize, ']');
	file.get();
	conversation_ = new TextSeqSection(file,false);
	//the TextSeqSection construction stops file at
	//"[i", "[p", "[c", or "[g".

	//If file is at "[i", this function recursively constructs a TextTreeNode.
	if ((char)file.peek() == 'i')
	{
		question_ = new Question();
		indra_child_ = new TextTreeNode(file);
		//The TextTreeNode construction stops file at "[p","[c", or"[g".
	}
	//If file is at "[p", this function recursively constructs a TextTreeNode.
	if ((char)file.peek() == 'p')
	{
		question_ = new Question();
		phil_child_ = new TextTreeNode(file);
		//The TextTreeNode construction stops file at "[i","[c", or "[g".
	}
	//If file is at "[c", a Checkpoint is created.
	if ((char)file.peek() == 'c')
	{
		checkpoint_ = new Checkpoint();

		//escape out of "[checkpoint]" that file is in.
		file.get(stream, kMaxStreamSize, '[');
		file.get();
		//file is currently at "[i","[p", or "[e".
	}
	//If file is at "[g", a Game Over is created.
	if ((char)file.peek() == 'g')
	{
		game_over_ = new GameOver();

		//escape out of "[game over]" that file is in.
		file.get(stream, kMaxStreamSize, '[');
		file.get();
		//file is currently at "[i","[p", or "[e".
	}
}
/*
This function only activates if this object is a
root TextTreeNode.
This function takes a filename and opens the file with that filename.
Then, it reads the file to initialize this object's members.

@credit http://stackoverflow.com/questions/798798/ifstreamopen-not-working-in-visual-studio-debug-mode
        For relative paths in Windows OS.
@param filename - filename of the file containing the dialogue
                  of the TextTreeSection (i.e. Conversation Tree)
                  this TextTreeNode is a part of.
@return Nothing
*/
void TextTreeNode::ReadFromTxtFile(const char * filename)
{
	//get the absolute file path of filename (see credits).
	string path = __FILE__; 
	path = path.substr(0, 1 + path.find_last_of('\\'));
	path += filename;
	//create file, the file reader of filename.
	char stream[kMaxStreamSize];
	ifstream file(path);
	//escape out of "[ ]" that file is in.
	file.get(stream, kMaxStreamSize, '['); 
	file.get();
	file.get(stream, kMaxStreamSize, ']');
	file.get();
	conversation_ = new TextSeqSection(file,false);
	//the TextSeqSection construction stops file at
	//"[i", "[p", "[c", or "[g".

	//If file is at "[i", this function recursively constructs a TextTreeNode.
	if ((char)file.peek() == 'i')
	{
		question_ = new Question();
		indra_child_ = new TextTreeNode(file);
		//The TextTreeNode construction stops file at "[p","[c", or"[g".
	}
	//If file is at "[p", this function recursively constructs a TextTreeNode.
	if ((char)file.peek() == 'p')
	{
		question_ = new Question();
		phil_child_ = new TextTreeNode(file);
		//The TextTreeNode construction stops file at "[i","[c", or "[g".
	}
	//If file is at "[c", a Checkpoint is created.
	if ((char)file.peek() == 'c')
	{
		checkpoint_ = new Checkpoint();

		//escape out of "[checkpoint]" that file is in.
		file.get(stream, kMaxStreamSize, '[');
		file.get();
		//file is currently at "[e".
	}
	//If file is at "[g", a GameOver is created.
	if ((char)file.peek() == 'g')
	{	
		game_over_ = new GameOver();

		//escape out of "[game over]" that file is in.
		file.get(stream, kMaxStreamSize, '[');
		file.get();
		//file is currently at "[e".
	}

	//close file here because at this point, we have reached "[e"
	//for "[end of file]".
	file.close();
}
/*
First, this function outputs this object's dialogue.
If this object is a leaf TextTreeNode, then this 
function activates a Checkpoint or a GameOver.

If this object is a non-leaf TextTreeNode, then 
this function asks the player who responds to the dialogue.
After getting the player's response, this function
recurses down to one of this object's children TextTreeNodes.

@return Result - this is sent back to this object's respective TextTreeSection, 
                 which then affects if the Main Game Loop continues to the next
				 Section, redoes the TextTreeSection, or terminates itself.
*/
Result TextTreeNode::OutputText()
{
	//output this object's dialogue.
	conversation_->OutputText();
	
	//this object is a leaf TextTreeNode.
	if (question_ == nullptr) 
	{
		//activate a Checkpoint or GameOver, whichever exists.
		if (checkpoint_ != nullptr) 
			return checkpoint_->OutputText();
		else //game_over_ != nullptr
			return game_over_->OutputText();
	}
	//this object is a non-leaf TextTreeNode.
	else 
	{
		//ask the player who responds to the dialogue.
		Choose question_answer = question_->OutputText();
		//after getting the player's response, recurse down
		//to one of this object's children TextTreeNodes.
		if (question_answer == INDRA)
			return indra_child_->OutputText();
		else //question_answer == PHIL
			return phil_child_->OutputText();
	}
}
/*
Getter for Member indra_child_.

@return TextTreeNode * - indra_child_
*/
TextTreeNode * TextTreeNode::get_indra_child()
{
	return indra_child_;
}
/*
Getter for Member phil_child_.

@return TextTreeNode * - phil_child_
*/
TextTreeNode * TextTreeNode::get_phil_child()
{
	return phil_child_;
}
