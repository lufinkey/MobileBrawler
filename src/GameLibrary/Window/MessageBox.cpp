
#include "MessageBox.h"
#include <SDL.h>

namespace GameLibrary
{
	#if !defined(TARGETPLATFORM_IOS)
	unsigned int MessageBox::show(Window*parent, const String&title, const String&message)
	{
		SDL_Window*window = nullptr;
		if(parent != nullptr)
		{
			window = (SDL_Window*)parent->getWindowData();
		}
		int buttonid = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, window);
		return (unsigned int)buttonid;
	}
	
	unsigned int MessageBox::show(Window*parent, const String&title, const String&message, const ArrayList<String>&options)
	{
		SDL_Window*window = nullptr;
		if(parent != nullptr)
		{
			window = (SDL_Window*)parent->getWindowData();
		}
		int numOptions = (int)options.size();
		SDL_MessageBoxButtonData*buttons = new SDL_MessageBoxButtonData[options.size()];
		for(int i=0; i<numOptions; i++)
		{
			SDL_MessageBoxButtonData button = {0, (int)i, (const char*)options[i]};
			buttons[i] = button;
		}
		SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION, window, (const char*)title, (const char*)message, numOptions, buttons, NULL};
		int buttonid = 0;
		SDL_ShowMessageBox(&messageBoxData, &buttonid);
		delete[] buttons;
		return (unsigned int)buttonid;
	}
	#endif
}
