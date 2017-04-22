
#include "MenuBar.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MenuBar::MenuBar(fgl::AssetManager* assetManager, const fgl::String& label, const fgl::Dictionary& properties)
		{
			assetManager->loadTexture("elements/menu_bar.png");
			
			backgroundElement = new fgl::ImageElement();
			backgroundElement->setImage(assetManager->getTexture("elements/menu_bar.png"));
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
			addChildElement(backgroundElement);
			
			fgl::Font* font = assetManager->getFont("fonts/default.ttf");
			
			labelElement = new fgl::TextElement();
			labelElement->setText(label);
			labelElement->setFont(font);
			labelElement->setFontSize(24);
			labelElement->setTextColor(fgl::Color::BLACK);
			labelElement->setTextAlignment(fgl::TEXTALIGN_LEFT);
			labelElement->setVerticalTextAlignment(fgl::VERTICALALIGN_BOTTOM);
			labelElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0.05, fgl::LAYOUTVALUE_RATIO);
			labelElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0.05, fgl::LAYOUTVALUE_RATIO);
			labelElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0.425, fgl::LAYOUTVALUE_RATIO);
			labelElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0.05, fgl::LAYOUTVALUE_RATIO);
			addChildElement(labelElement);
			
			applyProperties(properties);
		}
		
		MenuBar::~MenuBar()
		{
			delete labelElement;
			delete backgroundElement;
		}
		
		void MenuBar::applyProperties(const fgl::Dictionary& properties)
		{
			fgl::Any label_layoutRules_any = properties.get("label_layoutRules", fgl::Any());
			if(!label_layoutRules_any.isEmpty() && label_layoutRules_any.is<fgl::Dictionary>())
			{
				auto& label_layoutRules = label_layoutRules_any.as<fgl::Dictionary>();
				if(label_layoutRules.size() > 0)
				{
					labelElement->setLayoutRules(label_layoutRules);
				}
			}
			fgl::Any label_color_any = properties.get("label_color", fgl::Any());
			if(!label_color_any.isEmpty() && label_color_any.is<fgl::Dictionary>())
			{
				auto& label_color_dict = label_color_any.as<fgl::Dictionary>();
				if(label_color_dict.size() > 0)
				{
					labelElement->setTextColor(fgl::Color(label_color_dict));
				}
			}
		}

		fgl::ImageElement* MenuBar::getBackgroundElement() const
		{
			return backgroundElement;
		}

		fgl::TextElement* MenuBar::getLabelElement() const
		{
			return labelElement;
		}
	}
}
