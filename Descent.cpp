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
	waveNumberText = new TextDX();

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

	if (pauseText->initialize(graphics, 62, true, false, "Invasion2000") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	if (waveNumberText->initialize(graphics, 62, true, false, "Invasion2000") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if (!groundTexture.initialize(graphics, GROUND_TILESET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground texture"));

	if (!cannonballTexture.initialize(graphics, CANNONBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball texture"));

	if (!spaceshipTexture.initialize(graphics, SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship texture"));
	
	if (!menu1Texture.initialize(graphics, MENU1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	if (!ground.initialize(graphics, 0, 0, 0, &groundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground tiles"));

	if (!cannonball.initialize(this, CannonballNS::WIDTH, CannonballNS::HEIGHT, CannonballNS::TEXTURE_COLS, &cannonballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball game object"));

	if (!enemy_spaceship.initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, &spaceshipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));
	
	if (!menu1.initialize(graphics,MENU1_WIDTH, MENU1_HEIGHT, 2, &menu1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if (!bossTexture.initialize(graphics, BOSS_SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss texture"));
	if (!boss.initialize(this, Boss_SpaceshipNS::WIDTH, Boss_SpaceshipNS::HEIGHT, Boss_SpaceshipNS::TEXTURE_COLS, &bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss game object"));


	ground.setX(0);
	ground.setScale(GAME_WIDTH / ground.getWidth());
	ground.setY(GROUND_LEVEL_HEIGHT);		//sets ground to 3/4 of game width

	cannonball.setX(CannonballNS::X);
	cannonball.setY(CannonballNS::Y);
	cannonball.setVelocity(VECTOR2(CannonballNS::BASE_SPEED, -CannonballNS::BASE_SPEED));

	enemy_spaceship.setFrames(SpaceshipNS::START_FRAME, SpaceshipNS::END_FRAME);
	enemy_spaceship.setCurrentFrame(SpaceshipNS::START_FRAME);
	enemy_spaceship.setX(GAME_WIDTH / 4);
	enemy_spaceship.setY(GAME_HEIGHT / 4);


	//enemy_spaceship.setLoop(false);

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Descent::update()
{
	//exampleObject.update(frameTime);
	//cannonball.update(frameTime);
	//enemy_spaceship.update(frameTime);
	
	//other update mechanics here

	GENERAL_STATE state = gameControl->getGeneralState();
	WAVE_STATE waveState = waveControl->getWaveState();
	switch (state)
	{
	case GENERAL_STATE::menu: {
								  
									if (input->isKeyDown(DOWN_KEY)){
										menu1.setCurrentFrame(MENU1_END_FRAME);
										playerCount=2;
									}
									else if (input->isKeyDown(UP_KEY)){
										menu1.setCurrentFrame(MENU1_START_FRAME);
										playerCount=1;
									}
									if (input->isKeyDown(ENTER_KEY)){
									gameControl->setGeneralState(GENERAL_STATE::instructions);
									//playerCount=number of players to initialise
									}
	}break;
	case GENERAL_STATE::instructions : {
										   if (input->isKeyDown(TAB_KEY)){
											   gameControl->setGeneralState(GENERAL_STATE::game);
										   }
	}break;
	case GENERAL_STATE::game:{
								 cannonball.update(frameTime);
								 // checkpoints: player health = 0 -> change to end game screen
								 // if boss die -> change to end game screen
								 // if esc(quit pressed) -> change to end game screen
								 // TRY TO MOVE CONTROLS TO THE SPECIFIC CLASS FOR REUSABILITY ******************************************
								 if (cannonball.getY() > GAME_HEIGHT - 50)
								 {
									 cannonball.hit(land);
									 cannonball.update(frameTime);

								 }

								 if (input->wasKeyPressed(PAUSE_KEY))
								 {
									
									 gameControl->setGeneralState(GENERAL_STATE::paused);
								 }
								 switch (waveState){
								 case WAVE_STATE::pauseWave:{
																std::cout << "pause" << std::endl; 
																if (input->isKeyDown(SPACE_KEY))
																	waveControl->setWaveState(WAVE_STATE::wave1);
								 }break;
								 case WAVE_STATE::wave1:{//add wave 1 behaviors
															std::cout << "wave 1" << std::endl;
															enemy_spaceship.update(frameTime);
															if (input->wasKeyPressed(LEFT_KEY))
															{
																waveControl->setWaveState(WAVE_STATE::wave2);
															}
															 
								 }break;
								 case WAVE_STATE::wave2:{//add wave 2 enemy behavior
															std::cout << "wave 2" << std::endl;
															if (input->wasKeyPressed(RIGHT_KEY))
															{
																waveControl->setWaveState(WAVE_STATE::wave3);
															}
								 }break;
								 case WAVE_STATE::wave3:{//add boss spaceship behaviour
															std::cout << "wave 3" << std::endl;
															boss.setFrames(Boss_SpaceshipNS::START_FRAME, Boss_SpaceshipNS::END_FRAME);
															boss.setCurrentFrame(Boss_SpaceshipNS::START_FRAME);
															boss.setX(GAME_WIDTH / 4);
															boss.setY(GAME_HEIGHT / 4);
															boss.update(frameTime);

															
								 }break;
								 
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
	if (cannonball.collidesWith(enemy_spaceship, collisionVector))
	{
		cannonball.bounce(collisionVector, enemy_spaceship);
		cannonball.hit(spaceShip);
		std::cout << "COLLIDE SPACESHIP" << std::endl;
	}
	if (cannonball.collidesWith(boss, collisionVector))
	{
		cannonball.bounce(collisionVector, boss);
		
			std::cout << cannonball.getDamageLeft() + "COLLIDE BOSSSHIP" << std::endl;
		
		cannonball.hit(bossShip);
		
	}

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
	case GENERAL_STATE::instructions:{
								//draw instructions
	}break;
	case GENERAL_STATE::game:{
								 ground.draw();                   // add the object to the scene
								 cannonball.draw();					//in real game, Cannonball should be drawn later, when wormhole appears
								 
								 switch (waveControl->getWaveState())
								 {
								 case WAVE_STATE::pauseWave:{
																waveNumberText->print("Wave 1", GAME_HEIGHT / 2, GAME_WIDTH / 2); // need to change to picture
																
								 }break;
								 case WAVE_STATE::wave1:{
															enemy_spaceship.draw(); 
														//	std::cout << "wave1" << std::endl;
								 }break;//draw wave 3 stuff
								 case WAVE_STATE::wave2:{
															//std::cout << "wave2" << std::endl;

								 }break;//draw wave 2 stuff
								 case WAVE_STATE::wave3:{
															
															//std::cout << "wave3" << std::endl;
															boss.draw();
								 }break;//draw boss wave stuff
								 }

	}break;
	case GENERAL_STATE::paused:{
								   pauseText->print("Paused", GAME_HEIGHT / 2, GAME_WIDTH / 2);
	}break;
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
	cannonballTexture.onLostDevice();
	groundTexture.onLostDevice();
	spaceshipTexture.onLostDevice();
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
	cannonballTexture.onResetDevice();
	groundTexture.onResetDevice();
	spaceshipTexture.onResetDevice();
    Game::resetAll();
    return;
}
