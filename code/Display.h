#ifndef DISPLAY_H
#define DISPLAY_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
class Bitmap;
class Input;

class Display
{
public:
	friend Input;

	static Display& get();

	// These should not be implemented
	Display(const Display& disp) = delete;
	Display& operator=(const Display& disp) = delete;
	Display(Display&& disp) = delete;
	Display& operator=(Display&& disp) = delete;


	int getWidth() const;
	int getHeight() const;

	void update(const Bitmap& frameBuffer);

	void getWindowSize(int& w, int& h) const;
private:
	Display(int width, int height, const char* title);
	~Display();

	int width;
	int height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};

#endif
