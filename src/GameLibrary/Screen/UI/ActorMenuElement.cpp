
#include "ActorMenuElement.h"

namespace GameLibrary
{
	ActorMenuElement::ActorMenuElement(const RectangleF&frame) : ScreenElement(frame)
	{
		selectedIndex = ACTORMENU_NOSELECTION;
		keyboardEnabled = false;
		pressingActor = false;
	}
	
	ActorMenuElement::~ActorMenuElement()
	{
		//
	}
	
	void ActorMenuElement::update(ApplicationData appData)
	{
		ScreenElement::update(appData);
		ArrayList<Pair<Keyboard::Key, KeyDirection> > keyList = keys;
		for(unsigned int i=0; i<keyList.size(); i++)
		{
			Pair<Keyboard::Key, KeyDirection>& keypair = keyList.get(i);
			if(Keyboard::isKeyPressed(keypair.first) && !Keyboard::wasKeyPressed(keypair.first))
			{
				//on key press
				switch(keypair.second)
				{
					case KEYDIR_UP:
					moveHoverUp();
					break;
					
					case KEYDIR_DOWN:
					moveHoverDown();
					break;
					
					case KEYDIR_LEFT:
					moveHoverLeft();
					break;
					
					case KEYDIR_RIGHT:
					moveHoverRight();
					break;
					
					case KEYDIR_SELECT:
					if(keyboardEnabled && selectedIndex!=ACTORMENU_NOSELECTION)
					{
						pressingActor = true;
						onActorPress(selectedIndex);
					}
					break;
				}
			}
			else if(Keyboard::wasKeyPressed(keypair.first) && !Keyboard::isKeyPressed(keypair.first))
			{
				if(keypair.second==KEYDIR_SELECT)
				{
					if(keyboardEnabled && pressingActor)
					{
						onActorRelease(selectedIndex);
						selectCurrentIndex();
					}
				}
			}
		}
		
		if(keyboardEnabled)
		{
			unsigned int lastSelectedIndex = selectedIndex;
			if(lastSelectedIndex != ACTORMENU_NOSELECTION)
			{
				Actor* actor = actors.get(lastSelectedIndex);
				actor->update(appData);
				if(actor->isMouseOver() && !actor->wasMouseOver())
				{
					setKeyboardEnabled(false);
				}
				else if(actor->isMousePressed() && !actor->wasMousePressed())
				{
					setKeyboardEnabled(false);
				}
			}
			for(unsigned int i=0; i<actors.size(); i++)
			{
				if(i != lastSelectedIndex)
				{
					Actor* actor = actors.get(i);
					actor->update(appData);
					if(actor->isMouseOver() && !actor->wasMouseOver())
					{
						setKeyboardEnabled(false);
					}
					else if(actor->isMousePressed() && !actor->wasMousePressed())
					{
						setKeyboardEnabled(false);
					}
				}
			}
		}
		else
		{
			unsigned int lastSelectedIndex = selectedIndex;
			//test/update currently hovered actor
			if(lastSelectedIndex != ACTORMENU_NOSELECTION)
			{
				Actor* actor = actors.get(lastSelectedIndex);
				actor->update(appData);
				if(actor->isMouseOver())
				{
					if(pressingActor)
					{
						if(!actor->isMousePressed())
						{
							pressingActor = false;
							//actor->clearMouseState();
							onActorRelease(lastSelectedIndex);
							//onActorHoverFinish(lastSelectedIndex);
							onActorSelect(lastSelectedIndex);
						}
					}
					else
					{
						if(actor->isMousePressed())
						{
							pressingActor = true;
							onActorPress(lastSelectedIndex);
						}
					}
				}
				else
				{
					selectedIndex = ACTORMENU_NOSELECTION;
					if(pressingActor)
					{
						pressingActor = false;
						if(actor->didMouseRelease())
						{
							//TODO have mouse state clearing be called from menuscreen subclass
							//actor->clearMouseState();
							onActorRelease(lastSelectedIndex);
							onActorHoverFinish(lastSelectedIndex);
							onActorSelect(lastSelectedIndex);
						}
						else
						{
							onActorPressCancel(lastSelectedIndex);
							onActorHoverFinish(lastSelectedIndex);
						}
					}
					else
					{
						onActorHoverFinish(lastSelectedIndex);
					}
				}
			}

			ArrayList<Actor*> menuActors = actors;

			//test/update other actors
			for(unsigned int i=0; i<menuActors.size(); i++)
			{
				if(i != lastSelectedIndex)
				{
					Actor* actor = menuActors.get(i);

					//make sure actor wasn't added or removed from the screen during an event
					unsigned int actorIndex = ARRAYLIST_NOTFOUND;
					if(i<actors.size() && actors.get(i)==actor)
					{
						actorIndex = i;
					}
					else
					{
						actorIndex = actors.indexOf(actor);
					}
					
					//if the actor is still in the screen
					if(actorIndex!=ARRAYLIST_NOTFOUND)
					{
						actor->update(appData);
						
						//checking selection by mouse
						if(!keyboardEnabled)
						{
							if(selectedIndex == ACTORMENU_NOSELECTION)
							{
								if(actor->isMouseOver())
								{
									//actor->wasMouseOver() is implied to be false, since we're testing for objects that are not the current value of MenuScreen::selectedIndex
									
									//make sure actor wasn't added or removed from the screen during an event
									if(actorIndex<actors.size() && actors.get(actorIndex)==actor)
									{
										selectedIndex = actorIndex;
									}
									else
									{
										actorIndex = actors.indexOf(actor);
									}
									
									//check item's mouse hover/press state
									if(actorIndex != ACTORMENU_NOSELECTION)
									{
										selectedIndex = actorIndex;
										onActorHover(selectedIndex);
										
										//make sure actor wasn't added or removed from the screen during an event
										if(actorIndex<actors.size() && actors.get(actorIndex)==actor)
										{
											selectedIndex = actorIndex;
										}
										else
										{
											actorIndex = actors.indexOf(actor);
										}
										
										//check item's mouse press state
										if(actorIndex!=ARRAYLIST_NOTFOUND && selectedIndex==actorIndex && !keyboardEnabled)
										{
											if(actor->didMousePress() && !actor->wasMousePressed())
											{
												pressingActor = true;
												onActorPress(selectedIndex);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	void ActorMenuElement::drawActor(ApplicationData appData, Graphics graphics, Actor*actor) const
	{
		actor->draw(appData, graphics);
	}
	
	void ActorMenuElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		unsigned int hoveredIndex = selectedIndex;
		for(unsigned int i=0; i<actors.size(); i++)
		{
			if(i!=hoveredIndex)
			{
				drawActor(appData, graphics, actors.get(i));
			}
		}
		
		if(hoveredIndex != ACTORMENU_NOSELECTION)
		{
			drawActor(appData, graphics, actors.get(hoveredIndex));
		}
	}
	
	unsigned int ActorMenuElement::addActor(Actor*actor)
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("Cannot add a null Actor to an ActorMenuElement object");
		}
		actors.add(actor);
		return actors.size()-1;
	}
	
	Actor* ActorMenuElement::getActor(unsigned int index) const
	{
		return actors.get(index);
	}
	
	const ArrayList<Actor*>& ActorMenuElement::getActors() const
	{
		return actors;
	}
	
	void ActorMenuElement::removeActor(Actor*actor)
	{
		unsigned int index = actors.indexOf(actor);
		if(index != ARRAYLIST_NOTFOUND)
		{
			removeActor(index);
		}
	}
	
	void ActorMenuElement::removeActor(unsigned int index)
	{
		actors.remove(index);
		if(selectedIndex == index)
		{
			selectedIndex = ACTORMENU_NOSELECTION;
		}
		else if(selectedIndex > index)
		{
			if(actors.size()>0)
			{
				selectedIndex--;
			}
			else
			{
				selectedIndex = ACTORMENU_NOSELECTION;
			}
		}
	}
	
	unsigned int ActorMenuElement::getTotalActors()
	{
		return actors.size();
	}
	
	void ActorMenuElement::onActorHover(unsigned int index)
	{
		//
	}
	
	void ActorMenuElement::onActorHoverFinish(unsigned int index)
	{
		//
	}
	
	void ActorMenuElement::onActorPress(unsigned int index)
	{
		//
	}
	
	void ActorMenuElement::onActorPressCancel(unsigned int index)
	{
		//
	}
	
	void ActorMenuElement::onActorRelease(unsigned int index)
	{
		//
	}
	
	void ActorMenuElement::onActorSelect(unsigned int index)
	{
		//
	}
	
	
	void ActorMenuElement::moveHoverUp()
	{
		unsigned int index = getSelectedIndex();
		unsigned int totalItems = getTotalActors();
		if(index == ACTORMENU_NOSELECTION)
		{
			if(totalItems>0)
			{
				index = totalItems-1;
				setSelectedIndex(index);
			}
		}
		else
		{
			if(index==0)
			{
				if(totalItems>0)
				{
					index = totalItems-1;
				}
				else
				{
					index = ACTORMENU_NOSELECTION;
				}
			}
			else
			{
				index--;
			}
			
			setSelectedIndex(index);
		}
	}
	
	void ActorMenuElement::moveHoverDown()
	{
		unsigned int index = getSelectedIndex();
		unsigned int totalActors = getTotalActors();
		if(index == ACTORMENU_NOSELECTION)
		{
			if(totalActors>0)
			{
				index = 0;
				setSelectedIndex(index);
			}
		}
		else
		{
			index++;
			if(index>totalActors)
			{
				if(totalActors>0)
				{
					index = 0;
				}
				else
				{
					index = ACTORMENU_NOSELECTION;
				}
			}
			
			setSelectedIndex(index);
		}
	}
	
	void ActorMenuElement::moveHoverLeft()
	{
		moveHoverUp();
	}
	
	void ActorMenuElement::moveHoverRight()
	{
		moveHoverUp();
	}
	
	bool ActorMenuElement::selectCurrentIndex()
	{
		if(selectedIndex!=ACTORMENU_NOSELECTION && selectedIndex < actors.size())
		{
			onActorSelect(selectedIndex);
			return true;
		}
		return false;
	}
	
	void ActorMenuElement::addUpKey(const Keyboard::Key&key)
	{
		for(unsigned int i=0; i<keys.size(); i++)
		{
			Pair<Keyboard::Key, KeyDirection>& cmp = keys.get(i);
			if(cmp.first == key)
			{
				keys.remove(i);
				i = keys.size();
			}
		}
		keys.add(Pair<Keyboard::Key, KeyDirection>(key, KEYDIR_UP));
	}
	
	void ActorMenuElement::addDownKey(const Keyboard::Key&key)
	{
		for(unsigned int i=0; i<keys.size(); i++)
		{
			Pair<Keyboard::Key, KeyDirection>& cmp = keys.get(i);
			if(cmp.first == key)
			{
				keys.remove(i);
				i = keys.size();
			}
		}
		keys.add(Pair<Keyboard::Key, KeyDirection>(key, KEYDIR_DOWN));
	}
	
	void ActorMenuElement::addLeftKey(const Keyboard::Key&key)
	{
		for(unsigned int i=0; i<keys.size(); i++)
		{
			Pair<Keyboard::Key, KeyDirection>& cmp = keys.get(i);
			if(cmp.first == key)
			{
				keys.remove(i);
				i = keys.size();
			}
		}
		keys.add(Pair<Keyboard::Key, KeyDirection>(key, KEYDIR_LEFT));
	}
	
	void ActorMenuElement::addRightKey(const Keyboard::Key&key)
	{
		for(unsigned int i=0; i<keys.size(); i++)
		{
			Pair<Keyboard::Key, KeyDirection>& cmp = keys.get(i);
			if(cmp.first == key)
			{
				keys.remove(i);
				i = keys.size();
			}
		}
		keys.add(Pair<Keyboard::Key, KeyDirection>(key, KEYDIR_RIGHT));
	}
	
	void ActorMenuElement::addSelectKey(const Keyboard::Key&key)
	{
		for(unsigned int i=0; i<keys.size(); i++)
		{
			Pair<Keyboard::Key, KeyDirection>& cmp = keys.get(i);
			if(cmp.first == key)
			{
				keys.remove(i);
				i = keys.size();
			}
		}
		keys.add(Pair<Keyboard::Key, KeyDirection>(key, KEYDIR_SELECT));
	}
	
	void ActorMenuElement::clearKeys()
	{
		keys.clear();
	}
	
	void ActorMenuElement::setKeyboardEnabled(bool toggle)
	{
		if((toggle && !keyboardEnabled) || (keyboardEnabled && selectedIndex==ACTORMENU_NOSELECTION))
		{
			//enable keyboard
			keyboardEnabled = true;
			if(pressingActor)
			{
				pressingActor = false;
				onActorPressCancel(selectedIndex);
			}
		}
		else if(!toggle && keyboardEnabled)
		{
			//disable keyboard
			keyboardEnabled = false;
			if(pressingActor)
			{
				pressingActor = false;
				onActorPressCancel(selectedIndex);
			}
			if(selectedIndex != ACTORMENU_NOSELECTION)
			{
				Actor* actor = actors.get(selectedIndex);
				if(!actor->isMouseOver())
				{
					onActorHoverFinish(selectedIndex);
				}
			}
		}
	}
	
	void ActorMenuElement::clearMouseStates()
	{
		if(selectedIndex != ACTORMENU_NOSELECTION)
		{
			unsigned int oldSelectedIndex = selectedIndex;
			if(pressingActor)
			{
				onActorPressCancel(oldSelectedIndex);
			}
			selectedIndex = ACTORMENU_NOSELECTION;
			onActorHoverFinish(oldSelectedIndex);
		}
	}
	
	void ActorMenuElement::setSelectedIndex(unsigned int index)
	{
		bool keyboardWasEnabled = keyboardEnabled;
		setKeyboardEnabled(true);
		if(index != selectedIndex)
		{
			unsigned int oldSelectedIndex = selectedIndex;
			bool wasPressingActor = pressingActor;
			pressingActor = false;
			
			if(oldSelectedIndex != ACTORMENU_NOSELECTION)
			{
				if(wasPressingActor)
				{
					onActorPressCancel(oldSelectedIndex);
				}
				selectedIndex = ACTORMENU_NOSELECTION;
				onActorHoverFinish(oldSelectedIndex);
			}
			
			if(index != ACTORMENU_NOSELECTION && index<actors.size())
			{
				selectedIndex = index;
				onActorHover(index);
				if(wasPressingActor && keyboardWasEnabled)
				{
					pressingActor = true;
					onActorPress(index);
				}
			}
		}
	}
	
	bool ActorMenuElement::isKeyboardEnabled() const
	{
		return keyboardEnabled;
	}
	
	unsigned int ActorMenuElement::getSelectedIndex() const
	{
		return selectedIndex;
	}
	
}
