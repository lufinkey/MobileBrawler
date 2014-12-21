
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

		void setText(const String&);
		void setFont(Font*);
		void setFontSize(unsigned int);
		void setFontStyle(const Font::Style&);
		void setAlignment(const TextAlignment&);
		void setLineSpacing(int);
		
		const String& getText() const;
		Font* getFont() const;
		unsigned int getFontSize() const;
		const Font::Style& getFontStyle() const;
		const TextAlignment& getAlignment() const;
		int getLineSpacing() const;
		
	protected:
		virtual void updateSize();
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const;
		
	private:
		String text;
		Font* font;
		TextAlignment alignment;
		int lineSpacing;
		
		Font::Style fontstyle;
		unsigned int fontsize;

		RectangleF framerect;
		RectangleF boundsrect;
		ArrayList<RectangleF> linerects;

		RectangleF getBoundsRect(float width, float height) const;
		static void getLinesList(const String&text, ArrayList<String>&lines);
	};
}
