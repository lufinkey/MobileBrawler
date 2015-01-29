
#include "../ScreenElement.h"
#include "../../Actor/Actor.h"
#include "../../Actor/SpriteActor.h"
#include "../../Input/Keyboard.h"
#include <climits>

namespace GameLibrary
{
#define ACTORMENU_NOSELECTION UINT_MAX
	class ActorMenuElement : public ScreenElement
	{
	public:
		ActorMenuElement(const RectangleF&frame);
		virtual ~ActorMenuElement();
		
		virtual void update(ApplicationData appData) override;
		virtual void drawMain(ApplicationData appData, Graphics graphics) const override;
		
		virtual unsigned int addActor(Actor*actor);
		Actor* getActor(unsigned int index) const;
		const ArrayList<Actor*>& getActors() const;
		void removeActor(Actor*actor);
		void removeActor(unsigned int index);
		unsigned int getTotalActors();
		
		virtual void onActorHover(unsigned int index);
		virtual void onActorHoverFinish(unsigned int index);
		virtual void onActorPress(unsigned int index);
		virtual void onActorPressCancel(unsigned int index);
		virtual void onActorRelease(unsigned int index);
		virtual void onActorSelect(unsigned int index);
		
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
		void setSelectedIndex(unsigned int);
		
		bool isKeyboardEnabled() const;
		unsigned int getSelectedIndex() const;
		
	protected:
		virtual void drawActor(ApplicationData appData, Graphics graphics, Actor*actor) const;
		
	private:
		ArrayList<Actor*> actors;
		
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
