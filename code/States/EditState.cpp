#include "EditState.h"
#include "../Graphics/FrameBuffers/GameRenderer.h"
#include "../Input.h"
#include "../Display.h"

#include <iostream>

EditState::EditState() :
gridPos(5.0f, 5.0f),
rendererWidth(Display::get().getWidth()),
rendererHeight(Display::get().getHeight()),
gridWidth(rendererWidth / 50),
gridHeight(rendererHeight / 50)
{
}

void EditState::update(float delta)
{
	if(Input::get().isMouseButtonDown(Input::Mouse::LEFT_BUTTON))
	{
		int mouseX, mouseY;
		int oldMouseX, oldMouseY;
		getMouseCoords(mouseX, mouseY);
		getOldMouseCoords(oldMouseX, oldMouseY);
		Vector2f mouseChange;
		mouseChange.x = (mouseX - oldMouseX) / (gridWidth * 10.0f);
		mouseChange.y = (mouseY - oldMouseY) / (gridHeight * 10.0f);
		gridPos += mouseChange;
	}
}

void EditState::render(GameRenderer& renderer)
{
	renderer.clear(0x0);

	const int yStart = (int)(gridPos.y * (float)gridHeight * 10);

	for(int i = yStart; i < rendererHeight; i += gridHeight)
	{
		if(i < 0)
		{
			continue;
		}
		if((i - yStart) % (int)(gridHeight * 10) == 0)
		{
			renderer.drawLine(0, i, rendererWidth, i, 120, 120, 120);
		}
		else
		{
			renderer.drawLine(0, i, rendererWidth, i, 50, 50, 50);
		}
	}
	for(int i = yStart; i >= 0; i -= gridHeight)
	{
		if(i >= rendererHeight)
		{
			continue;
		}
		if((i - yStart) % (int)(gridHeight * 10) == 0)
		{
			renderer.drawLine(0, i, rendererWidth, i, 120, 120, 120);
		}
		else
		{
			renderer.drawLine(0, i, rendererWidth, i, 50, 50, 50);
		}
	}

	const int xStart = (int)(gridPos.x * (float)gridWidth * 10);

	for(int i = xStart; i < rendererWidth; i += gridWidth)
	{
		if(i < 0)
		{
			continue;
		}
		if((i - xStart) % (int)(gridWidth * 10) == 0)
		{
			renderer.drawLine(i, 0, i, rendererHeight, 120, 120, 120);
		}
		else
		{
			renderer.drawLine(i, 0, i, rendererHeight, 50, 50, 50);
		}
	}
	for(int i = xStart; i >= 0; i -= gridWidth)
	{
		if(i >= rendererWidth)
		{
			continue;
		}
		if((i - xStart) % (int)(gridWidth * 10) == 0)
		{
			renderer.drawLine(i, 0, i, rendererHeight, 120, 120, 120);
		}
		else
		{
			renderer.drawLine(i, 0, i, rendererHeight, 50, 50, 50);
		}
	}
}

void EditState::getMouseCoords(int& x, int& y)
{
	x = Input::get().getMouseX();
	y = Input::get().getMouseY();
	int displayWidth;
	int displayHeight;
	Display::get().getWindowSize(displayWidth, displayHeight);
	float widthFactor = (float)x / (float)displayWidth;
	float heightFactor = (float)y / (float)displayHeight;
	x = rendererWidth * widthFactor;
	y = rendererHeight * heightFactor;
}

void EditState::getOldMouseCoords(int& x, int& y)
{
	x = Input::get().getOldMouseX();
	y = Input::get().getOldMouseY();
	int displayWidth;
	int displayHeight;
	Display::get().getWindowSize(displayWidth, displayHeight);
	float widthFactor = (float)x / (float)displayWidth;
	float heightFactor = (float)y / (float)displayHeight;
	x = rendererWidth * widthFactor;
	y = rendererHeight * heightFactor;
}
