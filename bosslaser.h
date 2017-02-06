#ifndef _BOSSLASER_H
#define _BOSSLASER_H

#include "entity.h"
#include "constants.h"
#include "Player.h"
#include <math.h>
namespace BossLaserNS
{
	const int WIDTH = BOSSLASER_WIDTH;
	const int HEIGHT = BOSSLASER_HEIGHT;
	const float ROTATION_RATE = (float)PI;
	const float BASE_SPEED = BOSSLASER_BASE_SPEED;
	const float MASS = BOSSLASER_MASS;
	const int TEXTURE_COLS = BOSSLASER_TEXTURE_COLUMNS;
	const int START_FRAME = BOSSLASER_START_FRAME;
	const int END_FRAME = BOSSLASER_END_FRAME;
	const float ANIMATION_DELAY = SHELL_ANIMATION_DELAY;
	const int DAMAGE = SHELL_DAMAGE;
	const int X = 0;
	const int Y = 0;
}

class BossLaser : public Entity
{
private:
	bool moving;


public:
	BossLaser();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime, Player turret);


};
#endif