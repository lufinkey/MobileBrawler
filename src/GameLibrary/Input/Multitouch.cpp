
#include "Multitouch.h"
#include "../Application/EventManager.h"
#include <SDL.h>
#include <climits>
#include <mutex>

namespace GameLibrary
{
	/*Stores info about a particular "touch" instance*/
	typedef struct
	{
		//unique ID of the touch
		unsigned int touchID;
		//ID assigned by SDL
		long long givenID;
		//coordinate of the touch
		Vector2f position;
		//Window that the touch occured inside of
		Window*window;
	} MultitouchData;
	
	static unsigned int Multitouch_currentID = 0;
	void Multitouch_incrementID();
#define MULTITOUCH_MAXID 10000
	
	MultitouchData Multitouch_createTouchData(Window*window, unsigned int touchID, long long givenID, const Vector2f&position);
	unsigned int Multitouch_indexOfData(const ArrayList<MultitouchData>&touchDataList, Window*window, unsigned int touchID);
	unsigned int Multitouch_indexOfData_byGivenID(const ArrayList<MultitouchData>&touchDataList, Window*window, long long givenID);
	unsigned int Multitouch_indexOfData(const ArrayList<MultitouchData>&touchDataList, Window*window);
	
	//stores all the MultitouchEventListener objects for the Mouse class
	static ArrayList<MultitouchEventListener*> Multitouch_eventListeners;
	static std::mutex Multitouch_eventListeners_mutex;
	
	//tells whether the MultitouchEventListener objects are being looped through and having their events called
	static bool Multitouch_callingListeners = false;
	
	//stores listeners that were added or removed from inside a MultitouchEventListener event
	static ArrayList<Pair<MultitouchEventListener*, bool> > Multitouch_changedListeners;
	static std::mutex Multitouch_changedListeners_mutex;
	
	static std::mutex Multitouch_state_mutex;
	//stores the current state of all touches
	static ArrayList<MultitouchData> Multitouch_activeTouches;
	//stores the state of all touches in the most recent frame
	static ArrayList<MultitouchData> Multitouch_currentActiveTouches;
	//stores the state of all touches in the previous frame
	static ArrayList<MultitouchData> Multitouch_prevActiveTouches;

	void Multitouch_incrementID()
	{
		Multitouch_currentID++;
		if(Multitouch_currentID>MULTITOUCH_MAXID)
		{
			Multitouch_currentID = 0;
		}
		
		bool exists = false;
		
		do
		{
			exists = false;
			
			for(unsigned int i=0; i<Multitouch_activeTouches.size(); i++)
			{
				if(Multitouch_activeTouches.get(i).touchID == Multitouch_currentID)
				{
					exists = true;
					i=Multitouch_activeTouches.size();
				}
			}
			
			if(!exists)
			{
				for(unsigned int i=0; i<Multitouch_currentActiveTouches.size(); i++)
				{
					if(Multitouch_currentActiveTouches.get(i).touchID == Multitouch_currentID)
					{
						exists = true;
						i=Multitouch_currentActiveTouches.size();
					}
				}
			}
			
			if(!exists)
			{
				for(unsigned int i=0; i<Multitouch_prevActiveTouches.size(); i++)
				{
					if(Multitouch_prevActiveTouches.get(i).touchID == Multitouch_currentID)
					{
						exists = true;
						i=Multitouch_prevActiveTouches.size();
					}
				}
			}
			
			if(exists)
			{
				Multitouch_currentID++;
				if(Multitouch_currentID>MULTITOUCH_MAXID)
				{
					Multitouch_currentID = 0;
				}
			}
		}
		while(exists);
	}
	
	MultitouchData Multitouch_createTouchData(Window*window, unsigned int touchID, long long givenID, const Vector2f&position)
	{
		MultitouchData touchData;
		touchData.window = window;
		touchData.touchID = touchID;
		touchData.givenID = givenID;
		touchData.position = position;
		return touchData;
	}
	
	unsigned int Multitouch_indexOfData(const ArrayList<MultitouchData>&touchDataList, Window*window, unsigned int touchID)
	{
		for(unsigned int i=0; i<touchDataList.size(); i++)
		{
			const MultitouchData&touchData = touchDataList.get(i);
			if(touchData.window == window && touchData.touchID == touchID)
			{
				return i;
			}
		}
		return ARRAYLIST_NOTFOUND;
	}
	
