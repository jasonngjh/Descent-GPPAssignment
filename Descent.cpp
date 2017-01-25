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
	SAFE_DELETE(waveNumberText);
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
	if (!bossTexture.initialize(graphics, BOSS_SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss texture"));
	if (!boss.initialize(this, Boss_SpaceshipNS::WIDTH, Boss_SpaceshipNS::HEIGHT, Boss_SpaceshipNS::TEXTURE_COLS, &bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss game object"));

	ground.setX(0);
	ground.setScale(GAME_WIDTH / ground.getWidth());
	ground.setY((int)GROUND_LEVEL_HEIGHT);		//sets ground to 3/4 of game width

	cannonball.setX(GAME_WIDTH / 2);
	cannonball.setY(GROUND_LEVEL_HEIGHT - CANNONBALL_HEIGHT);

	enemy_spaceship.setFrames(SpaceshipNS::START_FRAME, SpaceshipNS::END_FRAME);
	enemy_spaceship.setCurrentFrame(SpaceshipNS::START_FRAME);
	enemy_spaceship.setX(1);
	enemy_spaceship.setY(1);
	enemy_spaceship.setHealth(2); //for testing only
	enemy_spaceship.setIsAtCritical(true);
	
	initializeTank();

	std::cout << "initialising spaceship array" << std::endl;

	int x = SPACESHIP_WIDTH;
	int y = 0;

	//wave one
	
	for (int i = 0; i < WAVE_1_SPACESHIPS_AMT_OF_ROWS; i++)
	{

		//spawn at y
		y += SPACESHIP_HEIGHT*2;

		std::cout << GAME_WIDTH / (SPACESHIP_WIDTH * 2.5) << std::endl;

		for (int j = 0; j < GAME_WIDTH/(SPACESHIP_WIDTH); j++)
		{
			Spaceship spaceship;

			//check if current Y can support game_width/spaceship_width amount of ships
			//if yes, create spaceship at game_width/width*i

			//if no, shift to next Y, keep current i counter

			if (x + SPACESHIP_WIDTH > GAME_WIDTH)
			{
				x = 0;//SPACESHIP_WIDTH;
			}

			else
			{
				x = SPACESHIP_WIDTH + (GAME_WIDTH / SPACESHIP_WIDTH)*(j + 1) + (SPACESHIP_WIDTH*j);
			}

			spaceship.setX(x);
			spaceship.setY(y);

			//previous loop can no longer support current Y

			if (!spaceship.initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, &spaceshipTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));

			array_spaceships.push_back(spaceship);
			std::cout << "Adding spaceship at row " << i + 1 << "(no. " << j+1 << " in row) for wave one at x: " << spaceship.getX() << " y: " << spaceship.getY() << "." << std::endl;

			currentActiveSpaceships++;

			std::cout << "Current amt of spaceships: " << currentActiveSpaceships << "." << std::endl;
			//zombieArray[i].update(ship, frameTime);
		}
		if (!shellTexture.initialize(graphics, SHELL_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shell texture"));
		if (!shell.initialize(this, ShellNS::WIDTH, ShellNS::HEIGHT, ShellNS::TEXTURE_COLS, &shellTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shell game object"));

		
	}

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Descent::update()
{
	//exampleObject.update(frameTime);
	//other update mechanics here

	GENERAL_STATE state = gameControl->getGeneralState();
	WAVE_STATE waveState = waveControl->getWaveState();
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
		enemy_spaceship.update(frameTime);
		tank.update(frameTime);
		
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
		
		if (cannonball.getY() > GAME_HEIGHT - 50)
		 {
			 cannonball.hit(land);
			 cannonball.update(frameTime);

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
										if (input->wasKeyPressed(TW_KEY))
										{
											waveControl->setWaveState(WAVE_STATE::wave2);
										}
										 
			 }break;
			 case WAVE_STATE::wave2:{//add wave 2 enemy behavior
										shell.update(frameTime);
										std::cout << "wave 2" << std::endl;

										
										
										
										if (input->wasKeyPressed(TH_KEY))
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
		
		if (input->wasKeyPressed(PAUSE_KEY))
		{

			gameControl->setGeneralState(GENERAL_STATE::paused);
		}

		if (currentActiveSpaceships > 0)
		{
			//endlessly loop update for each zombie until no more zombies
			for (int i = 0; i < currentActiveSpaceships; i++)
			{
			//std::cout << "looping spaceship" << std::endl;
			array_spaceships[i].update(frameTime);
			}
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
								 background.draw();
								 ground.draw();                   // add the object to the scene
								 cannonball.draw();					//in real game, Cannonball should be drawn later, when wormhole appears
								// enemy_spaceship.draw();
								 turret.draw();
								 tank.draw();
								 
								 for (int i = 0; i < currentActiveSpaceships; i++)
								 {
									 array_spaceships[i].draw();
								 }
								 
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
															std::cout << "shell draw" << std::endl;
															shell.draw();
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