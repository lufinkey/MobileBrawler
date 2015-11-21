
#include "TextInputElement.h"
#include "../../Input/Keyboard.h"
#include "../../Input/Mouse.h"
#include "../../Input/Multitouch.h"
#include <mutex>

namespace GameLibrary
{
	TextInputElement* TextInputElement_input_responder = nullptr;
	std::mutex TextInputElement_responder_mutex;
	
	TextInputElement::TextInputListener::TextInputListener(TextInputElement* element) : element(element)
	{
		//
	}
	
	void TextInputElement::TextInputListener::onTextInput(const String& text)
	{
		element->handleTextInput(text);
	}
	
	void TextInputElement::TextInputListener::onKeyPress(Keyboard::Key key)
	{
		if(key==Keyboard::BACKSPACE)
		{
			element->handleBackspace();
		}
	}
	
	TextInputElement::TextInputElement(const RectangleD&frame)
		: TouchElement(frame),
		textInputListener(this),
		textColor(Color::BLACK),
		font(Graphics::getDefaultFont()),
		cursorIndex(0),
		borderColor(Color::BLACK)
	{
		setBackgroundColor(Color::WHITE);
	}
	
	TextInputElement::~TextInputElement()
	{
		if(TextInputElement_input_responder==this)
		{
			resignTextInputResponder();
		}
	}
	
	void TextInputElement::update(ApplicationData appData)
	{
		ScreenElement::update(appData);
	}
	
	void TextInputElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		ScreenElement::drawMain(appData, graphics);
		RectangleD frame = getFrame();
		if(font!=nullptr)
		{
			Vector2u textSize = font->measureString(text);
			double textY = frame.y + ((frame.height + (double)textSize.y)/2);
			double textX = frame.x + 5;
			graphics.clip(frame);
			graphics.setColor(textColor);
			graphics.setFont(font);
			graphics.drawString(text, textX, textY);
		}
		graphics.setColor(borderColor);
		graphics.drawRect(frame);
	}
	
	void TextInputElement::becomeTextInputResponder()
	{
		if(TextInputElement_input_responder != nullptr)
		{
			if(TextInputElement_input_responder == this)
			{
				return;
			}
			TextInputElement_input_responder->resignTextInputResponder();
		}
		TextInputElement_responder_mutex.lock();
		TextInputElement_input_responder = this;
		Keyboard::addEventListener(&textInputListener);
		Keyboard::startTextInput();
		TextInputElement_responder_mutex.unlock();
	}
	
	void TextInputElement::resignTextInputResponder()
	{
		TextInputElement_responder_mutex.lock();
		if(TextInputElement_input_responder == nullptr)
		{
			return;
		}
		if(TextInputElement_input_responder != this)
		{
			return;
		}
		TextInputElement_input_responder = nullptr;
		Keyboard::removeEventListener(&textInputListener);
		Keyboard::endTextInput();
		TextInputElement_responder_mutex.unlock();
	}
	
	bool TextInputElement::isTextInputResponder() const
	{
		if(TextInputElement_input_responder == this)
		{
			return true;
		}
		return false;
	}
	
	void TextInputElement::handleTextInput(const String& inputted_text)
	{
		if(TextInputElement_input_responder != this)
		{
			return;
		}
		text += inputted_text;
		cursorIndex += inputted_text.length();
	}
	
	void TextInputElement::handleBackspace()
	{
		if(TextInputElement_input_responder != this)
		{
			return;
		}
		if(cursorIndex!=0)
		{
			text = text.substring(0,cursorIndex-1) + text.substring(cursorIndex,text.length());
			cursorIndex -= 1;
		}
	}
	
	void TextInputElement::setText(const String& txt)
	{
		text = txt;
		cursorIndex = text.length();
	}
	
	const String& TextInputElement::getText() const
	{
		return text;
	}
	
	void TextInputElement::setFont(Font* fnt)
	{
		font = fnt;
	}
	
	Font* TextInputElement::getFont() const
	{
		return font;
	}
	
	void TextInputElement::setCursorIndex(size_t index)
	{
		if(index > text.length())
		{
			throw OutOfBoundsException((String)"cursorIndex is out of bounds at index " + index);
		}
		cursorIndex = index;
	}
	
	size_t TextInputElement::getCursorIndex() const
	{
		return cursorIndex;
	}
	
	void TextInputElement::setBorderColor(const Color& color)
	{
		borderColor = color;
	}
	
	const Color& TextInputElement::getBorderColor() const
	{
		return borderColor;
	}
	
	void TextInputElement::onTouchUpInside(const TouchElementEvent& evt)
	{
		TouchElement::onTouchUpInside(evt);
		if(!isTextInputResponder())
		{
			becomeTextInputResponder();
		}
	}
	
	ScreenElement* TextInputElement::handleMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos)
	{
		ScreenElement* handler = TouchElement::handleMouseRelease(appData, mouseIndex, button, mousepos);
		if(isTextInputResponder())
		{
			if(handler!=this)
			{
				resignTextInputResponder();
			}
		}
		return handler;
	}
	void TextInputElement::elementHandledMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element)
	{
		if(isTextInputResponder())
		{
			resignTextInputResponder();
		}
		TouchElement::elementHandledMouseRelease(appData, mouseIndex, button, mousepos, element);
	}
	
	ScreenElement* TextInputElement::handleTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos)
	{
		ScreenElement* handler = TouchElement::handleTouchEnd(appData, touchID, touchpos);
		if(isTextInputResponder())
		{
			if(handler!=this)
			{
				resignTextInputResponder();
			}
		}
		return handler;
	}
	
	void TextInputElement::elementHandledTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element)
	{
		if(isTextInputResponder())
		{
			resignTextInputResponder();
		}
		TouchElement::elementHandledTouchEnd(appData, touchID, touchpos, element);
	}
}