	unsigned int Multitouch_indexOfData_byGivenID(const ArrayList<MultitouchData>&touchDataList, Window*window, long long givenID)
	{
		for(unsigned int i=0; i<touchDataList.size(); i++)
		{
			const MultitouchData&touchData = touchDataList.get(i);
			if(touchData.window == window && touchData.givenID == givenID)
			{
				return i;
			}
		}
		return ARRAYLIST_NOTFOUND;
	}
	
	unsigned int Multitouch_indexOfData(const ArrayList<MultitouchData>&touchDataList, Window*window)
	{
		for(unsigned int i=0; i<touchDataList.size(); i++)
		{
			const MultitouchData&touchData = touchDataList.get(i);
			if(touchData.window == window)
			{
				return i;
			}
		}
		return ARRAYLIST_NOTFOUND;
	}
	
	//Called when a touch state is changed. Forwards the event to all the MultitouchEventListeners
	void Multitouch_callListeners_press(const MultitouchData&touchData, bool pressed)
	{
		Multitouch_changedListeners_mutex.lock();
		Multitouch_changedListeners.clear();
		Multitouch_changedListeners_mutex.unlock();
		
		Multitouch_callingListeners = true;
		Multitouch_eventListeners_mutex.lock();
		ArrayList<MultitouchEventListener*> listeners = Multitouch_eventListeners;
		Multitouch_eventListeners_mutex.unlock();
		
		for(unsigned int i = 0; i<listeners.size(); i++)
		{
			MultitouchEventListener* listener = listeners.get(i);
			//check to make sure that the listener hasn't been removed during a MultitouchEventListener event
			bool listener_notremoved = true;
			Multitouch_changedListeners_mutex.lock();
			for(unsigned int j=0; j<Multitouch_changedListeners.size(); j++)
			{
				Pair<MultitouchEventListener*,bool>& cmp = Multitouch_changedListeners.get(j);
				if(cmp.first == listener)
				{
					if(!cmp.second)
					{
						listener_notremoved = false;
						j = Multitouch_changedListeners.size();
					}
				}
			}
			Multitouch_changedListeners_mutex.unlock();
			
			//call MultitouchEventListener event
			if(listener_notremoved)
			{
				if(pressed)
				{
					listener->onMultitouchDown(touchData.window, touchData.touchID, touchData.position);
				}
				else
				{
					listener->onMultitouchUp(touchData.window, touchData.touchID, touchData.position);
				}
			}
		}
		Multitouch_callingListeners = false;
		Multitouch_changedListeners_mutex.lock();
		Multitouch_changedListeners.clear();
		Multitouch_changedListeners_mutex.unlock();
	}
	
	//Called when a touch position is moved. Forwards the event to all the MultitouchEventListeners
	void Multitouch_callListeners_move(const MultitouchData&touchData, const Vector2f&touchdif)
	{
		Multitouch_changedListeners_mutex.lock();
		Multitouch_changedListeners.clear();
		Multitouch_changedListeners_mutex.unlock();
		
		Multitouch_callingListeners = true;
		Multitouch_eventListeners_mutex.lock();
		ArrayList<MultitouchEventListener*> listeners = Multitouch_eventListeners;
		Multitouch_eventListeners_mutex.unlock();
		
		for(unsigned int i = 0; i<listeners.size(); i++)
		{
			MultitouchEventListener* listener = listeners.get(i);
			//check to make sure that the listener hasn't been removed during a MultitouchEventListener event
			bool listener_notremoved = true;
			Multitouch_changedListeners_mutex.lock();
			for(unsigned int j=0; j<Multitouch_changedListeners.size(); j++)
			{
				Pair<MultitouchEventListener*,bool>& cmp = Multitouch_changedListeners.get(j);
				if(cmp.first == listener)
				{
					if(!cmp.second)
					{
						listener_notremoved = false;
						j = Multitouch_changedListeners.size();
					}
				}
			}
			Multitouch_changedListeners_mutex.unlock();
			
			//call MultitouchEventListener event
			if(listener_notremoved)
			{
				listener->onMultitouchMove(touchData.window, touchData.touchID, touchData.position, touchdif);
			}
		}
		Multitouch_callingListeners = false;
		Multitouch_changedListeners_mutex.lock();
		Multitouch_changedListeners.clear();
		Multitouch_changedListeners_mutex.unlock();
	}

