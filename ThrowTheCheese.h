#ifndef _THROWTHECHEESE_H             // Prevent multiple definitions if this 
#define _THROWTHECHEESE_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include statements for related classes here

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "object.h"
#include "cheese.h"
#include "Player.h"
#include "Spaceship.h"

#include <windows.h>
#include <conio.h>
#include <vector>

//=============================================================================
// This class is the core of the game
//=============================================================================
class ThrowTheCheese : public Game
{
private:
    //texture items
	//game items

	TextureManager exampleTexture;
	Image exampleImage;
    Object exampleObject;

	TextureManager backgroundTexture;
	TextureManager groundTexture;
	TextureManager cheeseTexture;
	TextureManager spaceshipTexture;

	Image background;
	Image ground;
	Cheese cheese;
	Spaceship enemy_spaceship;	//only one for now, testing only

	std::vector<Spaceship> spaceshipArray;
	const int maxActiveSpaceships = MAX_NO_OF_SPACESHIPS; //amt of spaceships allowed to exist (should be equal to spaceshipArray's size)
	

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
