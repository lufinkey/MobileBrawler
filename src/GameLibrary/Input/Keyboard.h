
#include "../Utilities/ArrayList.h"
#include "../Utilities/String.h"

#pragma once

namespace GameLibrary
{
	class KeyboardEventListener;

	/*Represents the Keyboard and all key states on the Keyboard*/
	class Keyboard
	{
		friend class EventManager;
	public:
		/*Constant that represents a Key*/
		enum Key
		{
			UNKNOWN_KEY,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			NUM_0,
			NUM_1,
			NUM_2,
			NUM_3,
			NUM_4,
			NUM_5,
			NUM_6,
			NUM_7,
			NUM_8,
			NUM_9,
			ESCAPE,
			CTRL_LEFT,
			SHIFT_LEFT,
			ALT_LEFT,
			WINDOWS_LEFT,
			CTRL_RIGHT,
			SHIFT_RIGHT,
			ALT_RIGHT,
			WINDOWS_RIGHT,
			CONTEXT_MENU,
			OPENBRACKET,
			CLOSEBRACKET,
			SEMICOLON,
			COMMA,
			PERIOD,
			QUOTE,
			FORWARDSLASH,
			BACKSLASH,
			EQUALS,
			DASH,
			SPACE,
			ENTER,
			BACKSPACE,
			TAB,
			PAGEUP,
			PAGEDOWN,
			END,
			HOME,
			INSERT,
			DELETE,
			ADD,
			SUBTRACT,
			MULTIPLY,
			DIVIDE,
			LEFTARROW,
			RIGHTARROW,
			UPARROW,
			DOWNARROW,
			NUMPAD_0,
			NUMPAD_1,
			NUMPAD_2,
			NUMPAD_3,
			NUMPAD_4,
			NUMPAD_5,
			NUMPAD_6,
			NUMPAD_7,
			NUMPAD_8,
			NUMPAD_9,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			PAUSE
		};
		typedef enum Key Key;

		/*Returns a String representing the specified Key*/
		static String getKeyText(Key key);

		/*Returns true if Key is currently in a pressed state*/
		bool isKeyPressed(Key key);
		/*Returns true if Key is currently in a released state*/
		bool isKeyReleased(Key key);

		/*Returns true if Key was in a pressed state in the previous frame*/
		bool wasKeyPressed(Key key);
		/*Returns true if Key was in a released state in the previous frame*/
		bool wasKeyReleased(Key key);

		/*Returns true if Key was just pressed (released state in the previous frame, pressed state in the current frame)*/
		bool didKeyPress(Key key);
		/*Returns true if Key was just released (pressed state in the previous frame, released state in the current frame)*/
		bool didKeyRelease(Key key);

		/*Adds a KeyboardEventListener to handle Keyboard events*/
		void addEventListener(KeyboardEventListener*);
		/*Removes a previously added KeyboardEventListener*/
		void removeEventListener(KeyboardEventListener*);

	private:
		/*Handles key press events sent from EventManager*/
		static void handleKeyPress(Key key);
		/*Handles key release events sent from EventManager*/
		static void handleKeyRelease(Key key);

		/*Updates all key states. Called once per frame from the main thread.*/
		static void update();
	};

	/*Event listener that handles Keyboard events*/
	class KeyboardEventListener
	{
	public:
		/*Event called when a Key state changes to pressed*/
		virtual void onKeyPress(Keyboard::Key key){}
		/*Event called when a Key state changes to released*/
		virtual void onKeyRelease(Keyboard::Key key){}
	};
}