	ArrayList<unsigned int> Multitouch::getTouchIDs(Window*window)
	{
		ArrayList<unsigned int> touchIDs;
		Multitouch_state_mutex.lock();
		for(unsigned int i=0; i<Multitouch_currentActiveTouches.size(); i++)
		{
			MultitouchData&touchData = Multitouch_currentActiveTouches.get(i);
			if(touchData.window == window)
			{
				touchIDs.add(touchData.touchID);
			}
		}
		Multitouch_state_mutex.unlock();
		return touchIDs;
	}
	
	void Multitouch::handleTouchMove(Window*window, long long givenID, const Vector2f&pos, const Vector2f&dif)
	{
		if(window!=nullptr)
		{
			Multitouch_state_mutex.lock();
			MultitouchData touchData;
			unsigned int index = Multitouch_indexOfData_byGivenID(Multitouch_activeTouches, window, givenID);
			if(index == ARRAYLIST_NOTFOUND)
			{
				unsigned int touchID = Multitouch_currentID;
				touchData = Multitouch_createTouchData(window, touchID, givenID, pos);
				Multitouch_activeTouches.add(touchData);
				Multitouch_incrementID();
			}
			else
			{
				touchData = Multitouch_activeTouches[index];
				Multitouch_activeTouches[index].position = pos;
			}
			Multitouch_state_mutex.unlock();

			Multitouch_callListeners_move(touchData, dif);
		}
	}
	
	void Multitouch::handleTouchDown(Window*window, long long givenID, const Vector2f&pos)
	{
		if(window!=nullptr)
		{
			Multitouch_state_mutex.lock();
			MultitouchData touchData;
			unsigned int index = Multitouch_indexOfData_byGivenID(Multitouch_activeTouches, window, givenID);
			if(index == ARRAYLIST_NOTFOUND)
			{
				unsigned int touchID = Multitouch_currentID;
				touchData = Multitouch_createTouchData(window, touchID, givenID, pos);
				Multitouch_activeTouches.add(touchData);
				Multitouch_incrementID();
			}
			else
			{
				touchData = Multitouch_activeTouches[index];
				Multitouch_activeTouches[index].position = pos;
			}
			Multitouch_state_mutex.unlock();
			
			Multitouch_callListeners_press(touchData,true);
		}
	}
	
	void Multitouch::handleTouchUp(Window*window, long long givenID, const Vector2f&pos)
	{
		if(window!=nullptr)
		{
			Multitouch_state_mutex.lock();
			MultitouchData touchData;
			unsigned int index = Multitouch_indexOfData_byGivenID(Multitouch_activeTouches, window, givenID);
			if(index == ARRAYLIST_NOTFOUND)
			{
				unsigned int touchID = Multitouch_currentID;
				touchData = Multitouch_createTouchData(window, touchID, givenID, pos);
				Multitouch_incrementID();
			}
			else
			{
				touchData = Multitouch_activeTouches[index];
				touchData.position = pos;
				Multitouch_activeTouches.remove(index);
			}
			Multitouch_state_mutex.unlock();
			
			Multitouch_callListeners_press(touchData, false);
		}
	}

	void Multitouch::removeWindow(Window*window)
	{
		Multitouch_state_mutex.lock();
		
		unsigned int index = Multitouch_indexOfData(Multitouch_activeTouches, window);
		while(index != ARRAYLIST_NOTFOUND)
		{
			Multitouch_activeTouches.remove(index);
			index = Multitouch_indexOfData(Multitouch_activeTouches, window);
		}
		
		Multitouch_state_mutex.unlock();
	}

	bool Multitouch::isTouchActive(Window*window, unsigned int touchID)
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
		Multitouch_state_mutex.lock();
		unsigned int index = Multitouch_indexOfData(Multitouch_currentActiveTouches, window, touchID);
		if(index != ARRAYLIST_NOTFOUND)
		{
			pressed = true;
		}
		Multitouch_state_mutex.unlock();
		
