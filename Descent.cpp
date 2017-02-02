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
	gameControl = new GameControl();
	waveControl = new WaveControl();
	//textures
	shellTexture = new TextureManager();
	bossTexture = new TextureManager();
	backgroundTexture = new TextureManager();
	groundTexture = new TextureManager();
	cannonballTexture = new TextureManager();
	spaceshipTexture = new TextureManager();
	menu1Texture = new TextureManager();
	tankTexture = new TextureManager();
	turretTexture = new TextureManager();
	smokeTexture = new TextureManager();
	powerup_downSpeed_texture = new TextureManager();
	powerup_restoreHealth_texture = new TextureManager();

	//images
	background = new Image();
	ground = new Image();
	menu1 = new Image();
	turret = new Image();

	//entities
	cannonball = new Cannonball();
	enemy_spaceship = new Spaceship();
	boss = new Boss_Spaceship();
	tank = new Player();
	shell = new Shell();
}

//=============================================================================
// Destructor
//=============================================================================
Descent::~Descent()
{
	SAFE_DELETE(pauseText);
	SAFE_DELETE(waveNumberText);
	deleteAll();
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

	srand(time(NULL));		//seeds the RNG
	
#pragma region Initialize Assets

	//object and texture initialization

	if (!pauseText->initialize(graphics, 62, true, false, "Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	if (waveNumberText->initialize(graphics, 62, true, false, "Invasion2000") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if (!groundTexture->initialize(graphics, GROUND_TILESET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground texture"));

	if (!cannonballTexture->initialize(graphics, CANNONBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball texture"));

	if (!spaceshipTexture->initialize(graphics, SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship texture"));
	if (!menu1Texture->initialize(graphics, MENU1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	if (!tankTexture->initialize(graphics, TANK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank texture"));

	if (!backgroundTexture->initialize(graphics, BKGRND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	
	if (!ground->initialize(graphics, 0, 0, 0, groundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground tiles"));

	if (!cannonball->initialize(this, CannonballNS::WIDTH, CannonballNS::HEIGHT, CannonballNS::TEXTURE_COLS, cannonballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball game object"));

	if (!enemy_spaceship->initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, spaceshipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));
	
	if (!menu1->initialize(graphics,MENU1_WIDTH, MENU1_HEIGHT, 2, menu1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	if (!tank->initialize(this,PlayerNS::WIDTH, PlayerNS::HEIGHT, PlayerNS::TEXTURE_COLS, tankTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank"));

	if (!turretTexture->initialize(graphics, TURRET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret texture"));
	if (!turret->initialize(graphics, TURRET_WIDTH, TURRET_HEIGHT, TURRET_TEXTURE_COLUMNS, turretTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret"));

	if (!background->initialize(graphics, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, BACKGROUND_TEXTURE_COLS, backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error initialising background"));
	if (!bossTexture->initialize(graphics, BOSS_SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss texture"));
	if (!boss->initialize(this, Boss_SpaceshipNS::WIDTH, Boss_SpaceshipNS::HEIGHT, Boss_SpaceshipNS::TEXTURE_COLS, bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss game object"));

	if (!smokeTexture->initialize(graphics, SMOKE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing smoke texture"));

	if (!shellTexture->initialize(graphics, SHELL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shell texture"));
	if (!shell->initialize(this, ShellNS::WIDTH, ShellNS::HEIGHT, ShellNS::TEXTURE_COLS, shellTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shell game object"));

	if (!powerup_downSpeed_texture->initialize(graphics, POWERUP_DOWN_SPEED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (down speed) texture"));

	if (!powerup_restoreHealth_texture->initialize(graphics, POWERUP_RESTORE_HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (restore health) texture"));

	background->setFrames(BACKGROUND_START_FRAME,BACKGROUND_END_FRAME);
	background->setCurrentFrame(BACKGROUND_START_FRAME);

	ground->setX(0);
	ground->setScale(GAME_WIDTH / ground->getWidth());
	ground->setY((int)GROUND_LEVEL_HEIGHT);		//sets ground to 3/4 of game width

	cannonball->setScale(0.5);
	cannonball->setVisible(false);

	enemy_spaceship->setFrames(SpaceshipNS::START_FRAME, SpaceshipNS::END_FRAME);
	enemy_spaceship->setCurrentFrame(SpaceshipNS::START_FRAME);
	enemy_spaceship->setX(1);
	enemy_spaceship->setY(1);
	enemy_spaceship->setHealth(2); //for testing only
	enemy_spaceship->setIsAtCritical(true);

	currentActiveSpaceships = 0;
	isAllSpaceshipMovingRight = true;
	isShipsReadyToShift = false;

	//loading powerup arrays

	powerup_downSpeed = new Powerup();

	if (!powerup_downSpeed->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_downSpeed_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (down speed) object"));

	powerup_restoreHealth = new Powerup();

	if (!powerup_restoreHealth->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_restoreHealth_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (restore health) object"));

	array_powerups_drawingSpace.push_back(powerup_downSpeed);
	array_powerups_drawingSpace.push_back(powerup_restoreHealth);

	totalAmtOfPowerupVariety = array_powerups_drawingSpace.size();
	std::cout << "total amount of loaded powerups: " << totalAmtOfPowerupVariety << std::endl;

	//setting boss variables

	boss->setFrames(Boss_SpaceshipNS::START_FRAME, Boss_SpaceshipNS::END_FRAME);
	boss->setCurrentFrame(Boss_SpaceshipNS::START_FRAME);
	
	shell->setX(boss->getX()+BOSS_SPACESHIP_WIDTH/2);
	shell->setY(boss->getY()+BOSS_SPACESHIP_HEIGHT/2);
	
#pragma endregion

	initializeTank();

	std::cout << "initialising spaceship array" << std::endl;
#pragma region Spawn Spaceships
	//place inside game state wave 1 when created

	int x = 0;	//starting position of first spaceship is a unit length away the left side of the screen
	int y = 0;					//to be manipulated in first for loop

	//wave one
	std::cout << "GAME WIDTH DIVIDED BY SHIP WIDTH (spaceships per row):" << GAME_WIDTH / (HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS) << std::endl;

	for (int i = 0; i < WAVE_1_SPACESHIPS_AMT_OF_ROWS; i++)
	{
		//this for loop spawns at Y
		y += SPACESHIP_HEIGHT+VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS;	//multipled by 2 so rows are one unit height away from each other

		for (int j = 0; j < GAME_WIDTH/(SPACESHIP_WIDTH); j++)
		{
			Spaceship* spaceship = new Spaceship();

			//check if current Y can support game_width/spaceship_width amount of ships

			if (x + ((HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS+SPACESHIP_WIDTH)) > GAME_WIDTH-HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS || j >= AMT_OF_SPACESHIPS_PER_ROW)
			{
				//if current ship's X is more than game width, shift to next Y, keep current i counter

				x = HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS;	//ship starts as first ship in a new row
				break;	//means that previous row can no longer support any more spaceships without clipping, breaks and starts new row (Y)
			}

			else		
			{
				//this is true if current y can support more ships
				//create ship at X position of game_width/width*i, current row

				x = (HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS*j);
			}

			spaceship->setX(x);
			spaceship->setY(y);
			spaceship->setHealth(SPACESHIP_STARTING_HEALTH);

			if (!spaceship->initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, spaceshipTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));

			array_spaceships.push_back(spaceship);
			std::cout << "Adding spaceship at row " << i + 1 << "(no. " << j+1 << " in row) for wave one at x: " << spaceship->getX() << " y: " << spaceship->getY() << "." << std::endl;

			currentActiveSpaceships++;

			std::cout << "Current amt of spaceships: " << currentActiveSpaceships << "." << std::endl;

			if (currentActiveSpaceships == maxActiveSpaceships)
				break;

		}
		
		if (currentActiveSpaceships == maxActiveSpaceships)
			break;
		
	}

#pragma endregion


	//std::thread t(&Descent::playBGM, this); //for background music - make sure .h file has relevant method
	//t.join();
	
	std::async(&Descent::timer_start, this); //run timer thread while main loop is contiuing

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
			menu1->setCurrentFrame(MENU1_END_FRAME);
			playerCount = 2;
		}
		else if (input->isKeyDown(UP_KEY)){
			menu1->setCurrentFrame(MENU1_START_FRAME);
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
		background->update(frameTime);
		cannonball->update(frameTime);
		enemy_spaceship->update(frameTime);
		tank->update(frameTime);
		//smoke->update(frameTime);

		if (currentActiveSpaceships > 0)
		{
			//endlessly loop update for each zombie until no more zombies
			for (int i = 0; i < currentActiveSpaceships; i++)
			{
				array_spaceships[i]->update(frameTime);
			}
		}

	// checkpoints: player health = 0 -> change to end game screen
	// if boss die -> change to end game screen
	// if esc(quit pressed) -> change to end game screen
	
		if (input->isKeyDown(LEFT_KEY))
		{
			turret->setX(tank->getX() + 28.0f);
		}
		if (input->isKeyDown(RIGHT_KEY))
		{		
			turret->setX(tank->getX() + 18.0f);
		}
		if (input->wasKeyPressed(UP_KEY) || (input->wasKeyPressed(DOWN_KEY)))
		{
			switch (tank->getTankAngle()){
			default: break;
			case 20:	turret->setCurrentFrame(0);
				break;
			case 40: turret->setCurrentFrame(1);
				break;
			case 60: turret->setCurrentFrame(2);
				break;
			case 90: turret->setCurrentFrame(3);
				break;
			case 120:turret->setCurrentFrame(4);
				break;
			case 140:turret->setCurrentFrame(5);
				break;
			case 160: turret->setCurrentFrame(6);
				break;
			}
		}
		if (input->isKeyDown(SPACE_KEY))
		{
			cannonball->getTank(*tank);
			cannonball->setVisible(true);

		}
		
		if (cannonball->getY() > GROUND)
		{
			//delete(cannonball);
			cannonball->hit(land);
		}

		 switch (waveState){
			case WAVE_STATE::pauseWave:{
											//std::cout << "pause" << std::endl; 
											if (input->isKeyDown(SPACE_KEY))
												waveControl->setWaveState(WAVE_STATE::wave1);
			 }break;
			 case WAVE_STATE::wave1:{//add wave 1 behaviors
										//std::cout << "wave 1" << std::endl;
										enemy_spaceship->update(frameTime);
										if (input->wasKeyPressed(TW_KEY))
										{
											waveControl->setWaveState(WAVE_STATE::wave2);
										}
										
										 
			 }break;
			 case WAVE_STATE::wave2:{//add wave 2 enemy behavior

										shell->update(frameTime, *turret);

										std::cout << "wave 2" << std::endl;

										if (input->wasKeyPressed(TH_KEY))
										{
											waveControl->setWaveState(WAVE_STATE::wave3);
										}
			 }break;
			 case WAVE_STATE::wave3:{//add boss spaceship behaviour
										//std::cout << "wave 3" << std::endl;
										
										boss->setX(GAME_WIDTH / 4);
										boss->setY(GAME_HEIGHT / 4);
										boss->update(frameTime);

										std::cout << "BOSS BATTA " << std::endl;

			 }break;
								 
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

	if (cannonball->collidesWith(*boss, collisionVector))
	{
		cannonball->bounce(collisionVector, *boss);
		
			//std::cout << cannonball->getDamageLeft() + "COLLIDE BOSSSHIP" << std::endl;
		
		cannonball->hit(bossShip);
		
	}	

	for (int i = 0; i < array_spaceships.size(); i++)
	{
		//Zombie zombie = zombieArray[i];
		// if collision between bullet and zombies
		if (cannonball->collidesWith(*array_spaceships[i], collisionVector))
		{

			if (!cannonball->getActive())
			{
				//do nothing
			}
			else
			{
				cannonball->hit(spaceShip);
				//actual damage code

				//calculate damage from cannonball
				
				int forcePower = 20;// cannonball.getDamageLeft();	//if unavailable, use 3


				array_spaceships[i]->setHealth(array_spaceships[i]->getHealth() - forcePower);	//decreases health
				std::cout << "Spaceship " << i << " took " << forcePower << " damage." << std::endl;
				std::cout << array_spaceships[i]->getHealth() << " health left " << std::endl;

				std::cout << "Cannonball has " << cannonball->getDamageLeft() << " power left " << std::endl;

				if (array_spaceships[i]->getHealth() <= SPACESHIP_STARTING_HEALTH / SPACESHIP_CRITICAL_HEALTH_FACTOR)
				{
					array_spaceships[i]->setIsAtCritical(true);
				}

				if (cannonball->getDamageLeft() == 0)
				{
					std::cout << "Cannonball is kill" << std::endl;
					cannonball->setVisible(false);
					cannonball->setActive(false);
				}

				if (array_spaceships[i]->getHealth() <= 0)
				{
					//simple destruction (not intended for actual game)
					array_spaceships[i]->setVisible(false);
					std::cout << "Spaceship " << i << " is kill" << std::endl;
					delete array_spaceships[i];
					array_spaceships.erase(array_spaceships.begin() + i);
					currentActiveSpaceships--;
				}

			}
		}
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
								 menu1->draw();
	}break;
	case GENERAL_STATE::instructions:{
								//draw instructions
	}break;
	case GENERAL_STATE::game:{
								 background->draw();
								 ground->draw();                   // add the object to the scene
								 cannonball->draw();					//in real game, Cannonball should be drawn later, when wormhole appears
								// enemy_spaceship->draw();
								 turret->draw();
								 tank->draw();
								// smoke->draw();
								 
								 for (int i = 0; i < currentActiveSpaceships; i++)
								 {
									 array_spaceships[i]->draw();
								 }
								 
								 switch (waveControl->getWaveState())
								 {
								 case WAVE_STATE::pauseWave:{
																waveNumberText->print("Wave 1", GAME_HEIGHT / 2, GAME_WIDTH / 2); // need to change to picture
																
								 }break;
								 case WAVE_STATE::wave1:{
															enemy_spaceship->draw(); 
														//	std::cout << "wave1" << std::endl;
								 }break;//draw wave 3 stuff
								 case WAVE_STATE::wave2:{
															std::cout << "shell draw" << std::endl;
															shell->draw();
															//std::cout << "wave2" << std::endl;

								 }break;//draw wave 2 stuff
								 case WAVE_STATE::wave3:{
															
															shell->draw();
															//std::cout << "wave3" << std::endl;
															boss->draw();
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
	//exampleTexture->onLostDevice();
	backgroundTexture->onLostDevice();
	cannonballTexture->onLostDevice();
	groundTexture->onLostDevice();
	spaceshipTexture->onLostDevice();
	tankTexture->onLostDevice();
	turretTexture->onLostDevice();
	smokeTexture->onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Descent::resetAll()
{
    //exampleTexture->onResetDevice();
	backgroundTexture->onResetDevice();
	cannonballTexture->onResetDevice();
	groundTexture->onResetDevice();
	spaceshipTexture->onResetDevice();
	tankTexture->onResetDevice();
	turretTexture->onResetDevice();
	smokeTexture->onResetDevice();
    Game::resetAll();
    return;
}

//=============================================================================
// initialise the tank
//=============================================================================
void Descent::initializeTank()
{
	tank->setFrames(PlayerNS::START_FRAME, PlayerNS::END_FRAME);
	tank->setCurrentFrame(PlayerNS::START_FRAME);
	tank->setX(GAME_WIDTH / 2);
	tank->setY(GROUND_LEVEL_HEIGHT - PLAYER_HEIGHT + 2.0f);
	tank->flipHorizontal(false);

	turret->setCurrentFrame(3);
	turret->setX(tank->getX() + 28.0f);
	turret->setY(tank->getY() - 15.0f);

	cannonball->setX(tank->getX());
	cannonball->setY(tank->getY());
}

//=============================================================================
// moves all spaceships once
// constantly called by thread (timer) every X seconds
// when one spaceships hits the screen border, ALL ships shifts 1 level down and moves the other direction
//=============================================================================
void Descent::moveSpaceships()
{

	//pseudo code for this section

	//are ships moving right?
		//if yes, check for next position of every ship
			//if any ship is reaching past the screen border, update true for shipsReadyToShift
			//if not, update false for shipsReadyToShift
		//if not, do the same for above, but for left side

	//above segment is to verify if ships need to be shifted to the next row, or they just need to move in the same direction

	//is shipsReadyToShift?
		//if true, shift all ships downwards and change to opposite moving direction
		//if false, move them all towards current direction
	
	if (isAllSpaceshipMovingRight)
	{
		//spaceships are CURRENTLY moving to the right
		for (int i = 0; i < currentActiveSpaceships; i++)
		{
			if ((array_spaceships[i]->getX() + SPACESHIP_WIDTH) > GAME_WIDTH)
			{
				//ship is at edge of right wall, time to stop checking and change direction
				isShipsReadyToShift = true;
				break;
			}
			//else, ship moves as usual, continue iterating
			else
				isShipsReadyToShift = false;
		}
	}

	else
	{
		//spaceships are CURRENTLY moving to the right
		for (int i = 0; i < currentActiveSpaceships; i++)
		{
			if (array_spaceships[i]->getX() < SPACESHIP_WIDTH)
			{
				//ship is at edge of left wall, time to stop checking and change direction
				isShipsReadyToShift = true;
				break;
			}
			//else, ship moves as usual, continue iterating
			else
				isShipsReadyToShift = false;
		}
	}

	//now, every spaceship is checked if their position warrants moving the entire spaceship army downwards, or just towards its current direction

	if (isShipsReadyToShift)		//ships ready to move downwards
	{

		isAllSpaceshipMovingRight = !isAllSpaceshipMovingRight;

		for (int i = 0; i < currentActiveSpaceships; i++)
		{
			//shifts everything downwards and changes direction
			array_spaceships[i]->setY(array_spaceships[i]->getY() + VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS + SPACESHIP_HEIGHT);
			array_spaceships[i]->setIsMovingRight(isAllSpaceshipMovingRight);

			Sleep(5);

		}

	}

	else							//ships ready to move towards current direction
	{
		if (isAllSpaceshipMovingRight == true)
		{
			for (int i = 0; i < currentActiveSpaceships; i++)
			{
				array_spaceships[i]->setX(array_spaceships[i]->getX() + SPACESHIP_MOVEMENT_DISTANCE); //ships moves its width horizontally to the right
				Sleep(5);			//without this line spaceships will move unhindered, not sure why
			}
		}

		if (isAllSpaceshipMovingRight == false)
		{
			for (int i = 0; i < currentActiveSpaceships; i++)
			{
				array_spaceships[i]->setX(array_spaceships[i]->getX() - SPACESHIP_MOVEMENT_DISTANCE); //ships moves its width horizontally to the left
				Sleep(5);			//without this line spaceships will move unhindered, not sure why
			}
			
		}
	}

}

//=============================================================================
// spawns a power up
// constantly called by thread (timer) every X seconds, or called when a spaceship is destroyed at a X chance
// when one spaceships hits the screen border, ALL ships shifts 1 level down and moves the other direction
//=============================================================================
void Descent::spawnPowerup()
{
	//get random seed based on amount of possible powerups

	
	int randomPowerupIndex;

	randomPowerupIndex = (rand() % totalAmtOfPowerupVariety);

	Powerup* powerup = array_powerups_drawingSpace[randomPowerupIndex];
	//take powerup from drawing space and add to actual powerup array
	array_powerups.push_back(powerup);
	currentActivePowerups++;

	std::cout << "powerup index : " << randomPowerupIndex << " spawned" << std::endl;

}


//=============================================================================
// start and run timer
//	using thread
//=============================================================================
void Descent::timer_start()
{
	//create timer
	clock_t timer = clock();//start timer
	int currentInGameTime = 0;		//this refers to in-game time

	bool loop = true;
	while (loop)
	{

		if (gameControl->getGeneralState() == GENERAL_STATE::game)	//timer only counts down in-game
		{
			setSecondsPassed((clock() - timer) / (double)CLOCKS_PER_SEC);  //convert computer timer to real life seconds

			if ((fmod(getSecondsPassed(), SECOND*timeModifier)) == 0)
			{	

				currentInGameTime++;		//adds towards in-game seconds
				
				//std::cout << "in game seconds passed: = " << currentInGameTime << std::endl;
				//std::cout << currentInGameTime << " seconds has passed in-game. " << getSecondsPassed() << " second(s) has passed (in program)." << std::endl;

				moveSpaceships();

			}

			if ((fmod(getSecondsPassed(), POWERUP_SPAWN_FREQUENCY)) == 0)
			{
				std::cout << "spawning a powerup" << std::endl;
				spawnPowerup();
			}

		}

	}
}