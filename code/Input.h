#ifndef INPUT_H
#define INPUT_H

class Display;

class Input
{
public:
	enum class Keyboard;
	enum class Mouse;

	static Input& get();

	Input(const Input& rhs) = delete;
	Input& operator=(const Input& rhs) = delete;
	Input(Input&& rhs) = delete;
	Input& operator=(Input&& rhs) = delete;

	void pollEvents();

	bool shouldCloseWindow() const;

	bool isKeyDown(Keyboard key);
	bool isKeyPressed(Keyboard key);

	bool isKeyDown(int key);
	bool isKeyPressed(int key);

	bool isMouseButtonDown(Mouse button);
	bool isMouseButtonPressed(Mouse button);

	bool isMouseButtonDown(int button);
	bool isMouseButtonPressed(int button);

	void setMousePosToMiddleOfScreen(Display& display);

	int getMouseX() const;
	int getMouseY() const;

	int getOldMouseX() const;
	int getOldMouseY() const;

	void hideMouse(bool value);

private:
	Input();
	~Input() = default;

	bool closeWindow;
	bool keyMap[300];
	bool oldKeyMap[300];
	bool mouseButtonMap[6];
	bool oldMouseButtonMap[6];

	int mouseX;
	int mouseY;
	int oldMouseX;
	int oldMouseY;

public:
	enum class Mouse
	{
		LEFT_BUTTON = 1,
		MIDDLE_BUTTON = 2,
		RIGHT_BUTTON = 3
	};

	enum class Keyboard
	{
		KEY_UNKNOWN = 0,
		A = 4,
		B = 5,
		C = 6,
		D = 7,
		E = 8,
		F = 9,
		G = 10,
		H = 11,
		I = 12,
		J = 13,
		K = 14,
		L = 15,
		M = 16,
		N = 17,
		O = 18,
		P = 19,
		Q = 20,
		R = 21,
		S = 22,
		T = 23,
		U = 24,
		V = 25,
		W = 26,
		X = 27,
		Y = 28,
		Z = 29,
		NUM_1 = 30,
		NUM_2 = 31,
		NUM_3 = 32,
		NUM_4 = 33,
		NUM_5 = 34,
		NUM_6 = 35,
		NUM_7 = 36,
		NUM_8 = 37,
		NUM_9 = 38,
		NUM_0 = 39,
		RETURN = 40,
		ESCAPE = 41,
		BACKSPACE = 42,
		TAB = 43,
		SPACE = 44,
		MINUS = 45,
		EQUALS = 46,
		LEFTBRACKET = 47,
		RIGHTBRACKET = 48,
		BACKSLASH = 49,
		NONUSHASH = 50,
		SEMICOLON = 51,
		APOSTROPHE = 52,
		GRAVE = 53,
		COMMA = 54,
		PERIOD = 55,
		SLASH = 56,
		CAPSLOCK = 57,
		F1 = 58,
		F2 = 59,
		F3 = 60,
		F4 = 61,
		F5 = 62,
		F6 = 63,
		F7 = 64,
		F8 = 65,
		F9 = 66,
		F10 = 67,
		F11 = 68,
		F12 = 69,
		PRINTSCREEN = 70,
		SCROLLLOCK = 71,
		PAUSE = 72,
		INSERT = 73,
		HOME = 74,
		PAGEUP = 75,
		DELETE = 76,
		END = 77,
		PAGEDOWN = 78,
		RIGHT = 79,
		LEFT = 80,
		DOWN = 81,
		UP = 82,
		LCTRL = 224,
		LSHIFT = 225,
		LALT = 226,
		RCTRL = 228,
		RSHIFT = 229,
		RALT = 230,
	};
};

#endif
