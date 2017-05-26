
#include "MenuBar.hpp"

namespace SmashBros
{
	namespace Menu
	{
		MenuBar::MenuBar(fgl::AssetManager* assetManager, const fgl::String& label)
			: MenuBar(assetManager, label, getDefaultProperties(assetManager))
		{
			//
		}

		MenuBar::MenuBar(fgl::AssetManager* assetManager, const fgl::String& label, const fgl::Dictionary& properties)
		{
			backgroundElement = new fgl::ImageElement();
			backgroundElement->setImage(assetManager->loadTexture("elements/menu_bar.png"));
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_LEFT, 0);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_TOP, 0);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT, 0);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0);
			addChildElement(backgroundElement);
			
			labelElement = new fgl::TextElement();
			labelElement->setText(label);
			labelElement->setFontSize(24);
			labelElement->setTextColor(fgl::Color::BLACK);
			labelElement->setTextAlignment(fgl::TEXTALIGN_LEFT);
			labelElement->setVerticalTextAlignment(fgl::VERTICALALIGN_CENTER);
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

		fgl::Dictionary MenuBar::getDefaultProperties(fgl::AssetManager* assetManager)
		{
			FILE* file = assetManager->openFile("elements/menu_bar.plist", "rb");
			if(file!=nullptr)
			{
				fgl::Dictionary properties;
				fgl::Plist::loadFromFile(&properties, file);
				fgl::FileTools::closeFile(file);
				return properties;
			}
			return {};
		}
		
		void MenuBar::applyProperties(const fgl::Dictionary& properties)
		{
			auto label_layoutRules = fgl::extract<fgl::Dictionary>(properties, "label_layoutRules", {});
			if(label_layoutRules.size() > 0)
			{
				labelElement->setLayoutRules(label_layoutRules);
			}
			auto label_color = fgl::extract<fgl::Dictionary>(properties, "label_color", {});
			if(label_color.size() > 0)
			{
				labelElement->setTextColor(fgl::Color(label_color));
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
