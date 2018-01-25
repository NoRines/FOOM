#ifndef EDITSTATE_H
#define EDITSTATE_H

#include "BaseState.h"
#include "../Maths/Math.h"
#include <vector>
#include "../World/Sector.h"

class EditState : public BaseState
{
public:
	EditState();

	void update(float delta) override;
	void render(GameRenderer& renderer) override;

private:
	void getMouseCoords(int& x, int& y);
	void getOldMouseCoords(int& x, int& y);

	Vector2f gridPos;

	const int rendererWidth;
	const int rendererHeight;
	float gridWidth;
	float gridHeight;
};

#endif
