
#include "MenuBar.h"

namespace SmashBros
{
	namespace Menu
	{
		MenuBar::MenuBar(float x, float y, const String&label_text, AssetManager*assetManager, const Dictionary&properties) : SpriteActor(x, y)
		{
			label_bounds = RectF(0.05f, 0.05f, 0.575f, 0.95f);//RectF(0.05f,0.05f,0.95f,0.95f);
			label_color = Color::BLACK;
			addAnimation("MenuBar", new Animation(1, assetManager, "elements/menu_bar.png"));
			changeAnimation("MenuBar", Animation::FORWARD);
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			label_actor = new TextActor(label_text, font, label_color, 24, Font::STYLE_PLAIN, TextActor::ALIGN_BOTTOMLEFT);
			
			applyProperties(properties);
		}
		
		MenuBar::~MenuBar()
		{
			delete label_actor;
		}
		
		void MenuBar::applyProperties(const Dictionary&properties)
		{
			Any label_bounds_any = properties.get("label_bounds");
			if(!label_bounds_any.empty() && label_bounds_any.is<Dictionary>())
			{
				const Dictionary& label_bounds_dict = label_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&label_bounds, label_bounds_dict);
			}
			Any label_color_any = properties.get("label_color");
			if(!label_color_any.empty() && label_color_any.is<Dictionary>())
			{
				const Dictionary& label_color_dict = label_color_any.as<Dictionary>(false);
				applyPropertiesDict(&label_color, label_color_dict);
			}
		}
		
		void MenuBar::applyPropertiesDict(RectF*bounds, const Dictionary&properties)
		{
			if(bounds == nullptr)
			{
				return;
			}
			Any left = properties.get("left");
			Any top = properties.get("top");
			Any right = properties.get("right");
			Any bottom = properties.get("bottom");
			if(!left.empty() && left.is<Number>())
			{
				bounds->left = left.as<Number>(false).asFloat();
			}
			if(!top.empty() && top.is<Number>())
			{
				bounds->top = top.as<Number>(false).asFloat();
			}
			if(!right.empty() && right.is<Number>())
			{
				bounds->right = right.as<Number>(false).asFloat();
			}
			if(!bottom.empty() && bottom.is<Number>())
			{
				bounds->bottom = bottom.as<Number>(false).asFloat();
			}
		}
		
		void MenuBar::applyPropertiesDict(Color*color, const Dictionary&properties)
		{
			if(color == nullptr)
			{
				return;
			}
			Any r = properties.get("r");
			Any g = properties.get("g");
			Any b = properties.get("b");
			Any a = properties.get("a");
			if(!r.empty() && r.is<Number>())
			{
				color->r = r.as<Number>(false).asUnsignedChar();
			}
			if(!g.empty() && g.is<Number>())
			{
				color->g = g.as<Number>(false).asUnsignedChar();
			}
			if(!b.empty() && b.is<Number>())
			{
				color->b = b.as<Number>(false).asUnsignedChar();
			}
			if(!a.empty() && a.is<Number>())
			{
				color->a = a.as<Number>(false).asUnsignedChar();
			}
		}
		
		RectangleF MenuBar::getLabelFrame(const RectF&bounds) const
		{
			RectangleF frame = getFrame();
			Vector2f topleft(bounds.left*frame.width, bounds.top*frame.height);
			Vector2f bottomright(bounds.right*frame.width, bounds.bottom*frame.height);
			return RectangleF(frame.x+topleft.x, frame.y+topleft.y, bottomright.x-topleft.x, bottomright.y-topleft.y);
		}
		
		void MenuBar::update(ApplicationData appData)
		{
			SpriteActor::update(appData);
			
			label_actor->setColor(label_color);
			label_actor->scaleToFit(getLabelFrame(label_bounds));
			label_actor->update(appData);
		}
		
		void MenuBar::draw(ApplicationData appData, Graphics graphics) const
		{
			SpriteActor::draw(appData, graphics);
			
			label_actor->setColor(label_color);
			label_actor->scaleToFit(getLabelFrame(label_bounds));
			label_actor->draw(appData, graphics);
		}
		
		void MenuBar::setLabel(const String&text)
		{
			label_actor->setText(text);
		}
		
		void MenuBar::setLabelBounds(const RectF&bounds)
		{
			label_bounds = bounds;
			label_actor->scaleToFit(getLabelFrame(label_bounds));
		}
		
		void MenuBar::setLabelAlignment(const TextActor::TextAlignment&alignment)
		{
			label_actor->setAlignment(alignment);
			label_actor->scaleToFit(getLabelFrame(label_bounds));
		}
		
		const String& MenuBar::getLabel() const
		{
			return label_actor->getText();
		}
		
		const RectF& MenuBar::getLabelBounds() const
		{
			return label_bounds;
		}
		
		const TextActor::TextAlignment& MenuBar::getLabelAlignment() const
		{
			return label_actor->getAlignment();
		}
	}
}