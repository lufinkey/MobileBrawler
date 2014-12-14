
#include "../Screen/Drawable.h"

#pragma once

namespace GameLibrary
{
	class BaseActor : public Drawable
	{
		friend class Actor;
		friend class TextActor;
		friend class WireframeActor;
	public:
		enum ActorType : byte
		{
			ACTORTYPE_BASE,
			ACTORTYPE_NORMAL,
			ACTORTYPE_WIREFRAME,
			ACTORTYPE_TEXT
		};
		typedef enum ActorType ActorType;
		
		float x;
		float y;
		
		BaseActor();
		BaseActor(const BaseActor&) = delete;
		virtual ~BaseActor();
		
		BaseActor& operator=(const BaseActor&) = delete;

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;
		
		ActorType getActorType() const;
		float getWidth() const;
		float getHeight() const;
		
		void setVisible(bool);
		void setColor(const Color&);
		void setRotation(float degrees);
		void setAlpha(float alpha);
		void setScale(float scale);

		bool isVisible() const;
		Color getColor() const;
		float getRotation() const;
		float getAlpha() const;
		float getScale() const;

		virtual bool isOnScreen(View*view) const;

		virtual bool isMouseClicked() const;
		virtual bool wasMouseClicked() const;
		virtual bool didMouseClick() const;
		virtual bool didMouseRelease() const;

		virtual RectangleF getFrame() const;
		
	private:
		float width;
		float height;
		
		ActorType actorType;
		bool clicked;
		bool prevclicked;
		bool visible;
		Color color;
		float rotation;
		float alpha;
		float scale;
	};
}
