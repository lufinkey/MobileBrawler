
#include "MenuBarValueAdjust.h"

namespace SmashBros
{
	namespace Menu
	{
		class MenuBarValueAdjust_ArrowButton : public ArrowButton
		{
		private:
			MenuBarValueAdjust* menuBar;
			
		public:
			MenuBarValueAdjust_ArrowButton(MenuBarValueAdjust*bar, double x, double y, Number*value, const Number&min, const Number&max, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hoverColor = Color::LIGHTBLUE, const Color&pressColor = Color::BLUE)
				: ArrowButton(x,y,value,min,max,increment,direction,assetManager,hoverColor,pressColor)
			{
				menuBar = bar;
			}
			
			virtual void onValueChange() override
			{
				MenuBarValueAdjustEventListener* listener = menuBar->getEventListener();
				if(listener != nullptr)
				{
					listener->onMenuBarValueAdjustValueChanged(menuBar);
				}
				menuBar->onValueChange();
			}
		};
		
		MenuBarValueAdjust::MenuBarValueAdjust(const String&label, const String&valueLabel, Number*value_arg, const Number&minimum, const Number&maximum, const Number&increment, AssetManager*assetManager, const Dictionary&properties)
			: MenuBarValueAdjust(0, 0, label, valueLabel, value_arg, minimum, maximum, increment, assetManager, properties)
		{
			//
		}

		MenuBarValueAdjust::MenuBarValueAdjust(double x, double y, const String&label, const String&valueLabel, Number*value_arg, const Number&minimum, const Number&maximum, const Number&increment, AssetManager*assetManager, const Dictionary&properties)
			: MenuBar(x,y,label,assetManager, properties)
		{
			value = value_arg;
			min = minimum;
			max = maximum;
			incr = increment;
			listener = nullptr;
			
			RectangleD frame = getFrame();
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			value_label_color = Color::BLACK;
			value_label_actor = new TextActor(valueLabel, font, value_label_color, 24, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
			value_label_autoLayoutMgr.setOffsetByContainer(true);
			value_label_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.65, LAYOUTVALUE_RATIO);
			value_label_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
			value_label_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.1, LAYOUTVALUE_RATIO);
			value_label_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
			value_label_actor->scaleToFit(value_label_autoLayoutMgr.calculateFrame(value_label_actor->getFrame(), frame));
			
