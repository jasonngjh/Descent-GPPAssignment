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
#include "Spaceship_bullet.h"
#include "powerup.h"
#include "Assist_Tank.h"
#include "Assist_Tank_bullet.h"
#include "Boss_Spaceship.h"
#include "shell.h"

#include "guicon.h"
#include "gameControl.h"
#include "waveControl.h"
#include "textDX.h"
#include "animation.h"

#include <windows.h>
#include <time.h>
#include <conio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <functional>
#include <ctime>
#include <future>
#include <string>


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
	TextDX* pauseText;
	TextDX* waveNumberText;
	TextDX* powerup_notification_text;
	GameControl*	gameControl;
	WaveControl*	waveControl;

	TextureManager* shellTexture;
	TextureManager* bossTexture;
	TextureManager* backgroundTexture;
	TextureManager* groundTexture;
	TextureManager* cannonballTexture;
	TextureManager* spaceshipTexture;
	TextureManager* spaceship_bulletTexture;
	TextureManager* menu1Texture;
	TextureManager* tankTexture;
	TextureManager* turretTexture;
	TextureManager* smokeTexture;
	TextureManager* assistTankTexture;
	TextureManager* assistTankBulletTexture;

	TextureManager* powerup_timeSlow_texture;
	TextureManager* powerup_restoreHealth_texture;
	TextureManager* powerup_increaseTankSpeed_texture;
	TextureManager* powerup_timeLock_texture;
	TextureManager* powerup_maxPower_texture;
	TextureManager* powerup_passerbyTank_texture;

	Image* background;
	Image* ground;
	Image* menu1;
	Image* turret;

	Cannonball* cannonball;
	Spaceship* enemy_spaceship;	//only one for now, testing only
	Boss_Spaceship* boss;
	int waveNumber=1;
	Player* tank;
	Shell* shell;
	Assist_Tank* assistTank;

	Powerup* powerup_timeSlow;
	Powerup* powerup_restoreHealth;
	Powerup* powerup_increaseTankSpeed;
	Powerup* powerup_timeLock;
	Powerup* powerup_maxPower;
	Powerup* powerup_passerbyTank;

	std::vector<Spaceship*> array_spaceships;
	std::vector<Spaceship_bullet*> array_spaceship_bullets;
	std::vector<Powerup*> array_powerups_drawingSpace;			//the vector where all different types of powerups are initialized
	std::vector<Powerup*> array_powerups;
	std::vector<Assist_Tank_bullet*> array_tank_assist_bullets;	//to store attacks by friendly NPC tank

	const int maxActiveSpaceships = MAX_NO_OF_SPACESHIPS; //amt of spaceships allowed to exist (should be equal to spaceshipArray's size)
	const int maxActiveSpaceshipBullets = MAX_NO_OF_SPACESHIP_BULLETS;
	const int maxActivePowerups = MAX_NO_OF_POWERUPS;
	const int maxActiveAssistTankBullets = MAX_NO_OF_ASSIST_TANK_BULLETS;

	int playerCount;//use this value to count 1 player or 2 player
	int highestY;
	int currentScore;

	//modifiers
	int timeModifier = GAME_BASE_TIME_MODIFIER; //Default value is 1, value affects time - this value will multiply by 1 second to achieve new time
	int speedModifier = GAME_BASE_SPEED_MODIFIER; //Default value is 1, value affects speed - this value will be multiplied by speed values to achieve new speed
	double secondsPassed;


public:
	int currentActiveSpaceships;			//amt of spaceships currently alive (should be dynamically less or equal to maxActiveSpaceships)
	int currentActiveSpaceshipBullets;		//amt of spaceship bullets active
	int currentActivePowerups;				//amt of powerups currently in the game as objects (NOT the ones in effect)
	int totalAmtOfPowerupVariety;			//for use with array_powerups_drawingSpace, keeps track of amount of hard-coded powerup effects
	int currentActiveTankAssistBullets;
	int maxAmountOfAllowedBulletsPerVolley;

	int hiscore;
	int comboSpaceshipCounter;		//to check how much spaceships has been destroyd by a single cannonball

	int acquiredPlayerSpeed;
	bool acquiredPlayerDirectionIsRight;

	bool isAllSpaceshipMovingRight;			//keeps track of ship direction
	bool isShipsReadyToShift;				//keeps track of ship movement, for use in downwards movement
	bool isCurrentScoreHighestScore;		// keeps track of high-scoring
	bool isPowerupInProgress;		//checks if there is currently an active powerup
	bool isPowerupSpawning;
	bool isCalculatingPlayerPattern;		//to prevent multiple instances of pattern acquirement
	bool isAllSpaceshipsFiring;

	bool hasWaveOneSpawned = false;
	bool hasWaveTwoSpawned = false;
	bool hasWaveThreeSpawned = false;

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
	void moveSpaceships();
	void spawnPowerup();

	void timer_start();
	void powerup_timer_start();

	void beginSimpleSpaceshipsFiringSequence();
	void beginAdvancedSpaceshipsFiringSequence();

	double getSecondsPassed() { return secondsPassed; }
	void setSecondsPassed(double seconds) { secondsPassed = seconds; }

	int getTimeModifier() { return timeModifier; }
	void setTimeModifier(int modifyingValue) { timeModifier = modifyingValue; }

	int getSpeedModifier() { return speedModifier; }
	void setSpeedModifier(int modifyingValue) { speedModifier = modifyingValue; }

	void acquirePlayerMovementPatterns();

	void applyPowerupEffect(int powerupCode);

	void applyPowerupEffect_timeSlow();
	void applyPowerupEffect_restoreHealth();
	void applyPowerupEffect_increaseTankSpeed();
	void applyPowerupEffect_timeLock();
	void applyPowerupEffect_maxPower();
	void applyPowerupEffect_tankAssist();

	void addToScore(int scoreToAdd);

	void spawnSpaceships(int waveNumber);
	void despawnSpaceships();		

	void loadHighScore();

};

#endif