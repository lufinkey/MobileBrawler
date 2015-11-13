
#pragma once

#include "AutoLayoutManager.h"
#include "../Utilities/Geometry/Rectangle.h"

namespace GameLibrary
{
	class AutoLayoutCalculator
	{
	public:
		AutoLayoutCalculator(const RectangleD& currentFrame, const RectangleD& containerFrame);
		
		RectangleD getCalculatedFrame() const;
		
		void setLeft(double value, const LayoutValueType& valueType);
		void setTop(double value, const LayoutValueType& valueType);
		void setRight(double value, const LayoutValueType& valueType);
		void setBottom(double value, const LayoutValueType& valueType);
		
		void setCenterX(double value, const LayoutValueType& valueType);
		void setCenterY(double value, const LayoutValueType& valueType);
		
		void setWidth(double value, const LayoutValueType& valueType);
		void setHeight(double value, const LayoutValueType& valueType);
		
		void setAspectRatio(double value);
		
	private:
		class LayoutValue
		{
		public:
			LayoutValue();
			LayoutValue(const double& value);
			LayoutValue(const LayoutValue&);
			
			LayoutValue& operator=(const LayoutValue&);
			LayoutValue& operator=(const double& value);
			
			operator double() const;
			double getValue() const;
			
			void set();
			void unset();
			bool isSet() const;
			
		private:
			double value;
			bool isset;
		};
		
		double resolveValueX(double value, const LayoutValueType& valueType) const;
		double resolveValueY(double value, const LayoutValueType& valueType) const;
		
		void layoutAspectRatioFromWidth();
		void layoutAspectRatioFromHeight();
		
		RectangleD containerFrame;
		
		LayoutValue left;
		LayoutValue top;
		LayoutValue right;
		LayoutValue bottom;
		
		LayoutValue centerX;
		LayoutValue centerY;
		
		LayoutValue width;
		LayoutValue height;
		
		LayoutValue aspectRatio;
	};
}
