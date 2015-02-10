
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
	/*! The selected index when a MenuScreen has not selected an item*/
#define MENUSCREEN_NOSELECTION ACTORMENU_NOSELECTION
	
	/*! Thin Screen wrapper around ActorMenuElement. The main difference is that this class DOES automatically handle deallocation of any added Actor pointers.*/
	class MenuScreen : public Screen
	{
	public:
		/*! default constructor*/
		MenuScreen();
		/*! Constructs a MenuScreen to be the root Screen of a Window. Only one screen in any Screen stack should be delegated as the root Screen.
			\param window the Window that the Screen will be contained within*/
		MenuScreen(Window*window);
		/*! virtual destructor*/
		virtual ~MenuScreen();
		
		
		MenuScreen(const MenuScreen&) = delete;
		MenuScreen& operator=(const MenuScreen&) = delete;
		
		
		/*! Adds a SpriteActor. This Actor's deallocation will be automatically handled when this Screen is deallocated
			\param actor a SpriteActor pointer
			\returns the index of the added SpriteActor*/
		unsigned int addItem(SpriteActor*actor);
		/*! Creates and adds a SpriteActor.
			\param position the position of the Actor in the Screen
			\param animation the default Animation of the Actor
			\param direction the default Animation::Direction of the Actor
			\param destructAnimation true to have the Actor handle deallocation of the Animation, or false to manually handle deallocation of the Animation*/
		unsigned int addItem(const Vector2f&position, Animation*animation, const Animation::Direction&direction=Animation::FORWARD, bool destructAnimation=true);
		/*! Adds a TextActor. This Actor's deallocation will be automatically handled when this Screen is deallocated.
			\param actor a TextActor pointer*/
		unsigned int addItem(TextActor*actor);
		/*! Creates and adds a TextActor.
			\param position the position of the Actor in the Screen
			\param text a string to display
			\param font a font to use to display the text
			\param color the text color
			\param fontSize the glyph size of the font
			\param fontStyle the style (plain, bold italic, etc.) of the font \see GameLibrary::Font::Style
			\param alignment the alignment of the text, relative the origin \see GameLibrary::TextActor::TextAlignment*/
		unsigned int addItem(const Vector2f&position, const String&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK, unsigned int fontsize=18, const Font::Style&fontstyle=Font::STYLE_PLAIN, const TextActor::TextAlignment&alignment=TextActor::ALIGN_CENTER);
		/*! Removes and deallocates a previously added Actor pointer.
			\param index the index of the Actor. When an Actor is removed, the indexes of other Actors may change*/
		void removeItem(unsigned int index);
		/*! Gets the total number of items stored in the menu.
			\returns an unsigned int representing the total amount of Actor pointers added to the menu*/
		unsigned int getTotalItems();
		/*! Gets an Actor pointer at a given index.
			\param index the index of the Actor
			\returns an Actor pointer*/
		Actor* getItem(unsigned int index) const;
		
		
		/*! Called when an Actor in the menu is hovered over by a mouse or touch instance.
			\param index the index of the Actor*/
		virtual void onItemHover(unsigned int index);
		/*! Called when an Actor in the menu finished being hovered over by a mouse or touch instance.
			\param index the index of the Actor*/
		virtual void onItemHoverFinish(unsigned int index);
		/*! Called when an Actor in the menu is pressed by a mouse or touch instance.
			\param index the index of the Actor*/
		virtual void onItemPress(unsigned int index);
		/*! Called when an Actor in the menu has a pressed mouse or touch instance leave the vicinity of the Actor, or some other event cancels the press.
			\param index the index of the Actor*/
		virtual void onItemPressCancel(unsigned int index);
		/*! Called when an Actor in the menu is released by a mouse or touch instance that previously pressed it.
			\param index the index of the Actor*/
		virtual void onItemRelease(unsigned int index);
		/*! Called after an Actor in the menu is released. Menu button actions should be handled here.
			\param index the index of the Actor*/
		virtual void onItemSelect(unsigned int index);
		
		
		/*! Manually sets the current hover to the next Actor above the current one, or the first Actor in the list, if no Actor is currently hovered.
		This function automatically sets the Keyboard to be the enabled input for this menu.*/
		virtual void moveHoverUp();
		/*! Manually sets the current hover to the next Actor below the current one, or the last Actor in the list, if no Actor is currently hovered.
		This function automatically sets the Keyboard to be the enabled input for this menu.*/
		virtual void moveHoverDown();
		/*! Manually sets the current hover to the next Actor to the left of the current one, or the first Actor in the list, if no Actor is currently hovered.
		This function automatically sets the Keyboard to be the enabled input for this menu.*/
		virtual void moveHoverLeft();
		/*! Manually sets the current hover to the next Actor to the right of the current one, or the last Actor in the list, if no Actor is currently hovered.
		This function automatically sets the Keyboard to be the enabled input for this menu.*/
		virtual void moveHoverRight();
		/*! Calls onActorSelect(unsigned int) for the currently hovered Actor, or does nothing if no Actor is currently hovered.
			\returns true if an Actor was selected, or false if otherwise*/
		virtual bool selectCurrentIndex();
		
		
		/*! Adds a keyboard key to manually move up in the menu.
			\param key a key constant*/
		void addUpKey(const Keyboard::Key&key);
		/*! Adds a keyboard key to manually move down in the menu.
			\param key a key constant*/
		void addDownKey(const Keyboard::Key&key);
		/*! Adds a keyboard key to manually move left in the menu.
			\param key a key constant*/
		void addLeftKey(const Keyboard::Key&key);
		/*! Adds a keyboard key to manually move right in the menu.
			\param key a key constant*/
		void addRightKey(const Keyboard::Key&key);
		/*! Adds a keyboard key to manually select the current menu item.
			\param key a key constant*/
		void addSelectKey(const Keyboard::Key&key);
		/*! Removes all the added keys from the menu.*/
		void clearKeys();
		
		
		/*! Enables keyboard input instead of mouse or touch input.
		The keyboard is automatically enabled if one of the added keys is pressed, and automatically disabled if one of the Actor objects becomes hovered or pressed.
			\param enabled true to enable keyboard input, false to disable keyboard input*/
		void setKeyboardEnabled(bool enabled);
		/*! Clears all the current mouse states for all the Actor objects, and cancels all press states.*/
		void clearMouseStates();
		/*! Sets the currently hovered Actor index in the menu. This automatically enables Keyboard input.
			\param index the Actor index to set hovered, or MENUSCREEN_NOSELECTION for no selected index*/
		void setSelectedIndex(unsigned int index);
		
		
		/*! Tells if the menu's input is currently set to the keyboard.
			\returns true if input is set to the keyboard, and false if input is set to mouse or touch*/
		bool isKeyboardEnabled() const;
		/*! Gets the currently hovered Actor index in the menu.
			\returns an index for an Actor in the menu, or MENUSCREEN_NOSELECTION if no index is selected*/
		unsigned int getSelectedIndex() const;
		
		
		/*! Gets the automatic layout manager for the contained actors.
			\returns a const AutoLayout reference*/
		const AutoLayout& getAutoActorLayout() const;
		
	protected:
		/*! Called to draw an Actor in the menu. This function can be overridden to add custom drawing behavior.
			\param appData specifies information about the Application drawing the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the Actor
			\param actor the Actor from the menu being drawn*/
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
