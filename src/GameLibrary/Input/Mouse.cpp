
#include "Mouse.h"
#include "../Application/EventManager.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include <SDL.h>
#include <mutex>
#include <vector>

namespace GameLibrary
{
	/*Stores info about a particular mouse instance*/
	typedef struct
	{
		unsigned int mouseIndex;
		Vector2f position;
		Window*window;
		bool state[4];
	} MouseData;

	MouseData Mouse_createMouseData(Window*window, unsigned int mouseIndex, const Vector2f&position);
	unsigned int Mouse_indexOfData(const ArrayList<MouseData>&mouseDataList, Window*window, unsigned int mouseIndex);
	unsigned int Mouse_indexOfData(const ArrayList<MouseData>&mouseDataList, Window*window);

	//stores all the MouseEventListener objects for the Mouse class
	static ArrayList<MouseEventListener*> Mouse_eventListeners;
	static std::mutex Mouse_eventListeners_mutex;

	//tells whether the MouseEventListener objects are being looped through and having their events called
	static bool Mouse_callingListeners = false;

	//stores listeners that were added or removed from inside a MouseEventListener event
	static ArrayList<Pair<MouseEventListener*, bool> > Mouse_changedListeners;
	static std::mutex Mouse_changedListeners_mutex;

	static std::mutex Mouse_state_mutex;
	//stores the current state of all mouse instances
	static ArrayList<MouseData> Mouse_states;
	//stores the state of all mouse instances since the most recent frame
	static ArrayList<MouseData> Mouse_currentStates;
	//stores the state of all mouse instances in the previous frame
	static ArrayList<MouseData> Mouse_prevStates;

	MouseData Mouse_createMouseData(Window*window, unsigned int mouseIndex, const Vector2f&position)
	{
		MouseData mouseData;
		mouseData.window = window;
		mouseData.mouseIndex = mouseIndex;
		mouseData.position = position;
		for(unsigned int i=0; i<4; i++)
		{
			mouseData.state[i] = false;
		}
		return mouseData;
	}

	unsigned int Mouse_indexOfData(const ArrayList<MouseData>&mouseDataList, Window*window, unsigned int mouseIndex)
	{
		for(unsigned int i=0; i<mouseDataList.size(); i++)
		{
			const MouseData&mouseData = mouseDataList.get(i);
			if(mouseData.window == window && mouseData.mouseIndex == mouseIndex)
			{
				return i;
			}
		}
		return ARRAYLIST_NOTFOUND;
	}

	unsigned int Mouse_indexOfData(const ArrayList<MouseData>&mouseDataList, Window*window)
	{
		for(unsigned int i=0; i<mouseDataList.size(); i++)
		{
			const MouseData&mouseData = mouseDataList.get(i);
			if(mouseData.window == window)
			{
				return i;
			}
		}
		return ARRAYLIST_NOTFOUND;
	}

	//Called when a button state is changed. Forwards the event to all the MouseEventListeners
	void Mouse_callListeners_press(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&pos, bool pressed)
	{
		Mouse_changedListeners_mutex.lock();
		Mouse_changedListeners.clear();
		Mouse_changedListeners_mutex.unlock();

		Mouse_callingListeners = true;
		Mouse_eventListeners_mutex.lock();
		ArrayList<MouseEventListener*> listeners = Mouse_eventListeners;
		Mouse_eventListeners_mutex.unlock();

		for(unsigned int i = 0; i<listeners.size(); i++)
		{
			MouseEventListener* listener = listeners.get(i);
			//check to make sure that the listener hasn't been removed during a MouseEventListener event
			bool listener_notremoved = true;
			Mouse_changedListeners_mutex.lock();
			for(unsigned int j=0; j<Mouse_changedListeners.size(); j++)
			{
				Pair<MouseEventListener*,bool>& cmp = Mouse_changedListeners.get(j);
				if(cmp.first == listener)
				{
					if(!cmp.second)
					{
						listener_notremoved = false;
						j = Mouse_changedListeners.size();
					}
				}
			}
			Mouse_changedListeners_mutex.unlock();

			//call MouseEventListener event
			if(listener_notremoved)
			{
				if(pressed)
				{
					listener->onMouseButtonPress(window, mouseIndex, button, pos);
				}
				else
				{
					listener->onMouseButtonRelease(window, mouseIndex, button, pos);
				}
			}
		}
		Mouse_callingListeners = false;
		Mouse_changedListeners_mutex.lock();
		Mouse_changedListeners.clear();
		Mouse_changedListeners_mutex.unlock();
	}

