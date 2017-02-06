#ifndef _AUDIO_H                 // Prevent multiple definitions if this 
#define _AUDIO_H
#define WIN32_LEAN_AND_MEAN

#include <SFML/Audio.hpp>
#include "constants.h"
#include <iostream>


class Audio
{

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string _source;

public:
	//constructor
	Audio(std::string source);

	//destructor
	~Audio();

	//additional methods here
	void loadAudio();
	void play();
	void stop();
	void setLoop(bool);
};

#endif