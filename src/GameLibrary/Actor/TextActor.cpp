
#include "TextActor.h"

namespace GameLibrary
{
	TextActor::TextActor()
		: TextActor(0,0, "", Graphics::getDefaultFont(), Color::BLACK)
	{
		//
	}
	
	TextActor::TextActor(const String&text, Font*font, const Color&color, unsigned int fontSize, int fontStyle, const TextActor::TextAlignment&align)
		: TextActor(0,0, text, font, color, fontSize, fontStyle, align)
	{
		//
	}
	
	TextActor::TextActor(float x1, float y1, const String&txt, Font*fnt, const Color&colr, unsigned int fontSize, int fontStyle, const TextActor::TextAlignment&align)
	{
		x = x1;
		y = y1;
		text = txt;
		font = fnt;
		color = colr;
		alignment = align;
		lineSpacing = 0;
		
		fontstyle = fontStyle;
		fontsize = fontSize;

		updateSize();
	}
	
	TextActor::~TextActor()
	{
		//
	}
	
	void TextActor::update(ApplicationData appData)
	{
		Actor::update(appData);
	}
	
	void TextActor::draw(ApplicationData appData, Graphics graphics) const
	{
		drawActor(appData, graphics, x, y, scale);
	}
	
	void TextActor::drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const
	{
		if(visible && scale!=0 && font!=nullptr)
		{
			graphics.translate(x,y);
			Graphics boundingBoxGraphics(graphics);
			if(rotation != 0)
			{
				graphics.rotate(rotation);
			}
			Graphics frameGraphics(graphics);
			if(mirroredHorizontal)
			{
				if(mirroredVertical)
				{
					graphics.scale(-scale,-scale);

				}
				else
				{
					graphics.scale(-scale,scale);
				}
			}
			else
			{
				if(mirroredVertical)
				{
					graphics.scale(scale,-scale);
				}
				else
				{
					graphics.scale(scale,scale);
				}
			}
			
			Actor::draw(appData, graphics);
			
			Graphics actorGraphics(graphics);
			actorGraphics.setColor(color);
			actorGraphics.setAlpha((byte)(alpha*255));
			
			unsigned int size_original = font->getSize();
			int style_original = font->getStyle();
			
			font->setSize(fontsize);
			font->setStyle(fontstyle);
			
			actorGraphics.setFont(font);
			
			ArrayList<String> lines;
			TextActor::getLinesList(text, lines);
			
			float lineoffset = boundsrect.y;
			
			for(unsigned int i=0; i<lines.size(); i++)
			{
				const String&line = lines.get(i);
				const RectangleF&linerect = linerects.get(i);
				//TODO add mirroring
				
				switch(alignment)
				{
					default:
					case ALIGN_BOTTOMLEFT:
					case ALIGN_TOPLEFT:
					actorGraphics.drawString(line, 0, lineoffset+linerect.y+linerect.height);
					break;
					
					case ALIGN_BOTTOMRIGHT:
					case ALIGN_TOPRIGHT:
					actorGraphics.drawString(line, (float)(boundsrect.width-linerect.width), lineoffset+linerect.y+linerect.height);
					break;
					
					case ALIGN_CENTER:
					actorGraphics.drawString(line, -linerect.width/2, lineoffset+linerect.y+linerect.height);
					break;
				}

				if(frame_visible)
				{
					RectangleF fixedLineRect;
					switch(alignment)
					{
						default:
						case ALIGN_BOTTOMLEFT:
						case ALIGN_TOPLEFT:
						fixedLineRect = RectangleF(0, lineoffset+linerect.y, linerect.width, linerect.height);
						break;
					
						case ALIGN_BOTTOMRIGHT:
						case ALIGN_TOPRIGHT:
						fixedLineRect = RectangleF((float)(boundsrect.width-linerect.width), lineoffset+linerect.y, linerect.width, linerect.height);
						break;
					
						case ALIGN_CENTER:
						fixedLineRect = RectangleF(-linerect.width/2, lineoffset+linerect.y, linerect.width, linerect.height);
						break;
					}

					actorGraphics.setColor(frame_color);
					actorGraphics.drawRect(fixedLineRect.x, fixedLineRect.y, fixedLineRect.width, fixedLineRect.height);
					actorGraphics.setColor(color);
				}
			}
			
			font->setSize(size_original);
			font->setStyle(style_original);
			
			if(frame_visible)
			{
				frameGraphics.setColor(frame_color);
				frameGraphics.drawRect(boundsrect.x*scale, boundsrect.y*scale, boundsrect.width*scale, boundsrect.height*scale);
				boundingBoxGraphics.setColor(frame_color);
				boundingBoxGraphics.drawRect(framerect.x, framerect.y, framerect.width, framerect.height);
			}
		}
	}
	
