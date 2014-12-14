
#include "ScreenElement.h"
#include "Transition/Transition.h"
#include "../Utilities/ArrayList.h"

#pragma once

namespace GameLibrary
{
	class ScreenManager;

	class Screen : private ScreenElement
	{
		friend class ScreenManager;
	private:
		typedef struct
		{
			Screen* screen;
			Screen* transitionScreen;
			byte action;
			bool requiresInitializing;
			long long startTime;
			const Transition*transition;
			float progress;
			unsigned long long duration;
			CompletionCallback completion;
			void* caller;
		} TransitionData;

		static void TransitionData_clear(TransitionData&data);
		static void TransitionData_begin(TransitionData&data, Screen*screen, Screen*transitionScreen, byte action, const Transition*transition, unsigned long long duration, CompletionCallback completion, void*caller);
		/*Makes sure the TransitionData is initialized, if it requires it.*/
		static void TransitionData_checkInitialization(ApplicationData& appData, TransitionData&data);
		/*Applies any new progress to the transition.
		If the transition finishes, a constant representing the finished transition is returned. Otherwise, 0 is returned.*/
		static byte TransitionData_applyProgress(ApplicationData& appData, TransitionData&data);
		/*Checks if the transition is finished by calling TransitionData_applyProgress, and stores the objects that need calling if so.*/
		static void TransitionData_checkFinished(ApplicationData&appData, TransitionData&data, Screen**didDisappearCaller, Screen**didAppearCaller);
		static void TransitionData_callVirtualFunctions(TransitionData&data, Screen*didDisappearCaller, Screen*didAppearCaller);

		enum TransitionAction : byte
		{
			TRANSITION_NONE,
			TRANSITION_SHOW,
			TRANSITION_HIDE
		};

		Window* window;
		Vector2f size;

		TransitionData overlayData;

		Screen* parentScreen;
		Screen* childScreen;

		ScreenManager* screenManager;

		virtual void setWindow(Window*window);

	protected:
		mutable bool drawingOverlayTransition;

		virtual void drawBackground(ApplicationData appData, Graphics graphics) const;
		virtual void drawElements(ApplicationData appData, Graphics graphics) const;
		virtual void drawOverlay(ApplicationData appData, Graphics graphics) const;

	public:
		static const Transition* const defaultPresentTransition;

		Screen(Window*window);
		Screen();
		virtual ~Screen();

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		virtual Vector2f getSize() const;

		virtual void willAppear(const Transition*transition);
		virtual void didAppear(const Transition*transition);

		virtual void willDisappear(const Transition*transition);
		virtual void didDisappear(const Transition*transition);

		void present(Screen*screen, const Transition*transition=defaultPresentTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		void dismiss(const Transition*transition=defaultPresentTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);

		Screen* getTopScreen();
		Screen* getBottomScreen();
		Screen* getRootScreen();
		bool isVisible();

		void setBackgroundColor(const Color&);
		const Color& getBackgroundColor() const;
	};
}