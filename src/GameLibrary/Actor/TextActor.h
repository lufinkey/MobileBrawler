
#include "BaseActor.h"

#pragma once

namespace GameLibrary
{
	class TextActor : public BaseActor
	{
	public:
		enum TextAlignment : byte
		{
			ALIGN_BOTTOMLEFT,
			ALIGN_BOTTOMRIGHT,
			ALIGN_CENTER,
			ALIGN_TOPLEFT,
			ALIGN_TOPRIGHT
		};
		typedef enum TextAlignment TextAlignment;

		TextActor();
		TextActor(const String&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK);
		TextActor(float x, float y, const String&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK);
		virtual ~TextActor();

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		virtual RectangleF getFrame() const;

		void setAlignment(const TextAlignment&alignment);
		TextAlignment getAlignment() const;

	private:
		String text;
		Font* font;
		TextAlignment alignment;
	};
}