	void TextActor::updateSize()
	{
		if(font == nullptr)
		{
			width = 0;
			height = 0;
			linerects.clear();
		}
		else
		{
			unsigned int size_original = font->getSize();
			int style_original = font->getStyle();

			font->setSize(fontsize);
			font->setStyle(fontstyle);

			ArrayList<String> lines;
			TextActor::getLinesList(text, lines);

			RectangleF rect = RectangleF(0,0,0,0);
			linerects.clear();
			float offset_y = 0;
			float spacing = (float)lineSpacing;
			for(unsigned int i=0; i<lines.size(); i++)
			{
				const String&line = lines.get(i);
				Vector2u lineSize = font->measureString(line);
				float lineH = (float)lineSize.y;
				RectangleF linerect = RectangleF(0, offset_y, (float)lineSize.x, lineH);
				rect.combine(linerect);
				linerects.add(linerect);
				offset_y += lineH;
				offset_y += spacing;
			}
			
			for(unsigned int i=0; i<linerects.size(); i++)
			{
				linerects[i].y -= rect.y;
			}
			
			font->setSize(size_original);
			font->setStyle(style_original);

			boundsrect = getBoundsRect(rect.width, rect.height);
			width = rect.width*scale;
			height = rect.height*scale;
		}

		framerect = rotationMatrix.transform(getBoundsRect(width, height));
	}

	void TextActor::getLinesList(const String&text, ArrayList<String>&lines)
	{
		String currentLine;
		for(unsigned int i=0; i<text.length(); i++)
		{
			char c = text.charAt(i);
			if(c == '\r')
			{
				if(i != (text.length() - 1))
				{
					if(text.charAt(i+1) == '\n')
					{
						i++;
					}
				}
				lines.add(currentLine);
				currentLine.clear();
			}
			else if(c == '\n')
			{
				lines.add(currentLine);
				currentLine.clear();
			}
			else
			{
				currentLine += c;
			}
		}
		if(currentLine.length() > 0)
		{
			lines.add(currentLine);
			currentLine.clear();
		}
	}
	
	RectangleF TextActor::getBoundsRect(float width, float height) const
	{
		switch(alignment)
		{
			default:
			case ALIGN_BOTTOMLEFT:
			return RectangleF(0, -height, width, height);
			
			case ALIGN_BOTTOMRIGHT:
			return RectangleF(-width, -height, width, height);
			
			case ALIGN_CENTER:
			return RectangleF(-(width/2), -(height/2), width, height);
			
			case ALIGN_TOPLEFT:
			return RectangleF(0, 0, width, height);
			
			case ALIGN_TOPRIGHT:
			return RectangleF(-width, 0, width, height);
		}
	}

	RectangleF TextActor::getFrame() const
	{
		RectangleF frame = framerect;
		frame.x += x;
		frame.y += y;
		return frame;
	}
	
