
#include "Drawable.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include <mutex>

#pragma once

namespace GameLibrary
{
	typedef void(*CompletionCallback)(void*);

	class ScreenElement : public Drawable
	{
		friend class Screen;
		friend class ScreenManager;
	private:
		ScreenElement* parentElement;
		ArrayList<ScreenElement*> childElements;
		ArrayList<ScreenElement*> removedChildElements;

		mutable bool updatingElements;
		bool relativePosition;

		Color backgroundColor;

	protected:
		virtual void drawBackground(ApplicationData appData, Graphics graphics) const;
		virtual void drawElements(ApplicationData appData, Graphics graphics) const;

	public:
		ScreenElement();
		ScreenElement(const ScreenElement&) = delete;
		virtual ~ScreenElement();

		ScreenElement& operator=(const ScreenElement&) = delete;

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		virtual RectangleF getFrame() const;
		virtual Vector2f getCenter() const;
		virtual Vector2f getSize() const;

		void addChildElement(ScreenElement*element);
		void removeFromParentElement();
		void bringChildElementToFront(ScreenElement*element);

		const ArrayList<ScreenElement*>& getChildElements() const;
		ScreenElement* getParentElement() const;

		void enableRelativePositioning(bool);
		bool relativePositioningEnabled() const;
		
		void setBackgroundColor(const Color&);
		const Color& getBackgroundColor() const;
	};
}
