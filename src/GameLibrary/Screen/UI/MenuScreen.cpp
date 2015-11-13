
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
	
	void MenuScreen::MainElement::onActorHover(size_t index)
	{
		menuScreen->onItemHover(index);
	}
	
	void MenuScreen::MainElement::onActorHoverFinish(size_t index)
	{
		menuScreen->onItemHoverFinish(index);
	}
	
	void MenuScreen::MainElement::onActorPress(size_t index)
	{
		menuScreen->onItemPress(index);
	}
	
	void MenuScreen::MainElement::onActorPressCancel(size_t index)
	{
		menuScreen->onItemPressCancel(index);
	}
	
	void MenuScreen::MainElement::onActorRelease(size_t index)
	{
		menuScreen->onItemRelease(index);
	}
	
	void MenuScreen::MainElement::onActorSelect(size_t index)
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
		mainElement->setLayoutRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
		mainElement->setLayoutRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
		mainElement->setLayoutRule(LAYOUTRULE_RIGHT,  1, LAYOUTVALUE_RATIO);
		mainElement->setLayoutRule(LAYOUTRULE_BOTTOM, 1, LAYOUTVALUE_RATIO);
		element->addChildElement(mainElement);
	}
	
	MenuScreen::~MenuScreen()
	{
		ArrayList<Actor*> items = mainElement->getActors();
		mainElement->removeFromParentElement();
		delete mainElement;
		mainElement = nullptr;
		for(size_t i=0; i<items.size(); i++)
		{
			delete items.get(i);
		}
	}
	
	void MenuScreen::drawItem(ApplicationData appData, Graphics graphics, Actor*item) const
	{
		item->draw(appData, graphics);
	}
	
	size_t MenuScreen::addItem(SpriteActor*actor)
	{
		return mainElement->addActor(actor);
	}
	
	size_t MenuScreen::addItem(const RectD&bounds, SpriteActor*actor)
	{
		return mainElement->addActor(bounds, actor);
	}
	
	size_t MenuScreen::addItem(const Vector2d&position, Animation*animation, const Animation::Direction&direction, bool destructAnimation)
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
	
	size_t MenuScreen::addItem(const RectD&bounds, Animation*animation, const Animation::Direction&direction, bool destructAnimation)
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
	
	size_t MenuScreen::addItem(TextActor*actor)
	{
		return mainElement->addActor(actor);
	}
	
	size_t MenuScreen::addItem(const RectD&bounds, TextActor*actor)
	{
		return mainElement->addActor(bounds, actor);
	}
	
	size_t MenuScreen::addItem(const Vector2d&position, const String&text, Font*font, const Color&color, unsigned int fontsize, int fontstyle, const TextActor::TextAlignment&alignment)
	{
		return mainElement->addActor(new TextActor(position.x, position.y, text, font, color, fontsize, fontstyle, alignment));
	}
	
	size_t MenuScreen::addItem(const RectD&bounds, const String&text, Font*font, const Color&color, unsigned int fontsize, int fontstyle, const TextActor::TextAlignment&alignment)
	{
		return mainElement->addActor(bounds, new TextActor(text, font, color, fontsize, fontstyle, alignment));
	}
	
	void MenuScreen::removeItem(size_t index)
	{
		delete mainElement->getActor(index);
		mainElement->removeActor(index);
	}
	
	size_t MenuScreen::getTotalItems()
	{
		return mainElement->getTotalActors();
	}
	
	Actor* MenuScreen::getItem(size_t index) const
	{
		return mainElement->getActor(index);
	}
	
	void MenuScreen::onItemHover(size_t index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemHoverFinish(size_t index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemPress(size_t index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemPressCancel(size_t index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemRelease(size_t index)
	{
		//Open for implementation
	}
	
	void MenuScreen::onItemSelect(size_t index)
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
	
	void MenuScreen::setSelectedIndex(size_t index)
	{
		mainElement->setSelectedIndex(index);
	}
	
	bool MenuScreen::isKeyboardEnabled() const
	{
		return mainElement->isKeyboardEnabled();
	}
	
	size_t MenuScreen::getSelectedIndex() const
	{
		return mainElement->getSelectedIndex();
	}
	
	AutoLayoutManager* MenuScreen::getActorAutoLayoutManager(size_t index) const
	{
		return mainElement->getActorAutoLayoutManager(index);
	}
}
