
#include "MenuBar.h"

namespace SmashBros
{
	namespace Menu
	{
		MenuBar::MenuBar(float x, float y, const String&label_text, AssetManager*assetManager, const Dictionary&properties) : SpriteActor(x, y)
		{
			label_bounds = RectF(0.05f,0.05f,0.95f,0.95f);
			addAnimation("MenuBar", new Animation(1, assetManager, "elements/menu_bar.png"));
			changeAnimation("MenuBar", Animation::FORWARD);
			
			Font* font = assetManager->getFont("fonts/default.ttf");
			label_actor = new TextActor(label_text, font, Color::BLACK, 24, Font::STYLE_PLAIN, TextActor::ALIGN_BOTTOMLEFT);
		}
		
		MenuBar::~MenuBar()
		{
			delete label_actor;
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
			
			label_actor->scaleToFit(getLabelFrame(label_bounds));
			label_actor->update(appData);
		}
		
		void MenuBar::draw(ApplicationData appData, Graphics graphics) const
		{
			SpriteActor::draw(appData, graphics);
			
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