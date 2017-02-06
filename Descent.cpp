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
	powerup_notification_text = new TextDX();

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
	assistTankTexture = new TextureManager();
	assistTankBulletTexture = new TextureManager();

	powerup_timeSlow_texture = new TextureManager();
	powerup_restoreHealth_texture = new TextureManager();
	powerup_increaseTankSpeed_texture = new TextureManager();
	powerup_timeLock_texture = new TextureManager();
	powerup_maxPower_texture = new TextureManager();
	powerup_passerbyTank_texture = new TextureManager();

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
	assistTank = new Assist_Tank();
}

//=============================================================================
// Destructor
//=============================================================================
Descent::~Descent()
{
	SAFE_DELETE(pauseText);
	SAFE_DELETE(waveNumberText);
	SAFE_DELETE(powerup_notification_text);
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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause text font"));
	if (!waveNumberText->initialize(graphics, 62, true, false, "Invasion2000"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wave number font"));
	if (!powerup_notification_text->initialize(graphics, 28, false, false, "Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup notification font"));

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
	
	if (!assistTankTexture->initialize(graphics, ASSIST_TANK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing assist tank texture"));
	if (!assistTank->initialize(this, Assist_Tank_NS::WIDTH, Assist_Tank_NS::HEIGHT, Assist_Tank_NS::TEXTURE_COLS, assistTankTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing assist tank game object"));

	if (!assistTankBulletTexture->initialize(graphics, ASSIST_TANK_BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing assist tank bullet texture"));

	if (!powerup_timeSlow_texture->initialize(graphics, POWERUP_TIME_SLOW_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (down speed) texture"));
	if (!powerup_restoreHealth_texture->initialize(graphics, POWERUP_RESTORE_HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (restore health) texture"));
	if (!powerup_increaseTankSpeed_texture->initialize(graphics, POWERUP_INCREASE_TANK_SPEED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (increase tank speed) texture"));
	if (!powerup_timeLock_texture->initialize(graphics, POWERUP_TIME_LOCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (time lock) texture"));
	if (!powerup_maxPower_texture->initialize(graphics, POWERUP_MAX_POWER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (max power) texture"));
	if (!powerup_passerbyTank_texture->initialize(graphics, POWERUP_PASSERBY_TANK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (passerby tank) texture"));

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
	currentActiveTankAssistBullets = 0;
	isAllSpaceshipMovingRight = true;
	isShipsReadyToShift = false;

	//setting boss variables

	boss->setFrames(Boss_SpaceshipNS::START_FRAME, Boss_SpaceshipNS::END_FRAME);
	boss->setCurrentFrame(Boss_SpaceshipNS::START_FRAME);
	
	shell->setX(boss->getX()+BOSS_SPACESHIP_WIDTH/2);
	shell->setY(boss->getY()+BOSS_SPACESHIP_HEIGHT/2);

	assistTank->setFrames(ASSIST_TANK_START_FRAME, ASSIST_TANK_END_FRAME);
	assistTank->setCurrentFrame(ASSIST_TANK_START_FRAME);
	assistTank->setX(ASSIST_TANK_WIDTH);
	assistTank->setY(GROUND_LEVEL_HEIGHT - ASSIST_TANK_HEIGHT);
	assistTank->setActive(false);
	
#pragma endregion

#pragma region Initialize Powerups Drawing Space
	//loading powerups

	powerup_timeSlow = new Powerup();
	powerup_restoreHealth = new Powerup();
	powerup_increaseTankSpeed = new Powerup();
	powerup_timeLock = new Powerup();
	powerup_maxPower = new Powerup();
	powerup_passerbyTank = new Powerup();

	powerup_timeSlow->setPowerupCode(POWERUP_TIME_SLOW_CODE);
	powerup_restoreHealth->setPowerupCode(POWERUP_RESTORE_HEALTH_CODE);
	powerup_increaseTankSpeed->setPowerupCode(POWERUP_INCREASE_TANK_SPEED_CODE);
	powerup_timeLock->setPowerupCode(POWERUP_TIME_LOCK_CODE);
	powerup_maxPower->setPowerupCode(POWERUP_MAX_POWER_CODE);
	powerup_passerbyTank->setPowerupCode(POWERUP_TANK_ASSIST_CODE);

	if (!powerup_timeSlow->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_timeSlow_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (down speed) object"));

	if (!powerup_restoreHealth->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_restoreHealth_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (restore health) object"));

	if (!powerup_increaseTankSpeed->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_increaseTankSpeed_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (increase tank speed) object"));

	if (!powerup_timeLock->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_timeLock_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (time lock) object"));

	if (!powerup_maxPower->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_maxPower_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (max power) object"));

	if (!powerup_passerbyTank->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_passerbyTank_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (passerby tank) object"));

	array_powerups_drawingSpace.push_back(powerup_timeSlow);
	array_powerups_drawingSpace.push_back(powerup_restoreHealth);
	array_powerups_drawingSpace.push_back(powerup_increaseTankSpeed);
	array_powerups_drawingSpace.push_back(powerup_timeLock);
	array_powerups_drawingSpace.push_back(powerup_maxPower);
	array_powerups_drawingSpace.push_back(powerup_passerbyTank);

	totalAmtOfPowerupVariety = array_powerups_drawingSpace.size();
	std::cout << "total amount of loaded powerups: " << totalAmtOfPowerupVariety << std::endl;

	currentActivePowerups = 0;

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
	
	std::async(&Descent::timer_start, this); //run timer thread while main loop is contiuing

	//applyPowerupEffect(1);

	std::ifstream infile;
	infile.open(HISCORE_FILE);

	if (infile.is_open())
	{
		//read the hiscore
		std::string str;
		while (std::getline(infile, str))

		hiscore = std::stoi(str);		//sets hiscore to be previous hiscore

		std::cout << "Current hiscore is " << hiscore << std::endl;
	}

	else
		std::cout << "'highscore.txt' is missing from the resources folder Please ensure it exists." << std::endl;

	comboSpaceshipCounter = 0;
	currentScore = 0;

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

		if (!cannonball->getActive())
			comboSpaceshipCounter = 0;		//cannonball now inactive, set collateral counter to 0

		enemy_spaceship->update(frameTime);
		tank->update(frameTime);
		//smoke->update(frameTime);

		if (currentActiveSpaceships > 0)
		{
			//endlessly loop update for each zombie until no more zombies
			for (int i = 0; i < currentActiveSpaceships; i++)
			{

				array_spaceships[i]->update(frameTime);

				if (array_spaceships[i]->getHealth() <= SPACESHIP_STARTING_HEALTH*SPACESHIP_CRITICAL_HEALTH_FACTOR)
					array_spaceships[i]->setIsAtCritical(true);

				if (array_spaceships[i]->getHealth() <= 0)
				{
					array_spaceships[i]->setVisible(false);
					std::cout << "Spaceship " << i << " is kill" << std::endl;
					delete array_spaceships[i];
					array_spaceships.erase(array_spaceships.begin() + i);
					currentActiveSpaceships--;

					comboSpaceshipCounter++;

					currentScore += (SPACESHIP_REWARD_SCORE*comboSpaceshipCounter);						//update score
					std::cout << "Combo: " << comboSpaceshipCounter << ", current score: " << currentScore << std::endl;
				}
			}
				
		}

		if (currentActivePowerups > 0)
		{
			for (int i = 0; i < currentActivePowerups; i++)
			{
				
				if (!array_powerups[i]->getActive())
				{
					array_powerups[i]->setVisible(false);
					std::cout << "Powerup " << i+1 << " expired" << std::endl;
					delete array_powerups[i];
					array_powerups.erase(array_powerups.begin() + i);
					currentActivePowerups--;
				}

				else
					array_powerups[i]->update(frameTime);

			}
		}

		if (isPowerupInProgress)
			powerup_notification_text->print("Powerup - Time Slow!", 100, 100);

		if (assistTank->getActive())
			assistTank->update(frameTime);
		else
			assistTank->setVisible(false);

		for (int i = 0; i < currentActiveTankAssistBullets; i++)
		{
			array_tank_assist_bullets[i]->update(frameTime);

			if (array_tank_assist_bullets[i]->getY() <= 0)			//reaches out of map
				array_tank_assist_bullets[i]->setActive(false);
				
			if (!array_tank_assist_bullets[i]->getActive())
			{
				//bullet not active, remove from game
				std::cout << "removed bullet " << std::endl;
				array_tank_assist_bullets[i]->setVisible(false);
				delete array_tank_assist_bullets[i];
				array_tank_assist_bullets.erase(array_tank_assist_bullets.begin() + i);
				currentActiveTankAssistBullets--;
			}

		}

		if (!isCurrentScoreHighestScore)
		{

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
										
										//simple spaceship bullet shooting

										 
			 }break;
			 case WAVE_STATE::wave2:{//add wave 2 enemy behavior

										shell->update(frameTime, *turret);

										std::cout << "wave 2" << std::endl;

										if (input->wasKeyPressed(TH_KEY))
										{
											waveControl->setWaveState(WAVE_STATE::wave3);
										}

										//advanced spaceship shooting

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

	//simple ai for wave 2 shooting

	//timer feedbacks player movement and speed to AI
		//DO SOMETHING RELATED 

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
		
		cannonball->hit(bossShip);
		
	}	

	for (int i = 0; i < currentActiveSpaceships; i++)
	{
		// if collision between cannonball and spaceship
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

				if (cannonball->getDamageLeft() == 0)
				{
					std::cout << "Cannonball is kill" << std::endl;
					cannonball->setVisible(false);
					//cannonball->setActive(false);
				}

			}
		}
	}

	//for collision between tank and powerup
	for (int i = 0; i < currentActivePowerups; i++)
	{
		if (tank->collidesWith(*array_powerups[i], collisionVector))
		{
			applyPowerupEffect(array_powerups[i]->getPowerupCode());

			delete array_powerups[i];
			array_powerups.erase(array_powerups.begin() + i);
			currentActivePowerups--;
			currentScore += POWERUP_REWARD_SCORE;						//update score
		}
	}

	//for collision between assist tank bulles and spaceship

	for (int i = 0; i < currentActiveTankAssistBullets; i++)
	{
		for (int j = 0; j < currentActiveSpaceships; j++)
		{
			if (array_tank_assist_bullets[i]->collidesWith(*array_spaceships[j], collisionVector))
			{
				array_spaceships[j]->setHealth(array_spaceships[j]->getHealth() - array_tank_assist_bullets[i]->damage);
				array_tank_assist_bullets[i]->setActive(false);
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
									 array_spaceships[i]->draw();

								 for (int i = 0; i < currentActivePowerups; i++)
									 array_powerups[i]->draw();
								 
								 if (assistTank->getActive())
									 assistTank->draw();

								 for (int i = 0; i < currentActiveTankAssistBullets; i++)
									 array_tank_assist_bullets[i]->draw();
									 
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
	assistTankTexture->onLostDevice();
	assistTankBulletTexture->onLostDevice();

	powerup_timeSlow_texture->onLostDevice();
	powerup_restoreHealth_texture->onLostDevice();
	powerup_increaseTankSpeed_texture->onLostDevice();
	powerup_timeLock_texture->onLostDevice();
	powerup_maxPower_texture->onLostDevice();
	powerup_passerbyTank_texture->onLostDevice();

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
	assistTankTexture->onResetDevice();
	assistTankBulletTexture->onResetDevice();
	powerup_timeSlow_texture->onResetDevice();
	powerup_restoreHealth_texture->onResetDevice();
	powerup_increaseTankSpeed_texture->onResetDevice();
	powerup_timeLock_texture->onResetDevice();
	powerup_maxPower_texture->onResetDevice();
	powerup_passerbyTank_texture->onResetDevice();

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
// applies a picked-up powerup's effect on the game
// called when the player tank collides with a powerup
// pickup's code allows for corresponding effect to take place
// most of this section is hard coded
//=============================================================================
void Descent::applyPowerupEffect(int powerupCode)
{

	

	switch (powerupCode)
	{

	case POWERUP_TIME_SLOW_CODE:
	{
							//apply effect for time slow 
							mciSendString("play resources\\music\\powerup_timeSlow_soundeffect.wav", NULL, 0, NULL);
							std::async(&Descent::applyPowerupEffect_timeSlow, this);
							//add to score
	}break;

	case POWERUP_RESTORE_HEALTH_CODE:
	{
							mciSendString("play resources\\music\\powerup_restoreHealth_soundeffect.wav", NULL, 0, NULL);
							std::async(&Descent:: applyPowerupEffect_restoreHealth, this);
							//this doesn't *need* to be in a thread, but if not it makes everything expire faster for some reason
	}break;

	case POWERUP_INCREASE_TANK_SPEED_CODE:
	{
							mciSendString("play resources\\music\\powerup_increaseTankSpeed_soundeffect.wav", NULL, 0, NULL);
							std::async(&Descent::applyPowerupEffect_increaseTankSpeed, this);

	}break;

	case POWERUP_TIME_LOCK_CODE:
	{
							mciSendString("play resources\\music\\powerup_timeLock_locking_soundeffect.wav", NULL, 0, NULL);
							std::async(&Descent::applyPowerupEffect_timeLock, this);

	}break;

	case POWERUP_MAX_POWER_CODE:
	{
							mciSendString("play resources\\music\\powerup_maxPower_soundeffect.wav", NULL, 0, NULL);
							std::async(&Descent::applyPowerupEffect_maxPower, this);
	}break;

	case POWERUP_TANK_ASSIST_CODE:
	{
							mciSendString("play resources\\music\\powerup_tankAssist_soundeffect.wav", NULL, 0, NULL);
							std::async(&Descent::applyPowerupEffect_tankAssist, this);
	}break;

	}
}

#pragma region Individual Powerup Effects here

void Descent::applyPowerupEffect_timeSlow()
{
	isPowerupInProgress = true;
	timeModifier = POWERUP_TIME_SLOW_MULTIPLER;

	//powerup_notification_text->print("Powerup - Time Slow!", 100, 100);

	std::cout << "Time modified to " << timeModifier << " times slower." << std::endl;

	clock_t timer = clock();//start timer

	time_t clockTimer;
	double seconds = 0;

	int startingTime = time(&clockTimer);

	bool loop = true;
	while (loop)
	{

		if (gameControl->getGeneralState() == GENERAL_STATE::game)	//timer only counts down in-game
		{
			
			if ((fmod(getSecondsPassed(), SECOND) == 0))
			{
				//every second in processor, check for real-time update
				time(&clockTimer);  //get and update current time
				seconds = difftime(clockTimer, startingTime);
			}

			if (seconds == POWERUP_INCREASE_TANK_SPEED_DURATION)
			{

				timeModifier = GAME_BASE_TIME_MODIFIER;
				std::cout << "Time slow duration over, resetting back to normal time" << std::endl;
				loop = false;	//breaks the loop, stops thread

			}

		}

	}

	//powerup_notification_text->print("", GAME_HEIGHT / 2, GAME_WIDTH / 2);
	isPowerupInProgress = false;

}

void Descent::applyPowerupEffect_restoreHealth()
{
	time_t clockTimer;
	double seconds = 0;

	int startingTime = time(&clockTimer);


	//for one player only
	if (tank->getHealth() < PLAYER_MAX_HEALTH)
	{
		tank->setHealth(tank->getHealth() + POWERUP_RESTORE_HEALTH_VALUE);

		if (tank->getHealth() > PLAYER_MAX_HEALTH)
			tank->setHealth(PLAYER_MAX_HEALTH);
	}

	std::cout << "Player health restored " << std::endl;

	//for multiple players
	//duplicate code for 2nd player (assuming both players are alive)
	
	//add to score
}

void Descent::applyPowerupEffect_increaseTankSpeed()
{
	isPowerupInProgress = true;
	tank->setSpeed(tank->getSpeed()*POWERUP_INCREASE_TANK_SPEED_FACTOR);	//increases tank speed

	clock_t timer = clock();//start timer
	
	time_t clockTimer;
	double seconds = 0;

	int startingTime = time(&clockTimer);

	bool loop = true;
	while (loop)
	{

		if (gameControl->getGeneralState() == GENERAL_STATE::game)	//timer only counts down in-game
		{
			
			if ((fmod(getSecondsPassed(), SECOND) == 0))
			{
				//every second in processor, check for real-time update

				time(&clockTimer);  //get and update current time

				seconds = difftime(clockTimer, startingTime);

			}

			if (seconds ==  POWERUP_INCREASE_TANK_SPEED_DURATION)
			{

				tank->setSpeed(PLAYER_BASE_SPEED);	//reset speed back to base value
				std::cout << "Tank speed powerup over, speed set back to - " << tank->getSpeed() << std::endl;
				loop = false;	//breaks the loop, stops thread

			}

		}

	}
	isPowerupInProgress = false;

}

void Descent::applyPowerupEffect_timeLock()
{
	isPowerupInProgress = true;
	timeModifier = POWERUP_TIME_LOCK_FACTOR;

	for (int i = 0; i < currentActiveSpaceships; i++)
	{
		array_spaceships[i]->setLoop(false);
	}

	std::cout << "Time locked. Chronosphere wolololo" << std::endl;

	clock_t timer = clock();//start timer

	time_t clockTimer;
	double seconds = 0;

	int startingTime = time(&clockTimer);

	bool loop = true;
	while (loop)
	{

		if (gameControl->getGeneralState() == GENERAL_STATE::game)	//timer only counts down in-game
		{
			
			if ((fmod(getSecondsPassed(), SECOND) == 0))
			{
				//every second in processor, check for real-time update
				time(&clockTimer);  //get and update current time
				seconds = difftime(clockTimer, startingTime);
			}

			if (seconds == (POWERUP_TIME_LOCK_DURATION - POWERUP_TIME_LOCK_UNLOCK_SOUND_DURATION))
				mciSendString("play resources\\music\\powerup_timeLock_unlocking_soundeffect.wav", NULL, 0, NULL);

			if (seconds == POWERUP_TIME_LOCK_DURATION)
			{

				timeModifier = GAME_BASE_TIME_MODIFIER;
				std::cout << "Time lock duration over, resetting back to normal time" << std::endl;
				loop = false;	//breaks the loop, stops thread
				
			}

		}

	}

	for (int i = 0; i < currentActiveSpaceships; i++)
	{
		array_spaceships[i]->setLoop(true);
	}

	isPowerupInProgress = false;

}

void Descent::applyPowerupEffect_maxPower()
{
	isPowerupInProgress = true;
	//increase tank power

	clock_t timer = clock();//start timer

	time_t clockTimer;
	double seconds = 0;

	int startingTime = time(&clockTimer);

	bool loop = true;
	while (loop)
	{

		if (gameControl->getGeneralState() == GENERAL_STATE::game)	//timer only counts down in-game
		{
			
			if ((fmod(getSecondsPassed(), SECOND) == 0))
			{
				//every second in processor, check for real-time update

				time(&clockTimer);  //get and update current time

				seconds = difftime(clockTimer, startingTime);

			}

			if (seconds == POWERUP_MAX_POWER_DURATION)
			{

				//set tank power to normal
				std::cout << "Tank max power over, power set back to - " << tank->getSpeed() << std::endl;
				loop = false;	//breaks the loop, stops thread

			}

		}

	}
	isPowerupInProgress = false;

}

void Descent::applyPowerupEffect_tankAssist()
{
	isPowerupInProgress = true;

	assistTank->setVisible(true);
	assistTank->setX(ASSIST_TANK_WIDTH);		//sets tank to left edge of screen
	//tank's Y is already set to ground level, no need to change
	assistTank->setActive(true);				//this starts the Passerby Tank up

	clock_t timer = clock();//start timer

	time_t clockTimer;
	int seconds = 0;

	int startingTime = time(&clockTimer);

	bool loop = true;
	while (loop)
	{

		if (gameControl->getGeneralState() == GENERAL_STATE::game)	//timer only counts down in-game
		{
			
			if (fmod(getSecondsPassed(), SECOND) == 0)
			{
				//every second in processor, check for real-time update
				time(&clockTimer);  //get and update current time
				seconds = difftime(clockTimer, startingTime);
			}

			if (fmod(seconds, ASSIST_TANK_ATTACK_FREQUENCY) == 0 && currentActiveTankAssistBullets < MAX_NO_OF_ASSIST_TANK_BULLETS)	//fires bullet every X seconds
			{
				//creates bullet
				//add bullet to array
				
				Assist_Tank_bullet* assist_bullet = new Assist_Tank_bullet();

				if (!assist_bullet->initialize(this, Assist_Tank_bullet_NS::WIDTH, Assist_Tank_bullet_NS::HEIGHT, Assist_Tank_bullet_NS::TEXTURE_COLS, assistTankBulletTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing assist tank bullet game object"));

				assist_bullet->setX(assistTank->getX() + (ASSIST_TANK_WIDTH / 2));	//sets bullet to center of tank
				assist_bullet->setY(GROUND_LEVEL_HEIGHT - ASSIST_TANK_HEIGHT);	//set to tip of cannon
				assist_bullet->setActive(true);
				assist_bullet->setVisible(true);

				array_tank_assist_bullets.push_back(assist_bullet);
				currentActiveTankAssistBullets++;
				//std::cout << "Passerby tank pew  " << seconds << std::endl;
			}

			if (seconds == POWERUP_TANK_ASSIST_DURATION)
			{
				///set passerby tank to inactive, let update take care of the rest
				assistTank->setActive(false);
				std::cout << "Passerby tank has left the premise " << std::endl;
				loop = false;	//breaks the loop, stops thread
			}

		}

	}
	isPowerupInProgress = false;

}

#pragma endregion

//=============================================================================
// adds and manipulate score
// updates hiscore when applicable
//=============================================================================
void Descent::addToScore(int scoreToAdd)
{
	currentScore += scoreToAdd;

	if (currentScore > hiscore)
	{
		isCurrentScoreHighestScore = true;		//triggers the file saving clause
		hiscore = currentScore;					//also update hiscore

		/*if (isCurrentScoreHighestScore)
		{
			std::ofstream out(HISCORE_FILE);
			out << 5000;
			out.close();
		}*/

	}
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
	srand(time(NULL));
	//get random seed based on amount of possible powerups
	
	int randomPowerupIndex = (rand() % totalAmtOfPowerupVariety);
	int randomPowerupXPosition = (rand() % GAME_WIDTH - POWERUP_WIDTH);	// for x position of powerup

	if (randomPowerupXPosition < 0)
		randomPowerupXPosition = 0;

	Powerup* powerup = new Powerup(*array_powerups_drawingSpace[randomPowerupIndex]);		//this deep copies the drawingSpace object into the actual array
	//take powerup from drawing space and add to actual powerup array
	powerup->setX(randomPowerupXPosition);
	powerup->setY(POWERUP_SPAWN_HEIGHT);

	array_powerups.push_back(powerup);
	currentActivePowerups++;

	mciSendString("play resources\\music\\powerup_spawn_soundeffect.wav", NULL, 0, NULL);

	array_powerups[currentActivePowerups - 1]->beginExpireCountdown();

	//std::cout << "powerup index : " << randomPowerupIndex << " spawned" << std::endl;
	//std::cout << "current amount of powerups: " << currentActivePowerups << std::endl;

}

//=============================================================================
// start and run timer
// this timer is for the main game
//	using thread
//=============================================================================
void Descent::timer_start()
{
	//create timer
	clock_t timer = clock();//start timer

	bool loop = true;
	while (loop)
	{

		if (gameControl->getGeneralState() == GENERAL_STATE::game)	//timer only counts down in-game
		{
			setSecondsPassed((clock() - timer) / (double)CLOCKS_PER_SEC);  //convert computer timer to real life seconds

			if ((fmod(getSecondsPassed(), SPACESHIP_MOVE_FREQUENCY*timeModifier)) == 0)
			{

				//std::cout << "in game seconds passed: = " << currentInGameTime << std::endl;
				//std::cout << currentInGameTime << " seconds has passed in-game. " << getSecondsPassed() << " second(s) has passed (in program)." << std::endl;

				moveSpaceships();

			}

			//if game state wave 1
			//fmod wave 1 speed shooting chance

			if (waveControl->getWaveState() == WAVE_STATE::wave1
				&& (fmod(getSecondsPassed(), SPACESHIP_ATTACK_FREQUENCY)) == 0)
			{	//if wave is wave 1, start simple spaceship shooting

				for (int i = 0; i < currentActiveSpaceships; i++)
				{
					//run for loop that iterates through every spaceship
					//for each spaceship, check and compare seed
					//if chance not hit, ignore
					//if chance hit, 

					double generatedChance = rand() % 100;
					if (WAVE_1_SPACESHIPS_FIRE_CHANCE >= generatedChance)	//pew!
					{
						std::cout << "Spaceship has decided to shoot " << std::endl;
						
						//create bullet
						//set bullet to target X
							//where x is player position at time of firing
						//set and calculate bullet degree to relevant X
						//set bullet active, let update take care of movment
					}
				}

			}

			if (waveControl->getWaveState() == WAVE_STATE::wave2
				&& (fmod(getSecondsPassed(), SPACESHIP_ATTACK_FREQUENCY)) == 0)
			{	//if wave is wave 1, start simple spaceship shooting

				for (int i = 0; i < currentActiveSpaceships; i++)
				{
					//run for loop that iterates through every spaceship
					//for each spaceship, check and compare seed
					//if chance not hit, ignore
					//if chance hit, 

					double generatedChance = rand() % 100;
					if (WAVE_2_SPACESHIPS_FIRE_CHANCE >= generatedChance)	//pew!
					{
						std::cout << "Spaceship has decided to shoot " << std::endl;

						//SIMPLE SHOOTING
					}

					double generatedChance = rand() % 100;
					if (WAVE_2_SPACESHIPS_FIRE_INTELLIGENT_CHANCE >= generatedChance)	//pew!
					{
						std::cout << "Spaceship has decided to shoot " << std::endl;

						//ADVANCED SHOOTING
						//read from AI to calculate possible player position
					}

				}

			}

			if ((fmod(getSecondsPassed(), POWERUP_SPAWN_FREQUENCY)) == 0 && currentActivePowerups < MAX_NO_OF_POWERUPS && !isPowerupInProgress)
				spawnPowerup();

		}

	}
}


