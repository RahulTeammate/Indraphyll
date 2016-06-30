#include "text.h"

using namespace game;

/*
Member Constructor

@param text - what member text_ will be set to.
*/
Text::Text(string text)
{
	text_ = text;
}
/*
Outputs text_ to the terminal.

@return Nothing
*/
void Text::OutputText()
{
	cout << text_;
}
/*
Modifies member text_.

@param text - what member text_ will be changed to.
@return Nothing
*/
void Text::ModifyText(string text)
{
	text_ = text;
}
