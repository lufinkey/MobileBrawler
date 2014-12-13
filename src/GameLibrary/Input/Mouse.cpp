
#include "Mouse.h"
#include "../Application/EventManager.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include <mutex>
#include <vector>

namespace GameLibrary
{
	//stores all the MouseEventListener objects for the Mouse class
	static ArrayList<MouseEventListener*> Mouse_eventListeners;
	static std::mutex Mouse_eventListeners_mutex;

	//tells whether the MouseEventListener objects are being looped through and having their events called
	static bool Mouse_callingListeners = false;

	//stores listeners that were added or removed from inside a MouseEventListener event
	static ArrayList<Pair<MouseEventListener*, bool> > Mouse_changedListeners;
	static std::mutex Mouse_changedListeners_mutex;

	static std::mutex Mouse_state_mutex;
	//stores the current state of all buttons
	static std::vector<bool> Mouse_activeButtons(255, false);
	//stores the state of all buttons since the most recent frame
	static std::vector<bool> Mouse_currentActiveButtons(255, false);
	//stores the state of all buttons in the previous frame
	static std::vector<bool> Mouse_prevActiveButtons(255, false);

	//stores the current position of the Mouse relative to Windows
	static ArrayList<Pair<Window*,Vector2f> > Mouse_pos;
	//stores the position of the Mouse since the most recent frame
	static ArrayList<Pair<Window*,Vector2f> > Mouse_pos_current;
	//stores the position of the Mouse in the previous
	static ArrayList<Pair<Window*,Vector2f> > Mouse_pos_previous;

	template<class T, class U>
	static unsigned int ArrayList_indexOfPair(const ArrayList<Pair<T, U> >& list, const T& obj)
	{
		for(unsigned int i=0; i<list.size(); i++)
		{
			if(list.get(i).first == obj)
			{
				return i;
			}
		}
		return ARRAYLIST_NOTFOUND;
	}

