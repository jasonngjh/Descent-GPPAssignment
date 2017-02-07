#ifndef _DESCENT_H             // Prevent multiple definitions if this 
#define _DESCENT_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include statements for related classes here
//#include <stdio.h>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "cannonball.h"
#include "Player.h"
#include "Spaceship.h"
#include "Boss_Spaceship.h"
#include "bosslaser.h"
#include "shell.h"

#include "guicon.h"
#include "gameControl.h"
#include "waveControl.h"
#include "textDX.h"
#include "animation.h"

#include <windows.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <thread>
#include <functional>
#include <ctime>
#include <future>
#include "Audio.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Descent : public Game
{
private:
	TextDX* pauseText;
	TextDX* waveNumberText;
	GameControl*	gameControl;
	WaveControl*	waveControl;
	GENERAL_STATE currentState;

	TextureManager* shellTexture;
	TextureManager* bossTexture;
	TextureManager* backgroundTexture;
	TextureManager* groundTexture;
	TextureManager* cannonballTexture;
	TextureManager* spaceshipTexture;
	TextureManager* menu1Texture;
	TextureManager* tankTexture;
	TextureManager* tank2Texture;
	TextureManager* turretTexture;
	TextureManager* smokeTexture;
	TextureManager* pauseTexture;
	TextureManager* instructionTexture;
	TextureManager* gamewinTexture;
	TextureManager* gameloseTexture;
	TextureManager* bossLaserTexture;

	Image* background;
	Image* pause;
	Image* instructionScreen;
	Image* ground;
	Image* menu1;
	Image* turret;
	Image* turret2;
	Image* gamewin;
	Image* gamelose;

	Cannonball* cannonball;
	Cannonball* cannonball2;
	Spaceship* enemy_spaceship;	//only one for now, testing only
	Boss_Spaceship* boss;
	Player* tank;
	Player* tank2;
	Shell* shell;
	std::vector<Spaceship*> array_spaceships;
	std::vector<Audio*> audio;
	std::vector<BossLaser*> array_bosslaser;
	BossLaser* bosslaser;
	
	bool initAlready = true;
	int waveNumber = 1;
	int playerCount = 1;//use this value to count 1 player or 2 player
	double secondsPassed;
	int pauseScreen=0;
	int gameOverScreen = 0;
	float array[3];
	int laserCounter = 0;
	bool existOnScreen = true;
	bool missileFire=true;

	//modifiers
	int timeModifier = GAME_BASE_TIME_MODIFIER; //Default value is 1, value affects time - this value will multiply by 1 second to achieve new time
	int speedModifier = GAME_BASE_SPEED_MODIFIER; //Default value is 1, value affects speed - this value will be multiplied by speed values to achieve new speed

	int gameStatus= 0;

public:
	int currentActiveSpaceships; //amt of spaceships currently alive (should be dynamically less or equal to maxActiveSpaceships)
	bool isAllSpaceshipMovingRight;	//keeps track of ship direction
	bool isShipsReadyToShift;		//keeps track of ship movement, for use in downwards movement

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
	void loadAudio(std::string source);
	void loadAllAudio();
	void initializeTank();
	void moveSpaceships(bool isMovingRight);
	void timer_start();
	void setTanks();
	void checkGamestatus();
	void resetShellPos();
	void launchBossLaser();

	double getSecondsPassed() { return secondsPassed; }
	void setSecondsPassed(double seconds) { secondsPassed = seconds; }

	int getTimeModifier() { return timeModifier; }
	void setTimeModifier(int modifyingValue) { timeModifier = modifyingValue; }

	int getSpeedModifier() { return speedModifier; }
	void setSpeedModifier(int modifyingValue) { speedModifier = modifyingValue; }

};
#endif