
#include "MenuScreen.h"
#include "../../Input/Multitouch.h"

namespace GameLibrary
{
//MenuScreen::MainElement
	
	MenuScreen::MainElement::MainElement(MenuScreen*screen, const RectangleD&frame) : ActorMenuElement(frame)
	{
		menuScreen = screen;
	}
	
	MenuScreen::MainElement::~MainElement()
	{
		//
	}
	
	void MenuScreen::MainElement::drawActor(ApplicationData appData, Graphics graphics, Actor*actor) const
	{
		menuScreen->drawItem(appData, graphics, actor);
	}
	
	void MenuScreen::MainElement::onActorHover(unsigned int index)
	{
		menuScreen->onItemHover(index);
	}
	
	void MenuScreen::MainElement::onActorHoverFinish(unsigned int index)
	{
		menuScreen->onItemHoverFinish(index);
	}
	
	void MenuScreen::MainElement::onActorPress(unsigned int index)
	{
		menuScreen->onItemPress(index);
	}
	
	void MenuScreen::MainElement::onActorPressCancel(unsigned int index)
	{
		menuScreen->onItemPressCancel(index);
	}
	
	void MenuScreen::MainElement::onActorRelease(unsigned int index)
	{
		menuScreen->onItemRelease(index);
	}
	
	void MenuScreen::MainElement::onActorSelect(unsigned int index)
	{
		menuScreen->onItemSelect(index);
	}
	
	
//MenuScreen
	
	MenuScreen::MenuScreen() : MenuScreen(nullptr)
	{
		//
	}
	
	MenuScreen::MenuScreen(Window*window) : Screen(window)
	{
		GameLibrary::ScreenElement* element = getElement();
		mainElement = new MainElement(this, element->getFrame());
		element->addChildElement(RectD(0,0,1,1), mainElement);
	}

	MenuScreen::~MenuScreen()
	{
		ArrayList<Actor*> items = mainElement->getActors();
		mainElement->removeFromParentElement();
		delete mainElement;
		mainElement = nullptr;
		for(unsigned int i=0; i<items.size(); i++)
		{
			delete items.get(i);
		}
	}
	
	void MenuScreen::drawItem(ApplicationData appData, Graphics graphics, Actor*item) const
	{
		item->draw(appData, graphics);
	}
	
	unsigned int MenuScreen::addItem(SpriteActor*actor)
	{
		return mainElement->addActor(actor);
	}
	
	unsigned int MenuScreen::addItem(const RectD&bounds, SpriteActor*actor)
	{
		return mainElement->addActor(bounds, actor);
	}
	
	unsigned int MenuScreen::addItem(const Vector2d&position, Animation*animation, const Animation::Direction&direction, bool destructAnimation)
	{
		if(animation == nullptr)
		{
			throw IllegalArgumentException("animation", "null");
		}
		else if(!(direction==Animation::FORWARD || direction==Animation::BACKWARD || direction==Animation::STOPPED || direction==Animation::NO_CHANGE))
		{
			throw IllegalArgumentException("direction", (String)"" + direction);
		}
		SpriteActor* actor = new SpriteActor(position.x, position.y);
		actor->addAnimation("default", animation, destructAnimation);
		actor->changeAnimation("default", direction);
		return mainElement->addActor(actor);
	}
	
	unsigned int MenuScreen::addItem(const RectD&bounds, Animation*animation, const Animation::Direction&direction, bool destructAnimation)
	{
		if(animation == nullptr)
		{
			throw IllegalArgumentException("animation", "null");
		}
		else if(!(direction==Animation::FORWARD || direction==Animation::BACKWARD || direction==Animation::STOPPED || direction==Animation::NO_CHANGE))
		{
			throw IllegalArgumentException("direction", (String)"" + direction);
		}
		SpriteActor* actor = new SpriteActor();
		actor->addAnimation("default", animation, destructAnimation);
		actor->changeAnimation("default", direction);
		return mainElement->addActor(bounds, actor);
	}
	
	unsigned int MenuScreen::addItem(TextActor*actor)
	{
		return mainElement->addActor(actor);
	}
	
	unsigned int MenuScreen::addItem(const RectD&bounds, TextActor*actor)
	{
		return mainElement->addActor(bounds, actor);
	}
	
	unsigned int MenuScreen::addItem(const Vector2d&position, const String&text, Font*font, const Color&color, unsigned int fontsize, int fontstyle, const TextActor::TextAlignment&alignment)
	{
		return mainElement->addActor(new TextActor(position.x, position.y, text, font, color, fontsize, fontstyle, alignment));
	}
	
	unsigned int MenuScreen::addItem(const RectD&bounds, const String&text, Font*font, const Color&color, unsigned int fontsize, int fontstyle, const TextActor::TextAlignment&alignment)
	{
		return mainElement->addActor(bounds, new TextActor(text, font, color, fontsize, fontstyle, alignment));
	}
	
	void MenuScreen::removeItem(unsigned int index)
	{
		delete mainElement->getActor(index);
		mainElement->removeActor(index);
	}
	
	unsigned int MenuScreen::getTotalItems()
	{
		return mainElement->getTotalActors();
	}
	
	Actor* MenuScreen::getItem(unsigned int index) const
	{
		return mainElement->getActor(index);
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
		mainElement->moveHoverUp();
	}
	
	void MenuScreen::moveHoverDown()
	{
		mainElement->moveHoverDown();
	}
	
	void MenuScreen::moveHoverLeft()
	{
		mainElement->moveHoverLeft();
	}
	
	void MenuScreen::moveHoverRight()
	{
		mainElement->moveHoverRight();
	}
	
	bool MenuScreen::selectCurrentIndex()
	{
		return mainElement->selectCurrentIndex();
	}
	
	void MenuScreen::addUpKey(const Keyboard::Key&key)
	{
		mainElement->addUpKey(key);
	}
	
	void MenuScreen::addDownKey(const Keyboard::Key&key)
	{
		mainElement->addDownKey(key);
	}
	
	void MenuScreen::addLeftKey(const Keyboard::Key&key)
	{
		mainElement->addLeftKey(key);
	}
	
	void MenuScreen::addRightKey(const Keyboard::Key&key)
	{
		mainElement->addRightKey(key);
	}

	void MenuScreen::addSelectKey(const Keyboard::Key&key)
	{
		mainElement->addSelectKey(key);
	}
	
	void MenuScreen::clearKeys()
	{
		mainElement->clearKeys();
	}

	void MenuScreen::setKeyboardEnabled(bool toggle)
	{
		mainElement->setKeyboardEnabled(toggle);
	}
	
	void MenuScreen::clearMouseStates()
	{
		mainElement->clearMouseStates();
	}
	
	void MenuScreen::setSelectedIndex(unsigned int index)
	{
		mainElement->setSelectedIndex(index);
	}
	
	bool MenuScreen::isKeyboardEnabled() const
	{
		return mainElement->isKeyboardEnabled();
	}
	
	unsigned int MenuScreen::getSelectedIndex() const
	{
		return mainElement->getSelectedIndex();
	}
	
	const AutoLayout& MenuScreen::getAutoActorLayout() const
	{
		return mainElement->getAutoActorLayout();
	}
}
