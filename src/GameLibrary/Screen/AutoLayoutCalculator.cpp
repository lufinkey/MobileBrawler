
#include "AutoLayoutCalculator.h"

namespace GameLibrary
{
	AutoLayoutCalculator::AutoLayoutCalculator(const RectangleD& currentFrame, const RectangleD& containerFrame)
		: containerFrame(containerFrame),
		left(currentFrame.x),
		top(currentFrame.y),
		right(currentFrame.x+currentFrame.width),
		bottom(currentFrame.y+currentFrame.height),
		centerX(currentFrame.x+(currentFrame.width/2)),
		centerY(currentFrame.y+(currentFrame.height/2)),
		width(currentFrame.width),
		height(currentFrame.height),
		aspectRatio(currentFrame.height!=0 ? (currentFrame.width/currentFrame.height) : 0)
	{
		//
	}
	
	RectangleD AutoLayoutCalculator::getCalculatedFrame() const
	{
		return RectangleD(left, top, right-left, bottom-top);
	}
	
	void AutoLayoutCalculator::setLeft(double value, const LayoutValueType& valueType)
	{
		if(left.isSet())
		{
			return;
		}
		
		left = resolveValueX(value, valueType);
		left.set();
		
		if(right.isSet())
		{
			width = right - left;
			width.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else if(width.isSet())
		{
			right = left + width;
			right.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else if(centerX.isSet())
		{
			width = 2*(centerX-left);
			width.set();
			right = left + width;
			right.set();
		}
		else
		{
			right = left + width;
			centerX = left + (width/2);
		}
		if(aspectRatio.isSet())
		{
			if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
			else if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
		}
	}
	
	void AutoLayoutCalculator::setTop(double value, const LayoutValueType& valueType)
	{
		if(top.isSet())
		{
			return;
		}

		top = resolveValueY(value, valueType);
		top.set();

		if(bottom.isSet())
		{
			height = bottom - top;
			height.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else if(height.isSet())
		{
			bottom = top + height;
			bottom.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else if(centerY.isSet())
		{
			height = 2*(centerY-top);
			height.set();
			bottom = top + height;
			bottom.set();
		}
		else
		{
			bottom = top + height;
			centerY = top + (height/2);
		}
		if(aspectRatio.isSet())
		{
			if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
			else if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
		}
	}
	
	void AutoLayoutCalculator::setRight(double value, const LayoutValueType& valueType)
	{
		if(right.isSet())
		{
			return;
		}

		right = resolveValueX(value, valueType);
		right.set();

		if(left.isSet())
		{
			width = right - left;
			width.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else if(width.isSet())
		{
			left = right - width;
			left.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else if(centerX.isSet())
		{
			width = 2*(right-centerX);
			width.set();
			left = right - width;
			left.set();
		}
		else
		{
			left = right - width;
			centerX = left + (width/2);
		}
		if(aspectRatio.isSet())
		{
			if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
			else if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
		}
	}
	
	void AutoLayoutCalculator::setBottom(double value, const LayoutValueType& valueType)
	{
		if(bottom.isSet())
		{
			return;
		}

		bottom = resolveValueY(value, valueType);
		bottom.set();

		if(top.isSet())
		{
			height = bottom - top;
			height.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else if(height.isSet())
		{
			top = bottom - height;
			top.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else if(centerY.isSet())
		{
			height = 2*(bottom-centerY);
			height.set();
			top = bottom - height;
			top.set();
		}
		else
		{
			top = bottom - height;
			centerY = top + (height/2);
		}
		if(aspectRatio.isSet())
		{
			if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
			else if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
		}
	}
	
	void AutoLayoutCalculator::setCenterX(double value, const LayoutValueType& valueType)
	{
		if(centerX.isSet())
		{
			return;
		}
		
		centerX = resolveValueX(value, valueType);
		centerX.set();

		if(left.isSet())
		{
			right = centerX + (centerX-left);
			right.set();
			width = right - left;
			width.set();
		}
		else if(right.isSet())
		{
			left = centerX - (right-centerX);
			left.set();
			width = right - left;
			width.set();
		}
		else if(width.isSet())
		{
			left = centerX - (width/2);
			left.set();
			right = left + width;
			right.set();
		}
		else
		{
			left = centerX - (width/2);
			right = left + width;
		}
		if(aspectRatio.isSet())
		{
			if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
			else if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
		}
	}
	
	void AutoLayoutCalculator::setCenterY(double value, const LayoutValueType& valueType)
	{
		if(centerY.isSet())
		{
			return;
		}

		centerY = resolveValueY(value, valueType);
		centerY.set();

		if(top.isSet())
		{
			bottom = centerY + (centerY-top);
			bottom.set();
			height = bottom - top;
			height.set();
		}
		else if(bottom.isSet())
		{
			top = centerY - (bottom-centerY);
			top.set();
			height = bottom - top;
			height.set();
		}
		else if(height.isSet())
		{
			top = centerY - (height/2);
			top.set();
			bottom = top + height;
			bottom.set();
		}
		else
		{
			top = centerY - (height/2);
			bottom = top + height;
		}
		if(aspectRatio.isSet())
		{
			if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
			else if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
		}
	}
	
	void AutoLayoutCalculator::setWidth(double value, const LayoutValueType& valueType)
	{
		if(width.isSet())
		{
			return;
		}
		
		width = resolveValueX(value, valueType);
		width.set();
		
		if(left.isSet())
		{
			right = left + width;
			right.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else if(right.isSet())
		{
			left = right - width;
			left.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else if(centerX.isSet())
		{
			left = centerX - (width/2);
			left.set();
			right = left + width;
			right.set();
		}
		else
		{
			right = left + width;
			centerX = left + (width/2);
		}
		if(aspectRatio.isSet())
		{
			if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
			else if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
		}
	}
	
	void AutoLayoutCalculator::setHeight(double value, const LayoutValueType& valueType)
	{
		if(height.isSet())
		{
			return;
		}

		height = resolveValueX(value, valueType);
		height.set();

		if(top.isSet())
		{
			bottom = top + height;
			bottom.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else if(bottom.isSet())
		{
			top = bottom - height;
			top.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else if(centerY.isSet())
		{
			top = centerY - (height/2);
			top.set();
			bottom = top + height;
			bottom.set();
		}
		else
		{
			bottom = top + height;
			centerY = top + (height/2);
		}
		if(aspectRatio.isSet())
		{
			if(height.isSet())
			{
				layoutAspectRatioFromHeight();
			}
			else if(width.isSet())
			{
				layoutAspectRatioFromWidth();
			}
		}
	}
	
	void AutoLayoutCalculator::setAspectRatio(double value)
	{
		if(aspectRatio.isSet())
		{
			return;
		}
		else if(width.isSet() && height.isSet())
		{
			if(height==0)
			{
				aspectRatio = 0;
			}
			else
			{
				aspectRatio = width/height;
			}
			aspectRatio.set();
			return;
		}
		
		aspectRatio = value;
		aspectRatio.set();
		
		if(width.isSet())
		{
			layoutAspectRatioFromWidth();
		}
		else if(height.isSet())
		{
			layoutAspectRatioFromHeight();
		}
	}
	
	double AutoLayoutCalculator::resolveValueX(double value, const LayoutValueType& valueType) const
	{
		switch(valueType)
		{
			case LAYOUTVALUE_PIXEL:
			return value;
			
			case LAYOUTVALUE_RATIO:
			return containerFrame.width*value;
		}
		return value;
	}
	
	double AutoLayoutCalculator::resolveValueY(double value, const LayoutValueType& valueType) const
	{
		switch(valueType)
		{
			case LAYOUTVALUE_PIXEL:
			return value;

			case LAYOUTVALUE_RATIO:
			return containerFrame.height*value;
		}
		return value;
	}
	
	void AutoLayoutCalculator::layoutAspectRatioFromWidth()
	{
		if(aspectRatio==0)
		{
			height = 0;
		}
		else
		{
			height = width/aspectRatio;
		}
		height.set();
		if(top.isSet())
		{
			bottom = top + height;
			bottom.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else if(bottom.isSet())
		{
			top = bottom - height;
			top.set();
			centerY = top + (height/2);
			centerY.set();
		}
		else
		{
			bottom = top + height;
			centerY = top + (height/2);
		}
	}
	
	void AutoLayoutCalculator::layoutAspectRatioFromHeight()
	{
		if(aspectRatio==0)
		{
			width = 0;
		}
		else
		{
			width = height*aspectRatio;
		}
		width.set();
		if(left.isSet())
		{
			right = left + width;
			right.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else if(right.isSet())
		{
			left = right - width;
			left.set();
			centerX = left + (width/2);
			centerX.set();
		}
		else
		{
			right = left + width;
			centerX = left + (width/2);
		}
	}
	
	AutoLayoutCalculator::LayoutValue::LayoutValue() : value(0), isset(false) {}
	AutoLayoutCalculator::LayoutValue::LayoutValue(const double& value) : value(value), isset(false) {}
	AutoLayoutCalculator::LayoutValue::LayoutValue(const LayoutValue& layoutValue) : value(layoutValue.value), isset(layoutValue.isset) {}
	
	AutoLayoutCalculator::LayoutValue& AutoLayoutCalculator::LayoutValue::operator=(const LayoutValue& layoutValue)
	{
		value = layoutValue.value;
		isset = layoutValue.isset;
		return *this;
	}
	
	AutoLayoutCalculator::LayoutValue& AutoLayoutCalculator::LayoutValue::operator=(const double& val)
	{
		value = val;
		return *this;
	}
	
	AutoLayoutCalculator::LayoutValue::operator double() const
	{
		return value;
	}
	
	double AutoLayoutCalculator::LayoutValue::getValue() const
	{
		return value;
	}
	
	void AutoLayoutCalculator::LayoutValue::set()
	{
		isset = true;
	}
	
	void AutoLayoutCalculator::LayoutValue::unset()
	{
		isset = false;
	}
	
	bool AutoLayoutCalculator::LayoutValue::isSet() const
	{
		return isset;
	}
}
