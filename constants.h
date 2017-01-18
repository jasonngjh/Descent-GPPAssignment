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
const char CLASS_NAME[] = "Throw The Cheese";
const char GAME_TITLE[] = "Throw The Cheese";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 800;               // width of game in pixels
const UINT GAME_HEIGHT = 760;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 6.67428e-11f;             // gravitational constant
const float MASS_PLANET = 1.0e14f;
const float MASS_SPACE_SHIP = 5.0f;		//number subject to change
const float MASS_PLAYER = 5.0f;			//number subject to change

const int OBJECT_WIDTH = 32;
const int OBJECT_HEIGHT = 32;
const int OBJECT_TEXTURE_COLUMNS = 1;
const int OBJECT_START_FRAME = 0;
const int OBJECT_END_FRAME = 1;
const float OBJECT_MASS = 300.0f;
const float OBJECT_SPEED = 300.0f;
const float OBJECT_ANIMATION_DELAY = 0.2f;


const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 64;
const int PLAYER_TEXTURE_COLUMNS = 1;
const int PLAYER_START_FRAME = 0;
const int PLAYER_END_FRAME = 1;
const float PLAYER_MASS = 50.0f;				//number subject to change - idk what to put here
const float PLAYER_SPEED = 100.0f;			//player movement speed when going < or >
const float PLAYER_ANIMATION_DELAY = 0.2f;		//note: make player animate only when moving and throwing
const float PLAYER_BASE_STRENGTH = 25.0f;		//base strength, related to player throwing
const float PLAYER_MAX_HEALTH = 100;			//for dynamic health values, should represent health as a number

const int CHEESE_WIDTH = 32;
const int CHEESE_HEIGHT = 32;
const int CHEESE_TEXTURE_COLUMNS = 1;
const int CHEESE_START_FRAME = 0;
const int CHEESE_END_FRAME = 1;
const float CHEESE_MASS = 50.0f;				//number subject to change - idk what to put here
const float CHEESE_BASE_SPEED = 100.0f;			//base speed that cheese always moves on, MAY NOT BE RELEVANT DEPENDING ON HOW WE CALCULATE SPEED 
const float CHEESE_ANIMATION_DELAY = 0.2f;		//note: maybe cheese animates when moving 

//refers to a wormhole/blackhole image, is not an actual object. Remove if confirmed to go for tank theme instead of cheese theme
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
const float SPACESHIP_MASS = 50.0f;				//number subject to change - idk what to put here
const float SPACESHIP_SPEED = 50.0f;				
const float SPACESHIP_ANIMATION_DELAY = 0.01f;		//passively animates
const int SPACESHIP_STARTING_HEALTH = 3;

const int MAX_NO_OF_SPACESHIPS = 30; //number of spaceships allowed to exist

const int POWERUP_WIDTH = 32;
const int POWERUP_HEIGHT = 32;
const int POWERUP_TEXTURE_COLUMNS = 1;
const int POWERUP_START_FRAME = 0;
const int POWERUP_END_FRAME = 1;
const float POWERUP_ANIMATION_DELAY = 0.1f;		//passively animates

const int GROUND_LEVEL_HEIGHT = 480;			//no objects may go beyond this line, essentially means 'ground level'

//main menu frames

const int MENU1_WIDTH = GAME_WIDTH;
const int MENU1_HEIGHT = GAME_HEIGHT;
const int MENU1_TEXTURE_COLUMNS = 0;
const int MENU1_START_FRAME = 0;
const int MENU1_END_FRAME = 1;

// graphic images
const char EXAMPLE_OBJECT_IMAGE[] = "images\\[PLACEHOLDER].jpg";
const char GROUND_TILESET_IMAGE[] = "images\\ground_tile.png";
const char CHEESE_IMAGE[] = "images\\cheese.png";
const char SPACESHIP_IMAGE[] = "images\\spaceship.png";
const char MENU1_IMAGE[] = "images\\menu1.png";
// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key
const UCHAR DOWN_KEY	 = VK_DOWN;
const UCHAR UP_KEY = VK_UP;
const UCHAR SPACE_KEY = VK_SPACE;
const UCHAR LEFT_KEY = VK_LEFT;
const UCHAR RIGHT_KEY = VK_RIGHT;

#endif
