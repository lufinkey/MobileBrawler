
#pragma once

#include "Actor.h"
#include "Animation.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Exception/IllegalStateException.h"

namespace GameLibrary
{
	class SpriteActorAnimationEvent
	{
		friend class SpriteActor;
	public:
		/*! copy constructor*/
		SpriteActorAnimationEvent(const SpriteActorAnimationEvent&);
		/*! assignment operator*/
		SpriteActorAnimationEvent& operator=(const SpriteActorAnimationEvent&);
		/*! default constructor*/
		explicit SpriteActorAnimationEvent(SpriteActor* target, const String& name, Animation* animation);
		
		
		/*! Gives the target of the animation event. The target is the SpriteActor which the event was performed on.
			\returns a SpriteActor pointer*/
		SpriteActor* getTarget() const;
		/*! Gives the user-defined identifier of the Animation.
			\returns a string representing an identifier*/
		const String& getAnimationName() const;
		/*! Gives the pointer to the Animation that was changed in the event.
			\returns an Animation pointer*/
		Animation* getAnimation() const;
		
	private:
		SpriteActor* target;
		String name;
		Animation* animation;
	};
	
	/*! A specialized Actor that can draw and animate images.
		\see GameLibrary::Animation*/
	class SpriteActor : public Actor
	{
	public:
		/*! default constructor*/
		SpriteActor();
		/*! Constructs a SpriteActor with the specified x and y coordinates
			\param x the x coordinate
			\param y the y coordinate*/
		SpriteActor(double x, double y);
		/*! virtual destructor*/
		virtual ~SpriteActor();
		
		
		/*! \copydoc GameLibrary::Actor::update(GameLibrary::ApplicationData)*/
		virtual void update(ApplicationData appData) override;
		/*! \copydoc GameLibrary::Actor::draw(GameLibrary::ApplicationData,GameLibrary::Graphics)const*/
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		
		/*! \copydoc GameLibrary::Actor::getFrame()const*/
		virtual RectangleD getFrame() const override;
		
		
		/*! Scales and repositions the Actor to fit within the specified container
			\param container the frame to fit the Actor into.
			\note this function will not work correctly if the Actor's scale value is set to 0*/
		virtual void scaleToFit(const RectangleD&container) override;
		
		
		/*! Adds an Animation. The Animation object's deallocation becomes manually managed by the SpriteActor, unless specified otherwise.
			\throws GameLibrary::IllegalArgumentException if the SpriteActor already contains an Animation with the specified identifier
			\param name a user-defined identifier for the Animation
			\param animation the Animation to be added.
			\param destruct specify true to tell the SpriteActor to deallocate the Animation when destroyed, false to manually deallocate the memory for the Animation
			\throws GameLibrary::IllegalArgumentException if the given name is an empty string, if an animation with the same name is already added, or if the given animation pointer is null*/
		void addAnimation(const String&name, Animation*animation, bool destruct=true);
		/*! Removes the Animation with the specified identifier from the SpriteActor. If the Animation was added with the destruct parameter set to true, the Animation is deallocated.
			\param name the user-defined identifier for the Animation*/
		void removeAnimation(const String&name);
		/*! Tells whether an Animation with the specified identifier has been added through SpriteActor::addAnimation.
			\param name the user-defined identifier for the Animation
			\returns true if an Animation has been added witht the specified name, and false if otherwise*/
		bool hasAnimation(const String&name) const;
		/*! Gets the Animation object with the specified identifier.
			\param name the user-defined identifier of the Animation
			\returns an Animation object, or null if there is no Animation with the specified identifier*/
		Animation* getAnimation(const String&name) const;
		/*! Changes the current Animation to the Animation with the specified identifier.
			\param name the user-defined identifier of the Animation
			\param direction the direction to iterate through the Animation frames
			\throws GameLibrary::IllegalArgumentException if the given name does not match an animation name in this SpriteActor*/
		void changeAnimation(const String&name, const Animation::Direction&direction = Animation::Direction::FORWARD);
		/*! Changes the current animation to a given animation pointer. This animation is given an empty string for a name, and is not stored in or managed by the SpriteActor.
			\param animation a pointer to an Animation
			\param direction the direction to iterate through the Animation frames*/
		void changeAnimation(Animation*animation, const Animation::Direction&direction = Animation::Direction::FORWARD);
		/*! Loads and re-stores the images for each frame of each Animation. Calls Animation::reloadFrames for each Animation.
			\param assetManager the AssetManager to load the images from. If null, the images for each frame are set to null.*/
		void reloadAnimations(AssetManager*assetManager);
		
		
		/*! Calculates whether this SpriteActor's pixels are overlapping with another SpriteActor's pixels. Transparent pixels are ignored.
			\param actor the SpriteActor to check overlapping pixels with.
			\returns true if the SpriteActor is colliding, and false if otherwise.*/
		bool isColliding(SpriteActor*actor) const;
		
		
		/*! \copydoc GameLibrary::Actor::updateSize()*/
		virtual void updateSize() override;
		/*! \copydoc GameLibrary::Actor::checkPointCollision(const Vector2d&)*/
		virtual bool checkPointCollision(const Vector2d&point) override;
		
	protected:
		/*! Called when the SpriteActor finishes running through the frames of the current Animation.
			\param evt contains information about the event*/
		virtual void onAnimationFinish(const SpriteActorAnimationEvent& evt);
		
		/*! Special draw function to draw the SpriteActor with specific properties. These properties are not stored into the SpriteActor. This function is called from SpriteActor::draw
			\param appData specifies information about the Application drawing the SpriteActor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the SpriteActor
			\param x the x coordinate
			\param y the y coordinate
			\param scale the ratio to size the SpriteActor from its default size*/
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, double x, double y, double scale) const;
		
	private:
		typedef struct
		{
			String name;
			Animation* animation;
			bool destruct;
		} AnimationInfo;
		
		ArrayList<AnimationInfo> animations;
		
		String animation_name;
		Animation* animation_current;
		unsigned int animation_frame;
		long long animation_prevFrameTime;
		Animation::Direction animation_direction;

		Vector2d framesize;
		
		bool firstUpdate;
		long long prevUpdateTime;
	};
}
