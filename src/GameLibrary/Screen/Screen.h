
#pragma once

#include "ScreenElement.h"
#include "Transition/Transition.h"
#include "../Exception/IllegalStateException.h"
#include "../Utilities/ArrayList.h"

namespace GameLibrary
{
	class ScreenManager;
	
	/*! A callback that handles a completion of presenting, dismissing, pushing, or popping of a Screen*/
	typedef void(*CompletionCallback)(void*);

	/*! An drawable entity that can be used to separate different menus or screens of an Application. This class is non-copyable.*/
	class Screen : public Drawable
	{
		friend class ScreenManager;
	public:
		/*! The default Transition to use for presenting or dismissing Screen objects*/
		static const Transition* const defaultPresentTransition;
		
		/*! default constructor*/
		Screen();
		/*! Constructs a Screen to be the root Screen of a Window. Only one screen in any Screen stack should be delegated as the root Screen.
			\param window the Window that the Screen will be contained within*/
		Screen(Window*window);
		/*! virtual destructor*/
		virtual ~Screen();
		
		
		Screen(const Screen&) = delete;
		Screen& operator=(const Screen&) = delete;
		
		
		/*! Updates the properties of the Screen. This should NOT be overridden except for creating a custom Screen container.
		If overridden, the overriding function should first call the base class's update function, and then check if the Screen contains a child Screen before updating.
			\param appData specifies information about the Application updating the Screen, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData*/
		virtual void update(ApplicationData appData) override;
		/*! Draws the Screen and all of its children. This should NOT be overridden except for creating a custom Screen container.
		If overridden, the overriding function should first call the base class's draw function, and then check if the Screen contains a child Screen that is transitioning before drawing.
			\param appData specifies information about the Application drawing the Screen, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the Screen*/
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		
		/*! Gets the actual frame (bounding box) of the Screen inside the Window.
			\returns a RectangleD object representing the Screen's bounding box*/
		virtual RectangleD getFrame() const override;
		
		
		//TODO add events for navigation from ScreenManager
		
		
		/*! Called when the Screen's frame has changed, possibly due to frame resizing, or window resizing, or a mobile device orientation change.*/
		virtual void onFrameChange();
		
		
		/*! Called when the Screen is about to appear at the top level of the Screen stack.
			\param transition the Transition used to display the Screen, or null if no Transition was used*/
		virtual void onWillAppear(const Transition*transition);
		/*! Called when the Screen has just appeared at the top level of the Screen stack.
			\param transition the Transition used to display the Screen, or null if no Transition was used*/
		virtual void onDidAppear(const Transition*transition);
		/*! Called when the Screen is about to disappear off the top level of the Screen stack.
			\param transition the Transition used to hide the Screen, or null if no Transition was used*/
		virtual void onWillDisappear(const Transition*transition);
		/*! Called when the Screen has just disappeared off the top level of the Screen stack.
			\param transition the Transition used to hide the Screen, or null if no Transition was used*/
		virtual void onDidDisappear(const Transition*transition);
		
		
		/*! Presents another Screen on top of this Screen. Only one child Screen can be presented to a Screen at a time, but the top level Screen can always present another Screen.
			\param screen the Screen to present
			\param transition a Transition to use to present the Screen
			\param duration a length of time, in milliseconds, that the transition will last
			\param completion a callback to call when the Screen finishes the transition
			\throws GameLibrary::IllegalArgumentException if the Screen being presented is:\n
				1.) null
				2.) already presented on another Screen,\n
				3.) a root Screen \see GameLibrary::Screen::Screen(GameLibrary::Window*),\n
				4.) already held within a ScreenManager,\n
			\throws GameLibrary::ScreenNavigationException if a Screen is already in the process of being presented on this Screen*/
		void present(Screen*screen, const Transition*transition=defaultPresentTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		/*! Dismisses the child Screen that is presented on top of this Screen, or if no Screen is presented on top of this Screen, this Screen is dismissed from its parent Screen.
			\param transition a Transition to use to dismiss the Screen
			\param duration a length of time, in milliseconds, that the transition will last
			\param completion a callback to call when the Screen finishes the transition*/
		void dismiss(const Transition*transition=defaultPresentTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		
		
		/*! Gets the root ScreenElement.
			\returns a ScreenElement pointer*/
		ScreenElement* getElement();
		/*! Gets the ScreenManager that the Screen is contained within.
			\returns a ScreenManager pointer, or null if the Screen is not contained within a ScreenManager*/
		ScreenManager* getScreenManager() const;
		/*! Gets the parent Screen, or the Screen that is presenting this Screen.
			\returns a Screen pointer, or null if the Screen is not being presented on another Screen*/
		Screen* getParentScreen() const;
		/*! Gets the child Screen, or the Screen that this Screen is presenting.
			\returns a Screen pointer, or null if this Screen is not presenting another Screen*/
		Screen* getChildScreen() const;
		
		
		/*! Gets the top level Screen in this Screen's presentation stack.
			\returns a Screen pointer*/
		Screen* getTopScreen();
		/*! Gets the bottom level Screen in this Screen's presentation stack.
			\returns a Screen pointer*/
		Screen* getBottomScreen();
		/*! Gets the root level Screen of this entire Screen heirarchy, which includes ScreenManager containers.
			\returns a Screen pointer*/
		Screen* getRootScreen();
		/*! Tells whether the Screen is visible in the Screen heirarchy, or if another Screen is covering it.
			\returns true if the Screen is visible in the Screen heirarchy, or false if otherwise*/
		bool isVisible();
		/*! Tells whether this Screen is in the process of presenting a Screen.
			\returns true if a transition to present a Screen is occurring, or false if otherwise*/
		bool isPresenting() const;
		/*! Tells whether this Screen is in the process of dismissing a presented Screen.
			\returns true if a transition to dismiss a presented Screen is occurring, or false if otherwise*/
		bool isDismissing() const;
		
		
		/*! Sets the background color.
			\param color a Color value*/
		void setBackgroundColor(const Color&color);
		/*! Gets the background color.
			\returns a Color value*/
		const Color& getBackgroundColor() const;
		
	protected:
		/*! Updates the properties of the Screen. This function is called from within the update function, and should not manually be called.
		This function is safe to override with custom behavior.
			\param appData specifies information about the Application updating the Screen, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData*/
		virtual void onUpdate(ApplicationData appData);
		/*! Draws the Screen and any contents to the Window. This function is called from within the draw function, and should not be manually called.
		This function is safe to override with custom behavior.
			\param appData specifies information about the Application updating the Screen, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to Draw the Screen contents*/
		virtual void onDraw(ApplicationData appData, Graphics graphics) const;
		
		
		/*! Used to tell if the Screen is drawing an overlay. This value is only set within the draw function.
		An example of how to use this within the draw function is this:
		\code{.cpp}
			void draw(ApplicationData appData, Graphics graphics) const
			{
				if(!isPresenting() && !isDismissing())
				{
					drawBackground(appData, graphics);
					drawElements(appData, graphics);
					drawOverlay(appData, graphics);
				}
				else if(drawingOverlayTransition)
				{
					drawBackground(appData, graphics);
					drawElements(appData, graphics);
				}
				else
				{
					drawingOverlayTransition = true;
					drawOverlay(appData, graphics);
					drawingOverlayTransition = false;
				}
			}
		\endcode\n
		This is useful if making a custom Screen container, such as ScreenManager*/
		mutable bool drawingOverlayTransition;
		
		
		/*! Draws the background of the Screen. Should only be called within Screen::draw \see GameLibrary::Screen::drawingOverlayTransition for an example of how to call this
			\param appData specifies information about the Application drawing the Screen, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the Screen*/
		virtual void drawBackground(ApplicationData appData, Graphics graphics) const;
		/*! Draws the elements of the Screen. Should only be called within Screen::draw \see GameLibrary::Screen::drawingOverlayTransition for an example of how to call this
			\param appData specifies information about the Application drawing the Screen, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the Screen*/
		virtual void drawElements(ApplicationData appData, Graphics graphics) const;
		/*! Draws the presented Screen. Should only be called within Screen::draw \see GameLibrary::Screen::drawingOverlayTransition for an example of how to call this
			\param appData specifies information about the Application drawing the Screen, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the Screen*/
		virtual void drawOverlay(ApplicationData appData, Graphics graphics) const;
		
	private:
		typedef enum
		{
			TRANSITION_NONE,
			TRANSITION_SHOW,
			TRANSITION_HIDE
		} TransitionAction;
		
		typedef struct
		{
			Screen* screen;
			Screen* transitionScreen;
			TransitionAction action;
			bool requiresInitializing;
			long long startTime;
			const Transition*transition;
			double progress;
			unsigned long long duration;
			CompletionCallback completion;
			void* caller;
		} TransitionData;
		
		static void TransitionData_clear(TransitionData&data);
		static void TransitionData_begin(TransitionData&data, Screen*screen, Screen*transitionScreen, TransitionAction action, const Transition*transition, unsigned long long duration, CompletionCallback completion, void*caller);
		/*Makes sure the TransitionData is initialized, if it requires it.*/
		static void TransitionData_checkInitialization(ApplicationData& appData, TransitionData&data);
		/*Applies any new progress to the transition.
		If the transition finishes, a constant representing the finished transition is returned. Otherwise, 0 is returned.*/
		static byte TransitionData_applyProgress(ApplicationData& appData, TransitionData&data);
		/*Checks if the transition is finished by calling TransitionData_applyProgress, and stores the objects that need calling if so.*/
		static void TransitionData_checkFinished(ApplicationData&appData, TransitionData&data, Screen**onDidDisappearCaller, Screen**onDidAppearCaller);
		static void TransitionData_callVirtualFunctions(TransitionData&data, Screen*onDidDisappearCaller, Screen*onDidAppearCaller);
		
		Window* window;
		Vector2d framesize;
		Color backgroundColor;
		
		TransitionData overlayData;
		
		ScreenElement* element;
		Screen* parentScreen;
		Screen* childScreen;
		ScreenManager* screenManager;
		
		bool isshown;
		
		void updateFrame(Window*window);
		virtual void setWindow(Window*window);
	};
}