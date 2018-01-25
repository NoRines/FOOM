#ifndef BASESTATE_H
#define BASESTATE_H

class GameRenderer;

class BaseState
{
public:
	virtual ~BaseState() = default;

	virtual void update(float delta) = 0;
	virtual void render(GameRenderer& renderer) = 0;
};

#endif
