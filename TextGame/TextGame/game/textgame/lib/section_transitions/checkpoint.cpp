#include "checkpoint.h"

/*
Default Constructor
You can modify the Checkpoint message
as well as its text scroll lag
(set to 50 at the moment)
by going to checkpoint.txt.

@warning Do not add brackets to the Checkpoint message and do not remove
         the brackets that are already there.
@credit http://stackoverflow.com/questions/798798/ifstreamopen-not-working-in-visual-studio-debug-mode
        For relative paths in Windows OS.
*/
Checkpoint::Checkpoint()
{
	//get the absolute file path of checkpoint.txt (see credits).
	string path = __FILE__; 
	path = path.substr(0, 1 + path.find_last_of('\\'));
	path += "checkpoint.txt";
	//open checkpoint.txt.
	char stream[kMaxStreamSize];
	ifstream file(path);
	int text_lag_in_ms;
	string text;

	file.get(stream, kMaxStreamSize, '[');
	file.get();
	//get the text scroll lag.
	file.get(stream, kMaxStreamSize, ']');
	file.get();
	text_lag_in_ms = atoi(stream);
	//get the Checkpoint Message.
	file.get(stream, kMaxStreamSize, '[');
	text = stream;
	checkpoint_msg_ = new ScrollingText(text, text_lag_in_ms);

	file.close();
}
/*
Destructor
*/
Checkpoint::~Checkpoint()
{
	delete checkpoint_msg_;
	checkpoint_msg_ = nullptr;
}
/*
This function outputs the Checkpoint Message
as a scrolling text.

@return Result - The value of Result is always SUCCESS.
*/
Result Checkpoint::OutputText()
{
	checkpoint_msg_->OutputText();
	return SUCCESS;
}