	void TextActor::scaleToFit(const RectangleF&container)
	{
		if(width == 0 || height == 0)
		{
			x = container.x + (container.width/2);
			y = container.y + (container.height/2);
			return;
		}
		RectangleF currentFrame = getFrame();
		RectangleF oldFrame = currentFrame;
		currentFrame.scaleToFit(container);
		float ratio = currentFrame.width/oldFrame.width;
		setScale(getScale()*ratio);
		RectangleF newFrame = getFrame();
		
		switch(alignment)
		{
			default:
			case ALIGN_BOTTOMLEFT:
			x = container.x + ((container.width-newFrame.width)/2);
			y = container.y + (((container.height-newFrame.height)/2) + newFrame.height);
			break;
			
			case ALIGN_BOTTOMRIGHT:
			x = container.x + (((container.width-newFrame.width)/2) + newFrame.width);
			y = container.y + (((container.height-newFrame.height)/2) + newFrame.height);
			break;
			
			case ALIGN_CENTER:
			x = container.x + (container.width/2);
			y = container.y + (container.height/2);
			break;
			
			case ALIGN_TOPLEFT:
			x = container.x + ((container.width-newFrame.width)/2);
			y = container.y + ((container.height-newFrame.height)/2);
			break;
			
			case ALIGN_TOPRIGHT:
			x = container.x + (((container.width-newFrame.width)/2) + newFrame.width);
			y = container.y + ((container.height-newFrame.height)/2);
			break;
		}
		updateSize();
	}
	
	void TextActor::setText(const String&str)
	{
		text = str;
		updateSize();
	}
	
	void TextActor::setFont(Font*fnt)
	{
		font = fnt;
		updateSize();
	}
	
	void TextActor::setFontSize(unsigned int size)
	{
		fontsize = size;
		updateSize();
	}
	
	void TextActor::setFontStyle(int style)
	{
		fontstyle = style;
		updateSize();
	}
	
	void TextActor::setAlignment(const TextActor::TextAlignment& align)
	{
		alignment = align;
		updateSize();
	}
	
	void TextActor::setLineSpacing(int spacing)
	{
		lineSpacing = spacing;
		updateSize();
	}
	
	const String& TextActor::getText() const
	{
		return text;
	}
	
	Font* TextActor::getFont() const
	{
		return font;
	}
	
	unsigned int TextActor::getFontSize() const
	{
		return fontsize;
	}
	
	int TextActor::getFontStyle() const
	{
		return fontstyle;
	}
	
	const TextActor::TextAlignment& TextActor::getAlignment() const
	{
		return alignment;
	}
	
	int TextActor::getLineSpacing() const
	{
		return lineSpacing;
	}
	
	bool TextActor::checkPointCollision(const Vector2f&point)
	{
		if(text.length() == 0 || font==nullptr)
		{
			return false;
		}
		RectangleF frame = getFrame();
		float left = frame.x;
		float top = frame.y;
		float right = frame.x+frame.width;
		float bottom = frame.y+frame.height;
		if(point.x>left && point.y>top && point.x<right && point.y<bottom)
		{
			Vector2f pointFixed = point;
			pointFixed.x -= x;
			pointFixed.y -= y;
			
			pointFixed = inverseRotationMatrix.transform(pointFixed);
			
			float ratX = pointFixed.x/width;
			float ratY = pointFixed.y/height;

			float pxlX = (ratX*((float)boundsrect.width));
			float pxlY = (ratY*((float)boundsrect.height));

			float lineoffset = boundsrect.y;
			
			for(unsigned int i=0; i<linerects.size(); i++)
			{
				const RectangleF&linerect = linerects.get(i);
				RectangleF fixedLineRect;
				switch(alignment)
				{
					default:
					case ALIGN_BOTTOMLEFT:
					case ALIGN_TOPLEFT:
					fixedLineRect = RectangleF(0, lineoffset+linerect.y, linerect.width, linerect.height);
					break;
					
					case ALIGN_BOTTOMRIGHT:
					case ALIGN_TOPRIGHT:
					fixedLineRect = RectangleF((float)(boundsrect.width-linerect.width), lineoffset+linerect.y, linerect.width, linerect.height);
					break;
					
					case ALIGN_CENTER:
					fixedLineRect = RectangleF(-linerect.width/2, lineoffset+linerect.y, linerect.width, linerect.height);
					break;
				}

				if(fixedLineRect.contains(Vector2f(pxlX, pxlY)))
				{
					return true;
				}
			}
		}
		return false;
	}
}
