#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <stack>
#include "States/BaseState.h"

class Application
{
public:
	int execute();

private:
	bool init();
	void gameLoop();

	void pushState(std::unique_ptr<BaseState> state);
	void popState();

	std::stack<std::unique_ptr<BaseState>> states;
};

#endif
