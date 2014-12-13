
#include "ScreenElement.h"
#include "Transition/Transition.h"
#include "../Utilities/ArrayList.h"

#pragma once

namespace GameLibrary
{
	class ScreenManager;

	class Screen : private ScreenElement
	{
		friend class Application;
		friend class ScreenManager;
	private:
		typedef struct
		{
			Screen* screen;
			Screen* transitionScreen;
			byte action;
			bool requiresInitializing;
			long long startTime;
			Transition* transition;
			double progress;
			unsigned long long duration;
			CompletionCallback completion;
			void* caller;
		} TransitionData;

		static void TransitionData_clear(TransitionData&data);
		static void TransitionData_begin(TransitionData&data, Screen*screen, Screen*transitionScreen, byte action, Transition*transition, unsigned long long duration, CompletionCallback completion, void*caller);
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

		TransitionData overlayData;

		Screen* parentScreen;
		Screen* childScreen;

		ScreenManager* screenManager;

		bool isrootscreen;

	protected:
		bool drawingOverlayTransition;

		virtual void drawBackground(ApplicationData&appData, Graphics&graphics);
		virtual void drawElements(ApplicationData&appData, Graphics&graphics);
		virtual void drawOverlay(ApplicationData&appData, Graphics&graphics);

	public:
		Screen();
		virtual ~Screen();

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics);

		virtual void willAppear(Transition* transition);
		virtual void didAppear(Transition* transition);

		virtual void willDisappear(Transition* transition);
		virtual void didDisappear(Transition* transition);

		void present(Screen*screen, Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);
		void dismiss(Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);

		Screen* getTopScreen();
		Screen* getBottomScreen();
		Screen* getRootScreen();
		bool isVisible();
	};
}