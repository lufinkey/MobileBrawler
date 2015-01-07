
#include "Screen.h"
#include "ScreenElement.h"
#include "../Actor/BaseActor.h"
#include "../Actor/Actor.h"
#include "../Actor/Animation.h"
#include "../Actor/TextActor.h"
#include "../Graphics/Graphics.h"
#include "../Input/Keyboard.h"
#include <climits>

#pragma once

namespace GameLibrary
{
#define MENUSCREEN_NOSELECTION UINT_MAX
	class MenuScreen : public Screen
	{
	public:
		MenuScreen();
		virtual ~MenuScreen();
		
		void addItem(float x, float y, Animation*animation, const Animation::Direction&direction, bool destruct=true);
		void addItem(float x, float y, const String&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK, unsigned int fontsize=18, const Font::Style&fontstyle=Font::STYLE_PLAIN, const TextActor::TextAlignment&alignment=TextActor::ALIGN_CENTER);
		void removeItem(unsigned int index);
		unsigned int getTotalItems();
		
		BaseActor* getItem(unsigned int index);
		
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
		
		void addUpKey(Keyboard::Key key);
		void addDownKey(Keyboard::Key key);
		void addLeftKey(Keyboard::Key key);
		void addRightKey(Keyboard::Key key);
		void addSelectKey(Keyboard::Key key);
		void clearKeys();

		void setKeyboardEnabled(bool);
		bool isKeyboardEnabled() const;
		
	private:
		class MainElement : public GameLibrary::ScreenElement
		{
		private:
			MenuScreen*menuScreen;
		public:
			MainElement(MenuScreen*menuScreen, const RectangleF&frame);
			virtual ~MainElement();
			
			virtual void update(ApplicationData appData);
			virtual void draw(ApplicationData appData, Graphics graphics) const;
		};

		class ImageItem : public GameLibrary::Actor
		{
		private:
			MenuScreen*menuScreen;
		public:
			ImageItem(MenuScreen*menuScreen, float x, float y);
			virtual ~ImageItem();
			
			virtual void onMousePress(Window*window, unsigned int touchID);
			virtual void onMouseRelease(Window*window, unsigned int touchID);
			virtual void onMouseEnter(Window*window, unsigned int touchID);
			virtual void onMouseLeave(Window*window, unsigned int touchID);
		};
		
		class TextItem : public GameLibrary::TextActor
		{
		private:
			MenuScreen*menuScreen;
		public:
			TextItem(MenuScreen*menuScreen, float x, float y, const String&text, Font*font, const Color&color, unsigned int fontsize, const Font::Style&fontstyle, const TextActor::TextAlignment&alignment);
			virtual ~TextItem();
			
			virtual void onMousePress(Window*window, unsigned int touchID);
			virtual void onMouseRelease(Window*window, unsigned int touchID);
			virtual void onMouseEnter(Window*window, unsigned int touchID);
			virtual void onMouseLeave(Window*window, unsigned int touchID);
		};
		
		ArrayList<BaseActor*> items;
		unsigned int selectedIndex;
		bool keyboardEnabled;
		bool pressingItem;
		
		typedef enum
		{
			KEYDIR_UP,
			KEYDIR_DOWN,
			KEYDIR_LEFT,
			KEYDIR_RIGHT,
			KEYDIR_SELECT
		} KeyDirection;
		
		ArrayList<Pair<Keyboard::Key, KeyDirection> > keys;
	};
}
