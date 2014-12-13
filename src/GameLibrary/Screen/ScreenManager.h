
#include "Screen.h"
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

	protected:
		void drawScreens(ApplicationData&appData, Graphics&graphics);

	public:
		ScreenManager(Screen*rootScreen);
		virtual ~ScreenManager();

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics);

		virtual void willAppear(Transition* transition);
		virtual void didAppear(Transition* transition);

		virtual void willDisappear(Transition* transition);
		virtual void didDisappear(Transition* transition);

		void set(const ArrayList<Screen*>& screens, Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);
		void push(Screen*screen, Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);
		void push(const ArrayList<Screen*>& screens, Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);
		Screen* pop(Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);
		ArrayList<Screen*> popTo(Screen*screen, Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);
		ArrayList<Screen*> popToRoot(Transition*const transition=nullptr, unsigned long long duration=250, CompletionCallback completion=nullptr);
	};
}