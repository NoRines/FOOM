#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "BaseState.h"
#include "../World/BspTree.h"
#include "../Entities/Camera.h"

class PlayState : public BaseState
{
public:
	PlayState();

	void update(float delta) override;

	void render(GameRenderer& renderer) override;

private:
	Camera playerCamera;
	BspTree bspTree;
};

#endif
