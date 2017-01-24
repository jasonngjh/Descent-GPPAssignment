/*
player(s)'s city is invaded by alien spaceships in the sky
sudddenly wormholes appear above the player and drop magical wheels of alien-destroying Cannonball
also drops a note in English that tells the player(s) to throw the Cannonball, and 
then the game starts after player presses a button

this game intentionally does not make sense

Main Menu:
* Press S to play 'Throw the Cannonball' (1 player)
* Press D to play 'Throw the Cannonball Together' (2 players)
* Press F to show credits (optional)

Instructions is shown before the game starts (during intro) so player(s) won't miss the instructions
Controls are shown during instructions and during the game so player(s) won't forget

if 2 player, color code them red and blue for clarity

*/ 

#include "Descent.h"

//=============================================================================
// Constructor
//=============================================================================
Descent::Descent()
{
	pauseText = new TextDX();

}

//=============================================================================
// Destructor
//=============================================================================
Descent::~Descent()
{
	SAFE_DELETE(pauseText);
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Descent::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	std::cout << "initialising game" << std::endl;

	//object and texture initialization
	/*
    // game item texture 
    if (!exampleTexture.initialize(graphics, EXAMPLE_OBJECT_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing example texture"));

    if (!exampleImage.initialize(graphics,0,0,0,&exampleTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing example image"));

	//initialize object
	if (!exampleObject.initialize(this, ObjectNS::WIDTH, ObjectNS::HEIGHT, ObjectNS::TEXTURE_COLS, &exampleTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing example object"));
	//lines to manipulate object (if any)
	exampleObject.setFrames(ObjectNS::START_FRAME, ObjectNS::END_FRAME);
	exampleObject.setCurrentFrame(ObjectNS::START_FRAME); 
	exampleObject.setX(GAME_WIDTH / 4);
	exampleObject.setY(GAME_HEIGHT / 4);
	//set velocity, set speed, set size, etc etc
	*/
	if (!pauseText->initialize(graphics, 62, true, false, "Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if (!groundTexture.initialize(graphics, GROUND_TILESET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground texture"));

	if (!cannonballTexture.initialize(graphics, CANNONBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball texture"));

	if (!spaceshipTexture.initialize(graphics, SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship texture"));
	if (!menu1Texture.initialize(graphics, MENU1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	if (!tankTexture.initialize(graphics, TANK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank texture"));

	if (!backgroundTexture.initialize(graphics, BKGRND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	
	if (!ground.initialize(graphics, 0, 0, 0, &groundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground tiles"));

	if (!cannonball.initialize(this, CannonballNS::WIDTH, CannonballNS::HEIGHT, CannonballNS::TEXTURE_COLS, &cannonballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball game object"));

	if (!enemy_spaceship.initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, &spaceshipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));
	
	if (!menu1.initialize(graphics,MENU1_WIDTH, MENU1_HEIGHT, 2, &menu1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	if (!tank.initialize(this,PlayerNS::WIDTH, PlayerNS::HEIGHT, PlayerNS::TEXTURE_COLS, &tankTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank"));

	if (!turretTexture.initialize(graphics, TURRET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret texture"));
	if (!turret.initialize(graphics, TURRET_WIDTH, TURRET_HEIGHT, TURRET_TEXTURE_COLUMNS, &turretTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret"));

	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error initialising background"));

	ground.setX(0);
	ground.setScale(GAME_WIDTH / ground.getWidth());
	ground.setY((int)GROUND_LEVEL_HEIGHT);		//sets ground to 3/4 of game width

	cannonball.setX(GAME_WIDTH / 2);
	cannonball.setY(GROUND_LEVEL_HEIGHT - CANNONBALL_HEIGHT);

	enemy_spaceship.setFrames(SpaceshipNS::START_FRAME, SpaceshipNS::END_FRAME);
	enemy_spaceship.setCurrentFrame(SpaceshipNS::START_FRAME);
	enemy_spaceship.setX(GAME_WIDTH / 4);
	enemy_spaceship.setY(GAME_HEIGHT / 4);

	initializeTank();

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Descent::update()
{
	//exampleObject.update(frameTime);
	cannonball.update(frameTime);
	enemy_spaceship.update(frameTime);
	tank.update(frameTime);
	//other update mechanics here

	GENERAL_STATE state = gameControl->getGeneralState();
	switch (state)
	{
	case GENERAL_STATE::menu: {
		if (input->isKeyDown(DOWN_KEY)){
			menu1.setCurrentFrame(MENU1_END_FRAME);
			playerCount = 2;
		}
		else if (input->isKeyDown(UP_KEY)){
			menu1.setCurrentFrame(MENU1_START_FRAME);
			playerCount = 1;
		}
		if (input->isKeyDown(ENTER_KEY)){
			gameControl->setGeneralState(GENERAL_STATE::game);
			//playerCount=number of players to initialise
		}
	}break;

	case GENERAL_STATE::game:{
	// checkpoints: player health = 0 -> change to end game screen
	// if boss die -> change to end game screen
	// if esc(quit pressed) -> change to end game screen
		if (input->isKeyDown(LEFT_KEY))
		{
			turret.setX(tank.getX() + 28.0f);

		}
		if (input->isKeyDown(RIGHT_KEY))
		{		
			turret.setX(tank.getX() + 18.0f);
		}
		if (input->wasKeyPressed(UP_KEY) || (input->wasKeyPressed(DOWN_KEY)))
		{
			switch (tank.getTankAngle()){
			default: break;
			case 20:	turret.setCurrentFrame(0);
				break;
			case 40: turret.setCurrentFrame(1);
				break;
			case 60: turret.setCurrentFrame(2);
				break;
			case 90: turret.setCurrentFrame(3);
				break;
			case 120:turret.setCurrentFrame(4);
				break;
			case 140:turret.setCurrentFrame(5);
				break;
			case 160: turret.setCurrentFrame(6);
				break;
			}
		}
								 
		if (input->wasKeyPressed(PAUSE_KEY))
		{

			gameControl->setGeneralState(GENERAL_STATE::paused);
		}
	}break;

	case GENERAL_STATE::paused:{
		if (input->wasKeyPressed(PAUSE_KEY))
		{

			gameControl->setGeneralState(GENERAL_STATE::game);
		}
	}break;
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Descent::ai()
{

	//no ai

}

//=============================================================================
// Handle collisions
//=============================================================================
void Descent::collisions()
{
    VECTOR2 collisionVector;
    
	//loop for multiple objects
		//if object collides with thing
			//do thing

	/*if (ship1.collidesWith(planet, collisionVector))
	{
		// bounce off planet
		ship1.bounce(collisionVector, planet);
		ship1.damage(PLANET);
	}*/


}



//=============================================================================
// Render game items
//=============================================================================
void Descent::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	switch (gameControl->getGeneralState())
	{
	case GENERAL_STATE::menu :{
								 menu1.draw();
	}break;
	case GENERAL_STATE::game:{
								 background.draw();
								 ground.draw();                   // add the object to the scene
								 cannonball.draw();					//in real game, Cannonball should be drawn later, when wormhole appears
								 enemy_spaceship.draw();
								 turret.draw();
								 tank.draw();
	}break;
	case GENERAL_STATE::paused:{
								   pauseText->print("Paused", GAME_HEIGHT / 2, GAME_WIDTH / 2);
	}
	}
    

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Descent::releaseAll()
{
	exampleTexture.onLostDevice();
	backgroundTexture.onLostDevice();
	cannonballTexture.onLostDevice();
	groundTexture.onLostDevice();
	spaceshipTexture.onLostDevice();
	tankTexture.onLostDevice();
	turretTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Descent::resetAll()
{
    exampleTexture.onResetDevice();
	backgroundTexture.onResetDevice();
	cannonballTexture.onResetDevice();
	groundTexture.onResetDevice();
	spaceshipTexture.onResetDevice();
	tankTexture.onResetDevice();
	turretTexture.onResetDevice();
    Game::resetAll();
    return;
}

//=============================================================================
// initialise the tank
//=============================================================================
void Descent::initializeTank()
{
	tank.setFrames(PlayerNS::START_FRAME, PlayerNS::END_FRAME);
	tank.setCurrentFrame(PlayerNS::START_FRAME);
	tank.setX(GAME_WIDTH / 2);
	tank.setY(GROUND_LEVEL_HEIGHT - PLAYER_HEIGHT + 2.0f);
	tank.flipHorizontal(false);

	turret.setCurrentFrame(3);
	turret.setX(tank.getX() + 28.0f);
	turret.setY(tank.getY() - 15.0f);
	
}
