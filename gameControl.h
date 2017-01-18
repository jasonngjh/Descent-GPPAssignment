#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

enum class GENERAL_STATE : int {
	menu = 1,
	game = 2,
	paused = 3,
	gameOver = 4,
	gameClear = 5,
	instructions = 6,
	credits = 7,
	home = 8,
};

class GameControl {
private:

	GENERAL_STATE generalState;

public:

	GameControl();
	~GameControl();

	GENERAL_STATE getGeneralState() { return generalState; }
	void setGeneralState(GENERAL_STATE gens) { generalState = gens; }
};

#endif