
#pragma once

#include "ScreenElement.h"
#include "Transition/Transition.h"
#include "../Exception/IllegalStateException.h"
#include "../Utilities/ArrayList.h"

namespace GameLibrary
{
	class ScreenManager;

	//TODO change to publically inheriting Drawable
	class Screen : public Drawable
	{
		friend class ScreenManager;
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
			float progress;
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
		Vector2f framesize;
		Color backgroundColor;

		TransitionData overlayData;

		ScreenElement* element;
		Screen* parentScreen;
		Screen* childScreen;
		ScreenManager* screenManager;

		bool isshown;

		void updateFrame(Window*window);
		virtual void setWindow(Window*window);

	protected:
		mutable bool drawingOverlayTransition;

		virtual void drawBackground(ApplicationData appData, Graphics graphics) const;
		virtual void drawElements(ApplicationData appData, Graphics graphics) const;
		virtual void drawOverlay(ApplicationData appData, Graphics graphics) const;

	public:
		static const Transition* const defaultPresentTransition;

		Screen();
		Screen(const Screen&) = delete;
		Screen(Window*window);
		virtual ~Screen();
		
		Screen& operator=(const Screen&) = delete;

		virtual void update(ApplicationData appData) override;
		virtual void onUpdate(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		virtual void onDraw(ApplicationData appData, Graphics graphics) const;
		
		virtual RectangleF getFrame() const override;
		
		//TODO add events for navigation from ScreenManager
		
		virtual void onWillAppear(const Transition*transition);
		virtual void onDidAppear(const Transition*transition);

		virtual void onWillDisappear(const Transition*transition);
		virtual void onDidDisappear(const Transition*transition);

		void present(Screen*screen, const Transition*transition=defaultPresentTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		void dismiss(const Transition*transition=defaultPresentTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);

		ScreenElement* getElement();
		ScreenManager* getScreenManager() const;
		Screen* getParentScreen() const;
		Screen* getChildScreen() const;

		Screen* getTopScreen();
		Screen* getBottomScreen();
		Screen* getRootScreen();
		bool isVisible();
		
		void setBackgroundColor(const Color&);
		const Color& getBackgroundColor() const;
	};
}