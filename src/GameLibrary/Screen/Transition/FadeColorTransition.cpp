
#include "FadeColorTransition.h"

namespace GameLibrary
{
	FadeColorTransition::FadeColorTransition(const Color&c, double frozenPortn)
	{
		if(frozenPortn < 0 || frozenPortn > 1)
		{
			throw IllegalArgumentException("frozenPortion must be a value between 0 and 1");
		}
		color = c;
		frozenPortion = frozenPortn;
	}
	
	FadeColorTransition::~FadeColorTransition()
	{
		//
	}
	
	void FadeColorTransition::draw(ApplicationData appData, Graphics graphics, double progress, Drawable*element1, Drawable*element2) const
	{
		double firstPart = (1-frozenPortion)/2;
		double secondPart = 1-firstPart;
		if (progress < firstPart)
		{
			double alpha = ((double)progress / firstPart);
			
			RectangleD e1rect = element1->getFrame();
			Vector2d e1center = Vector2d(e1rect.x+(e1rect.width/2), e1rect.y+(e1rect.height/2));
			
			element1->draw(appData, graphics);
			
			graphics.setColor(color);
			graphics.compositeAlpha((byte)(alpha*255));
			graphics.fillRect(e1center.x-(e1rect.width/2), e1center.y-(e1rect.height/2), e1rect.width, e1rect.height);
		}
		else if(progress > secondPart)
		{
			double alpha = 1 - (((double)progress - secondPart) / firstPart);

			RectangleD e2rect = element2->getFrame();
			Vector2d e2center = Vector2d(e2rect.x+(e2rect.width/2), e2rect.y+(e2rect.height/2));
			
			element2->draw(appData, graphics);
			
			graphics.setColor(color);
			graphics.compositeAlpha((byte)(alpha*255));
			graphics.fillRect(e2center.x-(e2rect.width/2), e2center.y-(e2rect.height/2), e2rect.width, e2rect.height);
		}
		else
		{
			RectangleD e1rect = element1->getFrame();
			Vector2d e1center = Vector2d(e1rect.x+(e1rect.width/2), e1rect.y+(e1rect.height/2));
			
			graphics.setColor(color);
			graphics.fillRect(e1center.x-(e1rect.width/2), e1center.y-(e1rect.height/2), e1rect.width, e1rect.height);
		}
	}
}