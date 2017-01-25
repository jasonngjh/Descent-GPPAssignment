#ifndef _DESCENT_H             // Prevent multiple definitions if this 
#define _DESCENT_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include statements for related classes here
#include <stdio.h>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "object.h"
#include "cannonball.h"
#include "Player.h"
#include "Spaceship.h"
#include "Boss_Spaceship.h"
#include "shell.h"

#include <windows.h>
#include <conio.h>
#include <vector>
#include "guicon.h"
#include <iostream>

#include "gameControl.h"
#include "waveControl.h"
#include "textDX.h"
#include <thread>
#include "animation.h"
//=============================================================================
// This class is the core of the game
//=============================================================================
class Descent : public Game
{
private:
    //texture items
	//game items
	
	TextureManager exampleTexture;
	Image exampleImage;
    Object exampleObject;
	TextDX* pauseText;
	TextDX* waveNumberText;
	GameControl*	gameControl = new GameControl;
	WaveControl*	waveControl = new WaveControl;

	TextureManager shellTexture;
	TextureManager bossTexture;
	TextureManager backgroundTexture;
	TextureManager groundTexture;
	TextureManager cannonballTexture;
	TextureManager spaceshipTexture;
	TextureManager menu1Texture;
	TextureManager tankTexture;
	TextureManager turretTexture;
	TextureManager smokeTexture;

	Image background;
	Image ground;
	Image smoke;
	Cannonball cannonball;
	Spaceship enemy_spaceship;	//only one for now, testing only
	Image menu1;
	//Boss_Spaceship boss;
	Boss_Spaceship boss;
	int waveNumber=1;
	Player tank;
	Image turret;
	Shell shell;
	std::vector<Spaceship> spaceshipArray;
	std::vector<Spaceship> array_spaceships;
	const int maxActiveSpaceships = MAX_NO_OF_SPACESHIPS; //amt of spaceships allowed to exist (should be equal to spaceshipArray's size)
	
	int playerCount;//use this value to count 1 player or 2 player
	int highestY;

public:
	int currentActiveSpaceships=0; //amt of spaceships currently alive (should be less or equal to maxActiveSpaceships)

    // Constructor
	Descent();

    // Destructor
	virtual ~Descent();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	//other functions
	void initializeTank();
};

#endif
