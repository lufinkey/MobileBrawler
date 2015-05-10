
#pragma once

#include "../ScreenElement.h"

namespace GameLibrary
{
	class TextInputElement : public ScreenElement
	{
	private:
		void* textinputdata;

	protected:
		virtual void onRemoveFromWindow(Window*window) override;
		virtual void onAddToWindow(Window*window) override;

	public:
		explicit TextInputElement(const RectangleD&frame);
		virtual ~TextInputElement();

		virtual void update(ApplicationData appData) override;
		virtual void drawMain(ApplicationData appData, Graphics graphics) const override;
	};
}
