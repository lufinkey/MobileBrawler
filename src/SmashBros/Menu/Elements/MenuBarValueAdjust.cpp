
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
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			value_label_color = Color::BLACK;
			value_label_actor = new TextActor(valueLabel, font, value_label_color, 24, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
			autoLayout.add(RectD(0.65, 0.05, 0.9, 0.95), value_label_actor);
			
			arrow_less_dir = "left";
			arrow_less = new MenuBarValueAdjust_ArrowButton(this, 0,0, value, min, max, -incr, ArrowButton::DIRECTION_LEFT, assetManager);
			autoLayout.add(RectD(0.6, 0.05, 0.65, 0.95), arrow_less);
			
			arrow_more_dir = "right";
			arrow_more = new MenuBarValueAdjust_ArrowButton(this, 0,0, value, min, max, incr, ArrowButton::DIRECTION_RIGHT, assetManager);
			autoLayout.add(RectD(0.9, 0.05, 0.95, 0.95), arrow_more);
			
			applyProperties(properties);
		}
		
		MenuBarValueAdjust::~MenuBarValueAdjust()
		{
			delete arrow_less;
			delete arrow_more;
			delete value_label_actor;
		}
		
		void MenuBarValueAdjust::applyProperties(const Dictionary&properties)
		{
			Any value_label_bounds_any = properties.get("value_label_bounds");
			if(!value_label_bounds_any.empty() && value_label_bounds_any.is<Dictionary>())
			{
				RectD value_label_bounds = autoLayout.get(value_label_actor);
				const Dictionary& value_label_bounds_dict = value_label_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&value_label_bounds, value_label_bounds_dict);
				autoLayout.set(value_label_actor, value_label_bounds);
			}
			Any value_label_color_any = properties.get("value_label_color");
			if(!value_label_color_any.empty() && value_label_color_any.is<Dictionary>())
			{
				const Dictionary& value_label_color_dict = value_label_color_any.as<Dictionary>(false);
				applyPropertiesDict(&value_label_color, value_label_color_dict);
				value_label_actor->setColor(value_label_color);
			}
			Any arrow_less_bounds_any = properties.get("arrow_less_bounds");
			if(!arrow_less_bounds_any.empty() && arrow_less_bounds_any.is<Dictionary>())
			{
				RectD arrow_less_bounds = autoLayout.get(arrow_less);
				const Dictionary& arrow_less_bounds_dict = arrow_less_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&arrow_less_bounds, arrow_less_bounds_dict);
				autoLayout.set(arrow_less, arrow_less_bounds);
			}
			Any arrow_less_dir_any = properties.get("arrow_less_dir");
			if(!arrow_less_dir_any.empty() && arrow_less_dir_any.is<String>())
			{
				String arrow_less_dir = arrow_less_dir_any.as<String>(false);
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
			Any arrow_more_bounds_any = properties.get("arrow_more_bounds");
			if(!arrow_more_bounds_any.empty() && arrow_more_bounds_any.is<Dictionary>())
			{
				RectD arrow_more_bounds = autoLayout.get(arrow_more);
				const Dictionary& arrow_more_bounds_dict = arrow_more_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&arrow_more_bounds, arrow_more_bounds_dict);
				autoLayout.set(arrow_more, arrow_more_bounds);
			}
			Any arrow_more_dir_any = properties.get("arrow_more_dir");
			if(!arrow_more_dir_any.empty() && arrow_more_dir_any.is<String>())
			{
				String arrow_more_dir = arrow_more_dir_any.as<String>(false);
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
			autoLayout.setFrame(getFrame());
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