	//Called when the mouse position changes. Forwards the event to all the MouseEventListeners
	void Mouse_callListeners_move(Window*window, unsigned int mouseIndex, const Vector2f&pos, const Vector2f&dif)
	{
		Mouse_changedListeners_mutex.lock();
		Mouse_changedListeners.clear();
		Mouse_changedListeners_mutex.unlock();

		Mouse_callingListeners = true;
		Mouse_eventListeners_mutex.lock();
		ArrayList<MouseEventListener*> listeners = Mouse_eventListeners;
		Mouse_eventListeners_mutex.unlock();

		for(unsigned int i = 0; i<listeners.size(); i++)
		{
			MouseEventListener* listener = listeners.get(i);
			//check to make sure that the listener hasn't been removed during a MouseEventListener event
			bool listener_notremoved = true;
			Mouse_changedListeners_mutex.lock();
			for(unsigned int j=0; j<Mouse_changedListeners.size(); j++)
			{
				Pair<MouseEventListener*,bool>& cmp = Mouse_changedListeners.get(j);
				if(cmp.first == listener)
				{
					if(!cmp.second)
					{
						listener_notremoved = false;
						j = Mouse_changedListeners.size();
					}
				}
			}
			Mouse_changedListeners_mutex.unlock();

			//call MouseEventListener event
			if(listener_notremoved)
			{
				listener->onMouseMove(window, mouseIndex, pos, dif);
			}
		}
		Mouse_callingListeners = false;
		Mouse_changedListeners_mutex.lock();
		Mouse_changedListeners.clear();
		Mouse_changedListeners_mutex.unlock();
	}
	
	void Mouse::handleMouseMovement(Window*window, unsigned int mouseIndex, const Vector2f&pos, const Vector2f&dif)
	{
		if(window!=nullptr)
		{
			Mouse_state_mutex.lock();
			unsigned int index = Mouse_indexOfData(Mouse_states, window, mouseIndex);
			if(index == ARRAYLIST_NOTFOUND)
			{
				MouseData mouseData = Mouse_createMouseData(window, mouseIndex, pos);
				Mouse_states.add(mouseData);
			}
			else
			{
				Mouse_states[index].position = pos;
			}
			Mouse_state_mutex.unlock();
		}
		Mouse_callListeners_move(window, mouseIndex, pos, dif);
	}
	
	void Mouse::handleButtonPress(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&pos)
	{
		if(button!=Mouse::UNKNOWN_BUTTON)
		{
			bool statechanged = false;
			Mouse_state_mutex.lock();
			unsigned int index = Mouse_indexOfData(Mouse_states, window, mouseIndex);
			if(index == ARRAYLIST_NOTFOUND)
			{
				MouseData mouseData = Mouse_createMouseData(window, mouseIndex, pos);
				mouseData.state[button] = true;
				Mouse_states.add(mouseData);
			}
			else
			{
				if(!Mouse_states[index].state[button])
				{
					statechanged = true;
				}
				Mouse_states[index].state[button] = true;
			}
			Mouse_state_mutex.unlock();
			
			if(statechanged)
			{
				Mouse_callListeners_press(window, mouseIndex, button, pos, true);
			}
		}
	}
	
	void Mouse::handleButtonRelease(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&pos)
	{
		if(button!=Mouse::UNKNOWN_BUTTON)
		{
			bool statechanged = false;
			Mouse_state_mutex.lock();
			unsigned int index = Mouse_indexOfData(Mouse_states, window, mouseIndex);
			if(index == ARRAYLIST_NOTFOUND)
			{
				MouseData mouseData = Mouse_createMouseData(window, mouseIndex, pos);
				mouseData.state[button] = false;
				Mouse_states.add(mouseData);
			}
			else
			{
				if(Mouse_states[index].state[button])
				{
					statechanged = true;
				}
				Mouse_states[index].state[button] = false;
			}
			Mouse_state_mutex.unlock();
			
			if(statechanged)
			{
				Mouse_callListeners_press(window, mouseIndex, button, pos, false);
			}
		}
	}
	
