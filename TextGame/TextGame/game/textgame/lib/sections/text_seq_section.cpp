#include "text_seq_section.h"

/*
Constructor

Sends the filename containing this objects's
dialogue to the ReadFromTxtFile function.
Initializes checkpoint_ if allow_checkpoint is true.

@param filename - filename containing this object's dialgoue.
@param allow_checkpoint - should a Checkpoint activate after 
                          this object finishes outputting?
*/
TextSeqSection::TextSeqSection(const char * filename, bool allow_checkpoint)
{
	if (allow_checkpoint == true)
		checkpoint_ = new Checkpoint();
	else
		checkpoint_ = nullptr;
	ReadFromTxtFile(filename);
}

/*
Constructor

Sends the file reader (ifstream reference) 
to the ReadFromTxtFile function.
Initializes checkpoint_ if allow_checkpoint is true.

@param file - file reader (ifstream reference) reading the dialogue
              that this object is a part of.
@param allow_checkpoint - should a Checkpoint activate after
                          this object finishes outputting?
*/
TextSeqSection::TextSeqSection(ifstream & file, bool allow_checkpoint)
{
	if (allow_checkpoint == true)
		checkpoint_ = new Checkpoint();
	else
		checkpoint_ = nullptr;
	ReadFromTxtFile(file);
}	
/*
Destructor
*/
TextSeqSection::~TextSeqSection()
{
	//empty the dialogue_ vector.
	vector<ScrollingText*>::iterator iter;
	for (iter = dialogue_.begin(); iter < dialogue_.end(); iter++) 
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	//delete checkpoint_
	if (checkpoint_ != nullptr) 
	{
		delete checkpoint_;
		checkpoint_ = nullptr;
	}
}
/*
This function takes a filename and opens the file with that filename.
Then, it reads the file from start to end, gathering a list of
ScrollingTexts with differing text scroll lag and putting them
into the dialogue_ vector.

@credit http://stackoverflow.com/questions/798798/ifstreamopen-not-working-in-visual-studio-debug-mode
        For relative paths in Windows OS.
@param filename - filename containing this object's dialgoue.
@return Nothing
*/
void TextSeqSection::ReadFromTxtFile(const char * filename)
{
	//get the absolute file path of filename (see credits).
	string path = __FILE__;
	path = path.substr(0, 1 + path.find_last_of('\\'));
	path += filename;
	//create file, the file reader of filename.
	char stream[kMaxStreamSize];
	ifstream file(path);
	int text_lag_in_ms;
	string text;
	//these file.get() calls are used to set up the
	//loop where file will read from start to end.
	file.get(stream, kMaxStreamSize, '[');
	file.get();

	//this loop uses file to gather each text with a different 
	//text scroll lag, create ScrollingTexts out of them, and 
	//push them into the dialogue_ vector.
	while (true) 
	{
		//get the text scroll lag
		file.get(stream, kMaxStreamSize, ']');
		file.get();
		text_lag_in_ms = atoi(stream);
		//get the text
		file.get(stream, kMaxStreamSize, '[');
		file.get();
		text = stream;
		//create and push a ScrollingText
		ScrollingText * input_dialogue = new ScrollingText(text, text_lag_in_ms);
		dialogue_.push_back(input_dialogue);
		
		//reached end of file.
		if ((char)file.peek() == 'e')
			break;
	}
}
/*
This function takes a file reader (ifstream reference)
and uses it to read and gather ScrollingTexts with differing
text scroll lag into the dialogue_ vector.

This function stops the file reader when it sees
"[i", "[p", "[c", or "[g".

@param file - file reader (ifstream reference) reading the dialogue
              that this object is a part of.
@return Nothing
*/
void TextSeqSection::ReadFromTxtFile(ifstream & file)
{
	//used for file.get() calls.
	char stream[kMaxStreamSize];
	int text_lag_in_ms;
	string text;
	//these file.get() calls are used to set up the
	//loop where file will read until it sees "[i", "[p", "[c", or "[g".
	file.get(stream, kMaxStreamSize, '[');
	file.get();

	//this loop uses file to gather each text with a different 
	//text scroll lag, create ScrollingTexts out of them, and 
	//push them into the dialogue_ vector.
	while (true)
	{
		//get the text scroll lag
		file.get(stream, kMaxStreamSize, ']');
		file.get();
		text_lag_in_ms = atoi(stream);
		//get the text
		file.get(stream, kMaxStreamSize, '[');
		text = stream;
		file.get();
		//create and push a ScrollingText
		ScrollingText * input_dialogue = new ScrollingText(text, text_lag_in_ms);
		dialogue_.push_back(input_dialogue);

		//reached "[i", "[p", "[c", or "[g".
		char next_char = (char)file.peek();
		if (next_char == 'c' || next_char == 'g' || next_char == 'i' || next_char == 'p') 
			break;
	}
}
/*
This function outputs all ScrollingTexts
from the dialogue_ vector.

Then, if a Checkpoint was initialized, the
Checkpoint will activate.

@return Result - The value of Result is always SUCCESS.
*/
Result TextSeqSection::OutputText()
{
	//output all the ScrollingTexts from dialogue_.
	vector<ScrollingText*>::iterator iter;
	for (iter = dialogue_.begin(); iter < dialogue_.end(); iter++) 
		(*iter)->OutputText();
	//activate the checkpoint if it was initialized.
	if (checkpoint_ != nullptr)
		return checkpoint_->OutputText();
	return SUCCESS;
}
