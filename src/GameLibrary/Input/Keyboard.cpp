
#include "Keyboard.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include <SDL.h>
#include <mutex>
#include <vector>

namespace GameLibrary
{
	//stores all the KeyboardEventListener objects for the Keyboard class
	static ArrayList<KeyboardEventListener*> Keyboard_eventListeners;
	static std::mutex Keyboard_eventListeners_mutex;

	//tells whether the KeyboardEventListener objects are being looped through and having their events called
	static bool Keyboard_callingListeners = false;

	//stores listeners that were added or removed from inside a KeyboardEventListener event
	static ArrayList<Pair<KeyboardEventListener*, bool> > Keyboard_changedListeners;
	static std::mutex Keyboard_changedListeners_mutex;
	
	static std::mutex Keyboard_key_mutex;
	//stores the current state of all keys
	static std::vector<bool> Keyboard_activeKeys = std::vector<bool>(255, false);
	//stores the state of all keys since the most recent frame
	static std::vector<bool> Keyboard_currentActiveKeys = std::vector<bool>(255, false);
	//stores the state of all keys in the previous frame
	static std::vector<bool> Keyboard_prevActiveKeys = std::vector<bool>(255, false);
	
	//tells whether text input has been started
	static bool Keyboard_textInputStarted = false;
	
	
	//Called when a key state is changed. Forwards the event to all the KeyboardEventListeners
	void Keyboard_callListeners(Keyboard::Key key, bool pressed)
	{
		Keyboard_changedListeners_mutex.lock();
		Keyboard_changedListeners.clear();
		Keyboard_changedListeners_mutex.unlock();
		
		Keyboard_callingListeners = true;
		Keyboard_eventListeners_mutex.lock();
		ArrayList<KeyboardEventListener*> listeners = Keyboard_eventListeners;
		Keyboard_eventListeners_mutex.unlock();
		
		for(size_t i = 0; i<listeners.size(); i++)
		{
			KeyboardEventListener* listener = listeners.get(i);
			//check to make sure that the listener hasn't been removed during a KeyboardEventListener event
			bool listener_notremoved = true;
			Keyboard_changedListeners_mutex.lock();
			for(size_t j=0; j<Keyboard_changedListeners.size(); j++)
			{
				Pair<KeyboardEventListener*,bool>& cmp = Keyboard_changedListeners.get(j);
				if(cmp.first == listener)
				{
					if(!cmp.second)
					{
						listener_notremoved = false;
						j = Keyboard_changedListeners.size();
					}
				}
			}
			Keyboard_changedListeners_mutex.unlock();
			
			//call KeyboardEventListener event
			if(listener_notremoved)
			{
				if(pressed)
				{
					listener->onKeyPress(key);
				}
				else
				{
					listener->onKeyRelease(key);
				}
			}
		}
		Keyboard_callingListeners = false;
		Keyboard_changedListeners_mutex.lock();
		Keyboard_changedListeners.clear();
		Keyboard_changedListeners_mutex.unlock();
	}
	
	void Keyboard_callListeners_textInput(const String& text)
	{
		Keyboard_changedListeners_mutex.lock();
		Keyboard_changedListeners.clear();
		Keyboard_changedListeners_mutex.unlock();
		
		Keyboard_callingListeners = true;
		Keyboard_eventListeners_mutex.lock();
		ArrayList<KeyboardEventListener*> listeners = Keyboard_eventListeners;
		Keyboard_eventListeners_mutex.unlock();
		
		for(size_t i = 0; i<listeners.size(); i++)
		{
			KeyboardEventListener* listener = listeners.get(i);
			//check to make sure that the listener hasn't been removed during a KeyboardEventListener event
			bool listener_notremoved = true;
			Keyboard_changedListeners_mutex.lock();
			for(size_t j=0; j<Keyboard_changedListeners.size(); j++)
			{
				Pair<KeyboardEventListener*,bool>& cmp = Keyboard_changedListeners.get(j);
				if(cmp.first == listener)
				{
					if(!cmp.second)
					{
						listener_notremoved = false;
						j = Keyboard_changedListeners.size();
					}
				}
			}
			Keyboard_changedListeners_mutex.unlock();
			
			//call KeyboardEventListener event
			if(listener_notremoved)
			{
				listener->onTextInput(text);
			}
		}
		Keyboard_callingListeners = false;
		Keyboard_changedListeners_mutex.lock();
		Keyboard_changedListeners.clear();
		Keyboard_changedListeners_mutex.unlock();
	}
	
