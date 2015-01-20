
#include "MenuScreen.h"

namespace GameLibrary
{
//MenuScreen::MainElement
	
	MenuScreen::MainElement::MainElement(MenuScreen*screen, const RectangleF&frame) : ScreenElement(frame)
	{
		menuScreen = screen;
	}
	
	MenuScreen::MainElement::~MainElement()
	{
		//
	}
	
	void MenuScreen::MainElement::update(ApplicationData appData)
	{
		setFrame(getParentElement()->getFrame());
		ScreenElement::update(appData);
		menuScreen->updateItems(appData);
	}
	
	void MenuScreen::MainElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		menuScreen->drawItems(appData, graphics);
	}
	
//MenuScreen::ImageItem
	
	MenuScreen::ImageItem::ImageItem(MenuScreen*screen, float x, float y) : SpriteActor(x,y)
	{
		menuScreen = screen;
	}

	MenuScreen::ImageItem::~ImageItem()
	{
		//
	}
	
	void MenuScreen::ImageItem::onMousePress(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
	void MenuScreen::ImageItem::onMouseRelease(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
	void MenuScreen::ImageItem::onMouseEnter(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
	void MenuScreen::ImageItem::onMouseLeave(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
//MenuScreen::TextItem
	
	MenuScreen::TextItem::TextItem(MenuScreen*menuScreen, float x, float y, const String&text, Font*font, const Color&color, unsigned int fontsize, const Font::Style&fontstyle, const TextActor::TextAlignment&alignment)
		: TextActor(x,y,text,font,color)
	{
		setFontSize(fontsize);
		setFontStyle(fontstyle);
		setAlignment(alignment);
	}
	
	MenuScreen::TextItem::~TextItem()
	{
		//
	}
	
	void MenuScreen::TextItem::onMousePress(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
	void MenuScreen::TextItem::onMouseRelease(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
	void MenuScreen::TextItem::onMouseEnter(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
	void MenuScreen::TextItem::onMouseLeave(Window*window, unsigned int touchID)
	{
		menuScreen->setKeyboardEnabled(false);
	}
	
//MenuScreen
	MenuScreen::MenuScreen() : MenuScreen(nullptr)
	{
		//
	}
	
	MenuScreen::MenuScreen(Window*window) : Screen(window)
	{
		selectedIndex = MENUSCREEN_NOSELECTION;
		keyboardEnabled = false;
		pressingItem = false;
		GameLibrary::ScreenElement* element = getElement();
		mainElement = new MainElement(this, element->getFrame());
		element->addChildElement(mainElement);
	}

	MenuScreen::~MenuScreen()
	{
		mainElement->removeFromParentElement();
		delete mainElement;
		mainElement = nullptr;
		
		for(unsigned int i = 0; i < items.size(); i++)
		{
			delete items.get(i);
		}
		items.clear();
	}
	
	void MenuScreen::updateItems(ApplicationData appData)
	{
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
					if(keyboardEnabled && selectedIndex!=MENUSCREEN_NOSELECTION)
					{
						pressingItem = true;
						onItemPress(selectedIndex);
					}
					break;
				}
			}
			else if(Keyboard::wasKeyPressed(keypair.first) && !Keyboard::isKeyPressed(keypair.first))
			{
				if(keypair.second==KEYDIR_SELECT)
				{
					if(keyboardEnabled && pressingItem)
					{
						onItemRelease(selectedIndex);
						selectCurrentIndex();
					}
				}
			}
		}

		if(!keyboardEnabled)
		{
			unsigned int lastSelectedIndex = selectedIndex;
			//test/update currently hovered actor
			if(lastSelectedIndex != MENUSCREEN_NOSELECTION)
			{
				Actor* actor = items.get(lastSelectedIndex);
				actor->update(appData);
				if(actor->isMouseOver())
				{
					//actor->wasMouseOver() is implied to be true, since we're testing for the currently hovered object
					if(actor->isMousePressed() && !actor->wasMousePressed())
					{
						pressingItem = true;
						onItemPress(lastSelectedIndex);
					}
					else if(pressingItem && !actor->isMousePressed())
					{
						pressingItem = false;
						actor->clearMouseState();
						onItemRelease(lastSelectedIndex);
						onItemHoverFinish(lastSelectedIndex);
						onItemSelect(lastSelectedIndex);
					}
				}
				else
				{
					selectedIndex = MENUSCREEN_NOSELECTION;
					if(pressingItem)
					{
						pressingItem = false;
						onItemPressCancel(lastSelectedIndex);
					}
					onItemHoverFinish(lastSelectedIndex);
				}
			}

			ArrayList<Actor*> menuItems = items;

			//test/update other actors
			for(unsigned int i=0; i<menuItems.size(); i++)
			{
				if(i != lastSelectedIndex)
				{
					Actor* actor = menuItems.get(i);

					//make sure actor wasn't added or removed from the screen during an event
					unsigned int actorIndex = ARRAYLIST_NOTFOUND;
					if(i<items.size() && items.get(i)==actor)
					{
						actorIndex = i;
					}
					else
					{
						actorIndex = items.indexOf(actor);
					}

					//if the actor is still in the screen
					if(actorIndex!=ARRAYLIST_NOTFOUND)
					{
						actor->update(appData);
						
						//checking selection by mouse
						if(!keyboardEnabled)
						{
							if(selectedIndex == MENUSCREEN_NOSELECTION)
							{
								if(actor->isMouseOver())
								{
									//actor->wasMouseOver() is implied to be false, since we're testing for objects that are not the current value of MenuScreen::selectedIndex
									
									//make sure actor wasn't added or removed from the screen during an event
									if(actorIndex<items.size() && items.get(actorIndex)==actor)
									{
										selectedIndex = actorIndex;
									}
									else
									{
										actorIndex = items.indexOf(actor);
									}
									
									//check item's mouse hover/press state
									if(actorIndex != MENUSCREEN_NOSELECTION)
									{
										selectedIndex = actorIndex;
										onItemHover(selectedIndex);
										
										//make sure actor wasn't added or removed from the screen during an event
										if(actorIndex<items.size() && items.get(actorIndex)==actor)
										{
											selectedIndex = actorIndex;
										}
										else
										{
											actorIndex = items.indexOf(actor);
										}
										
										//check item's mouse press state
										if(actorIndex!=ARRAYLIST_NOTFOUND && selectedIndex==actorIndex && !keyboardEnabled)
										{
											if(actor->isMousePressed() && !actor->wasMousePressed())
											{
												pressingItem = true;
												onItemPress(selectedIndex);
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
	
	void MenuScreen::drawItem(ApplicationData appData, Graphics graphics, unsigned int itemIndex) const
	{
		Actor* actor = items.get(itemIndex);
		actor->draw(appData, graphics);
	}
	
	void MenuScreen::drawItems(ApplicationData appData, Graphics graphics) const
	{
		unsigned int hoveredIndex = selectedIndex;
		for(unsigned int i=0; i<items.size(); i++)
		{
			if(i!=hoveredIndex)
			{
				drawItem(appData, graphics, i);
			}
		}
		
		if(hoveredIndex != MENUSCREEN_NOSELECTION)
		{
			drawItem(appData, graphics, hoveredIndex);
		}
	}
	
	unsigned int MenuScreen::addItem(const Vector2f&position, Animation*animation, const Animation::Direction&direction, bool destructAnimation)
	{
		if(animation == nullptr)
		{
			throw IllegalArgumentException("Cannot add an item with a null Animation to a GameLibrary::MenuScreen object");
		}
		else if(!(direction==Animation::FORWARD || direction==Animation::BACKWARD || direction==Animation::STOPPED || direction==Animation::NO_CHANGE))
		{
			throw IllegalArgumentException((String)"Invalid value " + direction + "for \"direction\" argument");
		}
		ImageItem* actor = new ImageItem(this, position.x, position.y);
		actor->addAnimation("default", animation, destructAnimation);
		actor->changeAnimation("default", direction);
		items.add(actor);
		return items.size()-1;
	}
	
	unsigned int MenuScreen::addItem(const Vector2f&position, const String&text, Font*font, const Color&color, unsigned int fontsize, const Font::Style&fontstyle, const TextActor::TextAlignment&alignment)
	{
		if(font == nullptr)
		{
			throw IllegalArgumentException("Cannot add an item with a null Font to a GameLibrary::MenuScreen object");
		}
		TextItem* textActor = new TextItem(this, position.x, position.y, text, font, color, fontsize, fontstyle, alignment);
		items.add(textActor);
		return items.size()-1;
	}
	
	void MenuScreen::removeItem(unsigned int index)
	{
		Actor* actor = items.get(index);
		items.remove(index);
		delete actor;
		if(selectedIndex == index)
		{
			selectedIndex = MENUSCREEN_NOSELECTION;
		}
		else if(selectedIndex > index)
		{
			if(items.size()>0)
			{
				selectedIndex--;
			}
			else
			{
				selectedIndex = MENUSCREEN_NOSELECTION;
			}
		}
	}
	
	unsigned int MenuScreen::getTotalItems()
	{
		return items.size();
	}
	
	Actor* MenuScreen::getItem(unsigned int index) const
	{
		return items.get(index);
	}
	
	void MenuScreen::onItemHover(unsigned int index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemHoverFinish(unsigned int index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemPress(unsigned int index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemPressCancel(unsigned int index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemRelease(unsigned int index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemSelect(unsigned int index)
	{
		//Open for implementation
	}
	
	void MenuScreen::moveHoverUp()
	{
		unsigned int index = getSelectedIndex();
		unsigned int totalItems = getTotalItems();
		if(index == MENUSCREEN_NOSELECTION)
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
					index = MENUSCREEN_NOSELECTION;
				}
			}
			else
			{
				index--;
			}

			setSelectedIndex(index);
		}
	}
	
	void MenuScreen::moveHoverDown()
	{
		unsigned int index = getSelectedIndex();
		unsigned int totalItems = getTotalItems();
		if(index == MENUSCREEN_NOSELECTION)
		{
			if(totalItems>0)
			{
				index = 0;
				setSelectedIndex(index);
			}
		}
		else
		{
			index++;
			if(index>totalItems)
			{
				if(totalItems>0)
				{
					index = 0;
				}
				else
				{
					index = MENUSCREEN_NOSELECTION;
				}
			}

			setSelectedIndex(index);
		}
	}
	
	void MenuScreen::moveHoverLeft()
	{
		moveHoverUp();
	}
	
	void MenuScreen::moveHoverRight()
	{
		moveHoverDown();
	}
	
	bool MenuScreen::selectCurrentIndex()
	{
		if(selectedIndex!=MENUSCREEN_NOSELECTION && selectedIndex < items.size())
		{
			onItemSelect(selectedIndex);
			return true;
		}
		return false;
	}
	
	void MenuScreen::addUpKey(Keyboard::Key key)
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
	
	void MenuScreen::addDownKey(Keyboard::Key key)
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
	
	void MenuScreen::addLeftKey(Keyboard::Key key)
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
	
	void MenuScreen::addRightKey(Keyboard::Key key)
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

	void MenuScreen::addSelectKey(Keyboard::Key key)
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
	
	void MenuScreen::clearKeys()
	{
		keys.clear();
	}

	void MenuScreen::setKeyboardEnabled(bool toggle)
	{
		if((toggle && !keyboardEnabled) || (keyboardEnabled && selectedIndex==MENUSCREEN_NOSELECTION))
		{
			//enable keyboard
			keyboardEnabled = true;
			if(pressingItem)
			{
				pressingItem = false;
				onItemPressCancel(selectedIndex);
			}
		}
		else if(!toggle && keyboardEnabled)
		{
			//disable keyboard
			keyboardEnabled = false;
			if(pressingItem)
			{
				pressingItem = false;
				onItemPressCancel(selectedIndex);
			}
			if(selectedIndex != MENUSCREEN_NOSELECTION)
			{
				Actor* actor = items.get(selectedIndex);
				if(!actor->isMouseOver())
				{
					onItemHoverFinish(selectedIndex);
				}
			}
		}
	}
	
	void MenuScreen::setSelectedIndex(unsigned int index)
	{
		bool keyboardWasEnabled = keyboardEnabled;
		setKeyboardEnabled(true);
		if(index != selectedIndex)
		{
			unsigned int oldSelectedIndex = selectedIndex;
			bool wasPressingItem = pressingItem;
			pressingItem = false;
			
			if(oldSelectedIndex != MENUSCREEN_NOSELECTION)
			{
				if(wasPressingItem)
				{
					onItemPressCancel(oldSelectedIndex);
				}
				selectedIndex = MENUSCREEN_NOSELECTION;
				onItemHoverFinish(oldSelectedIndex);
			}
			
			if(index != MENUSCREEN_NOSELECTION && index<items.size())
			{
				selectedIndex = index;
				onItemHover(index);
				if(wasPressingItem && keyboardWasEnabled)
				{
					pressingItem = true;
					onItemPress(index);
				}
			}
		}
	}
	
	bool MenuScreen::isKeyboardEnabled() const
	{
		return keyboardEnabled;
	}
	
	unsigned int MenuScreen::getSelectedIndex() const
	{
		return selectedIndex;
	}
}
