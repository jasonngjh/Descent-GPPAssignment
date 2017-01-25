#ifndef _ANIMATION_H_
#define _ANIMATION_H

#include "Player.h"
#include "Spaceship.h"
#include "Cannonball.h"

class animation
{
	//constructor
	animation();

	// Destructor
	virtual ~animation();

public:
	void blinkEffect(Player player)
	{
		
	}

	void blinkEffect(Spaceship spaceship)
	{

	}

	void blinkEffect(Cannonball cannonball)
	{

	}

};

#endif // !_ANIMATION_H
