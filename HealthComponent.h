#ifndef _HEALTHCOMPONENT_H                 // Prevent multiple definitions if this 
#define _HEALTHCOMPONENT_H                    // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"

class HealthComponent
{
private:
	int		currentHealth;
	int		totalHealth;
	bool	isAlive;
public:
	// constructor
	HealthComponent();

	//any other relevant methods here
	void setHealth();

};
#endif