			arrow_less_dir = "left";
			arrow_less = new MenuBarValueAdjust_ArrowButton(this, 0,0, value, min, max, -incr, ArrowButton::DIRECTION_LEFT, assetManager);
			arrow_less_autoLayoutMgr.setOffsetByContainer(true);
			arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.6, LAYOUTVALUE_RATIO);
			arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
			arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.35, LAYOUTVALUE_RATIO);
			arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
			arrow_less->scaleToFit(arrow_less_autoLayoutMgr.calculateFrame(arrow_less->getFrame(), frame));
			
			arrow_more_dir = "right";
			arrow_more = new MenuBarValueAdjust_ArrowButton(this, 0,0, value, min, max, incr, ArrowButton::DIRECTION_RIGHT, assetManager);
			arrow_more_autoLayoutMgr.setOffsetByContainer(true);
			arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.9, LAYOUTVALUE_RATIO);
			arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
			arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.05, LAYOUTVALUE_RATIO);
			arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
			arrow_more->scaleToFit(arrow_more_autoLayoutMgr.calculateFrame(arrow_more->getFrame(), frame));
			
			applyProperties(properties);
		}
		
		MenuBarValueAdjust::~MenuBarValueAdjust()
		{
			delete arrow_less;
			delete arrow_more;
			delete value_label_actor;
		}
		
		void MenuBarValueAdjust::updateSize()
		{
			MenuBar::updateSize();
			RectangleD frame = getFrame();
			value_label_actor->scaleToFit(value_label_autoLayoutMgr.calculateFrame(value_label_actor->getFrame(), frame));
			arrow_less->scaleToFit(arrow_less_autoLayoutMgr.calculateFrame(arrow_less->getFrame(), frame));
			arrow_more->scaleToFit(arrow_more_autoLayoutMgr.calculateFrame(arrow_more->getFrame(), frame));
		}
		
		void MenuBarValueAdjust::applyProperties(const Dictionary&properties)
		{
			Any value_label_layoutRules_any = properties.get("value_label_layoutRules", Any());
			if(!value_label_layoutRules_any.isEmpty() && value_label_layoutRules_any.is<Dictionary>())
			{
				const Dictionary& value_label_layoutRules = value_label_layoutRules_any.as<Dictionary>();
				applyPlacementDict(value_label_layoutRules, &value_label_autoLayoutMgr);
				if(!value_label_autoLayoutMgr.hasRules())
				{
					value_label_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.65, LAYOUTVALUE_RATIO);
					value_label_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
					value_label_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.1, LAYOUTVALUE_RATIO);
					value_label_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
				}
			}
			Any value_label_color_any = properties.get("value_label_color", Any());
			if(!value_label_color_any.isEmpty() && value_label_color_any.is<Dictionary>())
			{
				const Dictionary& value_label_color_dict = value_label_color_any.as<Dictionary>();
				applyColorDict(value_label_color_dict, &value_label_color);
				value_label_actor->setColor(value_label_color);
			}
			Any arrow_less_layoutRules_any = properties.get("arrow_less_layoutRules", Any());
			if(!arrow_less_layoutRules_any.isEmpty() && arrow_less_layoutRules_any.is<Dictionary>())
			{
				const Dictionary& arrow_less_layoutRules = arrow_less_layoutRules_any.as<Dictionary>();
				applyPlacementDict(arrow_less_layoutRules, &arrow_less_autoLayoutMgr);
				if(!arrow_less_autoLayoutMgr.hasRules())
				{
					arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.6, LAYOUTVALUE_RATIO);
					arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
					arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.35, LAYOUTVALUE_RATIO);
					arrow_less_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
				}
			}
			Any arrow_less_dir_any = properties.get("arrow_less_dir", Any());
			if(!arrow_less_dir_any.isEmpty() && arrow_less_dir_any.is<String>())
			{
				String arrow_less_dir = arrow_less_dir_any.as<String>();
				if(arrow_less_dir.equals("left"))
				{
					arrow_less->setDirection(ArrowButton::DIRECTION_LEFT);
				}
				else if(arrow_less_dir.equals("up"))
				{
					arrow_less->setDirection(ArrowButton::DIRECTION_UP);
				}
				else if(arrow_less_dir.equals("right"))
				{
					arrow_less->setDirection(ArrowButton::DIRECTION_RIGHT);
				}
				else if(arrow_less_dir.equals("down"))
				{
					arrow_less->setDirection(ArrowButton::DIRECTION_DOWN);
				}
			}
			Any arrow_more_layoutRules_any = properties.get("arrow_more_layoutRules", Any());
			if(!arrow_more_layoutRules_any.isEmpty() && arrow_more_layoutRules_any.is<Dictionary>())
			{
				const Dictionary& arrow_more_layoutRules = arrow_more_layoutRules_any.as<Dictionary>();
				applyPlacementDict(arrow_more_layoutRules, &arrow_more_autoLayoutMgr);
				if(!arrow_more_autoLayoutMgr.hasRules())
				{
					arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_LEFT, 0.9, LAYOUTVALUE_RATIO);
					arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_TOP, 0.05, LAYOUTVALUE_RATIO);
					arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_RIGHT, 0.05, LAYOUTVALUE_RATIO);
					arrow_more_autoLayoutMgr.setRule(LAYOUTRULE_BOTTOM, 0.05, LAYOUTVALUE_RATIO);
				}
			}
			Any arrow_more_dir_any = properties.get("arrow_more_dir", Any());
			if(!arrow_more_dir_any.isEmpty() && arrow_more_dir_any.is<String>())
			{
				String arrow_more_dir = arrow_more_dir_any.as<String>();
				if(arrow_more_dir.equals("left"))
				{
					arrow_more->setDirection(ArrowButton::DIRECTION_LEFT);
				}
				else if(arrow_more_dir.equals("up"))
				{
					arrow_more->setDirection(ArrowButton::DIRECTION_UP);
				}
				else if(arrow_more_dir.equals("right"))
				{
					arrow_more->setDirection(ArrowButton::DIRECTION_RIGHT);
				}
				else if(arrow_more_dir.equals("down"))
				{
					arrow_more->setDirection(ArrowButton::DIRECTION_DOWN);
				}
			}
			updateSize();
		}
		
		void MenuBarValueAdjust::update(ApplicationData appData)
		{
			MenuBar::update(appData);
			value_label_actor->update(appData);
			arrow_less->update(appData);
			arrow_more->update(appData);
		}
		
		void MenuBarValueAdjust::draw(ApplicationData appData, Graphics graphics) const
		{
			MenuBar::draw(appData, graphics);
			value_label_actor->draw(appData, graphics);
			arrow_less->draw(appData, graphics);
			arrow_more->draw(appData, graphics);
		}
		
		void MenuBarValueAdjust::onValueChange()
		{
			//Open for implementation
		}
		
		void MenuBarValueAdjust::setEventListener(MenuBarValueAdjustEventListener*eventListener)
		{
			listener = eventListener;
		}
		
		void MenuBarValueAdjust::setValueLabel(const String&label)
		{
			value_label_actor->setText(label);
			value_label_actor->scaleToFit(value_label_autoLayoutMgr.calculateFrame(value_label_actor->getFrame(), getFrame()));
		}
		
		MenuBarValueAdjustEventListener* MenuBarValueAdjust::getEventListener() const
		{
			return listener;
		}
		
		const String& MenuBarValueAdjust::getValueLabel() const
		{
			return value_label_actor->getText();
		}
		
		void MenuBarValueAdjust::setValueProperties(Number*value_arg, const Number&minimum, const Number&maximum, const Number&increment)
		{
			value = value_arg;
			min = minimum;
			max = maximum;
			incr = increment;
			arrow_less->setValueProperties(value_arg, minimum, maximum, -increment);
			arrow_more->setValueProperties(value_arg, minimum, maximum, increment);
		}
	}
}
