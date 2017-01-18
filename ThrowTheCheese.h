#ifndef _THROWTHECHEESE_H             // Prevent multiple definitions if this 
#define _THROWTHECHEESE_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include statements for related classes here
#include <stdio.h>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "object.h"
#include "cheese.h"
#include "Player.h"
#include "Spaceship.h"
<<<<<<< HEAD
<<<<<<< HEAD

#include <windows.h>
#include <conio.h>
#include <vector>
=======
#include "guicon.h"
#include <iostream>
>>>>>>> refs/remotes/origin/jason

=======
#include "gameControl.h"
>>>>>>> refs/remotes/origin/wex
//=============================================================================
// This class is the core of the game
//=============================================================================
class ThrowTheCheese : public Game
{
private:
    //texture items
	//game items
	GameControl*	gameControl=new GameControl;
	TextureManager exampleTexture;
	Image exampleImage;
    Object exampleObject;

	TextureManager backgroundTexture;
	TextureManager groundTexture;
	TextureManager cheeseTexture;
	TextureManager spaceshipTexture;
	TextureManager menu1Texture;

	Image background;
	Image ground;
	Cheese cheese;
	Spaceship enemy_spaceship;	//only one for now, testing only
	Image menu1;


<<<<<<< HEAD
	std::vector<Spaceship> spaceshipArray;
	const int maxActiveSpaceships = MAX_NO_OF_SPACESHIPS; //amt of spaceships allowed to exist (should be equal to spaceshipArray's size)
	

=======
	int playerCount;//use this value to count 1 player or 2 player
>>>>>>> refs/remotes/origin/wex
public:
	int currentActiveSpaceships; //amt of spaceships currently alive (should be less or equal to maxActiveSpaceships)

    // Constructor
	ThrowTheCheese();

    // Destructor
	virtual ~ThrowTheCheese();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
