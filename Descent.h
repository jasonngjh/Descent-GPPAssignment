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
#include "bosslaser.h"
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
#include "Audio.h"
#include <string>

//=============================================================================
// This class is the core of the game
//=============================================================================
class Descent : public Game
{
private:
	TextDX* pauseText;
	TextDX* waveNumberText;
	TextDX* powerup_notification_text;
	TextDX* highscoreText;
	GameControl	gameControl;
	WaveControl	waveControl;
	GENERAL_STATE currentState;

	TextureManager* shellTexture;
	TextureManager* bossTexture;
	TextureManager* backgroundTexture;
	TextureManager* groundTexture;
	TextureManager* cannonballTexture;
	TextureManager* spaceshipTexture;
	TextureManager* spaceship_bulletTexture;
	TextureManager* menuTexture;
	TextureManager* tankTexture;
	TextureManager* turretTexture;
	TextureManager* pauseTexture;
	TextureManager* instructionTexture;
	TextureManager* gamewinTexture;
	TextureManager* gameloseTexture;
	TextureManager* bossLaserTexture;
	TextureManager* assistTankTexture;
	TextureManager* assistTankBulletTexture;
	TextureManager* powerup_timeSlow_texture;
	TextureManager* powerup_shield_texture;
	TextureManager* powerup_increaseTankSpeed_texture;
	TextureManager* powerup_timeLock_texture;
	TextureManager* powerup_maxPower_texture;
	TextureManager* powerup_passerbyTank_texture;
	TextureManager* tankHealthTexture;
	TextureManager* loadingTexture;
	TextureManager* wormholeTexture;
	TextureManager* creditsTexture;

	Image* background;
	Image* pause;
	Image* instructionScreen;
	Image* loading;
	Image* ground;
	Image* menu;
	Image* turret;
	Image* gamewin;
	Image* gamelose;
	Image* tankHealth;
	Image* wormhole;
	Image* credits;

	Cannonball* cannonball;
	Boss_Spaceship* boss;
	Player* tank;
	Shell* shell;
	Assist_Tank* assistTank;

	Powerup* powerup_timeSlow;
	Powerup* powerup_shield;
	Powerup* powerup_increaseTankSpeed;
	Powerup* powerup_timeLock;
	Powerup* powerup_maxPower;
	Powerup* powerup_passerbyTank;

	std::vector<Spaceship*> array_spaceships;
	std::vector<Audio*> audio;
	std::vector<BossLaser*> array_bosslaser;
	BossLaser* bosslaser;
	std::vector<Spaceship_bullet*> array_spaceship_bullets;
	std::vector<Powerup*> array_powerups_drawingSpace;			//the vector where all different types of powerups are initialized
	std::vector<Powerup*> array_powerups;
	std::vector<Assist_Tank_bullet*> array_tank_assist_bullets;	//to store attacks by friendly NPC tank

	const int maxActiveSpaceships = MAX_NO_OF_SPACESHIPS; //amt of spaceships allowed to exist (should be equal to spaceshipArray's size)
	const int maxActiveSpaceshipBullets = MAX_NO_OF_SPACESHIP_BULLETS;
	const int maxActivePowerups = MAX_NO_OF_POWERUPS;
	const int maxActiveAssistTankBullets = MAX_NO_OF_ASSIST_TANK_BULLETS;

	int highestY;
	int currentScore;
	int playerCount = 1;

