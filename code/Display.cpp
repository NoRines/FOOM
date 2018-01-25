#include "Display.h"
#include <SDL2/SDL.h>
#include "Graphics/FrameBuffers/Bitmap.h"

Display& Display::get()
{
	//static Display display(320, 200, "FOOM"); // DOS upplösning
	static Display display(640, 480, "FOOM"); // 640x480
	//static Display display(800, 600, "FOOM"); // 800x600
	return display;
}

Display::Display(int width, int height, const char* title) :
width(width),
height(height)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw 1;
	}

	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_RESIZABLE);

	if(!window)
	{
		throw 2;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if(!renderer)
	{
		throw 3;
	}

	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		width,
		height);

	if(!texture)
	{
		throw 3;
	}
}

Display::~Display()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Display::getWidth() const
{
	return width;
}

int Display::getHeight() const
{
	return height;
}

void Display::update(const Bitmap& frameBuffer)
{
	uint8_t* textureData;
	int pitch;

	SDL_LockTexture(texture, nullptr, (void**)&textureData, &pitch);
	frameBuffer.copyToByteArray(textureData, pitch);
	SDL_UnlockTexture(texture);

	SDL_RenderCopy(
		renderer,
		texture,
		nullptr,
		nullptr);

	SDL_RenderPresent(renderer);
}

void Display::getWindowSize(int& w, int& h) const
{
	SDL_GetWindowSize(
		window,
		&w,
		&h);
}
