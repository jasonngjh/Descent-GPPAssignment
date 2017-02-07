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
	spaceship_bulletTexture = new TextureManager();
	menu1Texture = new TextureManager();

	tankTexture = new TextureManager();
	tankHealthTexture = new TextureManager();

	turretTexture = new TextureManager();
	pauseTexture = new TextureManager();
	instructionTexture = new TextureManager();
	gamewinTexture = new TextureManager();
	gameloseTexture = new TextureManager();
	bossLaserTexture = new TextureManager();
	assistTankTexture = new TextureManager();
	assistTankBulletTexture = new TextureManager();

	powerup_timeSlow_texture = new TextureManager();
	powerup_shield_texture = new TextureManager();
	powerup_increaseTankSpeed_texture = new TextureManager();
	powerup_timeLock_texture = new TextureManager();
	powerup_maxPower_texture = new TextureManager();
	powerup_passerbyTank_texture = new TextureManager();

	//images
	background = new Image();
	ground = new Image();
	tank = new Player();
	cannonball = new Cannonball();
	menu1 = new Image();
	tankHealth = new Image();
	turret = new Image();
	pause = new Image();
	instructionScreen = new Image();
	gamewin = new Image();
	gamelose = new Image();

	//entities
	bosslaser = new BossLaser();
	enemy_spaceship = new Spaceship();
	boss = new Boss_Spaceship();
	shell = new Shell();
	assistTank = new Assist_Tank();
}

