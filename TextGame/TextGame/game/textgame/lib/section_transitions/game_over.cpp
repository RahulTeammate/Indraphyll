#include "game_over.h"

/*
Default Constructor
You can modify the 5 GameOver messages
as well as each message's text scroll lag 
(set to 50,50,50,30,500 at the moment) 
by going to game_over.txt.

@warning Do not add brackets to the 5 messages and do not remove
         the brackets that are already there.
@credit http://stackoverflow.com/questions/798798/ifstreamopen-not-working-in-visual-studio-debug-mode
        For relative paths in Windows OS.
*/
GameOver::GameOver()
{
	//get the absolute file path of game_over.txt (see credits).
	string path = __FILE__;
	path = path.substr(0, 1 + path.find_last_of('\\'));
	path += "game_over.txt";
	//open game_over.txt.
	char stream[kMaxStreamSize];
	ifstream file(path);
	int text_lag_in_ms;
	string text;

	//get the Try Again Message and its text scroll lag.
	file.get(stream, kMaxStreamSize, '[');
	file.get();
	file.get(stream, kMaxStreamSize, ']');
	file.get();
	text_lag_in_ms = atoi(stream);
	file.get(stream, kMaxStreamSize, '#');
	text = stream;
	continue_msg_ = new ScrollingText(text, text_lag_in_ms);
	//get the Select Yes (to Continue Question) Message and its text scroll lag.
	file.get(stream, kMaxStreamSize, '[');
	file.get(); 
	file.get(stream, kMaxStreamSize, ']');
	file.get(); 
	text_lag_in_ms = atoi(stream);
	file.get(stream, kMaxStreamSize, '#');
	text = stream;
	select_yes_ = new ScrollingText(text, text_lag_in_ms);
	//get the Select No (to Continue Question) Message and its text scroll lag.
	file.get(stream, kMaxStreamSize, '[');
	file.get(); 
	file.get(stream, kMaxStreamSize, ']');
	file.get(); 
	text_lag_in_ms = atoi(stream);
	file.get(stream, kMaxStreamSize, '#');
	text = stream;
	select_no_ = new ScrollingText(text, text_lag_in_ms);
	//get the Game Over Message and its text scroll lag.
	file.get(stream, kMaxStreamSize, '[');
	file.get(); 
	file.get(stream, kMaxStreamSize, ']');
	file.get(); 
	text_lag_in_ms = atoi(stream);
	file.get(stream, kMaxStreamSize, '#');
	text = stream;
	gameover_msg_ = new ScrollingText(text, text_lag_in_ms);
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
GameOver::~GameOver()
{
	delete continue_msg_;
	delete select_yes_;
	delete select_no_;
	delete gameover_msg_;
	delete bad_input_msg_;

	continue_msg_ = nullptr;
	select_yes_ = nullptr;
	select_no_ = nullptr;
	gameover_msg_ = nullptr;
	bad_input_msg_ = nullptr;
}

/*
This function outputs the Try Again
Message and gets the player's input.

If the player inputs "y", the game gives the Select Yes Message,
and the game resumes from the previous checkpoint.
If the player inputs "n", the game gives the Select No Message,
then the Game Over Message, then terminates the game.
Else, the game gives the Bad Input message and re-prompts
the player to give an input.

@return Result - FAIL_TRY_AGAIN if player inputs "y"
                 FAIL_GAME_OVER if player inputs "n"
*/
Result GameOver::OutputText()
{
	bool chose_valid_choice = false;
	//give the Try Again message.
	continue_msg_->OutputText();
	Result choice;

	while (!chose_valid_choice)
	{
		//prompt the user for input.
		char player_input[kPlayerInputSize];
		cout << "> ";
		cin >> player_input;

		//if the user inputted "y" or "Y"
		if (_strcmpi(player_input, "y") == 0)
		{
			//give the Select Yes Message.
			select_yes_->OutputText();
			choice = FAIL_TRY_AGAIN;
			chose_valid_choice = true;
		}
		//if the user inputted "n" or "N"
		else if (_strcmpi(player_input, "n") == 0)
		{
			//give the Select No Message, then the Game Over Message.
			select_no_->OutputText();
			gameover_msg_->OutputText();
			choice = FAIL_GAME_OVER;
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