	void Mouse::removeWindow(Window*window)
	{
		Mouse_state_mutex.lock();
		
		unsigned int index = Mouse_indexOfData(Mouse_states, window);
		while(index != ARRAYLIST_NOTFOUND)
		{
			Mouse_states.remove(index);
			index = Mouse_indexOfData(Mouse_states, window);
		}
		
		Mouse_state_mutex.unlock();
	}
	
	bool Mouse::isButtonPressed(Window*window, unsigned int mouseIndex, Mouse::Button button)
	{
		if(window == nullptr)
		{
			SDL_Window*sdlwin = SDL_GetMouseFocus();
			if(sdlwin != nullptr)
			{
				window = EventManager::getWindowFromID(SDL_GetWindowID(sdlwin));
				if(window == nullptr)
				{
					return false;
				}
			}
		}
		
		bool pressed = false;
		Mouse_state_mutex.lock();
		unsigned int index = Mouse_indexOfData(Mouse_currentStates, window, mouseIndex);
		if(index != ARRAYLIST_NOTFOUND)
		{
			if(Mouse_currentStates[index].state[button])
			{
				pressed = true;
			}
		}
		Mouse_state_mutex.unlock();
		
		return pressed;
	}
	
	Vector2f Mouse::getPosition(Window*window, unsigned int mouseIndex)
	{
		if(window == nullptr)
		{
			SDL_Window*sdlwin = SDL_GetMouseFocus();
			if(sdlwin != nullptr)
			{
				window = EventManager::getWindowFromID(SDL_GetWindowID(sdlwin));
				if(window == nullptr)
				{
					return Vector2f(0,0);
				}
			}
		}
		
		Mouse_state_mutex.lock();
		unsigned int index = Mouse_indexOfData(Mouse_currentStates, window, mouseIndex);
		if(index == ARRAYLIST_NOTFOUND)
		{
			Mouse_state_mutex.unlock();
			return Vector2f(0,0);
		}
		Vector2f vect = Mouse_currentStates.get(index).position;
		Mouse_state_mutex.unlock();
		return vect;
	}
	
	float Mouse::getX(Window*window, unsigned int mouseIndex)
	{
		return Mouse::getPosition(window, mouseIndex).x;
	}
	
	float Mouse::getY(Window*window, unsigned int mouseIndex)
	{
		return Mouse::getPosition(window, mouseIndex).y;
	}
	
	void Mouse::setPosition(Window*window, unsigned int mouseIndex, const Vector2f&pos)
	{
		//TODO add support for multiple mouse indexes
		if(mouseIndex==0)
		{
			SDL_WarpMouseInWindow((SDL_Window*)EventManager::getDataFromWindow(window), (int)pos.x, (int)pos.y);
		}
	}
	
	void Mouse::setPosition(unsigned int mouseIndex, const Vector2f&pos)
	{
		//TODO add support for mouse warping globally
		//(uncomment this line when SDL 2.0.4 comes out)
		//SDL_WarpMouseGlobal((int)pos.x, (int)pos.y);
	}
	
	bool Mouse::wasButtonPressed(Window*window, unsigned int mouseIndex, Mouse::Button button)
	{
		if(window == nullptr)
		{
			SDL_Window*sdlwin = SDL_GetMouseFocus();
			if(sdlwin != nullptr)
			{
				window = EventManager::getWindowFromID(SDL_GetWindowID(sdlwin));
				if(window == nullptr)
				{
					return false;
				}
			}
		}
		
		bool pressed = false;
		Mouse_state_mutex.lock();
		unsigned int index = Mouse_indexOfData(Mouse_prevStates, window, mouseIndex);
		if(index != ARRAYLIST_NOTFOUND)
		{
			if(Mouse_prevStates[index].state[button])
			{
				pressed = true;
			}
		}
		Mouse_state_mutex.unlock();
		
		return pressed;
	}

