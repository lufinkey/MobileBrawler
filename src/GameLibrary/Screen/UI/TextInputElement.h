
#pragma once

#include "../ScreenElement.h"

namespace GameLibrary
{
	class TextInputElement : public ScreenElement
	{
	private:
		void* textinputdata;

	protected:
		virtual void onRemoveFromWindow(Window*window);
		virtual void onAddToWindow(Window*window);

	public:
		TextInputElement(const RectangleF&frame);
		virtual ~TextInputElement();

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;
	};
}
