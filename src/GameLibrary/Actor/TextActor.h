
#pragma once

#include "Actor.h"

namespace GameLibrary
{
	/*! A specialized Actor that can draw text.*/
	class TextActor : public Actor
	{
	public:
		/*! The position to align text, relative to the origin*/
		typedef enum
		{
			/*! The text aligns to the bottom left of the TextActor.*/
			ALIGN_BOTTOMLEFT,
			/*! The text aligns to the bottom right of the TextActor.*/
			ALIGN_BOTTOMRIGHT,
			/*! The text aligns to the center of the TextActor.*/
			ALIGN_CENTER,
			/*! The text aligns to the top left of the TextActor.*/
			ALIGN_TOPLEFT,
			/*! The text aligns to the top right of the TextActor.*/
			ALIGN_TOPRIGHT
		} TextAlignment;
		
		/*! default constructor*/
		TextActor();
		/*! Constructs a TextActor with a specified string, font, color, font size, font style, and alignment.
			\param text a string to display
			\param font a font to use to display the text
			\param color the text color
			\param fontSize the glyph size of the font
			\param fontStyle the style (plain, bold italic, etc.) of the font \see GameLibrary::Font::Style
			\param alignment the alignment of the text, relative the origin \see GameLibrary::TextActor::TextAlignment*/
		explicit TextActor(const WideString&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK, unsigned int fontSize=24, int fontStyle=Font::STYLE_PLAIN, const TextActor::TextAlignment&alignment=TextActor::ALIGN_BOTTOMLEFT);
		/*! Constructs a TextActor with a specified position, string, font, color, font size, font style, and alignment.
			\param x the x coordinate
			\param y the y coordinate
			\param text a string to display
			\param font a font to use to display the text
			\param color the text color
			\param fontSize the glyph size of the font
			\param fontStyle the style (plain, bold italic, etc.) of the font \see GameLibrary::Font::Style
			\param alignment the alignment of the text, relative the origin \see GameLibrary::TextActor::TextAlignment*/
		TextActor(double x, double y, const WideString&text, Font*font=Graphics::getDefaultFont(), const Color&color=Color::BLACK, unsigned int fontSize=24, int fontStyle=Font::STYLE_PLAIN, const TextActor::TextAlignment&alignment=TextActor::ALIGN_BOTTOMLEFT);
		/*virtual destructor*/
		virtual ~TextActor();
		
		
		/*! \copydoc GameLibrary::Actor::update(ApplicationData)*/
		virtual void update(ApplicationData appData) override;
		/*! \copydoc GameLibrary::Actor::draw(ApplicationData,Graphics)const*/
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		
		/*! \copydoc GameLibrary::Actor::getFrame()const*/
		virtual RectangleD getFrame() const override;
		
		
		/*! \copydoc GameLibrary::Actor::scaleToFit(const RectangleD&)*/
		virtual void scaleToFit(const RectangleD&container) override;
		
		
		/*! Sets the string to display when drawn.
			\param text the string to display*/
		void setText(const WideString&text);
		/*! Sets the font to use to display the text.
			\param font the font to display the string*/
		void setFont(Font*font);
		/*! Sets the size of the font.
			\param fontSize the glyph size of the font*/
		void setFontSize(unsigned int fontSize);
		/*! Sets the style (plain, bold, italic, etc.) of the font.
			\param fontStyle a bitmask of the font styles to use \see GameLibrary::Font::Style*/
		void setFontStyle(int fontStyle);
		/*! Sets the alignment to display the text, relative to the origin.
			\param alignment the alignment of the text, relative the origin \see GameLibrary::TextActor::TextAlignment*/
		void setAlignment(const TextAlignment&alignment);
		/*! Sets the spacing between each line of text. Lines are separated by the newline (\\n) character.
			\param spacing the amount of pixels to separate each line*/
		void setLineSpacing(int spacing);
		
		
		/*! Gets a constant reference to the String being displayed.
			\returns the string being displayed*/
		const WideString& getText() const;
		/*! Gets a pointer to the Font being used to display the text.
			\returns a pointer to the font being used*/
		Font* getFont() const;
		/*! Gets the font size being used to display the string.
			\returns the glyph size of the font*/
		unsigned int getFontSize() const;
		/*! Gets the font style (plain, bold, italic, etc.) being used to display the string.
			\returns a bitmask of the font styles being used. \see GameLibrary::Font::Style*/
		int getFontStyle() const;
		/*! Gets the alignment of the text, relative to the origin.
			\returns a TextAlignment constant \see GameLibrary::TextActor::TextAlignment*/
		const TextAlignment& getAlignment() const;
		/*! Gets the spacing between each line of text. Lines of text are separated with a newline (\\n) character.
			\returns an integer representing the amount of pixels between each line*/
		int getLineSpacing() const;
		
		
		/*! \copydoc GameLibrary::Actor::updateSize()*/
		virtual void updateSize() override;
		/*! \copydoc GameLibrary::Actor::checkPointCollision(const Vector2d&)*/
		virtual bool checkPointCollision(const Vector2d&point) override;
		
	protected:
		/*! Special draw function to draw the TextActor with specific properties. These properties are not stored into the TextActor. This function is called from TextActor::draw
			\param appData specifies information about the Application drawing the TextActor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the SpriteActor
			\param x the x coordinate
			\param y the y coordinate
			\param scale the ratio to size the SpriteActor from its default size*/
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, double x, double y, double scale) const;
		
	private:
		WideString text;
		Font* font;
		TextAlignment alignment;
		int lineSpacing;
		
		int fontstyle;
		unsigned int fontsize;

		RectangleD framerect;
		RectangleD boundsrect;
		ArrayList<RectangleD> linerects;

		RectangleD getBoundsRect(double width, double height) const;
		static void getLinesList(const WideString&text, ArrayList<WideString>&lines);
	};
}
