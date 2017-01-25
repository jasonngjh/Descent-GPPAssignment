// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Descent";
const char GAME_TITLE[] = "Descent";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 540;               // width of game in pixels
const UINT GAME_HEIGHT = 640;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 225.5f;             // gravitational constant
const float MASS_PLANET = 5000.0;
const float MASS_SPACE_SHIP = 5.0f;		//number subject to change
const float MASS_PLAYER = 5.0f;			//number subject to change

const int OBJECT_WIDTH = 16;
const int OBJECT_HEIGHT = 16;
const int OBJECT_TEXTURE_COLUMNS = 1;
const int OBJECT_START_FRAME = 0;
const int OBJECT_END_FRAME = 1;
const float OBJECT_MASS = 300.0f;
const float OBJECT_SPEED = 300.0f;
const float OBJECT_ANIMATION_DELAY = 0.2f;


const int PLAYER_WIDTH = 81;
const int PLAYER_HEIGHT = 64;
const int PLAYER_TEXTURE_COLUMNS = 4;
const int PLAYER_START_FRAME = 0;
const int PLAYER_END_FRAME = 3;
const float PLAYER_MASS = 50.0f;				//number subject to change - idk what to put here
//const float PLAYER_SPEED = 100.0f;			//player movement speed when going < or >
const float PLAYER_ANIMATION_DELAY = 0.2f;		//note: make player animate only when moving and throwing
const float PLAYER_BASE_STRENGTH = 25.0f;		//base strength, related to player throwing
const float PLAYER_MAX_HEALTH = 100;			//for dynamic health values, should represent health as a number

const int CANNONBALL_WIDTH = 32;
const int CANNONBALL_HEIGHT = 32;
const int CANNONBALL_TEXTURE_COLUMNS = 1;
const int CANNONBALL_START_FRAME = 0;
const int CANNONBALL_END_FRAME = 1;
const float CANNONBALL_MASS = 1200.0f;				//number subject to change - idk what to put here
const float CANNONBALL_BASE_SPEED = 200.0f;			//base speed that CANNONBALL always moves on, MAY NOT BE RELEVANT DEPENDING ON HOW WE CALCULATE SPEED 
const float CANNONBALL_ANIMATION_DELAY = 0.2f;		//note: maybe Cannonball animates when moving 
const int CANNONBALL_DAMAGE = 5;

//refers to a wormhole/blackhole image, is not an actual object. Remove if confirmed to go for tank theme instead of Cannonball theme
//can also incorporate to 'explain' arrival of spaceships
//not priority
const int WORMHOLE_WIDTH = 160;			
const int WORMHOLE_HEIGHT = 160;
const int WORMHOLE_TEXTURE_COLUMNS = 1;
const int WORMHOLE_START_FRAME = 0;
const int WORMHOLE_END_FRAME = 5;
const float WORMHOLE_ANIMATION_DELAY = 0.1f;		//animation can look very cool

const int SPACESHIP_WIDTH = 58;
const int SPACESHIP_HEIGHT = 32;
const int SPACESHIP_TEXTURE_COLUMNS = 12;
const int SPACESHIP_START_FRAME = 0;
const int SPACESHIP_END_FRAME = 11;
const int SPACESHIP_DAMAGED_START_FRAME = 12;
const int SPACESHIP_DAMAGED_END_FRAME = 23;
const float SPACESHIP_MASS = 50.0f;				//number subject to change - idk what to put here
const float SPACESHIP_SPEED = 50.0f;				
const float SPACESHIP_ANIMATION_DELAY = 0.1f;		//passively animates
const int SPACESHIP_STARTING_HEALTH = 5;
const double SPACESHIP_CRITICAL_HEALTH_FACTOR = 0.25;
const int HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS = 80;	//this affects how much ships can be created in a row, if values are too high will lead to weird spaceship orientation
const int VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS = 20;	

const int MAX_NO_OF_SPACESHIPS = 30; //number of spaceships allowed to exist
const int WAVE_1_SPACESHIPS_AMT_OF_ROWS = 4;
const int WAVE_2_SPACESHIPS_AMT_OF_ROWS = 6;