	Vector2f Mouse::getPreviousPosition(Window*window, unsigned int mouseIndex)
	{
		if(window == nullptr)
		{
			SDL_Window*sdlwin = SDL_GetMouseFocus();
			if(sdlwin != nullptr)
			{
				window = EventManager::getWindowFromID(SDL_GetWindowID(sdlwin));
				if(window == nullptr)
				{
					return Vector2f(0,0);
				}
			}
		}
		
		Mouse_state_mutex.lock();
		unsigned int index = Mouse_indexOfData(Mouse_prevStates, window, mouseIndex);
		if(index == ARRAYLIST_NOTFOUND)
		{
			Mouse_state_mutex.unlock();
			return Vector2f(0,0);
		}
		Vector2f vect = Mouse_prevStates.get(index).position;
		Mouse_state_mutex.unlock();
		return vect;
	}

	float Mouse::getPreviousX(Window*window, unsigned int mouseIndex)
	{
		return Mouse::getPreviousPosition(window, mouseIndex).x;
	}

	float Mouse::getPreviousY(Window*window, unsigned int mouseIndex)
	{
		return Mouse::getPreviousPosition(window, mouseIndex).y;
	}
	
	bool Mouse::didButtonPress(Window*window, unsigned int mouseIndex, Mouse::Button button)
	{
		if(window == nullptr)
		{
			SDL_Window*sdlwin = SDL_GetMouseFocus();
			if(sdlwin != nullptr)
			{
				window = EventManager::getWindowFromID(SDL_GetWindowID(sdlwin));
			}
		}
		
		Mouse_state_mutex.lock();
		bool pressed = false;
		if(Mouse::isButtonPressed(window, mouseIndex, button) && !Mouse::wasButtonPressed(window, mouseIndex, button))
		{
			pressed = true;
		}
		Mouse_state_mutex.unlock();
		return pressed;
	}
	
	bool Mouse::didButtonRelease(Window*window, unsigned int mouseIndex, Mouse::Button button)
	{
		if(window == nullptr)
		{
			SDL_Window*sdlwin = SDL_GetMouseFocus();
			if(sdlwin != nullptr)
			{
				window = EventManager::getWindowFromID(SDL_GetWindowID(sdlwin));
			}
		}
		
		Mouse_state_mutex.lock();
		bool released = false;
		if(Mouse::wasButtonPressed(window, mouseIndex, button) && !Mouse::isButtonPressed(window, mouseIndex, button))
		{
			released = true;
		}
		Mouse_state_mutex.unlock();
		return released;
	}
	
	void Mouse::addEventListener(MouseEventListener*listener)
	{
		if(listener == nullptr)
		{
			throw IllegalArgumentException("Cannot add a null MouseEventListener to Mouse");
		}
		
		if(Mouse_callingListeners)
		{
			Mouse_changedListeners_mutex.lock();
			Mouse_changedListeners.add(Pair<MouseEventListener*,bool>(listener,true));
			Mouse_changedListeners_mutex.unlock();
		}
		Mouse_eventListeners_mutex.lock();
		Mouse_eventListeners.add(listener);
		Mouse_eventListeners_mutex.unlock();
	}
	
	void Mouse::removeEventListener(MouseEventListener*listener)
	{
		if(listener == nullptr)
		{
			throw IllegalArgumentException("Cannot remove a null MouseEventListener from Mouse");
		}
		
		if(Mouse_callingListeners)
		{
			Mouse_changedListeners_mutex.lock();
			Mouse_changedListeners.add(Pair<MouseEventListener*,bool>(listener,false));
			Mouse_changedListeners_mutex.unlock();
		}
		Mouse_eventListeners_mutex.lock();
		unsigned int index = Mouse_eventListeners.indexOf(listener);
		while(index != ARRAYLIST_NOTFOUND)
		{
			Mouse_eventListeners.remove(index);
			index = Mouse_eventListeners.indexOf(listener);
		}
		Mouse_eventListeners_mutex.unlock();
	}
	
	void Mouse::update()
	{
		Mouse_state_mutex.lock();
		Mouse_prevStates = Mouse_currentStates;
		Mouse_currentStates = Mouse_states;
		Mouse_state_mutex.unlock();
	}

	void MouseEventListener::onMouseButtonPress(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&mousepos)
	{
		//
	}
	
	void MouseEventListener::onMouseButtonRelease(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&mousepos)
	{
		//
	}
	
	void MouseEventListener::onMouseMove(Window*window, unsigned int mouseIndex, const Vector2f&mousepos, const Vector2f&mousedif)
	{
		//
	}
	
	MouseEventListener::~MouseEventListener()
	{
		//Mouse::removeEventListener(this);
	}
}