
#include "TextActor.h"

namespace GameLibrary
{
	TextActor::TextActor() : TextActor(0,0, "", Graphics::getDefaultFont(), Color::BLACK)
	{
		//
	}

	TextActor::TextActor(const String&text, Font*font, const Color&color) : TextActor(0,0, "", Graphics::getDefaultFont(), Color::BLACK)
	{
		//
	}

	TextActor::TextActor(float x1, float y1, const String&txt, Font*fnt, const Color&colr)
	{
		x = x1;
		y = y1;
		text = txt;
		font = fnt;
		color = colr;
		alignment = ALIGN_BOTTOMLEFT;
	}

	TextActor::~TextActor()
	{
		//
	}

	void TextActor::update(ApplicationData appData)
	{
		BaseActor::update(appData);
	}

	void TextActor::draw(ApplicationData appData, Graphics graphics) const
	{
		BaseActor::draw(appData, graphics);
	}

	void TextActor::updateSize()
	{
		//TODO update size
	}

	RectangleF TextActor::getFrame() const
	{
		switch(alignment)
		{
			default:
			case ALIGN_BOTTOMLEFT:
			return RectangleF(x, y-height, width, height);

			case ALIGN_BOTTOMRIGHT:
			return RectangleF(x-width, y-height, width, height);

			case ALIGN_CENTER:
			return RectangleF(x-(width/2), y-(height/2), width, height);

			case ALIGN_TOPLEFT:
			return RectangleF(x, y, width, height);

			case ALIGN_TOPRIGHT:
			return RectangleF(x-width, y, width, height);
		}
	}

	void TextActor::setAlignment(const TextActor::TextAlignment& align)
	{
		alignment = align;
	}

	TextActor::TextAlignment TextActor::getAlignment() const
	{
		return alignment;
	}

	void TextActor::setScale(float scale)
	{
		BaseActor::setScale(scale);
		updateSize();
	}
}
