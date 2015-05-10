
#pragma once

#include "../ScreenElement.h"
#include "../../Actor/Actor.h"
#include "../../Actor/SpriteActor.h"
#include "../../Input/Keyboard.h"
#include <climits>

namespace GameLibrary
{
	/*! The selected index when an ActorMenuElement has not selected an actor*/
#define ACTORMENU_NOSELECTION UINT_MAX
	
	/*! Holds and updates a list of Actors, finds the currently hovered or selected actor in the list, and calls events ActorMenuElement events for it. This class is non-copyable.*/
	class ActorMenuElement : public ScreenElement
	{
	public:
		/*! \copydoc GameLibrary::ScreenElement::ScreenElement(const GameLibrary::RectangleD&)*/
		explicit ActorMenuElement(const RectangleD&frame);
		/*! virtual destructor*/
		virtual ~ActorMenuElement();
		
		
		/*! \copydoc GameLibrary::ScreenElement::update(ApplicationData)*/
		virtual void update(ApplicationData appData) override;
		/*! \copydoc GameLibrary::ScreenElement::setFrame(const GameLibrary::RectangleD&)*/
		virtual void setFrame(const RectangleD&frame) override;
		
		
		/*! Adds an actor to the menu.
			\param actor an Actor pointer
			\returns the index of the Actor inside the menu*/
		virtual unsigned int addActor(Actor*actor);
		/*! Adds an actor to the menu that will be automatically resized by the AutoLayout
			\param bounds the ratio in the frame where the Actor will be laid out
			\param actor an Actor pointer
			\returns the index of the Actor inside the menu*/
		virtual unsigned int addActor(const RectD&bounds, Actor*actor);
		/*! Gets an actor at a given index inside the menu.
			\param index the index of the Actor inside the menu
			\returns an Actor pointer*/
		Actor* getActor(unsigned int index) const;
		/*! Gets the list of all the Actor objects in the menu.
			\returns a const ArrayList reference of Actor pointers*/
		const ArrayList<Actor*>& getActors() const;
		/*! Removes a previously added Actor from the menu. When an Actor is removed, the indexes of other Actor entries may change.
			\param actor the Actor pointer*/
		void removeActor(Actor*actor);
		/*! Removes a previously added Actor from the menu. When an Actor is removed, the indexes of other Actor entries may change.
			\param index the Actor index inside the menu*/
		void removeActor(unsigned int index);
		/*! Gets the total amount of Actor objects stored in the menu.
			\returns an unsigned int representing the total number of Actor objects in the menu*/
		unsigned int getTotalActors();
		
		
		/*! Called when an Actor in the menu is hovered over by a mouse or touch instance.
			\param index the index of the Actor*/
		virtual void onActorHover(unsigned int index);
		/*! Called when an Actor in the menu finished being hovered over by a mouse or touch instance.
			\param index the index of the Actor*/
		virtual void onActorHoverFinish(unsigned int index);
		/*! Called when an Actor in the menu is pressed by a mouse or touch instance.
			\param index the index of the Actor*/
		virtual void onActorPress(unsigned int index);
		/*! Called when an Actor in the menu has a pressed mouse or touch instance leave the vicinity of the Actor, or some other event cancels the press.
			\param index the index of the Actor*/
		virtual void onActorPressCancel(unsigned int index);
		/*! Called when an Actor in the menu is released by a mouse or touch instance that previously pressed it.
			\param index the index of the Actor*/
		virtual void onActorRelease(unsigned int index);
		/*! Called after an Actor in the menu is released. Menu button actions should be handled here.
			\param index the index of the Actor*/
		virtual void onActorSelect(unsigned int index);
		
		
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
			\param index the Actor index to set hovered, or ACTORMENU_NOSELECTION for no selected index*/
		void setSelectedIndex(unsigned int index);
		
		
		/*! Tells if the menu's input is currently set to the keyboard.
			\returns true if input is set to the keyboard, and false if input is set to mouse or touch*/
		bool isKeyboardEnabled() const;
		/*! Gets the currently hovered Actor index in the menu.
			\returns an index for an Actor in the menu, or ACTORMENU_NOSELECTION if no index is selected*/
		unsigned int getSelectedIndex() const;
		
		
		/*! Gets the automatic layout manager for the contained actors.
			\returns a const AutoLayout reference*/
		const AutoLayout& getAutoActorLayout() const;
		
	protected:
		/*! \copydoc GameLibrary::ScreenElement::drawMain(ApplicationData)const*/
		virtual void drawMain(ApplicationData appData, Graphics graphics) const override;
		/*! Called to draw an Actor in the menu. This function can be overridden to add custom drawing behavior.
			\param appData specifies information about the Application drawing the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the Actor
			\param actor the Actor from the menu being drawn*/
		virtual void drawActor(ApplicationData appData, Graphics graphics, Actor*actor) const;
		
	private:
		ArrayList<Actor*> actors;
		AutoLayout autoActorLayout;
		
		unsigned int selectedIndex;
		bool keyboardEnabled;
		bool pressingActor;
		
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
	
	//TODO make moveHoverUp, moveHoverDown, moveHoverLeft, and moveHoverRight look for the nearest box in the specified direction
	// ex: moveHoverDown()
	//     _________
	//     |       |
	//     |_______|
	//    /         \
	//   /           \
	// _____
	// |___|
	//
	// that box at the bottom left will get selected, because it's within the range of "down" for the current item.
	// the "technical" x and y values will get stored in order to keep a straight line going down (ie. if there's a "fork")
	// if there are no items within the direction's range, it will look for all items with a center that is below it's center (or left of for left, right of for right, etc)
	// if there are no items there, it will look for the furthest most item within the opposite range
}
