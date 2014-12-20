
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
		
		virtual RectangleF getFrame() const;
		
		ActorType getActorType() const;
		float getWidth() const;
		float getHeight() const;
		
		void setVisible(bool);
		void setColor(const Color&);
		void setRotation(float degrees);
		void setAlpha(float alpha);
		void setScale(float scale);
		void mirror(bool);
		void mirrorVertical(bool);
		
		bool isVisible() const;
		Color getColor() const;
		float getRotation() const;
		float getAlpha() const;
		float getScale() const;
		bool isMirrored() const;
		bool isMirroredVertical() const;
		
		virtual bool isOnScreen(View*view) const;
		
		bool isMouseOver() const;
		bool isMouseClicked() const;
		bool wasMouseClicked() const;
		bool didMouseClick() const;
		bool didMouseRelease() const;
		
	protected:
		virtual void updateSize();
		
	private:
		float width;
		float height;
		
		ActorType actorType;
		bool clicked;
		bool prevclicked;
		bool visible;
		bool mirrored;
		bool mirroredVertical;
		Color color;
		float rotation;
		float alpha;
		float scale;
	};
}
