
#include "../Application/ApplicationData.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Graphics/Graphics.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include <mutex>

#pragma once

namespace GameLibrary
{
	typedef void(*CompletionCallback)(void*);

	class ScreenElement
	{
		friend class Screen;
		friend class ScreenManager;
	private:
		ScreenElement* parentElement;
		ArrayList<ScreenElement*> childElements;
		ArrayList<ScreenElement*> removedChildElements;

		bool updatingElements;
		bool relativePosition;

	public:
		float x;
		float y;

		ScreenElement();
		virtual ~ScreenElement();

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics);

		void addChildElement(ScreenElement*element);
		void removeFromParentElement();
		void bringChildElementToFront(ScreenElement*element);

		const ArrayList<ScreenElement*>& getChildElements() const;
		ScreenElement* getParentElement() const;

		void enableRelativePositioning(bool toggle);
		bool relativePositioningEnabled();
	};
}
