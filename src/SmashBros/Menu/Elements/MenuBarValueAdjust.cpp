
#include "MenuBarValueAdjust.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MenuBarValueAdjust::MenuBarValueAdjust(fgl::AssetManager* assetManager, const fgl::String& label, const fgl::Dictionary& properties)
			: MenuBar(assetManager, label, properties)
		{
			fgl::Font* font = assetManager->getFont("fonts/default.ttf");
			
			value = 0;
			minValue = 0;
			maxValue = 0;
			increment = 1;
			
			valueLabelElement = new fgl::TextElement();
			valueLabelElement->setFont(font);
			valueLabelElement->setFontSize(24);
			valueLabelElement->setTextColor(fgl::Color::BLACK);
			valueLabelElement->setTextAlignment(fgl::TEXTALIGN_CENTER);
			valueLabelElement->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
			valueLabelElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.65, fgl::LAYOUTVALUE_RATIO);
			valueLabelElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.05, fgl::LAYOUTVALUE_RATIO);
			valueLabelElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.1, fgl::LAYOUTVALUE_RATIO);
			valueLabelElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.05, fgl::LAYOUTVALUE_RATIO);
			addChildElement(valueLabelElement);
			
			prevValueButton = new ArrowButton(assetManager, ArrowButton::DIRECTION_LEFT);
			prevValueButton->setTapHandler([=]{
				auto newValue = value+increment;
				if(newValue <= maxValue)
				{
					value = newValue;
					updateValueLabelString();
					if(valueChangeHandler)
					{
						valueChangeHandler();
					}
				}
			});
			prevValueButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.6, fgl::LAYOUTVALUE_RATIO);
			prevValueButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.05, fgl::LAYOUTVALUE_RATIO);
			prevValueButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.35, fgl::LAYOUTVALUE_RATIO);
			prevValueButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.05, fgl::LAYOUTVALUE_RATIO);
			addChildElement(prevValueButton);
			
			nextValueButton = new ArrowButton(assetManager, ArrowButton::DIRECTION_RIGHT);
			nextValueButton->setTapHandler([=]{
				auto newValue = value-increment;
				if(newValue >= minValue)
				{
					value = newValue;
					updateValueLabelString();
					if(valueChangeHandler)
					{
						valueChangeHandler();
					}
				}
			});
			nextValueButton->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.9, fgl::LAYOUTVALUE_RATIO);
			nextValueButton->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.05, fgl::LAYOUTVALUE_RATIO);
			nextValueButton->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.05, fgl::LAYOUTVALUE_RATIO);
			nextValueButton->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.05, fgl::LAYOUTVALUE_RATIO);
			addChildElement(nextValueButton);
			
			valueStringResolver = [](fgl::Number number) -> fgl::String {
				return number.toString();
			};
			updateValueLabelString();
			
			applyProperties(properties);
		}
		
		MenuBarValueAdjust::~MenuBarValueAdjust()
		{
			delete valueLabelElement;
			delete prevValueButton;
			delete nextValueButton;
		}
		
		void MenuBarValueAdjust::applyProperties(const fgl::Dictionary& properties)
		{
			fgl::Any value_label_layoutRules_any = properties.get("value_label_layoutRules", fgl::Any());
			if(!value_label_layoutRules_any.isEmpty() && value_label_layoutRules_any.is<fgl::Dictionary>())
			{
				auto& value_label_layoutRules = value_label_layoutRules_any.as<fgl::Dictionary>();
				if(value_label_layoutRules.size() > 0)
				{
					valueLabelElement->setLayoutRules(value_label_layoutRules);
				}
			}
			fgl::Any value_label_color_any = properties.get("value_label_color", fgl::Any());
			if(!value_label_color_any.isEmpty() && value_label_color_any.is<fgl::Dictionary>())
			{
				auto& value_label_color_dict = value_label_color_any.as<fgl::Dictionary>();
				if(value_label_color_dict.size() > 0)
				{
					valueLabelElement->setTextColor(fgl::Color(value_label_color_dict));
				}
			}
			fgl::Any arrow_less_layoutRules_any = properties.get("arrow_less_layoutRules", fgl::Any());
			if(!arrow_less_layoutRules_any.isEmpty() && arrow_less_layoutRules_any.is<fgl::Dictionary>())
			{
				auto& arrow_less_layoutRules = arrow_less_layoutRules_any.as<fgl::Dictionary>();
				if(arrow_less_layoutRules.size() > 0)
				{
					prevValueButton->setLayoutRules(arrow_less_layoutRules);
				}
			}
			fgl::Any arrow_more_layoutRules_any = properties.get("arrow_more_layoutRules", fgl::Any());
			if(!arrow_more_layoutRules_any.isEmpty() && arrow_more_layoutRules_any.is<fgl::Dictionary>())
			{
				auto& arrow_more_layoutRules = arrow_more_layoutRules_any.as<fgl::Dictionary>();
				if(arrow_more_layoutRules.size() > 0)
				{
					nextValueButton->setLayoutRules(arrow_more_layoutRules);
				}
			}
		}
		
		void MenuBarValueAdjust::setValue(const fgl::Number& value_arg)
		{
			value = value_arg;
			updateValueLabelString();
		}
		
		const fgl::Number& MenuBarValueAdjust::getValue() const
		{
			return value;
		}
		
		void MenuBarValueAdjust::setMinValue(const fgl::Number& minValue_arg)
		{
			minValue = minValue_arg;
		}
		
		const fgl::Number& MenuBarValueAdjust::getMinValue() const
		{
			return minValue;
		}
		
		void MenuBarValueAdjust::setMaxValue(const fgl::Number& maxValue_arg)
		{
			maxValue = maxValue_arg;
		}
		
		const fgl::Number& MenuBarValueAdjust::getMaxValue() const
		{
			return maxValue;
		}
		
		void MenuBarValueAdjust::setValueIncrement(const fgl::Number& increment_arg)
		{
			increment = increment_arg;
		}
		
		const fgl::Number& MenuBarValueAdjust::getValueIncrement() const
		{
			return increment;
		}
		
		void MenuBarValueAdjust::setValueStringResolver(const std::function<fgl::String(fgl::Number)>& valueResolver)
		{
			valueStringResolver = valueResolver;
		}
		
		const std::function<fgl::String(fgl::Number)>& MenuBarValueAdjust::getValueStringResolver() const
		{
			return valueStringResolver;
		}
		
		void MenuBarValueAdjust::setValueChangeHandler(const std::function<void()>& valueChangeHandler_arg)
		{
			valueChangeHandler = valueChangeHandler_arg;
		}
		
		const std::function<void()>& MenuBarValueAdjust::getValueChangeHandler() const
		{
			return valueChangeHandler;
		}
		
		fgl::TextElement* MenuBarValueAdjust::getValueLabelElement() const
		{
			return valueLabelElement;
		}
		
		ArrowButton* MenuBarValueAdjust::getPreviousValueButton() const
		{
			return prevValueButton;
		}
		
		ArrowButton* MenuBarValueAdjust::getNextValueButton() const
		{
			return nextValueButton;
		}
		
		void MenuBarValueAdjust::updateValueLabelString()
		{
			if(valueStringResolver)
			{
				valueLabelElement->setText(valueStringResolver(value));
			}
		}
	}
}
