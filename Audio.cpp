#include "Audio.h"

//=============================================================================
// default constructor
//=============================================================================
Audio::Audio()
{
	bgmBuffer = new sf::SoundBuffer();
	tankBuffer = new sf::SoundBuffer();
}

//=============================================================================
// deconstructor
//=============================================================================
Audio::~Audio()
{
	delete bgmBuffer;
	delete tankBuffer;
}

//=============================================================================
// playBGM
// play background music of the game
//=============================================================================
void Audio::playBGM()
{
	if (!bgmBuffer->loadFromFile("resources/music/background.ogg"))
		return;
	bgm.setBuffer(*bgmBuffer);
	bgm.setLoop(true);
	bgm.play();
}

//=============================================================================
// stopBGM
// stop background music of the game
//=============================================================================
void Audio::stopBGM()
{
	bgm.pause();
}

//=============================================================================
// playTankSounds
// stop background music of the game
//=============================================================================
void Audio::playTankSounds(std::string fileLocation)
{
	if (!tankBuffer->loadFromFile(fileLocation))
		return;
	sf::Sound tank;
	tank.setBuffer(*bgmBuffer);
	tank.setLoop(true);
	tank.play();
}