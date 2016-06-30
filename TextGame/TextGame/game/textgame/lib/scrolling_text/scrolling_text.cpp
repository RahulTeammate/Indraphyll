#include "scrolling_text.h"

/*
Member Constructor
Also initializes text_length_ based on parameter text.

@param text - what member text_ will be set to.
@param text_lag_in_ms - what member text_lag_in_ms_ will be set to.
*/
ScrollingText::ScrollingText(string text, int text_lag_in_ms)
: Text(text)
{
	text_lag_in_ms_ = text_lag_in_ms;
	text_length_ = text.length();
}
/*
Modifies member text_lag_in_ms_.

@param text_lag_in_ms - what member text_lag_in_ms_ will be changed to.
*/
void ScrollingText::modify_text_lag(int text_lag_in_ms)
{
	text_lag_in_ms_ = text_lag_in_ms;
}
/*
This function outputs scrolling text to the terminal.
It achieves that by printing out text_ character-by-character,
where there is a text_lag_in_ms_ millisecond delay
between each printed character.

@return Nothing.
*/
void ScrollingText::OutputText()
{
	if (text_lag_in_ms_ == 0) 
	{
		cout << text_;
	}
	else
	{
		for (int char_index = 0; char_index < text_length_; char_index++)
		{
			//text_lag_in_ms_ millisecond delay.
			this_thread::sleep_for(chrono::milliseconds(text_lag_in_ms_));
			cout << text_[char_index];
		}
	}
}
/*
Modifies member text_, and by consequence, text_length_.

@param text_lag_in_ms - what member text_lag_in_ms_ will be changed to.
*/
void ScrollingText::ModifyText(string text)
{
	//calling the base class's ModifyText(text) modifies text_.
	Text::ModifyText(text);
	text_length_ = text_.length();
}