	//Called when a button state is changed. Forwards the event to all the MouseEventListeners
	void Mouse_callListeners_press(unsigned int mouseIndex, Mouse::Button button, bool pressed)
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
					listener->onMouseButtonPress(mouseIndex, button);
				}
				else
				{
					listener->onMouseButtonRelease(mouseIndex, button);
				}
			}
		}
		Mouse_callingListeners = false;
		Mouse_changedListeners_mutex.lock();
		Mouse_changedListeners.clear();
		Mouse_changedListeners_mutex.unlock();
	}

	//Called when the mouse position changes. Forwards the event to all the MouseEventListeners
	void Mouse_callListeners_move(unsigned int mouseIndex, Window*window, const Vector2f&pos, const Vector2f&dif)
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
				listener->onMouseMove(mouseIndex, window, pos, dif);
			}
		}
		Mouse_callingListeners = false;
		Mouse_changedListeners_mutex.lock();
		Mouse_changedListeners.clear();
		Mouse_changedListeners_mutex.unlock();
	}
	
	void Mouse::handleMouseMovement(unsigned int mouseIndex, Window*window, const Vector2f&pos, const Vector2f&dif)
	{
		if(window!=nullptr)
		{
			Mouse_state_mutex.lock();
			unsigned int index = ArrayList_indexOfPair<Window*, Vector2f>(Mouse_pos, window);
			if(index == ARRAYLIST_NOTFOUND)
			{
				Mouse_pos.add(Pair<Window*, Vector2f>(window,pos));
			}
			else
			{
				Mouse_pos[index].second = pos;
			}
			Mouse_state_mutex.unlock();
		}
		Mouse_callListeners_move(mouseIndex, window, pos, dif);
	}

	void Mouse::removeWindow(Window*window)
	{
		Mouse_state_mutex.lock();
		unsigned int index = ArrayList_indexOfPair<Window*, Vector2f>(Mouse_pos, window);
		if(index != ARRAYLIST_NOTFOUND)
		{
			Mouse_pos.remove(index);
		}
		index = ArrayList_indexOfPair<Window*, Vector2f>(Mouse_pos_current, window);
		if(index != ARRAYLIST_NOTFOUND)
		{
			Mouse_pos_current.remove(index);
		}
		index = ArrayList_indexOfPair<Window*, Vector2f>(Mouse_pos_previous, window);
		if(index != ARRAYLIST_NOTFOUND)
		{
			Mouse_pos_previous.remove(index);
		}
		Mouse_state_mutex.unlock();
	}

	void Mouse::handleButtonPress(unsigned int mouseIndex, Mouse::Button button)
	{
		if(button!=Mouse::UNKNOWN_BUTTON)
		{
			bool statechanged = false;
			Mouse_state_mutex.lock();
			if(!Mouse_activeButtons[button])
			{
				statechanged = true;
			}
			Mouse_activeButtons[button] = true;
			Mouse_state_mutex.unlock();

			if(statechanged)
			{
				Mouse_callListeners_press(mouseIndex, button, true);
			}
		}
	}

	void Mouse::handleButtonRelease(unsigned int mouseIndex, Mouse::Button button)
	{
		bool statechanged = false;
		Mouse_state_mutex.lock();
		if(Mouse_activeButtons[button])
		{
			statechanged = true;
		}
		Mouse_activeButtons[button] = false;
		Mouse_state_mutex.unlock();

		if(statechanged)
		{
			Mouse_callListeners_press(mouseIndex, button, false);
		}
	}

	bool Mouse::isButtonPressed(Mouse::Button button)
	{
		Mouse_state_mutex.lock();
		bool pressed = Mouse_currentActiveButtons[button];
		Mouse_state_mutex.unlock();

		return pressed;
	}

	bool Mouse::isButtonReleased(Mouse::Button button)
	{
		Mouse_state_mutex.lock();
		bool pressed = isButtonPressed(button);
		Mouse_state_mutex.unlock();

		return !pressed;
	}

	Vector2f Mouse::getPosition(Window*window)
	{
		Mouse_state_mutex.lock();
		unsigned int index = ArrayList_indexOfPair<Window*, Vector2f>(Mouse_pos_current, window);
		if(index == ARRAYLIST_NOTFOUND)
		{
			Mouse_state_mutex.unlock();
			return Vector2f(0,0);
		}
		Vector2f vect = Mouse_pos_current.get(index).second;
		Mouse_state_mutex.unlock();
		return vect;
	}

	float Mouse::getX(Window*window)
	{
		return Mouse::getPosition(window).x;
	}

	float Mouse::getY(Window*window)
	{
		return Mouse::getPosition(window).y;
	}

	void Mouse::setPosition(const Vector2f&pos, Window*window)
	{
		//TODO add support for mouse warping
		//(uncomment this line when SDL 2.0.4 comes out)
		//SDL_WarpMouseInWindow(EventManager::getDataFromWindow(window), (int)pos.x, (int)pos.y);
	}

	void Mouse::setPosition(const Vector2f&pos)
	{
		//TODO add support for mouse warping
		//(uncomment this line when SDL 2.0.4 comes out)
		//SDL_WarpMouseGlobal((int)pos.x, (int)pos.y);
	}

	bool Mouse::wasButtonPressed(Mouse::Button button)
	{
		Mouse_state_mutex.lock();
		bool pressed = Mouse_prevActiveButtons[button];
		Mouse_state_mutex.unlock();

		return pressed;
	}

	bool Mouse::wasButtonReleased(Mouse::Button button)
	{
		Mouse_state_mutex.lock();
		bool pressed = wasButtonPressed(button);
		Mouse_state_mutex.unlock();

		return !pressed;
	}

	Vector2f Mouse::getPreviousPosition(Window*window)
	{
		Mouse_state_mutex.lock();
		unsigned int index = ArrayList_indexOfPair<Window*, Vector2f>(Mouse_pos_previous, window);
		if(index == ARRAYLIST_NOTFOUND)
		{
			Mouse_state_mutex.unlock();
			return Vector2f(0,0);
		}
		Vector2f vect = Mouse_pos_previous.get(index).second;
		Mouse_state_mutex.unlock();
		return vect;
	}

	float Mouse::getPreviousX(Window*window)
	{
		return Mouse::getPreviousPosition(window).x;
	}

	float Mouse::getPreviousY(Window*window)
	{
		return Mouse::getPreviousPosition(window).y;
	}

	bool Mouse::didButtonPress(Mouse::Button button)
	{
		Mouse_state_mutex.lock();
		bool pressed = false;
		if(Mouse_currentActiveButtons[button] && !Mouse_prevActiveButtons[button])
		{
			pressed = true;
		}
		Mouse_state_mutex.unlock();
		return pressed;
	}

	bool Mouse::didButtonRelease(Mouse::Button button)
	{
		Mouse_state_mutex.lock();
		bool released = false;
		if(Mouse_prevActiveButtons[button] && !Mouse_currentActiveButtons[button])
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
		//fill prevActiveButtons with values of currentActiveButtons and currentActiveButtons with values of activeButtons
		Mouse_state_mutex.lock();
		for(unsigned int i=0; i<Mouse_activeButtons.size(); i++)
		{
			Mouse_prevActiveButtons[i] = Mouse_currentActiveButtons[i];
			Mouse_currentActiveButtons[i] = Mouse_activeButtons[i];
		}

		//fill Mouse_pos_previous with values of Mouse_pos_current and Mouse_pos_current with values of Mouse_pos
		Mouse_pos_previous = Mouse_pos_current;
		Mouse_pos_current = Mouse_pos;

		Mouse_state_mutex.unlock();
	}

	void MouseEventListener::onMouseButtonPress(unsigned int mouseIndex, Mouse::Button button)
	{
		//
	}

	void MouseEventListener::onMouseButtonRelease(unsigned int mouseIndex, Mouse::Button button)
	{
		//
	}

	void MouseEventListener::onMouseMove(unsigned int mouseIndex, Window*window, const Vector2f&mousepos, const Vector2f&mousedif)
	{
		//
	}

	MouseEventListener::~MouseEventListener()
	{
		//Mouse::removeEventListener(this);
	}
}