	bool isBossLevelInitialised = true;
	int waveNumber = 1;
	double secondsPassed;
	double shellStartSeconds;
	int pauseScreen = 0;
	int gameOverScreen = 0;
	float array[3];
	float array_angle[3];
	int laserCounter = 0;
	bool existOnScreen = true;
	bool missileFire=true;
	int gameStatus= 0;
	bool mainGameTimerLoop = true;
	//modifiers
	int timeModifier = GAME_BASE_TIME_MODIFIER; //Default value is 1, value affects time - this value will multiply by 1 second to achieve new time
	int speedModifier = GAME_BASE_SPEED_MODIFIER; //Default value is 1, value affects speed - this value will be multiplied by speed values to achieve new speed
	double playerDamageTakenModifier = PLAYER_DAMAGE_TAKEN_MODIFIER;
	
public:
	//limiter and counter variables
	int currentActiveSpaceships;			//amt of spaceships currently alive (should be dynamically less or equal to maxActiveSpaceships)
	int currentActiveSpaceshipBullets;		//amt of spaceship bullets active
	int currentActivePowerups;				//amt of powerups currently in the game as objects (NOT the ones in effect)
	int totalAmtOfPowerupVariety;			//for use with array_powerups_drawingSpace, keeps track of amount of hard-coded powerup effects
	int currentActiveTankAssistBullets;
	int maxAmountOfAllowedBulletsPerVolley;

	//misc variables

	int hiscore;
	int comboSpaceshipCounter;		//to check how much spaceships has been destroyd by a single cannonball

	int acquiredPlayerSpeed;
	bool acquiredPlayerDirectionIsRight;

	//game check variables
	bool isAllSpaceshipMovingRight;			//keeps track of ship direction
	bool isShipsReadyToShift;				//keeps track of ship movement, for use in downwards movement
	bool isCurrentScoreHighestScore;		// keeps track of high-scoring
	bool isPowerupInProgress;		//checks if there is currently an active powerup
	bool isPowerupSpawning;
	bool isCalculatingPlayerPattern;		//to prevent multiple instances of pattern acquirement
	bool isAllSpaceshipsFiring;
	bool isGameWaiting = false;			//to check if the game is in 'break time'
	bool isWaveReadyToBegin = false;	//to check if game/wave is ready for player

	bool hasWaveOneSpawned = false;
	bool hasWaveTwoSpawned = false;
	bool hasWaveThreeSpawned = false;

	int currentWaveNumber = 0;
	bool isNextLevelBossLevel = false;

	//music-related boolean
	bool hasDefeatSoundPlayed = false;
	bool hasVictorySoundPlayed = false;

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
	void initializeBoss();
	void moveSpaceships();
	void spawnPowerup();

	void timer_start();
	void beginGameBreakTime();
	void setTanks();
	void checkGamestatus();
	void resetShellPos();
	void launchBossLaser();
	void powerup_timer_start();
	void restartGame();

	void beginSimpleSpaceshipsFiringSequence();
	void beginAdvancedSpaceshipsFiringSequence();

	double getSecondsPassed() { return secondsPassed; }
	void setSecondsPassed(double seconds) { secondsPassed = seconds; }

	int getTimeModifier() { return timeModifier; }
	void setTimeModifier(int modifyingValue) { timeModifier = modifyingValue; }

	int getSpeedModifier() { return speedModifier; }
	void setSpeedModifier(int modifyingValue) { speedModifier = modifyingValue; }

	double getPlayerDamageTakenModifier() { return playerDamageTakenModifier; }
	void setPlayerDamageTakenModifier(double modifyingValue) { playerDamageTakenModifier = modifyingValue; }

	void acquirePlayerMovementPatterns();
	void applyPowerupEffect(int powerupCode);
	void applyPowerupEffect_timeSlow();
	void applyPowerupEffect_shield();
	void applyPowerupEffect_increaseTankSpeed();
	void applyPowerupEffect_timeLock();
	void applyPowerupEffect_maxPower();
	void applyPowerupEffect_tankAssist();
	void addToScore(int scoreToAdd);
	void spawnSpaceships(int waveNumber);
	void despawnSpaceships();
	void despawnPowerups();
	void despawnPowerupsDrawingSpace();
	void despawnSpaceshipBullets();
	void despawnAssistTankBullets();
	void loadHighScore();
	void refreshCannonball();

};
#endif