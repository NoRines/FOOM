#include "Application.h"
#include "Display.h"
#include "Input.h"
#include "Utils/Clock.h"
#include "Graphics/FrameBuffers/GameRenderer.h"
#include "States/PlayState.h"
#include "States/EditState.h"

// tmp
#include <iostream>

int Application::execute()
{
	if(!init())
	{
		return 1;
	}

	//pushState(std::make_unique<EditState>());
	pushState(std::make_unique<PlayState>());
	gameLoop();

	popState();

	return 0;
}

bool Application::init()
{
	try
	{
		Display::get();
	}
	catch(int e)
	{
		return false;
	}
	return true;
}

void Application::gameLoop()
{
	constexpr double sampleResolution = 1000000000.0;
	uint64_t sampleTicks = 0;
	uint64_t ticksPerFrame = (uint64_t)(sampleResolution) / 30;
	Clock<std::chrono::nanoseconds> clock;
	double delta = 0.0;
	double secCounter = 0.0;

	GameRenderer frameBuffer(Display::get().getWidth(), Display::get().getHeight());

	while(!Input::get().shouldCloseWindow())
	{
		sampleTicks = clock.ticksSinceSample();
		delta = sampleTicks / sampleResolution;
		clock.sample();

		if(sampleTicks < ticksPerFrame)
		{
			clock.sleep(ticksPerFrame - sampleTicks);
		}

		secCounter += delta;
		if(secCounter >= 1.0)
		{
			//std::cout << 1.0 / delta << std::endl;
			secCounter = 0.0;
		}

		Input::get().pollEvents();

		states.top()->update(delta);

		states.top()->render(frameBuffer);

		Display::get().update(frameBuffer);
	}
}

void Application::pushState(std::unique_ptr<BaseState> state)
{
	states.push(std::move(state));
}

void Application::popState()
{
	states.pop();
}