const int BOSS_SPACESHIP_WIDTH = 212;
const int BOSS_SPACESHIP_HEIGHT = 265;
const int BOSS_SPACESHIP_TEXTURE_COLUMNS = 3;
const int BOSS_SPACESHIP_START_FRAME = 0;
const int BOSS_SPACESHIP_END_FRAME = 2;
const float BOSS_SPACESHIP_ANIMATION_DELAY = 0.0001f;
const int BOSS_SPACESHIP_STARTING_HEALTH = 10;

const int POWERUP_WIDTH = 32;
const int POWERUP_HEIGHT = 32;
const int POWERUP_TEXTURE_COLUMNS = 1;
const int POWERUP_START_FRAME = 0;
const int POWERUP_END_FRAME = 1;
const float POWERUP_ANIMATION_DELAY = 0.1f;		//passively animates

//individual powerup effect values
const double POWERUP_TIME_SLOW_MULTIPLER = 2; //the bigger the number the slower it gets
const double POWERUP_TIME_FAST_MULTIPLIER = 0.5; //the lower the number the faster it gets (past 0.5 it gets weird)
const int POWERUP_TIME_FREEZE_DURATION = 10; //in seconds
const int POWERUP_FORCE_MULTIPLIER = 2;

const int GROUND_LEVEL_HEIGHT = GAME_HEIGHT - GAME_HEIGHT / 10;			//no objects may go beyond this line, essentially means 'ground level'
const int SKY_LEVEL_DIVIDER = 78;

//main menu frames

const int MENU1_WIDTH = GAME_WIDTH;
const int MENU1_HEIGHT = GAME_HEIGHT;
const int MENU1_TEXTURE_COLUMNS = 0;
const int MENU1_START_FRAME = 0;
const int MENU1_END_FRAME = 1;

//turret frames
const int TURRET_WIDTH = 35;
const int TURRET_HEIGHT = 35;
const int TURRET_TEXTURE_COLUMNS = 7;

//smoke frames
const int SMOKE_WIDTH = 16;
const int SMOKE_HEIGHT = 32;
const int SMOKE_TEXTURE_COLS = 4;
const int SMOKE_START_FRAME = 0;
const int SMOKE_END_FRAME = 3;

//shell
const int SHELL_WIDTH = 18;
const int SHELL_HEIGHT = 7;
const int SHELL_START_FRAME = 0;
const int SHELL_END_FRAME = 0;
const int SHELL_TEXTURE_COLUMNS = 0;
const float SHELL_MASS = 5.0f;
const float SHELL_BASE_SPEED = 5.0f;
const float SHELL_ANIMATION_DELAY = 0.0f;
const int SHELL_DAMAGE = 10;

//background frames
const int BACKGROUND_WIDTH = 540;
const int BACKGROUND_HEIGHT = 640;
const int BACKGROUND_TEXTURE_COLS = 4;
const int BACKGROUND_START_FRAME = 0;
const int BACKGROUND_END_FRAME = 3;

// graphic images
const char EXAMPLE_OBJECT_IMAGE[] = "images\\[PLACEHOLDER].jpg";
const char GROUND_TILESET_IMAGE[] = "images\\ground_tile.png";
const char CANNONBALL_IMAGE[] = "images\\cannonball.png";
const char SPACESHIP_IMAGE[] = "images\\spaceship.png";
const char MENU1_IMAGE[] = "images\\menu1.png";
const char BOSS_SPACESHIP_IMAGE[] = "images\\boss_spaceship.png";
const char TANK_IMAGE[] = "images\\tank.png";
const char BKGRND_IMAGE[] = "images\\background.png";
const char TURRET_IMAGE[] = "images\\turret.png";
const char SMOKE_IMAGE[] = "images\\smoke.png";
const char SHELL_IMAGE[] = "images\\shell.png";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR DOWN_KEY	 = VK_DOWN;
const UCHAR SPACE_KEY = VK_SPACE;
const UCHAR UP_KEY = VK_UP;
const UCHAR LEFT_KEY = VK_LEFT;
const UCHAR RIGHT_KEY = VK_RIGHT;
const UCHAR TAB_KEY = VK_TAB;
const UCHAR PAUSE_KEY = 0x50;
const UCHAR O_KEY = 0x31;
const UCHAR TW_KEY = 0x32;
const UCHAR TH_KEY = 0x33;

enum hitWho{land,spaceShip,bossShip,player};

#endif