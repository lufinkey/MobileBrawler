
#include "TextActor.h"

namespace GameLibrary
{
	TextActor::TextActor()
		: TextActor(0,0, L"", Graphics::getDefaultFont(), Color::BLACK)
	{
		//
	}
	
	TextActor::TextActor(const WideString&text, Font*font, const Color&color, unsigned int fontSize, int fontStyle, const TextActor::TextAlignment&align)
		: TextActor(0,0, text, font, color, fontSize, fontStyle, align)
	{
		//
	}
	
	TextActor::TextActor(double x1, double y1, const WideString&txt, Font*fnt, const Color&colr, unsigned int fontSize, int fontStyle, const TextActor::TextAlignment&align)
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
	
	void TextActor::drawActor(ApplicationData&appData, Graphics&graphics, double x, double y, double scale) const
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
			
			ArrayList<WideString> lines;
			TextActor::getLinesList(text, lines);
			
			double lineoffset = boundsrect.y;
			
			for(unsigned int i=0; i<lines.size(); i++)
			{
				const WideString&line = lines.get(i);
				const RectangleD&linerect = linerects.get(i);
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
					actorGraphics.drawString(line, (double)(boundsrect.width-linerect.width), lineoffset+linerect.y+linerect.height);
					break;
					
					case ALIGN_CENTER:
					actorGraphics.drawString(line, -linerect.width/2, lineoffset+linerect.y+linerect.height);
					break;
				}

				if(frame_visible)
				{
					RectangleD fixedLineRect;
					switch(alignment)
					{
						default:
						case ALIGN_BOTTOMLEFT:
						case ALIGN_TOPLEFT:
						fixedLineRect = RectangleD(0, lineoffset+linerect.y, linerect.width, linerect.height);
						break;
					
						case ALIGN_BOTTOMRIGHT:
						case ALIGN_TOPRIGHT:
						fixedLineRect = RectangleD((double)(boundsrect.width-linerect.width), lineoffset+linerect.y, linerect.width, linerect.height);
						break;
					
						case ALIGN_CENTER:
						fixedLineRect = RectangleD(-linerect.width/2, lineoffset+linerect.y, linerect.width, linerect.height);
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

			ArrayList<WideString> lines;
			TextActor::getLinesList(text, lines);

			RectangleD rect = RectangleD(0,0,0,0);
			linerects.clear();
			double offset_y = 0;
			double spacing = (double)lineSpacing;
			for(unsigned int i=0; i<lines.size(); i++)
			{
				const WideString&line = lines.get(i);
				Vector2u lineSize = font->measureString(line);
				double lineH = (double)lineSize.y;
				RectangleD linerect = RectangleD(0, offset_y, (double)lineSize.x, lineH);
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

	void TextActor::getLinesList(const WideString&text, ArrayList<WideString>&lines)
	{
		WideString currentLine;
		for(size_t i=0; i<text.length(); i++)
		{
			wchar_t c = text.charAt(i);
			if(c == L'\r')
			{
				if(i != (text.length() - 1))
				{
					if(text.charAt(i+1) == L'\n')
					{
						i++;
					}
				}
				lines.add(currentLine);
				currentLine.clear();
			}
			else if(c == L'\n')
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
	
	RectangleD TextActor::getBoundsRect(double width, double height) const
	{
		switch(alignment)
		{
			default:
			case ALIGN_BOTTOMLEFT:
			return RectangleD(0, -height, width, height);
			
			case ALIGN_BOTTOMRIGHT:
			return RectangleD(-width, -height, width, height);
			
			case ALIGN_CENTER:
			return RectangleD(-(width/2), -(height/2), width, height);
			
			case ALIGN_TOPLEFT:
			return RectangleD(0, 0, width, height);
			
			case ALIGN_TOPRIGHT:
			return RectangleD(-width, 0, width, height);
		}
	}

	RectangleD TextActor::getFrame() const
	{
		RectangleD frame = framerect;
		frame.x += x;
		frame.y += y;
		return frame;
	}
	
	void TextActor::scaleToFit(const RectangleD&container)
	{
		if(width == 0 || height == 0)
		{
			x = container.x + (container.width/2);
			y = container.y + (container.height/2);
			return;
		}
		RectangleD currentFrame = getFrame();
		RectangleD oldFrame = currentFrame;
		currentFrame.scaleToFit(container);
		double ratio = currentFrame.width/oldFrame.width;
		setScale(getScale()*ratio);
		RectangleD newFrame = getFrame();
		
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
	
	void TextActor::setText(const WideString&str)
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
	
	const WideString& TextActor::getText() const
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
	
	bool TextActor::checkPointCollision(const Vector2d&point)
	{
		if(text.length() == 0 || font==nullptr)
		{
			return false;
		}
		RectangleD frame = getFrame();
		double left = frame.x;
		double top = frame.y;
		double right = frame.x+frame.width;
		double bottom = frame.y+frame.height;
		if(point.x>left && point.y>top && point.x<right && point.y<bottom)
		{
			Vector2d pointFixed = point;
			pointFixed.x -= x;
			pointFixed.y -= y;
			
			pointFixed = inverseRotationMatrix.transform(pointFixed);
			
			double ratX = pointFixed.x/width;
			double ratY = pointFixed.y/height;

			double pxlX = (ratX*((double)boundsrect.width));
			double pxlY = (ratY*((double)boundsrect.height));

			double lineoffset = boundsrect.y;
			
			for(unsigned int i=0; i<linerects.size(); i++)
			{
				const RectangleD&linerect = linerects.get(i);
				RectangleD fixedLineRect;
				switch(alignment)
				{
					default:
					case ALIGN_BOTTOMLEFT:
					case ALIGN_TOPLEFT:
					fixedLineRect = RectangleD(0, lineoffset+linerect.y, linerect.width, linerect.height);
					break;
					
					case ALIGN_BOTTOMRIGHT:
					case ALIGN_TOPRIGHT:
					fixedLineRect = RectangleD((double)(boundsrect.width-linerect.width), lineoffset+linerect.y, linerect.width, linerect.height);
					break;
					
					case ALIGN_CENTER:
					fixedLineRect = RectangleD(-linerect.width/2, lineoffset+linerect.y, linerect.width, linerect.height);
					break;
				}

				if(fixedLineRect.contains(Vector2d(pxlX, pxlY)))
				{
					return true;
				}
			}
		}
		return false;
	}
}
