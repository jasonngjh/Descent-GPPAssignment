#ifndef _SHELL_H
#define _SHELL_H

#include "entity.h"
#include "constants.h"

namespace ShellNS
{
	const int WIDTH = SHELL_WIDTH;
	const int HEIGHT = SHELL_HEIGHT;
	const float ROTATION_RATE = (float)PI;
	const float BASE_SPEED = SHELL_BASE_SPEED;
	const float MASS = SHELL_MASS;
	const int TEXTURE_COLS = SHELL_TEXTURE_COLUMNS;
	const int START_FRAME = SHELL_START_FRAME;
	const int END_FRAME = SHELL_END_FRAME;
	const float ANIMATION_DELAY = SHELL_ANIMATION_DELAY;
	const int DAMAGE = SHELL_DAMAGE;

	const int X = 0;
	const int Y = 0;
}

class Shell : public Entity
{
private:

public:
	Shell();

	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
};
#endif