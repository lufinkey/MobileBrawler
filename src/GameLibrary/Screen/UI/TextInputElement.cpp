
#include "TextInputElement.h"
#include "../../Utilities/PlatformChecks.h"

#if defined(TARGETPLATFORM_WINDOWS)
	#include <Windows.h>
#endif

namespace GameLibrary
{
#if defined(TARGETPLATFORM_WINDOWS)
	typedef struct
	{
		HWND handle;
	} TextInputElementData;
#endif

	void TextInputElement::onRemoveFromWindow(Window*window)
	{
		ScreenElement::onRemoveFromWindow(window);
		/*#if defined(TARGETPLATFORM_WINDOWS)
			DestroyWindow(((TextInputElementData*)textinputdata)->handle);
			((TextInputElementData*)textinputdata)->handle = nullptr;
		#endif*/
	}

	void TextInputElement::onAddToWindow(Window*window)
	{
		/*RectangleF frame = getFrame();

		#if defined(TARGETPLATFORM_WINDOWS)
			HWND hwnd = nullptr;
			window->getHandlePtr(&hwnd);
			HWND inputHandle = nullptr;
			inputHandle = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"ED_123",
									WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_LEFT,
									frame.x, frame.y, frame.width, frame.height,
									hwnd, (HMENU)(123),
									(HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
		#endif*/

		ScreenElement::onAddToWindow(window);
	}

	TextInputElement::TextInputElement(const RectangleF&frame)
	{
		//
	}

	TextInputElement::~TextInputElement()
	{
		//
	}

	void TextInputElement::update(ApplicationData appData)
	{
		//
	}

	void TextInputElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		//
	}
}