	void Keyboard::handleKeyPress(Key key)
	{
		if(key!=Keyboard::UNKNOWN_KEY)
		{
			bool statechanged = false;
			Keyboard_key_mutex.lock();
			if(!Keyboard_activeKeys[key])
			{
				statechanged = true;
			}
			Keyboard_activeKeys[key] = true;
			Keyboard_key_mutex.unlock();

			if(statechanged)
			{
				Keyboard_callListeners(key, true);
			}
		}
	}

	void Keyboard::handleKeyRelease(Key key)
	{
		if(key!=Keyboard::UNKNOWN_KEY)
		{
			bool statechanged = false;
			Keyboard_key_mutex.lock();
			if(Keyboard_activeKeys[key])
			{
				statechanged = true;
			}
			Keyboard_activeKeys[key] = false;
			Keyboard_key_mutex.unlock();

			if(statechanged)
			{
				Keyboard_callListeners(key, false);
			}
		}
	}
	
	void Keyboard::handleTextInput(const String& text)
	{
		Keyboard_callListeners_textInput(text);
	}

	bool Keyboard::isKeyPressed(Key key)
	{
		Keyboard_key_mutex.lock();
		bool pressed = Keyboard_currentActiveKeys[key];
		Keyboard_key_mutex.unlock();

		return pressed;
	}

	bool Keyboard::isKeyReleased(Key key)
	{
		Keyboard_key_mutex.lock();
		bool pressed = isKeyPressed(key);
		Keyboard_key_mutex.unlock();

		return !pressed;
	}

	bool Keyboard::wasKeyPressed(Key key)
	{
		Keyboard_key_mutex.lock();
		bool pressed = Keyboard_prevActiveKeys[key];
		Keyboard_key_mutex.unlock();

		return pressed;
	}

	bool Keyboard::wasKeyReleased(Key key)
	{
		Keyboard_key_mutex.lock();
		bool pressed = wasKeyPressed(key);
		Keyboard_key_mutex.unlock();

		return !pressed;
	}

	bool Keyboard::didKeyPress(Key key)
	{
		Keyboard_key_mutex.lock();
		bool pressed = false;
		if(Keyboard_currentActiveKeys[key] && !Keyboard_prevActiveKeys[key])
		{
			pressed = true;
		}
		Keyboard_key_mutex.unlock();
		return pressed;
	}

	bool Keyboard::didKeyRelease(Key key)
	{
		Keyboard_key_mutex.lock();
		bool released = false;
		if(Keyboard_prevActiveKeys[key] && !Keyboard_currentActiveKeys[key])
		{
			released = true;
		}
		Keyboard_key_mutex.unlock();
		return released;
	}

	void Keyboard::addEventListener(KeyboardEventListener*eventListener)
	{
		if(eventListener == nullptr)
		{
			throw IllegalArgumentException("eventListener", "null");
		}
		
		if(Keyboard_callingListeners)
		{
			Keyboard_changedListeners_mutex.lock();
			Keyboard_changedListeners.add(Pair<KeyboardEventListener*,bool>(eventListener,true));
			Keyboard_changedListeners_mutex.unlock();
		}
		Keyboard_eventListeners_mutex.lock();
		Keyboard_eventListeners.add(eventListener);
		Keyboard_eventListeners_mutex.unlock();
	}

	void Keyboard::removeEventListener(KeyboardEventListener*eventListener)
	{
		if(eventListener == nullptr)
		{
			throw IllegalArgumentException("eventListener", "null");
		}
		
		if(Keyboard_callingListeners)
		{
			Keyboard_changedListeners_mutex.lock();
			Keyboard_changedListeners.add(Pair<KeyboardEventListener*,bool>(eventListener,false));
			Keyboard_changedListeners_mutex.unlock();
		}
		Keyboard_eventListeners_mutex.lock();
		size_t index = Keyboard_eventListeners.indexOf(eventListener);
		while(index != ARRAYLIST_NOTFOUND)
		{
			Keyboard_eventListeners.remove(index);
			index = Keyboard_eventListeners.indexOf(eventListener);
		}
		Keyboard_eventListeners_mutex.unlock();
	}
	
