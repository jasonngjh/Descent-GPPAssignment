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
	pauseTexture = new TextureManager();
	instructionTexture = new TextureManager();

	//images
	background = new Image();
	ground = new Image();
	menu1 = new Image();
	turret = new Image();
	pause = new Image();
	instructionScreen = new Image();

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
	releaseAll();           // call onLostDevice() for every graphics item
	SAFE_DELETE(pauseText);
	SAFE_DELETE(waveNumberText);
	delete gameControl;
	//delete waveControl;
	delete background;
	delete ground;
	delete menu1;
	delete instructionScreen;
	delete turret;
	delete pause;
	delete cannonball;
	delete enemy_spaceship;
	delete boss;
	delete shell;
	for (Spaceship* spaceShip : array_spaceships)
	{
		delete spaceShip;
	}
	for (Audio* a : audio)
	{
		delete a;
	}
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Descent::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	std::cout << "initialising game" << std::endl;
	
#pragma region Initialize Assets

	//object and texture initialization

	if (!pauseText->initialize(graphics, 62, true, false, "Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
	if (waveNumberText->initialize(graphics, 62, true, false,"Invasion2000") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if (!groundTexture->initialize(graphics, GROUND_TILESET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground texture"));

	if (!cannonballTexture->initialize(graphics, CANNONBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball texture"));

	if (!spaceshipTexture->initialize(graphics, SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship texture"));
	if (!menu1Texture->initialize(graphics, MENU1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!pauseTexture->initialize(graphics, PAUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause texture"));

	if (!tankTexture->initialize(graphics, TANK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank texture"));

	if (!cannonball->initialize(this, CannonballNS::WIDTH, CannonballNS::HEIGHT, CannonballNS::TEXTURE_COLS, cannonballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball game object"));

	if (!backgroundTexture->initialize(graphics, BKGRND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	if (!instructionTexture->initialize(graphics, INSTRUCTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction texture"));
	
	if (!ground->initialize(graphics, 0, 0, 0, groundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground tiles"));

	if (!enemy_spaceship->initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, spaceshipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));
	
	if (!menu1->initialize(graphics,MENU1_WIDTH, MENU1_HEIGHT, 2, menu1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	if (!pause->initialize(graphics, PAUSE_WIDTH, PAUSE_HEIGHT, 2, pauseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause screen"));

	if (!tank->initialize(this,PlayerNS::WIDTH, PlayerNS::HEIGHT, PlayerNS::TEXTURE_COLS, tankTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank"));

	if (!turretTexture->initialize(graphics, TURRET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret texture"));
	if (!turret->initialize(graphics, TURRET_WIDTH, TURRET_HEIGHT, TURRET_TEXTURE_COLUMNS, turretTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret"));

	if (!background->initialize(graphics, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, BACKGROUND_TEXTURE_COLS, backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,"Error initialising background"));

	if (!instructionScreen->initialize(graphics, INSTRUCTIONS_WIDTH, INSTRUCTIONS_HEIGHT, INSTRUCTIONS_TEXTURE_COLUMNS, instructionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction screen"));

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

	background->setFrames(BACKGROUND_START_FRAME,BACKGROUND_END_FRAME);
	background->setCurrentFrame(BACKGROUND_START_FRAME);

	loadAllAudio();
	audio[0]->setLoop(true); // background music
	audio[0]->play();

	ground->setX(0);
	ground->setScale((float)(GAME_WIDTH / ground->getWidth()));
	ground->setY((int)GROUND_LEVEL_HEIGHT);		//sets ground to 3/4 of game width

	enemy_spaceship->setFrames(SpaceshipNS::START_FRAME, SpaceshipNS::END_FRAME);
	enemy_spaceship->setCurrentFrame(SpaceshipNS::START_FRAME);
	enemy_spaceship->setX(1);
	enemy_spaceship->setY(1);
	enemy_spaceship->setHealth(2); //for testing only
	enemy_spaceship->setIsAtCritical(true);

	currentActiveSpaceships = 0;
	isAllSpaceshipMovingRight = true;
	isShipsReadyToShift = false;

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
				std::cout << "Current x: " << x << "->" << std::endl;
			}

			spaceship->setX((float)x);
			spaceship->setY((float)y);
			spaceship->setHealth(SPACESHIP_STARTING_HEALTH);

			if (!spaceship->initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, spaceshipTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));

			array_spaceships.push_back(spaceship);
			std::cout << "Adding spaceship at row " << i + 1 << "(no. " << j+1 << " in row) for wave one at x: " << spaceship->getX() << " y: " << spaceship->getY() << "." << std::endl;

			currentActiveSpaceships++;

			std::cout << "Current amt of spaceships: " << currentActiveSpaceships << "." << std::endl;

			if (currentActiveSpaceships == MAX_NO_OF_SPACESHIPS)
				break;
		}
		
		if (currentActiveSpaceships == MAX_NO_OF_SPACESHIPS)
			break;
		
	}

#pragma endregion
	
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
		if (input->wasKeyPressed(ENTER_KEY)){
			gameControl->setGeneralState(GENERAL_STATE::instructions);
			//playerCount=number of players to initialise
		}
	}break;
	case GENERAL_STATE::instructions : {
										   if (input->wasKeyPressed(SPACE_KEY)){
											   Sleep(300);
											   gameControl->setGeneralState(GENERAL_STATE::game);		  
										   }
	}break;

	case GENERAL_STATE::game:{
		background->update(frameTime);
		tank->update(frameTime);

		if (currentActiveSpaceships > 0)
		{
			//endlessly loop update for each zombie until no more zombies
			for (int i = 0; i < currentActiveSpaceships; i++)
			{
				//std::cout << "looping spaceship" << std::endl;
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

		if (input->wasKeyPressed(SPACE_KEY))
		{
			cannonball->getTank(tank);
		}
		 cannonball->update(frameTime);
		 cannonball->updateChargingBar(frameTime, tank->getX());

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

		if (input->isKeyDown(DOWN_KEY)){
			pause->setCurrentFrame(PAUSE_END_FRAME);
			pauseScreen = 1;
		}
		else if (input->isKeyDown(UP_KEY)){
			pause->setCurrentFrame(PAUSE_START_FRAME);
			pauseScreen = 0;
		}
		if (input->wasKeyPressed(ENTER_KEY)){
			Sleep(500);
			switch (pauseScreen)
			{
			case 0: gameControl->setGeneralState(GENERAL_STATE::game);
				break;
			case 1: gameControl->setGeneralState(GENERAL_STATE::menu);
				break;
			}
			
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

	if (cannonball->collidesWith(*boss, collisionVector))
	{
		cannonball->bounce(collisionVector, *boss);
		
		//std::cout << cannonball->getDamageLeft() + "COLLIDE BOSSSHIP" << std::endl;
		
		//cannonball->hit(bossShip);
	}	

	for (int i = 0; i < array_spaceships.size(); i++)
	{
		if (cannonball->collidesWith(*array_spaceships[i], collisionVector))
		{
			if (cannonball->getActive())
			{
				//actual damage code
				//calculate damage from cannonball
				int spaceshipHealth = array_spaceships[i]->getHealth();
				array_spaceships[i]->setHealth(array_spaceships[i]->getHealth() - cannonball->getForcePower());	//decreases health of spaceship
				if (cannonball->getForcePower() > 0)
				{
					cannonball->setForcePower(cannonball->getForcePower() - spaceshipHealth); //decreases health of cannonball
				}
				else
				{
					cannonball->setForcePower(0);
				}

				if (array_spaceships[i]->getHealth() <= SPACESHIP_STARTING_HEALTH * SPACESHIP_CRITICAL_HEALTH_FACTOR)
				{
					array_spaceships[i]->setIsAtCritical(true);
				}

				if (array_spaceships[i]->getHealth() <= 0)
				{
					audio[2]->play();
					//simple destruction (not intended for actual game)
					array_spaceships[i]->setVisible(false);
					delete array_spaceships[i];
					array_spaceships.erase(array_spaceships.begin() + i);
					currentActiveSpaceships--;
				}

				if (cannonball->getForcePower() == 0)
				{
					cannonball->hit(land);
				}
			}
		}
	}

	if (cannonball->collidesWith(*tank, collisionVector))
	{
		if (cannonball->getActive())
		{
			tank->setHealth(tank->getHealth() - cannonball->getForcePower());
			cannonball->hit(land);
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
								 instructionScreen->draw();
	}break;
	case GENERAL_STATE::game:{
								 background->draw();
								 ground->draw();                   // add the object to the scene
								 cannonball->draw();					//in real game, Cannonball should be drawn later, when wormhole appears
								 turret->draw();
								 tank->draw();
								 
								 
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
								   pause->draw();
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
	//exampleTexture->onLostDevice();
	pauseTexture->onLostDevice();
	instructionTexture->onLostDevice();
	backgroundTexture->onLostDevice();
	cannonballTexture->onLostDevice();
	groundTexture->onLostDevice();
	spaceshipTexture->onLostDevice();
	tankTexture->onLostDevice();
	turretTexture->onLostDevice();
	smokeTexture->onLostDevice();
	cannonball->releaseAll();
	tank->releaseAll();
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
	pauseTexture->onResetDevice();
	instructionTexture->onResetDevice();
	backgroundTexture->onResetDevice();
	cannonballTexture->onResetDevice();
	groundTexture->onResetDevice();
	spaceshipTexture->onResetDevice();
	tankTexture->onResetDevice();
	turretTexture->onResetDevice();
	smokeTexture->onResetDevice();
	cannonball->resetAll();
	tank->resetAll();
    Game::resetAll();
    return;
}

//=============================================================================
// load audio
//=============================================================================
void Descent::loadAudio(std::string source)
{
	audio.push_back(new Audio(source));
}

//=============================================================================
// initialise the tank
//=============================================================================
void Descent::initializeTank()
{
	tank->setFrames(PlayerNS::START_FRAME, PlayerNS::END_FRAME);
	tank->setCurrentFrame(PlayerNS::START_FRAME);
	/*if (playerCount == 1)
	{*/
		tank->setX(GAME_WIDTH / 2);
		tank->setY(GROUND_LEVEL_HEIGHT - PLAYER_HEIGHT + 2.0f);
	/*}
	else
	{
	}*/
	tank->flipHorizontal(false);
	tank->initialiseTankHealthbar();

	turret->setCurrentFrame(3);
	turret->setX(tank->getX() + 28.0f);
	turret->setY(tank->getY() - 15.0f);

	cannonball->setX(tank->getX());
	cannonball->setY(tank->getY());
	cannonball->initialiseChargingbar(tank->getX(),tank->getY());
}

//=============================================================================
// moves all spaceships once
// constantly called by thread (timer)
// when one spaceships hits the screen border, ALL ships shifts 1 level down and moves the other direction
//=============================================================================
void Descent::moveSpaceships(bool isMovingRight)
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

			//std::cout << "ship " << i + 1 << " initial x/y: " << array_spaceships[i].getX() << "/" << array_spaceships[i].getY() << std::endl;	//for some reason not having this line destroys the movement???

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

			//std::cout << "ship " << i + 1 << " initial x/y: " << array_spaceships[i].getX() << "/" << array_spaceships[i].getY() << std::endl; //for some reason not having this line destroys the movement???

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

			//std::cout << "ship " << i + 1 << " x/y: " << array_spaceships[i]->getX() << "/" << array_spaceships[i]->getY() << std::endl;
			//shifts everything downwards and changes direction
			array_spaceships[i]->setY(array_spaceships[i]->getY() + VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS + SPACESHIP_HEIGHT);
			array_spaceships[i]->setIsMovingRight(isAllSpaceshipMovingRight);

			//std::cout << "ship " << i + 1 << " shifts down " << std::endl;
			//std::cout << "ship " << i + 1 << " x/y: " << array_spaceships[i]->getX() << "/" << array_spaceships[i]->getY() << std::endl;

		}

	}

	else							//ships ready to move towards current direction
	{
		if (isAllSpaceshipMovingRight == true)
		{
			for (int i = 0; i < currentActiveSpaceships; i++)
			{
				array_spaceships[i]->setX(array_spaceships[i]->getX() + SPACESHIP_WIDTH); //ships moves its width horizontally to the right
				Sleep(5);			//without this line spaceships will move unhindered, not sure why

				//std::cout << "ship " << i + 1 << " moves right " << std::endl;	//without this code or Sleep(5) things move2fast
			}
		}

		if (isAllSpaceshipMovingRight == false)
		{
			for (int i = 0; i < currentActiveSpaceships; i++)
			{
				array_spaceships[i]->setX(array_spaceships[i]->getX() - SPACESHIP_WIDTH); //ships moves its width horizontally to the left
				Sleep(5);			//without this line spaceships will move unhindered, not sure why

				//std::cout << "ship " << i + 1 << " moves left " << std::endl;		//without this code or Sleep(5) things move2fast
			}
			
		}
	}




	/*for (int i = currentActiveSpaceships-1; i >= 0; i--)
	{
		//iterates through every existing spaceship (iterates backwards)
		//individually shifts each spaceship to its current direction
		//if spaceships hits the edge of the screen, it will be shifted downwards and will move to the other direction

		


		if (isAllSpaceshipMovingRight) //is moving to the right
		{
			
			if ((array_spaceships[i].getX() + SPACESHIP_WIDTH) > GAME_WIDTH)
			{
				for (int j = currentActiveSpaceships - 1; j >= 0; j--)
				{

					std::cout << "ship " << j+1 << " x/y: " << array_spaceships[i].getX() << "/" << array_spaceships[i].getY() << std::endl;
					//shifts everything downwards and changes direction
					array_spaceships[j].setY(array_spaceships[j].getY() + VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS + SPACESHIP_HEIGHT);
					array_spaceships[j].setIsMovingRight(false);

					std::cout << "ship " << j+1 << " shifts down " << std::endl;
					std::cout << "ship " << j+1 << " x/y: " << array_spaceships[i].getX() << "/" << array_spaceships[i].getY() << std::endl;

				}
			}

			else
			{
				std::cout << "ship " << i+1 << " moving right" << std::endl;
				array_spaceships[i].setX(array_spaceships[i].getX() + SPACESHIP_WIDTH); //ships moves its width horizontally to the right

				/*std::cout << "ship changing direction to LEFT, moving down at x " << array_spaceships[i].getX() << std::endl;

				array_spaceships[i].setY(array_spaceships[i].getY() + VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS + SPACESHIP_HEIGHT);	//ship shifts downwards

				array_spaceships[i].setIsMovingRight(false);																		//ship changes moving direction

				//if reach beyond y
				if (array_spaceships[i].getY() > GAMEOVER_SPACESHIP_DISTANCE)
				{
					std::cout << "GAME OVER" << std::endl;
					break;
				}

			}
				
		}

		else //is moving left
		{


			if (array_spaceships[i].getX() < SPACESHIP_WIDTH)
			{
				for (int j = currentActiveSpaceships - 1; j >= 0; j--)
				{
					//shifts everything downwards and changes direction
					array_spaceships[j].setY(array_spaceships[j].getY() + VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS + SPACESHIP_HEIGHT);
					array_spaceships[j].setIsMovingRight(true);

					std::cout << "ship " << j+1 << " shifts down " << std::endl;

				}
			}
				
			else
			{
				std::cout << "ship " << i+1 << " moving left" << std::endl;
				array_spaceships[i].setX(array_spaceships[i].getX() - SPACESHIP_WIDTH); //ships moves its width horizontally to the left

				/*std::cout << "ship changing direction to RIGHT, moving down at x " << array_spaceships[i].getX() << std::endl;

				array_spaceships[i].setY(array_spaceships[i].getY() + VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS + SPACESHIP_HEIGHT);//ship shifts downwards
				array_spaceships[i].setIsMovingRight(true);													//ship changes moving direction

				//if reach beyond y
				if (array_spaceships[i].getY() > GAMEOVER_SPACESHIP_DISTANCE)
				{
					std::cout << "GAME OVER" << std::endl;
					break;
				}

			}
		}

	}*/

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
				currentInGameTime++;
				//std::cout << "in game seconds passed: = " << currentInGameTime << std::endl;
				//std::cout << currentInGameTime << " seconds has passed in-game. " << getSecondsPassed() << " second(s) has passed (in program)." << std::endl;
				moveSpaceships(isAllSpaceshipMovingRight);
			}
		}
	}
}

//=============================================================================
// load all audios
//=============================================================================
void Descent::loadAllAudio()
{
	loadAudio("resources\\music\\background.ogg");
	loadAudio("resources\\music\\tankMoving.wav");
	loadAudio("resources\\music\\explode.wav");
}