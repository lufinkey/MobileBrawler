
#include "MenuBar.h"

namespace SmashBros
{
	namespace Menu
	{
		MenuBar::MenuBar(const String&label_text, AssetManager*assetManager, const Dictionary&properties)
			: MenuBar(0,0,label_text,assetManager,properties)
		{
			//
		}
		
		MenuBar::MenuBar(double x, double y, const String&label_text, AssetManager*assetManager, const Dictionary&properties) : SpriteActor(x, y)
		{
			label_actor = nullptr;
			
			addAnimation("MenuBar", new Animation(1, assetManager, "elements/menu_bar.png"));
			changeAnimation("MenuBar", Animation::FORWARD);
			
			RectangleD frame = getFrame();
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			label_color = Color::BLACK;
			label_actor = new TextActor(label_text, font, label_color, 24, Font::STYLE_PLAIN, TextActor::ALIGN_BOTTOMLEFT);
			label_autoLayoutMgr.setOffsetByContainer(true);
			label_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.05, LAYOUTVALUE_RATIO);
			label_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
			label_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.425, LAYOUTVALUE_RATIO);
			label_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
			label_actor->scaleToFit(label_autoLayoutMgr.calculateFrame(label_actor->getFrame(), frame));
			
			applyProperties(properties);
		}
		
		MenuBar::~MenuBar()
		{
			delete label_actor;
		}
		
		void MenuBar::updateSize()
		{
			SpriteActor::updateSize();
			RectangleD frame = getFrame();
			if(label_actor!=nullptr)
			{
				label_actor->scaleToFit(label_autoLayoutMgr.calculateFrame(label_actor->getFrame(), frame));
			}
		}
		
		void MenuBar::applyProperties(const Dictionary&properties)
		{
			Any label_layoutRules_any = properties.get("label_layoutRules", Any());
			if(!label_layoutRules_any.isEmpty() && label_layoutRules_any.is<Dictionary>())
			{
				const Dictionary& label_layoutRules = label_layoutRules_any.as<Dictionary>();
				applyPlacementDict(label_layoutRules, &label_autoLayoutMgr);
				if(!label_autoLayoutMgr.hasRules())
				{
					label_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.05, LAYOUTVALUE_RATIO);
					label_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
					label_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.425, LAYOUTVALUE_RATIO);
					label_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
				}
			}
			Any label_color_any = properties.get("label_color", Any());
			if(!label_color_any.isEmpty() && label_color_any.is<Dictionary>())
			{
				const Dictionary& label_color_dict = label_color_any.as<Dictionary>();
				applyColorDict(label_color_dict, &label_color);
				label_actor->setColor(label_color);
			}
			updateSize();
		}
		
		void MenuBar::applyPlacementDict(const Dictionary& dict, AutoLayoutManager* layoutMgr)
		{
			layoutMgr->setRules(dict);
		}
		
		void MenuBar::applyColorDict(const Dictionary& dict, Color* color)
		{
			if(color == nullptr)
			{
				return;
			}
			Any r = dict.get("r", Any());
			Any g = dict.get("g", Any());
			Any b = dict.get("b", Any());
			Any a = dict.get("a", Any());
			if(!r.isEmpty() && r.is<Number>())
			{
				color->r = r.as<Number>().toArithmeticValue<byte>();
			}
			if(!g.isEmpty() && g.is<Number>())
			{
				color->g = g.as<Number>().toArithmeticValue<byte>();
			}
			if(!b.isEmpty() && b.is<Number>())
			{
				color->b = b.as<Number>().toArithmeticValue<byte>();
			}
			if(!a.isEmpty() && a.is<Number>())
			{
				color->a = a.as<Number>().toArithmeticValue<byte>();
			}
		}
		
		void MenuBar::update(ApplicationData appData)
		{
			SpriteActor::update(appData);
			label_actor->update(appData);
		}
		
		void MenuBar::draw(ApplicationData appData, Graphics graphics) const
		{
			SpriteActor::draw(appData, graphics);
			label_actor->draw(appData, graphics);
		}
		
		void MenuBar::setLabel(const String&text)
		{
			label_actor->setText(text);
			label_actor->scaleToFit(label_autoLayoutMgr.calculateFrame(label_actor->getFrame(), getFrame()));
		}
		
		void MenuBar::setLabelAlignment(const TextActor::TextAlignment&alignment)
		{
			label_actor->setAlignment(alignment);
			label_actor->scaleToFit(label_autoLayoutMgr.calculateFrame(label_actor->getFrame(), getFrame()));
		}
		
		const String& MenuBar::getLabel() const
		{
			return label_actor->getText();
		}
		
		AutoLayoutManager& MenuBar::getLabelAutoLayoutManager()
		{
			return label_autoLayoutMgr;
		}
		
		const AutoLayoutManager& MenuBar::getLabelAutoLayoutManager() const
		{
			return label_autoLayoutMgr;
		}
		
		const TextActor::TextAlignment& MenuBar::getLabelAlignment() const
		{
			return label_actor->getAlignment();
		}
	}
}
