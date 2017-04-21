
#pragma once

#include "MenuBar.hpp"
#include "ArrowButton.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class MenuBarValueAdjust : public MenuBar
		{
		public:
			MenuBarValueAdjust(fgl::AssetManager* assetManager, const fgl::String& label, const fgl::Dictionary& properties);
			virtual ~MenuBarValueAdjust();
			
			void setValue(const fgl::Number& value);
			void setMinValue(const fgl::Number& minValue);
			void setMaxValue(const fgl::Number& maxValue);
			void setValueIncrement(const fgl::Number& increment);
			
			const fgl::Number& getValue() const;
			const fgl::Number& getMinValue() const;
			const fgl::Number& getMaxValue() const;
			const fgl::Number& getValueIncrement() const;
			
			void setValueStringResolver(const std::function<fgl::String(fgl::Number)>& valueResolver);
			const std::function<fgl::String(fgl::Number)>& getValueStringResolver() const;
			
			void setValueChangeHandler(const std::function<void()>& valueChangeHandler);
			const std::function<void()>& getValueChangeHandler() const;
			
			fgl::TextElement* getValueLabelElement() const;
			ArrowButton* getPreviousValueButton() const;
			ArrowButton* getNextValueButton() const;
			
		private:
			void applyProperties(const fgl::Dictionary& properties);
			
			void updateValueLabelString();
			
			fgl::TextElement* valueLabelElement;
			ArrowButton* prevValueButton;
			ArrowButton* nextValueButton;
			
			fgl::Number value;
			fgl::Number minValue;
			fgl::Number maxValue;
			fgl::Number increment;
			
			std::function<fgl::String(fgl::Number)> valueStringResolver;
			std::function<void()> valueChangeHandler;
		};
	}
}
