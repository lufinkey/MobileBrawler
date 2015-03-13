
#include "MenuBar.h"

namespace SmashBros
{
	namespace Menu
	{
		MenuBar::MenuBar(const WideString&label_text, AssetManager*assetManager, const Dictionary&properties)
			: MenuBar(0,0,label_text,assetManager,properties)
		{
			//
		}
		
		MenuBar::MenuBar(double x, double y, const WideString&label_text, AssetManager*assetManager, const Dictionary&properties) : SpriteActor(x, y)
		{
			addAnimation("MenuBar", new Animation(1, assetManager, "elements/menu_bar.png"));
			changeAnimation("MenuBar", Animation::FORWARD);
			
			autoLayout.setFrame(getFrame());
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			label_color = Color::BLACK;
			label_actor = new TextActor(label_text, font, label_color, 24, Font::STYLE_PLAIN, TextActor::ALIGN_BOTTOMLEFT);
			autoLayout.add(RectD(0.05, 0.05, 0.575, 0.95), label_actor);
			
			applyProperties(properties);
		}
		
		MenuBar::~MenuBar()
		{
			delete label_actor;
		}
		
		void MenuBar::updateSize()
		{
			SpriteActor::updateSize();
			autoLayout.setFrame(getFrame());
		}
		
		void MenuBar::applyProperties(const Dictionary&properties)
		{
			Any label_bounds_any = properties.get("label_bounds");
			if(!label_bounds_any.empty() && label_bounds_any.is<Dictionary>())
			{
				RectD label_bounds = autoLayout.get(label_actor);
				const Dictionary& label_bounds_dict = label_bounds_any.as<Dictionary>(false);
				applyPropertiesDict(&label_bounds, label_bounds_dict);
				autoLayout.set(label_actor, label_bounds);
			}
			Any label_color_any = properties.get("label_color");
			if(!label_color_any.empty() && label_color_any.is<Dictionary>())
			{
				const Dictionary& label_color_dict = label_color_any.as<Dictionary>(false);
				applyPropertiesDict(&label_color, label_color_dict);
				label_actor->setColor(label_color);
			}
		}
		
		void MenuBar::applyPropertiesDict(RectD*bounds, const Dictionary&properties)
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
				bounds->left = left.as<Number>(false).asDouble();
			}
			if(!top.empty() && top.is<Number>())
			{
				bounds->top = top.as<Number>(false).asDouble();
			}
			if(!right.empty() && right.is<Number>())
			{
				bounds->right = right.as<Number>(false).asDouble();
			}
			if(!bottom.empty() && bottom.is<Number>())
			{
				bounds->bottom = bottom.as<Number>(false).asDouble();
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
		
		RectangleD MenuBar::getLabelFrame(const RectD&bounds) const
		{
			RectangleD frame = getFrame();
			Vector2d topleft(bounds.left*frame.width, bounds.top*frame.height);
			Vector2d bottomright(bounds.right*frame.width, bounds.bottom*frame.height);
			return RectangleD(frame.x+topleft.x, frame.y+topleft.y, bottomright.x-topleft.x, bottomright.y-topleft.y);
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
		
		void MenuBar::setLabel(const WideString&text)
		{
			label_actor->setText(text);
			autoLayout.setFrame(getFrame());
		}
		
		void MenuBar::setLabelBounds(const RectD&bounds)
		{
			autoLayout.set(label_actor, bounds);
		}
		
		void MenuBar::setLabelAlignment(const TextActor::TextAlignment&alignment)
		{
			label_actor->setAlignment(alignment);
			autoLayout.setFrame(getFrame());
		}
		
		const WideString& MenuBar::getLabel() const
		{
			return label_actor->getText();
		}
		
		const RectD& MenuBar::getLabelBounds() const
		{
			return autoLayout.get(label_actor);
		}
		
		const TextActor::TextAlignment& MenuBar::getLabelAlignment() const
		{
			return label_actor->getAlignment();
		}
	}
}