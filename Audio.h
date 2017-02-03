#ifndef _AUDIO_H                 // Prevent multiple definitions if this 
#define _AUDIO_H
#define WIN32_LEAN_AND_MEAN

#include <SFML/Audio.hpp>
#include "constants.h"
#include <iostream>


class Audio
{
private:
	sf::SoundBuffer* bgmBuffer;
	sf::Sound bgm;
	sf::SoundBuffer* tankBuffer;
	sf::SoundBuffer spaceshipBuffer;
	sf::Sound spaceship;

public:
	//constructor
	Audio();

	//destructor
	~Audio();

	//additional methods here
	void playBGM();
	void stopBGM();
	void playTankSounds(std::string);
};

#endif