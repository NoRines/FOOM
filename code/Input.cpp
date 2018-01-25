#include "Input.h"
#include <SDL2/SDL.h>
#include "Display.h"

#include <algorithm>

Input& Input::get()
{
	static Input input;
	return input;
}

Input::Input() :
closeWindow(false),
keyMap{false},
oldKeyMap{false},
mouseButtonMap{false},
oldMouseButtonMap{false},
mouseX(0),
mouseY(0),
oldMouseX(0),
oldMouseY(0)
{
}

void Input::pollEvents()
{
	std::copy(keyMap, keyMap + 300, oldKeyMap);
	std::copy(mouseButtonMap, mouseButtonMap + 6, oldMouseButtonMap);

	oldMouseX = mouseX;
	oldMouseY = mouseY;

	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
			{
				closeWindow = true;
			} break;

			case SDL_KEYDOWN:
			{
				keyMap[e.key.keysym.scancode] = true;
			} break;

			case SDL_KEYUP:
			{
				keyMap[e.key.keysym.scancode] = false;
			} break;

			case SDL_MOUSEBUTTONDOWN:
			{
				mouseButtonMap[e.button.button] = true;
			} break;

			case SDL_MOUSEBUTTONUP:
			{
				mouseButtonMap[e.button.button] = false;
			} break;

			case SDL_MOUSEMOTION:
			{
				mouseX = e.motion.x;
				mouseY = e.motion.y;
			} break;

			default:
			{} break;
		}
	}
}

bool Input::shouldCloseWindow() const
{
	return closeWindow;
}

bool Input::isKeyDown(Keyboard key)
{
	return isKeyDown((int)key);
}

bool Input::isKeyPressed(Keyboard key)
{
	return isKeyPressed((int)key);
}

bool Input::isKeyDown(int key)
{
	return keyMap[key];
}

bool Input::isKeyPressed(int key)
{
	return (keyMap[key] && !oldKeyMap[key]);
}

bool Input::isMouseButtonDown(Mouse button)
{
	return isMouseButtonDown((int)button);
}

bool Input::isMouseButtonPressed(Mouse button)
{
	return isMouseButtonPressed((int)button);
}

bool Input::isMouseButtonDown(int button)
{
	return mouseButtonMap[button];
}

bool Input::isMouseButtonPressed(int button)
{
	return (mouseButtonMap[button] && !oldMouseButtonMap[button]);
}

void Input::setMousePosToMiddleOfScreen(Display& display)
{
	int windowWidth;
	int windowHeight;

	display.getWindowSize(
		windowWidth,
		windowHeight);

	SDL_WarpMouseInWindow(
		display.window,
		windowWidth / 2,
		windowHeight / 2);
}

int Input::getMouseX() const
{
	return mouseX;
}

int Input::getMouseY() const
{
	return mouseY;
}

int Input::getOldMouseX() const
{
	return oldMouseX;
}

int Input::getOldMouseY() const
{
	return oldMouseY;
}

void Input::hideMouse(bool value)
{
	if(value)
	{
		SDL_ShowCursor(SDL_DISABLE);
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
	}
}
