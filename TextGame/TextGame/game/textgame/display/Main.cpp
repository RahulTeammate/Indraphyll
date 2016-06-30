//Includes
#include "..\lib\main_game\game.h"
//Namespaces
using namespace std;

/*
The main function, which creates
and activates the Game.

@return int 0
*/
int main()
{
	Game * game = new Game();
	game->OutputText();
	return 0;
}