
#include "Screen.h"
#include "../Exception/Screen/ScreenNavigationException.h"
#include "../Utilities/ArrayList.h"

#pragma once

namespace GameLibrary
{
	class ScreenManager : public Screen
	{
		friend class Screen;
	private:
		TransitionData pushpopData;

		ArrayList<Screen*> screens;

		virtual void setWindow(Window*window);

	protected:
		void drawScreens(ApplicationData appData, Graphics graphics) const;

	public:
		static const Transition* const defaultPushTransition;

		ScreenManager(const ScreenManager&) = delete;
		ScreenManager(Screen*rootScreen);
		ScreenManager(Window*window, Screen*rootScreen);
		virtual ~ScreenManager();
		
		ScreenManager& operator=(const ScreenManager&) = delete;

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		virtual void onWillAppear(const Transition*transition);
		virtual void onDidAppear(const Transition*transition);

		virtual void onWillDisappear(const Transition*transition);
		virtual void onDidDisappear(const Transition*transition);

		void set(const ArrayList<Screen*>& screens, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		void push(Screen*screen, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		void push(const ArrayList<Screen*>& screens, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		Screen* pop(const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		ArrayList<Screen*> popTo(Screen*screen, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		ArrayList<Screen*> popToRoot(const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
	};
}