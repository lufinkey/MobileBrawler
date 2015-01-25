
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

		MenuBarValueAdjust::MenuBarValueAdjust(float x, float y, const String&label, const String&valueLabel, Number*value_arg, const Number&minimum, const Number&maximum, const Number&increment, AssetManager*assetManager) : MenuBar(x,y,label,assetManager)
		{
			value = value_arg;
			min = minimum;
			max = maximum;
			incr = increment;
			
			setLabelBounds(RectF(0.05f, 0.05f, 0.6f, 0.95f));
			value_label_bounds = RectF(0.65f, 0.05f, 0.8f, 0.95f);
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			value_label_actor = new TextActor(valueLabel, font, Color::BLACK, 24, Font::STYLE_PLAIN, TextActor::ALIGN_CENTER);
			value_label_actor->scaleToFit(getLabelFrame(value_label_bounds));
			
			Vector2f arrow_less_pos(x-(getWidth()*0.125f), y);
			arrow_less = new MenuBarValueAdjust_ArrowButton(this, arrow_less_pos.x, arrow_less_pos.y, value, min, max, -incr, ArrowButton::DIRECTION_LEFT, assetManager);
			arrow_less->Actor::scaleToFit(Vector2f(getWidth(), getHeight()*1.1f));
			Vector2f arrow_more_pos(x+(getWidth()*0.325f), y);
			arrow_more = new MenuBarValueAdjust_ArrowButton(this, arrow_more_pos.x, arrow_more_pos.y, value, min, max, -incr, ArrowButton::DIRECTION_RIGHT, assetManager);
			arrow_more->Actor::scaleToFit(Vector2f(getWidth(), getHeight()*1.1f));
		}
		
		MenuBarValueAdjust::~MenuBarValueAdjust()
		{
			delete arrow_less;
			delete arrow_more;
			delete value_label_actor;
		}
		
		void MenuBarValueAdjust::update(ApplicationData appData)
		{
			MenuBar::update(appData);
			
			value_label_actor->scaleToFit(getLabelFrame(value_label_bounds));
			value_label_actor->update(appData);
			
			Vector2f arrow_less_pos(x-(getWidth()*0.125f), y);
			arrow_less->x = arrow_less_pos.x;
			arrow_less->y = arrow_less_pos.y;
			arrow_less->Actor::scaleToFit(Vector2f(getWidth(), getHeight()*1.1f));
			arrow_less->update(appData);
			
			Vector2f arrow_more_pos(x+(getWidth()*0.325f), y);
			arrow_more->x = arrow_more_pos.x;
			arrow_more->y = arrow_more_pos.y;
			arrow_more->Actor::scaleToFit(Vector2f(getWidth(), getHeight()*1.1f));
			arrow_more->update(appData);
		}
		
		void MenuBarValueAdjust::draw(ApplicationData appData, Graphics graphics) const
		{
			MenuBar::draw(appData, graphics);
			
			value_label_actor->scaleToFit(getLabelFrame(value_label_bounds));
			value_label_actor->draw(appData, graphics);
			
			Vector2f arrow_less_pos(x-(getWidth()*0.125f), y);
			arrow_less->x = arrow_less_pos.x;
			arrow_less->y = arrow_less_pos.y;
			arrow_less->Actor::scaleToFit(Vector2f(getWidth(), getHeight()*1.1f));
			arrow_less->draw(appData, graphics);
			
			Vector2f arrow_more_pos(x+(getWidth()*0.325f), y);
			arrow_more->x = arrow_more_pos.x;
			arrow_more->y = arrow_more_pos.y;
			arrow_more->Actor::scaleToFit(Vector2f(getWidth(), getHeight()*1.1f));
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