	void Keyboard::update()
	{
		//fill prevActiveKeys with values of currentActiveKeys and currentActiveKeys with values of activeKeys
		Keyboard_key_mutex.lock();
		for(size_t i=0; i<Keyboard_activeKeys.size(); i++)
		{
			Keyboard_prevActiveKeys[i] = Keyboard_currentActiveKeys[i];
			Keyboard_currentActiveKeys[i] = Keyboard_activeKeys[i];
		}
		Keyboard_key_mutex.unlock();
	}

	String Keyboard::getKeyText(Keyboard::Key key)
	{
		switch (key)
		{
			case UNKNOWN_KEY: return "";
			case A: return "a";
			case B: return "b";
			case C: return "c";
			case D: return "d";
			case E: return "e";
			case F: return "f";
			case G: return "g";
			case H: return "h";
			case I: return "i";
			case J: return "j";
			case K: return "k";
			case L: return "l";
			case M: return "m";
			case N: return "n";
			case O: return "o";
			case P: return "p";
			case Q: return "q";
			case R: return "r";
			case S: return "s";
			case T: return "t";
			case U: return "u";
			case V: return "v";
			case W: return "w";
			case X: return "x";
			case Y: return "y";
			case Z: return "z";
			case NUM_0: return "0";
			case NUM_1: return "1";
			case NUM_2: return "2";
			case NUM_3: return "3";
			case NUM_4: return "4";
			case NUM_5: return "5";
			case NUM_6: return "6";
			case NUM_7: return "7";
			case NUM_8: return "8";
			case NUM_9: return "9";
			case ESCAPE: return "esc";
			case CTRL_LEFT: return "ctrl";
			case SHIFT_LEFT: return "shift";
			case ALT_LEFT: return "alt";
			case WINDOWS_LEFT: return "windows";
			case CTRL_RIGHT: return "ctrl";
			case SHIFT_RIGHT: return "shift";
			case ALT_RIGHT: return "alt";
			case WINDOWS_RIGHT: return "windows";
			case CONTEXT_MENU: return "context";
			case OPENBRACKET: return "[";
			case CLOSEBRACKET: return "]";
			case SEMICOLON: return ";";
			case COMMA: return ",";
			case PERIOD: return ".";
			case QUOTE: return "\"";
			case FORWARDSLASH: return "/";
			case BACKSLASH: return "\\";
			case EQUALS: return "=";
			case DASH: return "-";
			case SPACE: return "space";
			case ENTER: return "enter";
			case BACKSPACE: return "backspace";
			case TAB: return "tab";
			case PAGEUP: return "pg up";
			case PAGEDOWN: return "pg dn";
			case END: return "end";
			case HOME: return "home";
			case INSERT: return "insert";
			case DELETE: return "delete";
			case PAUSE: return "pause";
			case ADD: return "+";
			case SUBTRACT: return "-";
			case MULTIPLY: return "*";
			case DIVIDE: return "/";
			case LEFTARROW: return "left arrow";
			case RIGHTARROW: return "right arrow";
			case UPARROW: return "up arrow";
			case DOWNARROW: return "down arrow";
			case NUMPAD_0: return "[0]";
			case NUMPAD_1: return "[1]";
			case NUMPAD_2: return "[2]";
			case NUMPAD_3: return "[3]";
			case NUMPAD_4: return "[4]";
			case NUMPAD_5: return "[5]";
			case NUMPAD_6: return "[6]";
			case NUMPAD_7: return "[7]";
			case NUMPAD_8: return "[8]";
			case NUMPAD_9: return "[9]";
			case F1: return "f1";
			case F2: return "f2";
			case F3: return "f3";
			case F4: return "f4";
			case F5: return "f5";
			case F6: return "f6";
			case F7: return "f7";
			case F8: return "f8";
			case F9: return "f9";
			case F10: return "f10";
			case F11: return "f11";
			case F12: return "f12";
			case F13: return "f13";
			case F14: return "f14";
			case F15: return "f15";
		}
		return "";
	}
	
	void Keyboard::startTextInput()
	{
		if(Keyboard_textInputStarted)
		{
			throw IllegalStateException("text input has already been started");
		}
		Keyboard_textInputStarted = true;
		SDL_StartTextInput();
	}
	
	void Keyboard::endTextInput()
	{
		if(!Keyboard_textInputStarted)
		{
			throw IllegalStateException("text input has not been started");
		}
		SDL_StopTextInput();
		Keyboard_textInputStarted = false;
	}
}
