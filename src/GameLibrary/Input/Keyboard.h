
#pragma once

#include "../Utilities/String.h"
#include "../Exception/IllegalArgumentException.h"

namespace GameLibrary
{
	class KeyboardEventListener;

	/*! Represents the Keyboard and all key states on the Keyboard*/
	class Keyboard
	{
		friend class EventManager;
	public:
		/*! Constant that represents a Key*/
		typedef enum
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
		} Key;
		
		/*! Gets a String that represents the specified Key.
			\returns a String value*/
		static String getKeyText(Key key);
		
		
		/*! Checks if a key on the keyboard is currently being pressed.
			\returns true if Key is currently in a pressed state, or false if otherwise*/
		static bool isKeyPressed(Key key);
		/*! Checks if a key on the keyboard is currently not being pressed.
			\returns true if Key is currently in a released state, or false if otherwise*/
		static bool isKeyReleased(Key key);
		
		
		/*! Checks if a key on the keyboard was being pressed in the previous frame.
			\returns true if Key was in a pressed state in the previous frame, or false if otherwise*/
		static bool wasKeyPressed(Key key);
		/*! Checks if a key on the keyboard was not being pressed in the previous frame.
			\returns true if Key was in a released state in the previous frame, or false if otherwise*/
		static bool wasKeyReleased(Key key);
		
		
		/*! Checks if a key on the keyboard was just pressed.
			\returns true if Key was just pressed (released state in the previous frame, pressed state in the current frame), or false if otherwise*/
		static bool didKeyPress(Key key);
		/*! Checks if a key on the keyboard was just released.
			\returns true if Key was just released (pressed state in the previous frame, released state in the current frame), or false if otherwise*/
		static bool didKeyRelease(Key key);

		/*! Adds a KeyboardEventListener to handle Keyboard events.
			\param eventListener the listener pointer*/
		static void addEventListener(KeyboardEventListener*eventListener);
		/*! Removes a previously added KeyboardEventListener.
			\param eventListener the listener pointer*/
		static void removeEventListener(KeyboardEventListener*eventListener);

	private:
		/*! Handles key press events sent from EventManager.
			\param key the key that was pressed*/
		static void handleKeyPress(Keyboard::Key key);
		/*! Handles key release events sent from EventManager.
			\param key the key that was released*/
		static void handleKeyRelease(Keyboard::Key key);
		
		/*! Updates all key states. Called once per frame by EventManager from the Application in main thread.*/
		static void update();
	};
	
	
	/*! Event listener that handles Keyboard events*/
	class KeyboardEventListener
	{
	public:
		/*! virtual destructor*/
		virtual ~KeyboardEventListener(){}
		/*! Called when a Key state changes to pressed.
			\param key a constant that represents the pressed key*/
		virtual void onKeyPress(Keyboard::Key key){}
		/*! Called when a Key state changes to released.
			\param key a constant that represents the released key*/
		virtual void onKeyRelease(Keyboard::Key key){}
	};
}