//=============================================================================
// Destructor
//=============================================================================
Descent::~Descent()
{
	// call onLostDevice() for every graphics item
	SAFE_DELETE(pauseText);
	SAFE_DELETE(waveNumberText);
	SAFE_DELETE(gameControl);

	SAFE_DELETE(background);
	SAFE_DELETE(ground);
	SAFE_DELETE(menu1);
	SAFE_DELETE(gamewin);
	SAFE_DELETE(gamelose);
	SAFE_DELETE(instructionScreen);
	SAFE_DELETE(turret);
	SAFE_DELETE(pause);
	SAFE_DELETE(cannonball);
	SAFE_DELETE(enemy_spaceship);
	SAFE_DELETE(tank);
	SAFE_DELETE(tankHealth);
	SAFE_DELETE(boss);
	SAFE_DELETE(shell);
	for (Spaceship* spaceShip : array_spaceships)
	{
		SAFE_DELETE(spaceShip);
	}
	for (Audio* a : audio)
	{
		SAFE_DELETE(a);
	}
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
	std::cout << "initialising game" << std::endl;

	std::cout << "Fonts...";

	Game::initialize(hwnd); // throws GameError
	if (dxFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	srand(time(NULL));		//seeds the RNG

	//object and texture initialization

	if (!pauseText->initialize(graphics, 62, true, false, "Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause text font"));
	if (!waveNumberText->initialize(graphics, 62, true, false, "Invasion2000"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wave number font"));
	if (!powerup_notification_text->initialize(graphics, 28, false, false, "Arial"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup notification font"));

	std::cout << "loaded. " << std::endl;

	std::cout << "Game textures...";

	if (!groundTexture->initialize(graphics, GROUND_TILESET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground texture"));

	if (!cannonballTexture->initialize(graphics, CANNONBALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball texture"));

	if (!spaceshipTexture->initialize(graphics, SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship texture"));

	if (!spaceship_bulletTexture->initialize(graphics, SPACESHIP_BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship bullet texture"));

	if (!menu1Texture->initialize(graphics, MENU1_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!pauseTexture->initialize(graphics, PAUSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause texture"));

	if (!tankTexture->initialize(graphics, TANK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank texture"));

	if (!backgroundTexture->initialize(graphics, BKGRND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	if (!instructionTexture->initialize(graphics, INSTRUCTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction texture"));

	if (!tank->initialize(this, PlayerNS::WIDTH, PlayerNS::HEIGHT, PlayerNS::TEXTURE_COLS, tankTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank"));
	if (!cannonball->initialize(this, CannonballNS::WIDTH, CannonballNS::HEIGHT, CannonballNS::TEXTURE_COLS, cannonballTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannonball game object"));

	if (!ground->initialize(graphics, 0, 0, 0, groundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground tiles"));

	if (!enemy_spaceship->initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, spaceshipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));

	if (!menu1->initialize(graphics, MENU1_WIDTH, MENU1_HEIGHT, 2, menu1Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	if (!pause->initialize(graphics, PAUSE_WIDTH, PAUSE_HEIGHT, 2, pauseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pause screen"));

	if (!turretTexture->initialize(graphics, TURRET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret texture"));
	if (!turret->initialize(graphics, TURRET_WIDTH, TURRET_HEIGHT, TURRET_TEXTURE_COLUMNS, turretTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret"));

	if (!background->initialize(graphics, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, BACKGROUND_TEXTURE_COLS, backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising background"));

	if (!instructionScreen->initialize(graphics, INSTRUCTIONS_WIDTH, INSTRUCTIONS_HEIGHT, INSTRUCTIONS_TEXTURE_COLUMNS, instructionTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instruction screen"));

	if (!bossTexture->initialize(graphics, BOSS_SPACESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss texture"));
	if (!boss->initialize(this, Boss_SpaceshipNS::WIDTH, Boss_SpaceshipNS::HEIGHT, Boss_SpaceshipNS::TEXTURE_COLS, bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss game object"));

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
	if (!powerup_shield_texture->initialize(graphics, POWERUP_RESTORE_HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (restore health) texture"));
	if (!powerup_increaseTankSpeed_texture->initialize(graphics, POWERUP_INCREASE_TANK_SPEED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (increase tank speed) texture"));
	if (!powerup_timeLock_texture->initialize(graphics, POWERUP_TIME_LOCK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (time lock) texture"));
	if (!powerup_maxPower_texture->initialize(graphics, POWERUP_MAX_POWER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (max power) texture"));
	if (!powerup_passerbyTank_texture->initialize(graphics, POWERUP_PASSERBY_TANK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (passerby tank) texture"));

	if (!gamewinTexture->initialize(graphics, GAME_WIN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game win texture"));
	if (!gamewin->initialize(graphics, WINLOSE_WIDTH, WINLOSE_HEIGHT, WINLOSE_TEXTURE_COLUMNS, gamewinTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game win image"));

	if (!gameloseTexture->initialize(graphics, GAME_LOSE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game lose texture"));
	if (!gamelose->initialize(graphics, WINLOSE_WIDTH, WINLOSE_HEIGHT, WINLOSE_TEXTURE_COLUMNS, gameloseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game lose image"));

	if (!bossLaserTexture->initialize(graphics, BOSSLASER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss laser texture"));
	if (!shell->initialize(this, ShellNS::WIDTH, ShellNS::HEIGHT, ShellNS::TEXTURE_COLS, shellTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shell game object"));

	std::cout << "loaded. " << std::endl;

	

	background->setFrames(BACKGROUND_START_FRAME, BACKGROUND_END_FRAME);
	background->setCurrentFrame(BACKGROUND_START_FRAME);
	
	
	std::cout << "Audio...";
	loadAllAudio();
	audio[0]->setLoop(true); // background music
	audio[0]->play();
	std::cout << "loaded. " << std::endl;

	ground->setX(0);
	ground->setScale((float)(GAME_WIDTH / ground->getWidth()));
	ground->setY((int)GROUND_LEVEL_HEIGHT);		//sets ground to 3/4 of game width

	initializeTank();

	std::cout << "Boss...";
	launchBossLaser();
	boss->setVelocity(VECTOR2(100, 0)); // VECTOR2(X, Y)
	boss->setFrames(Boss_SpaceshipNS::START_FRAME, Boss_SpaceshipNS::END_FRAME);
	boss->setCurrentFrame(Boss_SpaceshipNS::START_FRAME);
	boss->setX(GAME_WIDTH / 4 + 45);
	boss->setY(20);
	boss->setScale(0.75);
	boss->setActive(false);

	shell->setX(boss->getX() + BOSS_SPACESHIP_WIDTH / 2);
	shell->setY(boss->getY() + BOSS_SPACESHIP_HEIGHT / 2);
	shell->setScale(0.045);

	std::cout << "loaded. " << std::endl;
	
#pragma region Initialize Powerups Drawing Space
	//loading powerups. Only need to call this ONE TIME
	std::cout << "Powerups... ";

	powerup_timeSlow = new Powerup();
	powerup_shield = new Powerup();
	powerup_increaseTankSpeed = new Powerup();
	powerup_timeLock = new Powerup();
	powerup_maxPower = new Powerup();
	powerup_passerbyTank = new Powerup();

	powerup_timeSlow->setPowerupCode(POWERUP_TIME_SLOW_CODE);
	powerup_shield->setPowerupCode(POWERUP_RESTORE_HEALTH_CODE);
	powerup_increaseTankSpeed->setPowerupCode(POWERUP_INCREASE_TANK_SPEED_CODE);
	powerup_timeLock->setPowerupCode(POWERUP_TIME_LOCK_CODE);
	powerup_maxPower->setPowerupCode(POWERUP_MAX_POWER_CODE);
	powerup_passerbyTank->setPowerupCode(POWERUP_TANK_ASSIST_CODE);

	if (!powerup_timeSlow->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_timeSlow_texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing power-up (down speed) object"));

	if (!powerup_shield->initialize(this, PowerupNS::WIDTH, PowerupNS::HEIGHT, PowerupNS::TEXTURE_COLS, powerup_shield_texture))
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
	array_powerups_drawingSpace.push_back(powerup_shield);
	array_powerups_drawingSpace.push_back(powerup_increaseTankSpeed);
	array_powerups_drawingSpace.push_back(powerup_timeLock);
	array_powerups_drawingSpace.push_back(powerup_maxPower);
	array_powerups_drawingSpace.push_back(powerup_passerbyTank);

	totalAmtOfPowerupVariety = array_powerups_drawingSpace.size();
	currentActivePowerups = 0;

	std::cout << "loaded." << std::endl;

#pragma endregion

	std::cout << "Timer...";
	std::async(&Descent::timer_start, this); //run timer thread while main loop is contiuing
	std::cout << "started. " << std::endl;

	std::cout << "Misc variables...";
	//instantiating counter and boolean variables
	currentActiveSpaceships = 0;
	currentActiveSpaceshipBullets = 0;
	currentActiveTankAssistBullets = 0;
	comboSpaceshipCounter = 0;
	currentScore = 0;

	acquiredPlayerSpeed = 0;
	acquiredPlayerDirectionIsRight = true;

	isAllSpaceshipMovingRight = true;
	isShipsReadyToShift = false;
	isPowerupInProgress = false;
	isPowerupSpawning = false;
	//isCalculatingPlayerPattern = false; //this is set in wave 2 spawn instead
	isAllSpaceshipsFiring = false;

	std::cout << "loaded. " << std::endl;

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Descent::update()
{
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
								  }
	}break;
	case GENERAL_STATE::instructions: {
										  if (input->wasKeyPressed(SPACE_KEY)){
											  Sleep(300);
											  gameControl->setGeneralState(GENERAL_STATE::game);
										  }
	}break;

	case GENERAL_STATE::game:{
								 background->update(frameTime);
								 checkGamestatus();
								 cannonball->update(frameTime);

								 if (!cannonball->getActive())
									 comboSpaceshipCounter = 0;		//cannonball now inactive, set collateral counter to 0

								 enemy_spaceship->update(frameTime);

								 

								 if (assistTank->getActive())
									 assistTank->update(frameTime);
								 else
									 assistTank->setVisible(false);

								 // checkpoints: player health = 0 -> change to end game screen
								 // if boss die -> change to end game screen
								 // if esc(quit pressed) -> change to end game screen

								 if (input->isKeyDown(LEFT_KEY))
								 {
									 turret->setX(tank->getX() + 28.0f);
									 tankHealth->setX(tank->getX() + 10.0f);
								 }
								 if (input->isKeyDown(RIGHT_KEY))
								 {
									 turret->setX(tank->getX() + 18.0f);
									 tankHealth->setX(tank->getX() + 10.0f);
								 }
								 tank->update(frameTime);

								 if (tank->getHealth() < (0.1 * PLAYER_MAX_HEALTH)) //less than 10%
									 tankHealth->setCurrentFrame(6);
								 else if (tank->getHealth() < (0.25 * PLAYER_MAX_HEALTH)) // less than 25%
									 tankHealth->setCurrentFrame(5);
								 else if (tank->getHealth() < (0.5* PLAYER_MAX_HEALTH)) // less than 50%
									 tankHealth->setCurrentFrame(4);
								 else if (tank->getHealth() < (0.6 * PLAYER_MAX_HEALTH)) // less than 60%
									 tankHealth->setCurrentFrame(3);
								 else if (tank->getHealth() < (0.8 * PLAYER_MAX_HEALTH)) //less than 80%
									 tankHealth->setCurrentFrame(2);
								 else if (tank->getHealth() < PLAYER_MAX_HEALTH) // less than 100%
									 tankHealth->setCurrentFrame(1);
								 else if (tank->getHealth() == PLAYER_MAX_HEALTH) // 100%
									 tankHealth->setCurrentFrame(0);
								 else if (tank->getHealth() == 0)
									 tankHealth->setVisible(false); //GAMES END HERE

								 tankHealth->update(frameTime);

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


#pragma region In-game Vector For Loops

								 for (int i = currentActiveSpaceships - 1; i >= 0; i--)
								 {
									 //updates spaceships
									 //checks for HP and changes them accordingly
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

								 for (int i = currentActivePowerups - 1; i >= 0; i--)
								 {

									 if (!array_powerups[i]->getActive())
									 {
										 array_powerups[i]->setVisible(false);
										 std::cout << "Powerup " << i + 1 << " expired" << std::endl;
										 delete array_powerups[i];
										 array_powerups.erase(array_powerups.begin() + i);
										 currentActivePowerups--;
									 }

									 else
										 array_powerups[i]->update(frameTime);

								 }

								 for (int i = currentActiveSpaceshipBullets - 1; i >= 0; i--)
								 {
									 array_spaceship_bullets[i]->update(frameTime);

									 if (array_spaceship_bullets[i]->getY() >= GROUND_LEVEL_HEIGHT)			//reaches out of map
										 array_spaceship_bullets[i]->setActive(false);
								 }

								 //below loop purges all inactive spaceship bullets
								 for (int i = currentActiveSpaceshipBullets - 1; i >= 0; i--)
								 {

									 if (!array_spaceship_bullets[i]->getActive())
									 {
										 //bullet not active, remove from game
										 array_spaceship_bullets[i]->setVisible(false);
										 delete array_spaceship_bullets[i];
										 array_spaceship_bullets.erase(array_spaceship_bullets.begin() + i);
										 currentActiveSpaceshipBullets--;
										 std::cout << "current amt of bullets left : " << currentActiveSpaceshipBullets << std::endl;
									 }

								 }

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

#pragma endregion



								 switch (waveState){
								 case WAVE_STATE::pauseWave:{
																//std::cout << "pause" << std::endl; 
																if (input->isKeyDown(SPACE_KEY))
																{
																	waveControl->setWaveState(WAVE_STATE::wave1);
																	maxAmountOfAllowedBulletsPerVolley = WAVE_1_MAX_AMOUNT_OF_SPACESHIP_BULLETS_PER_VOLLEY;
																}

								 }break;
								 case WAVE_STATE::wave1:{//add wave 1 behaviors

															//std::cout << "wave 1" << std::endl;

															if (!hasWaveOneSpawned)
															{
																despawnSpaceships();
																spawnSpaceships(1);
															}

															if (input->wasKeyPressed(TW_KEY))
															{
																waveControl->setWaveState(WAVE_STATE::wave2);
																maxAmountOfAllowedBulletsPerVolley = WAVE_2_MAX_AMOUNT_OF_SPACESHIP_BULLETS_PER_VOLLEY;

															}

								 }break;
								 case WAVE_STATE::wave2:{//add wave 2 enemy behavior

															//shell->update(frameTime, *turret);

															//std::cout << "wave 2" << std::endl;

															if (!hasWaveTwoSpawned)
															{
																despawnSpaceships();
																spawnSpaceships(2);
															}

															if (input->wasKeyPressed(TH_KEY))		//press 3, for testing only
															{
																waveControl->setWaveState(WAVE_STATE::wave3);
															}


								 }break;
								 case WAVE_STATE::wave3:{//add boss spaceship behaviour
															if (initAlready)
															{
																std::cout << "Initialising boss" << std::endl;
																if (!boss->initialize(this, Boss_SpaceshipNS::WIDTH, Boss_SpaceshipNS::HEIGHT, Boss_SpaceshipNS::TEXTURE_COLS, bossTexture))
																	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss game object"));
																initAlready = false;
																boss->setActive(true);
															}
															despawnSpaceships();

															boss->update(frameTime);
															shell->update(frameTime, *tank);

															if (array_bosslaser.size() != 0){
																for (int i = 0; i < array_bosslaser.size(); i++)
																{

																	array_bosslaser[i]->update(frameTime);
																	if (array_bosslaser[i]->getY() >= GROUND_LEVEL_HEIGHT)
																	{
																		delete array_bosslaser[i];
																		array_bosslaser.erase(array_bosslaser.begin() + i);
																	}
																}
															}
															else launchBossLaser();

															if ((fmod(secondsPassed, SHELL_SPAWNCOUNTER) == 0) && (shell->getActive() == false))
															{
																resetShellPos();
															}
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
	case GENERAL_STATE::gameOver:{
									 if (gameStatus == 1)
									 {
										 gamewin->update(frameTime);
										 if (input->isKeyDown(DOWN_KEY)){
											 gamewin->setCurrentFrame(WINLOSE_END_FRAME);
											 gameOverScreen = 1;
										 }
										 else if (input->isKeyDown(UP_KEY)){
											 gamewin->setCurrentFrame(WINLOSE_START_FRAME);
											 gameOverScreen = 0;
										 }
									 }
									 else if (gameStatus == 2)
									 {
										 gamelose->update(frameTime);
										 if (input->isKeyDown(DOWN_KEY)){
											 gamelose->setCurrentFrame(WINLOSE_END_FRAME);
											 gameOverScreen = 1;
										 }
										 else if (input->isKeyDown(UP_KEY)){
											 gamelose->setCurrentFrame(WINLOSE_START_FRAME);
											 gameOverScreen = 0;
										 }
									 }
									 if (input->wasKeyPressed(ENTER_KEY)){
										 Sleep(500);
										 gameStatus = 0;
										 switch (gameOverScreen)
										 {
										 case 0: gameControl->setGeneralState(GENERAL_STATE::instructions);
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

	//simple ai for wave 2 shooting

	if (gameControl->getGeneralState() == GENERAL_STATE::game
		&&!isCalculatingPlayerPattern)
		std::async(&Descent::acquirePlayerMovementPatterns, this);

}

//=============================================================================
// Handle collisions
//=============================================================================
void Descent::collisions()
{
	VECTOR2 collisionVector;

	for (int i = 0; i < array_bosslaser.size(); i++)
	{
		if (array_bosslaser[i]->collidesWith(*tank, collisionVector))
		{
			std::cout << "bosslaser hit tank" << array_bosslaser[i] << std::endl;
			existOnScreen = false;
			delete array_bosslaser[i];
			array_bosslaser.erase(array_bosslaser.begin() + i);
		}

	}
	if (shell->collidesWith(*tank, collisionVector))
	{

		std::cout << "collide with tank liao" << std::endl;
		shell->setActive(false);
		shell->setVisible(false);
		std::cout << "can u see dis" << std::endl;
	}

	if (cannonball->collidesWith(*shell, collisionVector))
	{
		std::cout << "cannonball hit shell" << std::endl;
		shell->setActive(false);
		shell->setVisible(false);
	}
	if (cannonball->collidesWith(*boss, collisionVector))
	{
		cannonball->bounce(collisionVector, *boss);

		//std::cout << cannonball->getDamageLeft() + "COLLIDE BOSSSHIP" << std::endl;

		cannonball->hit(bossShip);
		boss->setHealth((boss->getHealth() - cannonball->getForcePower()));
		//boss->setVisible(false);
		std::cout << "Boss HP Left:" << (int)boss->getHealth() << std::endl;
	}

	for (int i = currentActiveSpaceships - 1; i >= 0; i--)
	{
		// if collision between cannonball and spaceship
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

	//for collision between tank and powerup
	for (int i = currentActivePowerups - 1; i >= 0; i--)
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

	//for collision between enemy spaceship bullets and tank
	for (int i = currentActiveSpaceshipBullets - 1; i >= 0; i--)
	{
		if (tank->collidesWith(*array_spaceship_bullets[i], collisionVector))
		{
			if (array_spaceship_bullets[i]->getActive())
			{
				array_spaceship_bullets[i]->setActive(false);		//triggers its deletion clause in update()
				tank->setHealth(tank->getHealth() - array_spaceship_bullets[i]->getDamage());
				std::cout << "player took " << array_spaceship_bullets[i]->getDamage() << "damage. Current health : " << tank->getHealth() << "." << std::endl;
			}

			
		}
	}

	//for collision between assist tank bulles and spaceship

	for (int i = currentActiveTankAssistBullets - 1; i >= 0; i--)
	{
		for (int j = currentActiveSpaceships - 1; j >= 0; j--)
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
	const int BUF_SIZE = 20;
	static char buffer[BUF_SIZE];
	graphics->spriteBegin();                // begin drawing sprites
	switch (gameControl->getGeneralState())
	{
	case GENERAL_STATE::menu:{
								 menu1->draw();
	}break;
	case GENERAL_STATE::instructions:{
										 instructionScreen->draw();
	}break;
	case GENERAL_STATE::game:{
								 dxFont.setFontColor(gameNS::FONT_COLOR);
								 background->draw();
								 ground->draw();
								 cannonball->draw();					//in real game, Cannonball should be drawn later, when wormhole appears
								 turret->draw();
								 tank->draw();
								 tankHealth->draw();
								 _snprintf_s(buffer, BUF_SIZE, "Seconds Passed %d ", (int)getSecondsPassed());
								 dxFont.print(buffer, GAME_WIDTH - 200, GAME_HEIGHT - 50);

								 for (int i = 0; i < currentActiveSpaceships; i++)
									 array_spaceships[i]->draw();

								 for (int i = 0; i < currentActivePowerups; i++)
									 array_powerups[i]->draw();

								 if (assistTank->getActive())
									 assistTank->draw();

								 for (int i = 0; i < currentActiveSpaceshipBullets; i++)
									 array_spaceship_bullets[i]->draw();

								 for (int i = 0; i < currentActiveTankAssistBullets; i++)
									 array_tank_assist_bullets[i]->draw();

								 switch (waveControl->getWaveState())
								 {
								 case WAVE_STATE::pauseWave:{
																waveNumberText->print("Wave 1", GAME_HEIGHT / 2, GAME_WIDTH / 2); // need to change to picture

								 }break;
								 case WAVE_STATE::wave1:{
															enemy_spaceship->draw();
								 }break;
								 case WAVE_STATE::wave2:{

								 }break;//draw wave 2 stuff
								 case WAVE_STATE::wave3:{
															boss->draw();
															shell->draw();
															for (int i = 0; i < array_bosslaser.size(); i++)
															{
																array_bosslaser[i]->draw();
															}
								 }break;
								 }

	}break;
	case GENERAL_STATE::paused:{
								   pauseText->print("Paused", GAME_HEIGHT / 2, GAME_WIDTH / 2);
								   pause->draw();
	}break;
	case GENERAL_STATE::gameOver:{
									 if (gameStatus == 1)
									 {
										 gamewin->draw();
									 }
									 else if (gameStatus == 2)
									 {
										 gamelose->draw();
									 }
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

	shellTexture->onLostDevice();
	bossTexture->onLostDevice();
	backgroundTexture->onLostDevice();
	groundTexture->onLostDevice();
	cannonballTexture->onLostDevice();
	spaceshipTexture->onLostDevice();
	spaceship_bulletTexture->onLostDevice();
	menu1Texture->onLostDevice();
	tankTexture->onLostDevice();
	turretTexture->onLostDevice();
	tankHealthTexture->onLostDevice();
	pauseTexture->onLostDevice();
	instructionTexture->onLostDevice();
	gamewinTexture->onLostDevice();
	gameloseTexture->onLostDevice();
	bossLaserTexture->onLostDevice();
	assistTankTexture->onLostDevice();
	assistTankBulletTexture->onLostDevice();
	powerup_timeSlow_texture->onLostDevice();
	powerup_shield_texture->onLostDevice();
	powerup_increaseTankSpeed_texture->onLostDevice();
	powerup_timeLock_texture->onLostDevice();
	powerup_maxPower_texture->onLostDevice();
	powerup_passerbyTank_texture->onLostDevice();

	cannonball->releaseAll();

	despawnSpaceships();
	despawnPowerups();
	despawnPowerupsDrawingSpace();
	despawnSpaceshipBullets();
	despawnAssistTankBullets();


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
	shellTexture->onResetDevice();
	bossTexture->onResetDevice();
	backgroundTexture->onResetDevice();
	groundTexture->onResetDevice();
	cannonballTexture->onResetDevice();
	spaceshipTexture->onResetDevice();
	spaceship_bulletTexture->onResetDevice();
	menu1Texture->onResetDevice();
	tankTexture->onResetDevice();
	turretTexture->onResetDevice();
	tankHealthTexture->onResetDevice();
	pauseTexture->onResetDevice();
	instructionTexture->onResetDevice();
	gamewinTexture->onResetDevice();
	gameloseTexture->onResetDevice();
	bossLaserTexture->onResetDevice();
	assistTankTexture->onResetDevice();
	assistTankBulletTexture->onResetDevice();
	powerup_timeSlow_texture->onResetDevice();
	powerup_shield_texture->onResetDevice();
	powerup_increaseTankSpeed_texture->onResetDevice();
	powerup_timeLock_texture->onResetDevice();
	powerup_maxPower_texture->onResetDevice();
	powerup_passerbyTank_texture->onResetDevice();

	

	cannonball->resetAll();
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
	std::cout << "Tank...";
	tank->setFrames(PlayerNS::START_FRAME, PlayerNS::END_FRAME);
	tank->setCurrentFrame(PlayerNS::START_FRAME);

	tank->setX(GAME_WIDTH / 2);
	tank->setY(GROUND_LEVEL_HEIGHT - PLAYER_HEIGHT + 2.0f);
	tank->flipHorizontal(false);
	
	tankHealth->setCurrentFrame(0);
	tankHealth->setScale(2);
	tankHealth->setX(tank->getX() + 10.0f);
	tankHealth->setY(tank->getY() + 70.0f);

	turret->setCurrentFrame(3);
	turret->setX(tank->getX() + 28.0f);
	turret->setY(tank->getY() - 15.0f);

	cannonball->setX(tank->getX());
	cannonball->setY(tank->getY());
	cannonball->initialiseChargingbar(tank->getX(), tank->getY());

	std::cout << "loaded." << std::endl;

}

//=============================================================================
// in real-time, acquires and updates player movement patterns
//=============================================================================
void Descent::acquirePlayerMovementPatterns()
{
	isCalculatingPlayerPattern = true;

	int positionOriginal = 0;
	int positionFinal = 0;
	int offsetFromOriginal = 0;

	positionOriginal = tank->getX() + (tank->getWidth() / 2);

	Sleep(1000);

	positionFinal = tank->getX() + (tank->getWidth() / 2);

	offsetFromOriginal = (positionOriginal - positionFinal);

	std::cout << "offset:" << offsetFromOriginal << std::endl;
	//in three seconds, the player has moved X from original starting position

	//player's actual speed is distance offset

	if (offsetFromOriginal < 0)			//if negative, change to positive
		offsetFromOriginal = abs(offsetFromOriginal);

	acquiredPlayerSpeed = offsetFromOriginal;		//in 1 second, player has moved pO - pF distance
	acquiredPlayerDirectionIsRight = tank->getTankDirection();

	std::cout << "acquired player speed :" << acquiredPlayerSpeed << ". Is player moving right? " << acquiredPlayerDirectionIsRight << std::endl;

	isCalculatingPlayerPattern = false;

	//tweak/refine algorithm next time
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
										mciSendString("play resources\\music\\powerup_shield_soundeffect.wav", NULL, 0, NULL);
										std::async(&Descent::applyPowerupEffect_restoreHealth, this);
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

			if (seconds == POWERUP_INCREASE_TANK_SPEED_DURATION)
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
// all spaceship runs through a chance and shoots
// simple shooting
// spaceships target curret position of player at time of firing
//=============================================================================
void Descent::beginSimpleSpaceshipsFiringSequence()
{
	//run for loop that iterates through every spaceship
	//for each spaceship, check and compare seed
	//if chance misses
	//nothing happens
	//if chance hit, 
	//create bullet
	//set bullet to target X, where x is player position at time of firing
	//set and calculate bullet degree to relevant X
	//set bullet active, let update take care of movment

	//break once max shots is fired or all spaceships iterated through

	isAllSpaceshipsFiring = true;

	std::cout << "FIRING COMMENCING. YOU SHOULD NOT SEE THIS TWICE." << std::endl;

	for (int i = 0; i < currentActiveSpaceships; i++)
	{

		if (currentActiveSpaceshipBullets <= maxAmountOfAllowedBulletsPerVolley)
		{
			//current max shots per volley not yet reached, so shoot more bullets
			//if false, stop shooting new bullets, end volley

			double generatedChance = rand() % 100;
			if (WAVE_1_SPACESHIPS_FIRE_CHANCE >= generatedChance)
			{
				std::cout << "Spaceship has decided to shoot " << std::endl;
				Spaceship_bullet* bullet = new Spaceship_bullet();

				if (!bullet->initialize(this, Spaceship_bullet_NS::WIDTH, Spaceship_bullet_NS::HEIGHT, Spaceship_bullet_NS::TEXTURE_COLS, spaceship_bulletTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship bullet game object"));

				bullet->setX(array_spaceships[i]->getX() + (array_spaceships[i]->getWidth() / 2));
				bullet->setY(array_spaceships[i]->getY() + array_spaceships[i]->getHeight());
				bullet->setActive(true);

				//take current position of player (at time of firing) and fly towards there
				bullet->setTarget(tank->getX() + (tank->getWidth() / 2));

				array_spaceship_bullets.push_back(bullet);
				currentActiveSpaceshipBullets++;
				std::cout << "fired a bullet " << std::endl;
			}

		}

		if (currentActiveSpaceshipBullets >= maxAmountOfAllowedBulletsPerVolley)
		{
			std::cout << "too much bullets, stopped " << currentActiveSpaceshipBullets << " to " << maxAmountOfAllowedBulletsPerVolley << std::endl;
			break;
		}

	}

	isAllSpaceshipsFiring = false;

}

//=============================================================================
// all spaceship runs through a chance and shoots
//=============================================================================
void Descent::beginAdvancedSpaceshipsFiringSequence()
{
	isAllSpaceshipsFiring = true;


	//break once max shots is fired or all spaceships iterated through
	std::cout << "advance pew pew " << maxAmountOfAllowedBulletsPerVolley << std::endl;
	for (int i = 0; i < currentActiveSpaceships; i++)
	{

		if (currentActiveSpaceshipBullets < maxAmountOfAllowedBulletsPerVolley)
		{

			//current max shots per volley not yet reached, so shoot more bullets
			//if false, stop shooting new bullets, end volley

			double generatedChance = rand() % 100;
			if (WAVE_1_SPACESHIPS_FIRE_CHANCE >= generatedChance)
			{

				Spaceship_bullet* bullet = new Spaceship_bullet();

				if (!bullet->initialize(this, Spaceship_bullet_NS::WIDTH, Spaceship_bullet_NS::HEIGHT, Spaceship_bullet_NS::TEXTURE_COLS, spaceship_bulletTexture))
					throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship bullet game object"));

				bullet->setX(array_spaceships[i]->getX() + (array_spaceships[i]->getWidth() / 2));
				bullet->setY(array_spaceships[i]->getY() + array_spaceships[i]->getHeight());
				bullet->setActive(true);

				if (acquiredPlayerDirectionIsRight)
				{
					//player is moving to the right, aim to the right of player
					bullet->setTarget(tank->getX() + (tank->getWidth() / 2)
						+ (acquiredPlayerSpeed*(bullet->getY() / SPACESHIP_BULLET_SPEED)));
				}
				else
				{
					//player is moving left
					bullet->setTarget(tank->getX() + (tank->getWidth() / 2)
						- (acquiredPlayerSpeed*(bullet->getY() / SPACESHIP_BULLET_SPEED)));
				}


				std::cout << "Spaceship shoots at " << bullet->getTarget() << ", player position is "
					<< tank->getX() + (tank->getWidth() / 2) << std::endl;
				//acquiredPlayerSPeed * bulletY/Spaceship_bullet_speed
				//this calculates how far the bullet needs to lead the shot

				array_spaceship_bullets.push_back(bullet);
				currentActiveSpaceshipBullets++;

			}

		}

		else
			break;
	}

	isAllSpaceshipsFiring = false;

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
			
			//MOVE SPACESHIPS
			if ((fmod(getSecondsPassed(), SPACESHIP_MOVE_FREQUENCY*timeModifier)) == 0)
			{
				moveSpaceships();
				
			}

			//SIMPLE WAVE 1 SPACESHIP SHOOTING
			if (waveControl->getWaveState() == WAVE_STATE::wave1
				&& (fmod(getSecondsPassed(), SPACESHIP_ATTACK_FREQUENCY)) == 0
				&& currentActiveSpaceshipBullets == 0
				&& !isAllSpaceshipsFiring)
			{	//if wave is wave 1, start simple spaceship shooting
				std::async(&Descent::beginSimpleSpaceshipsFiringSequence, this);
				Sleep(5);	//to prevent thread overload
			}

			//ADVANCED WAVE 2 SPACESHIP SHOOTING
			if (waveControl->getWaveState() == WAVE_STATE::wave2
				&& (fmod(getSecondsPassed(), SPACESHIP_ATTACK_FREQUENCY)) == 0
				&& !isAllSpaceshipsFiring)
			{

				std::async(&Descent::beginSimpleSpaceshipsFiringSequence, this);
				std::async(&Descent::beginAdvancedSpaceshipsFiringSequence, this);
				Sleep(5);	//to prevent thread overload
			}

			//SPAWN POWERUP
			if ((fmod(getSecondsPassed(), POWERUP_SPAWN_FREQUENCY)) == 0
				&& currentActivePowerups < MAX_NO_OF_POWERUPS
				&& !isPowerupInProgress
				&& isPowerupSpawning)
				spawnPowerup();

		}
	}
}


//=============================================================================
// spawn spaceships 
// waveNumber = No. of wave, relies on this number to pull certain numbers from constants.h
//=============================================================================
void Descent::spawnSpaceships(int waveNumber)
{

	int amountOfRows = 0;
	int spaceshipHealth = 0;

	switch (waveNumber)
	{
	case 1: {
				amountOfRows = WAVE_1_SPACESHIPS_AMT_OF_ROWS;
				spaceshipHealth = WAVE_1_SPACESHIPS_HEALTH;
				hasWaveOneSpawned = true;
	}break;
	case 2: {
				amountOfRows = WAVE_2_SPACESHIPS_AMT_OF_ROWS;
				spaceshipHealth = WAVE_2_SPACESHIPS_HEALTH;
				hasWaveTwoSpawned = true;
				isCalculatingPlayerPattern = false; //is not null anymore, AI now activates
	}break;

	case 3: {
				amountOfRows = WAVE_3_SPACESHIPS_AMT_OF_ROWS;
				spaceshipHealth = WAVE_3_SPACESHIPS_HEALTH;
				hasWaveThreeSpawned = true;
	}break;

	}

	//place inside game state wave 1 when created

	int x = 0;	//starting position of first spaceship is a unit length away the left side of the screen
	int y = 0;	//to be manipulated in first for loop

	//wave one
	std::cout << "GAME WIDTH DIVIDED BY SHIP WIDTH (spaceships per row):" << GAME_WIDTH / (HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS) << std::endl;

	for (int i = 0; i < amountOfRows; i++)
	{
		//this for loop spawns at Y
		y += SPACESHIP_HEIGHT + VERTICAL_GAP_LENGTH_BETWEEN_SPACESHIPS;

		for (int j = 0; j < GAME_WIDTH / (SPACESHIP_WIDTH); j++)
		{
			Spaceship* spaceship = new Spaceship();

			//check if current Y can support game_width/spaceship_width amount of ships

			if (x + ((HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS + SPACESHIP_WIDTH)) > GAME_WIDTH - HORIZONTAL_GAP_LENGTH_BETWEEN_SPACESHIPS
				|| j >= AMT_OF_SPACESHIPS_PER_ROW)
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
			spaceship->setHealth(spaceshipHealth);

			if (!spaceship->initialize(this, SpaceshipNS::WIDTH, SpaceshipNS::HEIGHT, SpaceshipNS::TEXTURE_COLS, spaceshipTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spaceship game object"));

			array_spaceships.push_back(spaceship);
			std::cout << "Adding spaceship at row " << i + 1 << "(no. " << j + 1 << " in row) for wave one at x: " << spaceship->getX() << " y: " << spaceship->getY() << "." << std::endl;

			currentActiveSpaceships++;

			std::cout << "Current amt of spaceships: " << currentActiveSpaceships << "." << std::endl;

			if (currentActiveSpaceships == maxActiveSpaceships)
				break;
		}
		if (currentActiveSpaceships == maxActiveSpaceships)
			break;
	}
}

//=============================================================================
// reset Shell position
//	reset the shell position 
//=============================================================================
void Descent::resetShellPos()
{
	shell->setActive(true);
	shell->setVisible(true);
	if (!shell->initialize(this, ShellNS::WIDTH, ShellNS::HEIGHT, ShellNS::TEXTURE_COLS, shellTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shell game object"));
	shell->setX(boss->getX() + BOSS_SPACESHIP_WIDTH / 2);
	shell->setY(boss->getY() + BOSS_SPACESHIP_HEIGHT / 2);
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

//=============================================================================
// checkGameStatus
// see if win or lose
//=============================================================================
void Descent::checkGamestatus()
{
	if (tank->getHealth() == 0)
	{
		gameStatus = 2;
		gameControl->setGeneralState(GENERAL_STATE::gameOver);
	}
}

//=============================================================================
// launch the boss laser
//=============================================================================
void Descent::launchBossLaser()
{
	array[0] = 45;
	array[1] = 0;
	array[2] = -45;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "initialising laser number " << i << std::endl;
		BossLaser* bosslaser = new BossLaser();
		if (!bosslaser->initialize(this, BossLaserNS::WIDTH, BossLaserNS::HEIGHT, BossLaserNS::TEXTURE_COLS, bossLaserTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initialising background"));
		array_bosslaser.push_back(bosslaser);
		array_bosslaser[i]->setX(boss->getCenterX());
		array_bosslaser[i]->setY(boss->getY());
		array_bosslaser[i]->setDegrees(-array[i]);
		array_bosslaser[i]->setDegree(array[i]);
		array_bosslaser[i]->setFrames(BossLaserNS::START_FRAME, BossLaserNS::END_FRAME);
		array_bosslaser[i]->setCurrentFrame(BossLaserNS::START_FRAME);
		laserCounter++;
	}
	existOnScreen = false;
}

//=============================================================================
// cleans up spaceship arrays
// call before major changes to spaceship array
// INDISCRIMINATELY removes ALL spaceships regardless of activeness
//=============================================================================
void Descent::despawnSpaceships()
{
	for (int i = currentActiveSpaceships - 1; i >= 0; i--)
	{
		array_spaceships[i]->setVisible(false);
		std::cout << "Spaceship " << i << " is deleted" << std::endl;
		delete array_spaceships[i];
		array_spaceships.erase(array_spaceships.begin() + i);
		currentActiveSpaceships--;
	}

	if (array_spaceships.size() != 0)
		std::cout << "WARNING: Spaceship array is not emptied correctly." << std::endl;


}

//=============================================================================
// cleans up powerup arrays
//=============================================================================
void Descent::despawnPowerups()
{
	for (int i = currentActivePowerups - 1; i >= 0; i--)
	{
		array_powerups[i]->setVisible(false);
		std::cout << "Powerup " << i << " is deleted" << std::endl;
		delete array_powerups[i];
		array_powerups.erase(array_powerups.begin() + i);
		currentActivePowerups--;
	}

	if (array_powerups.size() != 0)
		std::cout << "WARNING: Powerup array is not emptied correctly." << std::endl;

}

//=============================================================================
// cleans up powerup drawing space arrays
//=============================================================================
void Descent::despawnPowerupsDrawingSpace()
{
	for (int i = totalAmtOfPowerupVariety - 1; i >= 0; i--)
	{
		array_powerups_drawingSpace[i]->setVisible(false);
		std::cout << "Powerup (original) " << i << " is deleted" << std::endl;
		delete array_powerups_drawingSpace[i];
		array_powerups_drawingSpace.erase(array_powerups_drawingSpace.begin() + i);
		currentActivePowerups--;
	}

	if (array_powerups_drawingSpace.size() != 0)
		std::cout << "WARNING: Powerup drawingSpace array is not emptied correctly." << std::endl;

}

//=============================================================================
// cleans up powerup arrays
//=============================================================================
void Descent::despawnSpaceshipBullets()
{
	for (int i = currentActiveSpaceshipBullets - 1; i >= 0; i--)
	{
		array_spaceship_bullets[i]->setVisible(false);
		std::cout << "Spaceship bullet " << i << " is deleted" << std::endl;
		delete array_spaceship_bullets[i];
		array_spaceship_bullets.erase(array_spaceship_bullets.begin() + i);
		currentActiveSpaceshipBullets--;
	}

	if (array_spaceship_bullets.size() != 0)
		std::cout << "WARNING: Spaceship bullets array is not emptied correctly." << std::endl;

}


//=============================================================================
// cleans up powerup arrays
//=============================================================================
void Descent::despawnAssistTankBullets()
{
	for (int i = currentActiveTankAssistBullets - 1; i >= 0; i--)
	{
		array_tank_assist_bullets[i]->setVisible(false);
		std::cout << "Assist-tank bullet " << i << " is deleted" << std::endl;
		delete array_tank_assist_bullets[i];
		array_tank_assist_bullets.erase(array_tank_assist_bullets.begin() + i);
		currentActiveTankAssistBullets--;
	}

	if (array_tank_assist_bullets.size() != 0)
		std::cout << "WARNING: Assist-tank bullets array is not emptied correctly." << std::endl;

}


//=============================================================================
// loads highscore
// MAY NOT NEED TO BE AN EXTERNAL METHOD
//=============================================================================
void Descent::loadHighScore()
{
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
}