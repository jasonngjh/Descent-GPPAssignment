#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H
enum class GENERAL_STATE {
	menu ,
	game ,
	paused ,
	gameOver,
	gameClear ,
	instructions,
	credits ,
	home ,
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