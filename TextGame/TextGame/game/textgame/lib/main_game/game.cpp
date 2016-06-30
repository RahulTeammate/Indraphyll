#include "game.h"
/*
Default Constructor
The constructor reads section_types.txt line by line.
Each line in section_types.txt contains 3 attributes for a
Section that will be loaded into the game.

1. The file containing this Section's dialogue.
2. Is this Section a TextSeqSection (Wall of Text) or 
   TextTreeSection (Conversation Tree)?
3. N/A - This Section is a TextTreeSection
   true - This Section has a checkpoint after it outputs all of its text.
   false - This Section has no checkpoint after it outputs all of its text.

For each line of section_types.txt, the constructor
creates a TextSeqSection or TextTreeSection and pushes it
into the scenes vector.

@credit http://stackoverflow.com/questions/798798/ifstreamopen-not-working-in-visual-studio-debug-mode
        For relative paths in Windows OS.
*/
Game::Game()
{
	//get the absolute file path of section_types.txt (see credits).
	string path = __FILE__;
	path = path.substr(0, 1 + path.find_last_of('\\'));
	path += "..\\section_scripts\\section_types.txt"; 
	//open section_types.txt.
	char stream[kMaxStreamSize];
	ifstream file(path);

	//read section_types.txt line-by-line
	while (file.getline(stream,kMaxStreamSize)) 
	{
		stringstream line(stream);
		string section_file;
		string section_type;
		bool give_checkpoint;
		string section_filepath;

		//gather the 3 attributes from this line.
		line >> section_file >> section_type >> std::boolalpha >> give_checkpoint;
		//create the relative path to the file containing this Section's dialogue.
		section_filepath = "..\\section_scripts\\";
		section_filepath += section_file;
		//use the 3 attributes to create a TextSeqSection or TextTreeSection.
		if (section_type == "TextSeqSection")
			scenes_.push_back(new TextSeqSection(section_filepath.c_str(), give_checkpoint));
		else
			scenes_.push_back(new TextTreeSection(section_filepath.c_str()));
	}
	file.close();
}
/*
Destructor
*/
Game::~Game()
{
	//empty the scenes_ vector
	vector<Section*>::iterator iter;
	for (iter = scenes_.begin(); iter < scenes_.end(); iter++) 
	{
		delete (*iter);
		(*iter) = nullptr;
	}
}

/*
This function is the Main Game Loop.
It plays through all Sections of the Game object,
and ends either when the player refuses to continue 
after a Game Over, or the player beats all the Sections.

@return Nothing
*/
void Game::OutputText()
{
	vector<Section*>::iterator iter = scenes_.begin();

	while (iter < scenes_.end()) 
	{
		//run the gameplay of this Section.
		Result scene_result = (*iter)->OutputText();
		//use the Result of the gameplay
		//to decide how the player transitions in the game.
		if (scene_result == SUCCESS)
			iter++;
		else if (scene_result == FAIL_GAME_OVER)
			break;
		//scene_result == FAIL_TRY_AGAIN, reloop Section.
	}
}
