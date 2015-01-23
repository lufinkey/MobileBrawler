
#pragma once

#include "Actor.h"

namespace GameLibrary
{
	class TextActor : public Actor
	{
	public:
		enum TextAlignment
		{
			ALIGN_BOTTOMLEFT,
			ALIGN_BOTTOMRIGHT,
			ALIGN_CENTER,
			ALIGN_TOPLEFT,
			ALIGN_TOPRIGHT
		};
		typedef enum TextAlignment TextAlignment;
		
		TextActor();
		TextActor(const TextActor&) = delete;
		TextActor(const String&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK, unsigned int fontSize=24, const Font::Style&fontStyle=Font::STYLE_PLAIN, const TextActor::TextAlignment&alignment=TextActor::ALIGN_BOTTOMLEFT);
		TextActor(float x, float y, const String&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK, unsigned int fontSize=24, const Font::Style&fontStyle=Font::STYLE_PLAIN, const TextActor::TextAlignment&alignment=TextActor::ALIGN_BOTTOMLEFT);
		virtual ~TextActor();
		
		TextActor& operator=(const TextActor&) = delete;
		
		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;
		
		virtual RectangleF getFrame() const;
		
		virtual void scaleToFit(const RectangleF&container);

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
		//NOTE: this function is very inefficient in loops. You should use it for checking single pixels. Do NOT use for pixel level collisions (use PixelIterator)
		virtual bool checkPointCollision(const Vector2f&point);
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
