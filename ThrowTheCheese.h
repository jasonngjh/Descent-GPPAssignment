#ifndef _THROWTHECHEESE_H             // Prevent multiple definitions if this 
#define _THROWTHECHEESE_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include statements for related classes here

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "object.h"
#include "cheese.h"

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


	Cheese cheese;

public:
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
