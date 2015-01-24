
#pragma once

#include "Screen.h"
#include "../Exception/Screen/ScreenNavigationException.h"
#include "../Utilities/ArrayList.h"

namespace GameLibrary
{
	class ScreenManager : public Screen
	{
		friend class Screen;
	private:
		TransitionData pushpopData;

		ArrayList<Screen*> screens;

		virtual void setWindow(Window*window) override;

	protected:
		void drawScreens(ApplicationData appData, Graphics graphics) const;

	public:
		static const Transition* const defaultPushTransition;

		ScreenManager(const ScreenManager&) = delete;
		ScreenManager(Screen*rootScreen);
		ScreenManager(Window*window, Screen*rootScreen);
		virtual ~ScreenManager();
		
		ScreenManager& operator=(const ScreenManager&) = delete;

		virtual void update(ApplicationData appData) override;
		virtual void draw(ApplicationData appData, Graphics graphics) const override;

		virtual void onWillAppear(const Transition*transition) override;
		virtual void onDidAppear(const Transition*transition) override;

		virtual void onWillDisappear(const Transition*transition) override;
		virtual void onDidDisappear(const Transition*transition) override;

		void set(const ArrayList<Screen*>& screens, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		void push(Screen*screen, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		void push(const ArrayList<Screen*>& screens, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		Screen* pop(const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		ArrayList<Screen*> popTo(Screen*screen, const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
		ArrayList<Screen*> popToRoot(const Transition*transition=defaultPushTransition, unsigned long long duration=Transition::defaultDuration, CompletionCallback completion=nullptr);
	};
}