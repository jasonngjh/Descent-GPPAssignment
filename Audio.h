#ifndef _AUDIO_H                 // Prevent multiple definitions if this 
#define _AUDIO_H
#define WIN32_LEAN_AND_MEAN

#include <SFML/Audio.hpp>
#include "constants.h"

sf::SoundBuffer bgmBuffer;
sf::Sound bgm;

void playBGM()
{
	if (!bgmBuffer.loadFromFile("resources/music/backgroundmusic.wav"))
		return;
	bgm.setBuffer(bgmBuffer);
	bgm.setLoop(true);
	bgm.play();
}

void stopBGM()
{
	bgm.pause();
}

void playSound()
{
	
}

#endif