		return pressed;
	}
	
	bool Multitouch::wasTouchActive(Window*window, unsigned int touchID)
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
		Multitouch_state_mutex.lock();
		unsigned int index = Multitouch_indexOfData(Multitouch_prevActiveTouches, window, touchID);
		if(index != ARRAYLIST_NOTFOUND)
		{
			pressed = true;
		}
		Multitouch_state_mutex.unlock();
		
		return pressed;
	}

	Vector2f Multitouch::getPosition(Window*window, unsigned int touchID)
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
		
		Multitouch_state_mutex.lock();
		unsigned int index = Multitouch_indexOfData(Multitouch_currentActiveTouches, window, touchID);
		if(index == ARRAYLIST_NOTFOUND)
		{
			Multitouch_state_mutex.unlock();
			return Vector2f(0,0);
		}
		Vector2f vect = Multitouch_currentActiveTouches.get(index).position;
		Multitouch_state_mutex.unlock();
		return vect;
	}

	float Multitouch::getX(Window*window, unsigned int touchID)
	{
		return Multitouch::getPosition(window, touchID).x;
	}
	
	float Multitouch::getY(Window*window, unsigned int touchID)
	{
		return Multitouch::getPosition(window, touchID).y;
	}

	Vector2f Multitouch::getPreviousPosition(Window*window, unsigned int touchID)
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
		
		Multitouch_state_mutex.lock();
		unsigned int index = Multitouch_indexOfData(Multitouch_prevActiveTouches, window, touchID);
		if(index == ARRAYLIST_NOTFOUND)
		{
			Multitouch_state_mutex.unlock();
			return Vector2f(0,0);
		}
		Vector2f vect = Multitouch_prevActiveTouches.get(index).position;
		Multitouch_state_mutex.unlock();
		return vect;
	}

	float Multitouch::getPreviousX(Window*window, unsigned int touchID)
	{
		return Multitouch::getPreviousPosition(window, touchID).x;
	}
	
	float Multitouch::getPreviousY(Window*window, unsigned int touchID)
	{
		return Multitouch::getPreviousPosition(window, touchID).y;
	}

	void Multitouch::addEventListener(MultitouchEventListener*listener)
	{
		if(listener == nullptr)
		{
			throw IllegalArgumentException("Cannot add a null MultitouchEventListener to Multitouch");
		}
		
		if(Multitouch_callingListeners)
		{
			Multitouch_changedListeners_mutex.lock();
			Multitouch_changedListeners.add(Pair<MultitouchEventListener*,bool>(listener,true));
			Multitouch_changedListeners_mutex.unlock();
		}
		Multitouch_eventListeners_mutex.lock();
		Multitouch_eventListeners.add(listener);
		Multitouch_eventListeners_mutex.unlock();
	}
	
	void Multitouch::removeEventListener(MultitouchEventListener*listener)
	{
		if(listener == nullptr)
		{
			throw IllegalArgumentException("Cannot remove a null MultitouchEventListener from Multitouch");
		}
		
		if(Multitouch_callingListeners)
		{
			Multitouch_changedListeners_mutex.lock();
			Multitouch_changedListeners.add(Pair<MultitouchEventListener*,bool>(listener,false));
			Multitouch_changedListeners_mutex.unlock();
		}
		Multitouch_eventListeners_mutex.lock();
		unsigned int index = Multitouch_eventListeners.indexOf(listener);
		while(index != ARRAYLIST_NOTFOUND)
		{
			Multitouch_eventListeners.remove(index);
			index = Multitouch_eventListeners.indexOf(listener);
		}
		Multitouch_eventListeners_mutex.unlock();
	}
	
	void Multitouch::update()
	{
		Multitouch_state_mutex.lock();
		Multitouch_prevActiveTouches = Multitouch_currentActiveTouches;
		Multitouch_currentActiveTouches = Multitouch_activeTouches;
		Multitouch_state_mutex.unlock();
	}
	
	void MultitouchEventListener::onMultitouchDown(Window*window, unsigned int touchID, const Vector2f&touchpos)
	{
		//
	}
	
	void MultitouchEventListener::onMultitouchUp(Window*window, unsigned int touchID, const Vector2f&touchpos)
	{
		//
	}
	
	void MultitouchEventListener::onMultitouchMove(Window*window, unsigned int touchID, const Vector2f&touchpos, const Vector2f&touchdif)
	{
		//
	}
	
	MultitouchEventListener::~MultitouchEventListener()
	{
		//
	}
}
