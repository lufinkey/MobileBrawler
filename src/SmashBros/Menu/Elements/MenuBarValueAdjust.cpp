
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
			MenuBarValueAdjust_ArrowButton(MenuBarValueAdjust*bar, float x, float y, Number*value, const Number&min, const Number&max, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hoverColor = Color::LIGHTBLUE, const Color&pressColor = Color::BLUE)
				: ArrowButton(x,y,value,min,max,increment,direction,assetManager,hoverColor,pressColor)
			{
				menuBar = bar;
			}
			
			virtual void onValueChange() override
			{
				menuBar->onValueChange();
			}
		};

		MenuBarValueAdjust::MenuBarValueAdjust(float x, float y, const String&label, const String&valueLabel, Number*value_arg, const Number&minimum, const Number&maximum, const Number&increment, AssetManager*assetManager, const Dictionary&properties)
			: MenuBar(x,y,label,assetManager, properties)
		{
			value = value_arg;
			min = minimum;
			max = maximum;
			incr = increment;
			
			value_label_bounds = RectF(0.65f, 0.05f, 0.9f, 0.95f);
			value_label_color = Color::BLACK;
			arrow_less_bounds = RectF(0.6f, 0.05f, 0.65f, 0.95f);
			arrow_less_dir = "left";
			arrow_more_bounds = RectF(0.9f, 0.05f, 0.95f, 0.95f);
			arrow_more_dir = "right";
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			value_label_actor = new TextActor(valueLabel, font, Color::BLACK, 24, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
			value_label_actor->scaleToFit(getLabelFrame(value_label_bounds));
			
			Vector2f arrow_less_pos(x+(getWidth()*0.125f), y);
			arrow_less = new MenuBarValueAdjust_ArrowButton(this, arrow_less_pos.x, arrow_less_pos.y, value, min, max, -incr, ArrowButton::DIRECTION_LEFT, assetManager);
			arrow_less->scaleToFit(arrow_less_bounds);
			Vector2f arrow_more_pos(x+(getWidth()*0.425f), y);
			arrow_more = new MenuBarValueAdjust_ArrowButton(this, arrow_more_pos.x, arrow_more_pos.y, value, min, max, incr, ArrowButton::DIRECTION_RIGHT, assetManager);
			arrow_more->scaleToFit(arrow_more_bounds);
			
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
				const Dictionary& value_label_bounds_dict = value_label_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&value_label_bounds, value_label_bounds_dict);
			}
			Any value_label_color_any = properties.get("value_label_color");
			if(!value_label_color_any.empty() && value_label_color_any.is<Dictionary>())
			{
				const Dictionary& value_label_color_dict = value_label_color_any.as<Dictionary>(false);
				applyPropertiesDict(&value_label_color, value_label_color_dict);
			}
			Any arrow_less_bounds_any = properties.get("arrow_less_bounds");
			if(!arrow_less_bounds_any.empty() && arrow_less_bounds_any.is<Dictionary>())
			{
				const Dictionary& arrow_less_bounds_dict = arrow_less_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&arrow_less_bounds, arrow_less_bounds_dict);
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
				const Dictionary& arrow_more_bounds_dict = arrow_more_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&arrow_more_bounds, arrow_more_bounds_dict);
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
			
			value_label_actor->setColor(value_label_color);
			value_label_actor->scaleToFit(getLabelFrame(value_label_bounds));
			value_label_actor->update(appData);
			
			arrow_less->scaleToFit(getLabelFrame(arrow_less_bounds));
			arrow_less->update(appData);
			
			arrow_more->scaleToFit(getLabelFrame(arrow_more_bounds));
			arrow_more->update(appData);
		}
		
		void MenuBarValueAdjust::draw(ApplicationData appData, Graphics graphics) const
		{
			MenuBar::draw(appData, graphics);
			
			value_label_actor->setColor(value_label_color);
			value_label_actor->scaleToFit(getLabelFrame(value_label_bounds));
			value_label_actor->draw(appData, graphics);
			
			arrow_less->scaleToFit(getLabelFrame(arrow_less_bounds));
			arrow_less->draw(appData, graphics);
			
			arrow_more->scaleToFit(getLabelFrame(arrow_more_bounds));
			arrow_more->draw(appData, graphics);
		}
		
		void MenuBarValueAdjust::onValueChange()
		{
			//Open for implementation
		}
		
		void MenuBarValueAdjust::setValueLabel(const String&label)
		{
			value_label_actor->setText(label);
		}
		
		const String& MenuBarValueAdjust::getValueLabel() const
		{
			return value_label_actor->getText();
		}
	}
}
