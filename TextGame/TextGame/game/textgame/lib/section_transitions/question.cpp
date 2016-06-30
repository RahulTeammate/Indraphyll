#include "question.h"

/*
Default Constructor
You can modify the 2 Question messages
as well as each message's text scroll lag
(set to 50,30 at the moment) by going to question.txt.

@warning Do not add brackets to the 2 messages and do not remove
         the brackets that are already there.
@credit http://stackoverflow.com/questions/798798/ifstreamopen-not-working-in-visual-studio-debug-mode
        For relative paths in Windows OS.
*/
Question::Question()
{
	//get the absolute file path of question.txt (see credits).
	string path = __FILE__;
	path = path.substr(0, 1 + path.find_last_of('\\'));
	path += "question.txt";
	//open question.txt.
	char stream[kMaxStreamSize];
	ifstream file(path);
	int text_lag_in_ms;
	string text;

	//get the Question Message and its text scroll lag.
	file.get(stream, kMaxStreamSize, '[');
	file.get(); 
	file.get(stream, kMaxStreamSize, ']');
	file.get(); 
	text_lag_in_ms = atoi(stream);
	file.get(stream, kMaxStreamSize, '#');
	text = stream;
	question_msg_ = new ScrollingText(text, text_lag_in_ms);
	//get the Bad Input (Player Error) Message and its text scroll lag.
	file.get(stream, kMaxStreamSize, '[');
	file.get(); 
	file.get(stream, kMaxStreamSize, ']');
	file.get(); 
	text_lag_in_ms = atoi(stream);
	file.get(stream, kMaxStreamSize, '[');
	text = stream;
	bad_input_msg_ = new ScrollingText(text, text_lag_in_ms);

	file.close();
}
/*
Destructor
*/
Question::~Question()
{
	delete question_msg_;
	delete bad_input_msg_;

	question_msg_ = nullptr;
	bad_input_msg_ = nullptr;
}

/*
This function outputs the Question
Message and gets the player's input.

If the player inputs "i", the game has Indra speak and
continue down the Conversation Tree.
If the player inputs "p", the game has Phil speak and
continue down the Conversation Tree.
Else, the game gives the Bad Input message and re-prompts
the player to give an input.

@return Result - INDRA if player inputs "i"
                 PHIL if player inputs "p"
*/
Choose Question::OutputText()
{
	bool chose_valid_choice = false;
	//give the Question message.
	question_msg_->OutputText();
	Choose choice;

	while (!chose_valid_choice)
	{
		//prompt the user for input.
		char player_input[kPlayerInputSize];
		cout << "> ";
		cin >> player_input;

		//if the user inputted "i" or "I"
		if (_strcmpi(player_input, "i") == 0)
		{
			choice = INDRA;
			chose_valid_choice = true;
		}
		//if the user inputted "p" or "P"
		else if (_strcmpi(player_input, "p") == 0)
		{
			choice = PHIL;
			chose_valid_choice = true;
		}
		else
		{
			//give the Bad Input Message.
			bad_input_msg_->OutputText();
		}
	}
	return choice;
}
