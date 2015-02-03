
#pragma once

#include "Screen.h"
#include "UI/ActorMenuElement.h"
#include "../Actor/Actor.h"
#include "../Actor/SpriteActor.h"
#include "../Actor/Animation.h"
#include "../Actor/TextActor.h"
#include "../Graphics/Graphics.h"
#include "../Input/Keyboard.h"
#include <climits>

namespace GameLibrary
{
#define MENUSCREEN_NOSELECTION ACTORMENU_NOSELECTION
	class MenuScreen : public Screen
	{
	public:
		MenuScreen();
		MenuScreen(const MenuScreen&) = delete;
		MenuScreen(Window*window);
		virtual ~MenuScreen();
		
		MenuScreen& operator=(const MenuScreen&) = delete;
		
		//this object's deallocation will be handled by the menu screen if added
		unsigned int addItem(SpriteActor*actor);
		unsigned int addItem(const Vector2f&position, Animation*animation, const Animation::Direction&direction=Animation::FORWARD, bool destructAnimation=true);
		//this object's deallocation will be handled by the menu screen if added
		unsigned int addItem(TextActor*actor);
		unsigned int addItem(const Vector2f&position, const String&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK, unsigned int fontsize=18, const Font::Style&fontstyle=Font::STYLE_PLAIN, const TextActor::TextAlignment&alignment=TextActor::ALIGN_CENTER);
		void removeItem(unsigned int index);
		unsigned int getTotalItems();
		
		Actor* getItem(unsigned int index) const;
		
		virtual void onItemHover(unsigned int index);
		virtual void onItemHoverFinish(unsigned int index);
		virtual void onItemPress(unsigned int index);
		virtual void onItemPressCancel(unsigned int index);
		virtual void onItemRelease(unsigned int index);
		virtual void onItemSelect(unsigned int index);
		
		virtual void moveHoverUp();
		virtual void moveHoverDown();
		virtual void moveHoverLeft();
		virtual void moveHoverRight();
		virtual bool selectCurrentIndex();
		
		void addUpKey(const Keyboard::Key&key);
		void addDownKey(const Keyboard::Key&key);
		void addLeftKey(const Keyboard::Key&key);
		void addRightKey(const Keyboard::Key&key);
		void addSelectKey(const Keyboard::Key&key);
		void clearKeys();

		void setKeyboardEnabled(bool);
		void clearMouseStates();
		void setSelectedIndex(unsigned int);
		
		bool isKeyboardEnabled() const;
		unsigned int getSelectedIndex() const;
		
	protected:
		virtual void drawItem(ApplicationData appData, Graphics graphics, Actor*item) const;
		
	private:
		class MainElement : public ActorMenuElement
		{
		private:
			MenuScreen*menuScreen;
			
		protected:
			virtual void drawActor(ApplicationData appData, Graphics graphics, Actor*actor) const override;
			
		public:
			MainElement(MenuScreen*menuScreen, const RectangleF&frame);
			virtual ~MainElement();
			
			virtual void onActorHover(unsigned int index) override;
			virtual void onActorHoverFinish(unsigned int index) override;
			virtual void onActorPress(unsigned int index) override;
			virtual void onActorPressCancel(unsigned int index) override;
			virtual void onActorRelease(unsigned int index) override;
			virtual void onActorSelect(unsigned int index) override;
		};
		
		MainElement* mainElement;
	};
}
