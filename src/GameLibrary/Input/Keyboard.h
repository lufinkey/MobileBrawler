
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
			/*! Unknown or unsupported key*/
			UNKNOWN_KEY,
			/*! A key*/
			A,
			/*! B key*/
			B,
			/*! C key*/
			C,
			/*! D key*/
			D,
			/*! E key*/
			E,
			/*! F key*/
			F,
			/*! G key*/
			G,
			/*! H key*/
			H,
			/*! I key*/
			I,
			/*! J key*/
			J,
			/*! K key*/
			K,
			/*! L key*/
			L,
			/*! M key*/
			M,
			/*! N key*/
			N,
			/*! O key*/
			O,
			/*! P key*/
			P,
			/*! Q key*/
			Q,
			/*! R key*/
			R,
			/*! S key*/
			S,
			/*! T key*/
			T,
			/*! U key*/
			U,
			/*! V key*/
			V,
			/*! W key*/
			W,
			/*! X key*/
			X,
			/*! Y key*/
			Y,
			/*! Z key*/
			Z,
			/*! 0 key*/
			NUM_0,
			/*! 1 key*/
			NUM_1,
			/*! 2 key*/
			NUM_2,
			/*! 3 key*/
			NUM_3,
			/*! 4 key*/
			NUM_4,
			/*! 5 key*/
			NUM_5,
			/*! 6 key*/
			NUM_6,
			/*! 7 key*/
			NUM_7,
			/*! 8 key*/
			NUM_8,
			/*! 9 key*/
			NUM_9,
			/*! Esc key*/
			ESCAPE,
			/*! Left Ctrl key*/
			CTRL_LEFT,
			/*! Left Shift key*/
			SHIFT_LEFT,
			/*! Left Alt key*/
			ALT_LEFT,
			/*! Left Windows or System key*/
			WINDOWS_LEFT,
			/*! Right Ctrl key*/
			CTRL_RIGHT,
			/*! Right Shift key*/
			SHIFT_RIGHT,
			/*! Right Alt key*/
			ALT_RIGHT,
			/*! Right Windows or System key*/
			WINDOWS_RIGHT,
			/*! Context Menu key*/
			CONTEXT_MENU,
			/*! [ key*/
			OPENBRACKET,
			/*! ] key*/
			CLOSEBRACKET,
			/*! ; key*/
			SEMICOLON,
			/*! , key*/
			COMMA,
			/*! . key*/
			PERIOD,
			/*! ' key*/
			QUOTE,
			/*! / key*/
			FORWARDSLASH,
			/*! \\ key*/
			BACKSLASH,
			/*! = key*/
			EQUALS,
			/*! - key*/
			DASH,
			/*! Spacebar key*/
			SPACE,
			/*! Enter or Return key*/
			ENTER,
			/*! Backspace key*/
			BACKSPACE,
			/*! Tab key*/
			TAB,
			/*! PageUp key*/
			PAGEUP,
			/*! PageDown key*/
			PAGEDOWN,
			/*! End key*/
			END,
			/*! Home key*/
			HOME,
			/*! Insert key*/
			INSERT,
			/*! Delete key*/
			DELETE,
			/*! Pause key*/
			PAUSE,
			/*! dedicated + key*/
			ADD,
			/*! dedicated - key*/
			SUBTRACT,
			/*! dedicated * key*/
			MULTIPLY,
			/*! dedicated / key*/
			DIVIDE,
			/*! Left Arrow key*/
			LEFTARROW,
			/*! Right Arrow key*/
			RIGHTARROW,
			/*! Up Arrow key*/
			UPARROW,
			/*! Down Arrow key*/
			DOWNARROW,
			/*! 0 key on the number pad*/
			NUMPAD_0,
			/*! 1 key on the number pad*/
			NUMPAD_1,
			/*! 2 key on the number pad*/
			NUMPAD_2,
			/*! 3 key on the number pad*/
			NUMPAD_3,
			/*! 4 key on the number pad*/
			NUMPAD_4,
			/*! 5 key on the number pad*/
			NUMPAD_5,
			/*! 6 key on the number pad*/
			NUMPAD_6,
			/*! 7 key on the number pad*/
			NUMPAD_7,
			/*! 8 key on the number pad*/
			NUMPAD_8,
			/*! 9 key on the number pad*/
			NUMPAD_9,
			/*! F1 key*/
			F1,
			/*! F2 key*/
			F2,
			/*! F3 key*/
			F3,
			/*! F4 key*/
			F4,
			/*! F5 key*/
			F5,
			/*! F6 key*/
			F6,
			/*! F7 key*/
			F7,
			/*! F8 key*/
			F8,
			/*! F9 key*/
			F9,
			/*! F10 key*/
			F10,
			/*! F11 key*/
			F11,
			/*! F12 key*/
			F12,
			/*! F13 key*/
			F13,
			/*! F14 key*/
			F14,
			/*! F15 key*/
			F15
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