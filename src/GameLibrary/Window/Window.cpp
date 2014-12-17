
#include "Window.h"
#include "../Application/EventManager.h"
#include "../Utilities/PlatformChecks.h"
#include <SDL.h>
#include <SDL_syswm.h>

#if defined(TARGETPLATFORM_WINDOWS)
	#include <Windows.h>
#endif

namespace GameLibrary
{
//WindowSettings implementation

	WindowSettings::WindowSettings()
	{
		position = Vector2i(Window::POSITION_UNDEFINED, Window::POSITION_UNDEFINED);
		size = Vector2u(640,480);
		title = "Program";
		icon = nullptr;
		backgroundColor = Color::WHITE;
		style = Window::STYLE_DEFAULT;
	}

	WindowSettings::WindowSettings(const WindowSettings&windowSettings)
	{
		position = windowSettings.position;
		size = windowSettings.size;
		title = windowSettings.title;
		icon = windowSettings.icon;
		backgroundColor = windowSettings.backgroundColor;
		style = windowSettings.style;
	}

	WindowSettings::WindowSettings(const Vector2i& pos, const Vector2u& sz, const String&ttl, Image*ico, const Color&bgcolor, byte sty)
	{
		position = pos;
		size = sz;
		title = ttl;
		icon = ico;
		backgroundColor = bgcolor;
		style = sty;
	}

	WindowSettings::~WindowSettings()
	{
		//
	}

	WindowSettings& WindowSettings::operator=(const WindowSettings&windowSettings)
	{
		position = windowSettings.position;
		size = windowSettings.size;
		title = windowSettings.title;
		icon = windowSettings.icon;
		backgroundColor = windowSettings.backgroundColor;
		style = windowSettings.style;

		return *this;
	}
		
	void WindowSettings::setPosition(const Vector2i&pos)
	{
		position = pos;
	}

	const Vector2i& WindowSettings::getPosition() const
	{
		return position;
	}
		
	void WindowSettings::setSize(const Vector2u&sz)
	{
		size = sz;
	}

	const Vector2u& WindowSettings::getSize() const
	{
		return size;
	}
		
	void WindowSettings::setTitle(const String&ttl)
	{
		title = ttl;
	}

	const String& WindowSettings::getTitle() const
	{
		return title;
	}
	
	void* WindowSettings::createIconData() const
	{
		void*icondata = nullptr;
		if(icon != nullptr)
		{
			const ArrayList<Color>& pixels = icon->getPixels();
			if(pixels.size()>0)
			{
				icondata = (void*)SDL_CreateRGBSurfaceFrom((void*)pixels.getData(), (int)icon->getWidth(), (int)icon->getHeight(), 32, (int)(icon->getWidth()*4), 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
			}
		}
		return icondata;
	}
	
	void WindowSettings::setIcon(Image*ico)
	{
		icon = ico;
	}

	const Image* WindowSettings::getIcon() const
	{
		return icon;
	}
	
	void WindowSettings::setBackgroundColor(const Color&bgcolor)
	{
		backgroundColor = bgcolor;
	}
	
	const Color& WindowSettings::getBackgroundColor() const
	{
		return backgroundColor;
	}
	
	void WindowSettings::setStyle(byte sty)
	{
		style = sty;
	}
	
	byte WindowSettings::getStyle() const
	{
		return style;
	}
	
//Window implementation
	
	const WindowSettings Window::defaultDesktopSettings = WindowSettings(Vector2i(Window::POSITION_UNDEFINED, Window::POSITION_UNDEFINED), Vector2u(640, 480), "", nullptr, Color::WHITE, Window::STYLE_DEFAULT);
	const WindowSettings Window::defaultMobileSettings = WindowSettings(Vector2i(Window::POSITION_UNDEFINED, Window::POSITION_UNDEFINED), Vector2u(480, 320), "", nullptr, Color::WHITE, Window::STYLE_BORDERLESS);
	
	Window::Window()
	{
		windowed_size = settings.size;
		view = nullptr;
		windowdata = nullptr;
		windowID = 0;
		icondata = nullptr;
		graphics = nullptr;
	}
	
	Window::~Window()
	{
		if(windowdata != nullptr)
		{
			destroy();
		}
		if(view != nullptr)
		{
			delete view;
			view = nullptr;
		}
		if(icondata != nullptr)
		{
			SDL_FreeSurface((SDL_Surface*)icondata);
			icondata = nullptr;
		}
	}
	
	void Window::create(const WindowSettings&windowSettings)
	{
		if(windowdata != nullptr)
		{
			destroy();
		}
		
		int positionx = 0;
		int positiony = 0;
		#ifndef TARGETPLATFORM_MOBILE
			if(windowSettings.position.x == Window::POSITION_CENTERED)
			{
				positionx = SDL_WINDOWPOS_CENTERED;
			}
			else if(windowSettings.position.x == Window::POSITION_UNDEFINED)
			{
				positionx = SDL_WINDOWPOS_UNDEFINED;
			}
			if(windowSettings.position.y == Window::POSITION_CENTERED)
			{
				positiony = SDL_WINDOWPOS_CENTERED;
			}
			else if(windowSettings.position.y == Window::POSITION_UNDEFINED)
			{
				positiony = SDL_WINDOWPOS_UNDEFINED;
			}
		#endif
		
		unsigned int flags = 0;
		byte style = windowSettings.style;
		if(style != Window::STYLE_DEFAULT)
		{
			if((style & Window::STYLE_BORDERLESS) == Window::STYLE_BORDERLESS)
			{
				flags = flags | SDL_WINDOW_BORDERLESS;
			}
			if((style & Window::STYLE_FULLSCREEN) == Window::STYLE_FULLSCREEN)
			{
				flags = flags | SDL_WINDOW_FULLSCREEN;
			}
			if((style & Window::STYLE_HIDDEN) == Window::STYLE_HIDDEN)
			{
				flags = flags | SDL_WINDOW_HIDDEN;
			}
			else
			{
				flags = flags | SDL_WINDOW_SHOWN;
			}
			if((style & Window::STYLE_RESIZABLE) == Window::STYLE_RESIZABLE)
			{
				flags = flags | SDL_WINDOW_RESIZABLE;
			}
			if((style & Window::STYLE_MINIMIZED) == Window::STYLE_MINIMIZED)
			{
				flags = flags | SDL_WINDOW_MINIMIZED;
			}
			else if((style & Window::STYLE_MAXIMIZED) == Window::STYLE_MAXIMIZED)
			{
				flags = flags | SDL_WINDOW_MAXIMIZED;
			}
		}
		else
		{
			flags = flags | SDL_WINDOW_SHOWN;
		}
		
		windowdata = (void*)SDL_CreateWindow(windowSettings.title,positionx,positiony,windowSettings.size.x,windowSettings.size.y, flags | SDL_WINDOW_OPENGL);
		if(windowdata == nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception(SDL_GetError());
		}
		windowID = SDL_GetWindowID((SDL_Window*)windowdata);
		
		if(windowSettings.getIcon()!=nullptr)
		{
			icondata = windowSettings.createIconData();
			if(icondata!=nullptr)
			{
				SDL_SetWindowIcon((SDL_Window*)windowdata, (SDL_Surface*)icondata);
			}
		}
		
		bool createdView = false;
		if(view == nullptr)
		{
			view = new View((float)windowed_size.x, (float)windowed_size.y);
			createdView = true;
		}
		
		try
		{
			graphics = new Graphics(*this);
		}
		catch(const Exception&e)
		{
			SDL_DestroyWindow((SDL_Window*)windowdata);
			windowdata = nullptr;
			windowID = 0;
			if(createdView)
			{
				delete view;
				view = nullptr;
			}
			if(icondata!=nullptr)
			{
				SDL_FreeSurface((SDL_Surface*)icondata);
				icondata = nullptr;
			}
			//TODO replace with more specific exception type
			throw Exception(e);
		}
		
		settings = windowSettings;
#ifdef TARGETPLATFORM_MOBILE
		settings.position.x = 0;
		settings.position.y = 0;
#endif
		if((style & Window::STYLE_FULLSCREEN) != Window::STYLE_FULLSCREEN)
		{
			windowed_size = windowSettings.size;
		}
		else
		{
			if(view!=nullptr)
			{
				Vector2f viewSize = view->getSize();
				windowed_size = Vector2u((unsigned int)viewSize.x, (unsigned int)viewSize.y);
			}
			else
			{
				windowed_size = windowSettings.size;
			}
		}

		assetManager = new AssetManager(*this);

		EventManager::addWindow(this);
	}
	
	void Window::update()
	{
		if(windowdata!=nullptr)
		{
			//SDL_GL_SwapWindow((SDL_Window*)windowdata);
			SDL_RenderPresent((SDL_Renderer*)graphics->renderer);
			graphics->reset(settings.getBackgroundColor());
		}
	}
	
	void Window::destroy()
	{
		if(windowdata != nullptr)
		{
			SDL_DestroyWindow((SDL_Window*)windowdata);
			windowdata = nullptr;
			delete graphics;
			graphics = nullptr;
			delete assetManager;
			assetManager = nullptr;
			settings = WindowSettings();
			if(view != nullptr)
			{
				delete view;
				view = nullptr;
			}
			EventManager::removeWindow(this);
			windowID = 0;
		}
	}
	
	Image*Window::capture()
	{
		if(windowdata == nullptr)
		{
			return nullptr;
		}

		Image*img = new Image();
		img->create(settings.size.x, settings.size.y);
		if(SDL_RenderReadPixels((SDL_Renderer*)graphics->renderer, nullptr, SDL_PIXELFORMAT_RGBA8888, (void*)(img->getPixels().getData()), settings.size.x * 4) < 0)
		{
			//TODO replace with more specific exception type
			throw Exception(SDL_GetError());
		}
		return img;
	}
	
	Graphics* Window::getGraphics()
	{
		return graphics;
	}
	
	AssetManager* Window::getAssetManager()
	{
		return assetManager;
	}
	
	Rectangle Window::getDisplayBounds(unsigned int displayIndex)
	{
		SDL_Rect rect;
		if(SDL_GetDisplayBounds((int)displayIndex, &rect) == 0)
		{
			return Rectangle(rect.x,rect.y,rect.w,rect.h);
		}
		return Rectangle();
	}
	
	const Vector2i& Window::getPosition()
	{
		if(windowdata != nullptr)
		{
			int x = 0;
			int y = 0;
			SDL_GetWindowPosition((SDL_Window*)windowdata,&x,&y);
			settings.setPosition(Vector2i(x,y));
		}
		return settings.position;
	}
	
	void Window::setPosition(const Vector2i&pos)
	{
		if(windowdata!=nullptr)
		{
			#ifndef TARGETPLATFORM_MOBILE
				settings.setPosition(pos);
				SDL_SetWindowPosition((SDL_Window*)windowdata,pos.x,pos.y);
			#endif
		}
	}
	
	const Vector2u& Window::getSize()
	{
		if(windowdata != nullptr)
		{
			int w = 0;
			int h = 0;
			SDL_GetWindowSize((SDL_Window*)windowdata,&w,&h);
			settings.setSize(Vector2u((unsigned int)w,(unsigned int)h));
			if((settings.style & Window::STYLE_FULLSCREEN) != Window::STYLE_FULLSCREEN)
			{
				windowed_size = settings.size;
			}
		}
		return settings.size;
	}

	void Window::setSize(const Vector2u&size)
	{
		if(windowdata != nullptr)
		{
			if((settings.style & Window::STYLE_FULLSCREEN) == Window::STYLE_FULLSCREEN)
			{
				if(SDL_SetWindowFullscreen((SDL_Window*)windowdata, 0) < 0)
				{
					return;
				}
				settings.style = settings.style & ~Window::STYLE_FULLSCREEN;
			}
			settings.setSize(size);
			windowed_size = size;
			SDL_SetWindowSize((SDL_Window*)windowdata,(int)size.x,(int)size.y);
			if(view != nullptr && view->matchesWindow())
			{
				view->setSize((float)size.x, (float)size.y);
			}
		}
	}

	const String& Window::getTitle()
	{
		if(windowdata != nullptr)
		{
			settings.setTitle(SDL_GetWindowTitle((SDL_Window*)windowdata));
		}
		return settings.title;
	}

	void Window::setTitle(const String&title)
	{
		if(windowdata != nullptr)
		{
			settings.setTitle(title);
			SDL_SetWindowTitle((SDL_Window*)windowdata, title);
		}
	}

	const Color& Window::getBackgroundColor()
	{
		return settings.getBackgroundColor();
	}

	void Window::setBackgroundColor(const Color&bgcolor)
	{
		settings.setBackgroundColor(bgcolor);
	}

	const Image* Window::getIcon()
	{
		return settings.icon;
	}

	void Window::setIcon(Image*icon)
	{
		if(windowdata != nullptr)
		{
			settings.setIcon(icon);
			if(icondata != nullptr)
			{
				SDL_FreeSurface((SDL_Surface*)icondata);
				icondata = nullptr;
			}
			if(icon == nullptr)
			{
				SDL_SetWindowIcon((SDL_Window*)windowdata, nullptr);
			}
			else
			{
				icondata = settings.createIconData();
				SDL_SetWindowIcon((SDL_Window*)windowdata, (SDL_Surface*)icondata);
			}
		}
	}

	View* Window::getView()
	{
		return view;
	}
	
	bool Window::isOpen()
	{
		if(windowdata != nullptr)
		{
			return true;
		}
		return false;
	}

	bool Window::isFocused()
	{
		if(windowdata != nullptr)
		{
			unsigned int flags = SDL_GetWindowFlags((SDL_Window*)windowdata);
			if((flags & SDL_WINDOW_INPUT_FOCUS) == SDL_WINDOW_INPUT_FOCUS)
			{
				return true;
			}
		}
		return false;
	}

	bool Window::isVisible()
	{
		if(windowdata != nullptr)
		{
			unsigned int flags = SDL_GetWindowFlags((SDL_Window*)windowdata);
			if((flags & SDL_WINDOW_SHOWN) == SDL_WINDOW_SHOWN)
			{
				settings.setStyle(settings.style & ~Window::STYLE_HIDDEN);
				return true;
			}
			else
			{
				settings.setStyle(settings.style | Window::STYLE_HIDDEN);
			}
		}
		return false;
	}

	void Window::setVisible(bool toggle)
	{
		if(windowdata != nullptr)
		{
			unsigned int flags = SDL_GetWindowFlags((SDL_Window*)windowdata);
			if(toggle)
			{
				if((flags & SDL_WINDOW_HIDDEN) == SDL_WINDOW_HIDDEN)
				{
					SDL_ShowWindow((SDL_Window*)windowdata);
				}
			}
			else
			{
				if((flags & SDL_WINDOW_SHOWN) == SDL_WINDOW_SHOWN)
				{
					SDL_HideWindow((SDL_Window*)windowdata);
				}
			}
		}
	}

	bool Window::isFullscreen()
	{
		if(windowdata != nullptr)
		{
			unsigned int flags = SDL_GetWindowFlags((SDL_Window*)windowdata);
			if((flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
			{
				settings.setStyle(settings.style | Window::STYLE_FULLSCREEN);
				return true;
			}
			else
			{
				settings.setStyle(settings.style & ~Window::STYLE_FULLSCREEN);
			}
		}
		return false;
	}

	void Window::setFullscreen(bool toggle)
	{
		setFullscreen(toggle, windowed_size.x, windowed_size.y);
	}

	void Window::setFullscreen(bool toggle, unsigned int width, unsigned int height)
	{
		if(windowdata != nullptr)
		{
			unsigned int flags = SDL_GetWindowFlags((SDL_Window*)windowdata);
			if(toggle)
			{
				if((flags & SDL_WINDOW_FULLSCREEN) != SDL_WINDOW_FULLSCREEN)
				{
					Vector2u oldsize = settings.size;
					SDL_SetWindowSize((SDL_Window*)windowdata, (int)width, (int)height);
					if(SDL_SetWindowFullscreen((SDL_Window*)windowdata, SDL_WINDOW_FULLSCREEN)==0)
					{
						settings.setStyle(settings.style | Window::STYLE_FULLSCREEN);
						settings.setSize(Vector2u(width,height));
						windowed_size = oldsize;
						if(view != nullptr && view->matchesWindow())
						{
							view->setSize((float)width, (float)height);
						}
					}
					else
					{
						SDL_SetWindowSize((SDL_Window*)windowdata, (int)oldsize.x, (int)oldsize.y);
					}
				}
			}
			else
			{
				if((flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
				{
					if(SDL_SetWindowFullscreen((SDL_Window*)windowdata, 0)==0)
					{
						settings.setStyle(settings.style & ~Window::STYLE_FULLSCREEN);
						SDL_SetWindowSize((SDL_Window*)windowdata, (int)width, (int)height);
						if(view != nullptr && view->matchesWindow())
						{
							view->setSize((float)width, (float)height);
						}
					}
				}
			}
		}
	}
	
	void Window::addEventListener(WindowEventListener*listener)
	{
		listenermutex.lock();
		eventListeners.add(listener);
		listenermutex.unlock();
	}
	
	void Window::removeEventListener(WindowEventListener*listener)
	{
		listenermutex.lock();
		unsigned int index = eventListeners.indexOf(listener);
		if(index != ARRAYLIST_NOTFOUND)
		{
			eventListeners.remove(index);
		}
		listenermutex.unlock();
	}
	
	void Window::callListenerEvent(byte eventType, int x, int y, bool external)
	{
		listenermutex.lock();
		ArrayList<WindowEventListener*> listeners = eventListeners;
		listenermutex.unlock();

		for(unsigned int i = 0; i<listeners.size(); i++)
		{
			WindowEventListener* listener = listeners.get(i);
			switch(eventType)
			{
				case SDL_WINDOWEVENT_SHOWN:
				listener->onWindowShown(this);
				break;

				case SDL_WINDOWEVENT_HIDDEN:
				listener->onWindowHidden(this);
				break;

				case SDL_WINDOWEVENT_EXPOSED:
				listener->onWindowExposed(this);
				break;

				case SDL_WINDOWEVENT_MOVED:
				listener->onWindowMoved(this, Vector2f((float)x, (float)y));
				break;

				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				listener->onWindowResized(this, Vector2u((unsigned int)x,(unsigned int)y), external);
				break;

				case SDL_WINDOWEVENT_MINIMIZED:
				listener->onWindowMinimize(this);
				break;

				case SDL_WINDOWEVENT_MAXIMIZED:
				listener->onWindowMinimize(this);
				break;

				case SDL_WINDOWEVENT_RESTORED:
				listener->onWindowRestore(this);
				break;

				case SDL_WINDOWEVENT_ENTER:
				listener->onWindowMouseEnter(this);
				break;

				case SDL_WINDOWEVENT_LEAVE:
				listener->onWindowMouseLeave(this);
				break;

				case SDL_WINDOWEVENT_FOCUS_GAINED:
				listener->onWindowFocusGained(this);
				break;

				case SDL_WINDOWEVENT_FOCUS_LOST:
				listener->onWindowFocusLost(this);
				break;

				case SDL_WINDOWEVENT_CLOSE:
				listener->onWindowClose(this);
				break;
			}
		}
	}

	void Window::getHandlePtr(void*ptr) const
	{
		if(windowdata!=nullptr)
		{
			SDL_SysWMinfo info;
			SDL_GetWindowWMInfo((SDL_Window*)windowdata, &info);
			#if defined(TARGETPLATFORM_WINDOWS)
				*((HWND*)ptr) = info.info.win.window;
			#endif
		}
	}

	WindowEventListener::~WindowEventListener()
	{
		//
	}

	void WindowEventListener::onWindowShown(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowHidden(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowExposed(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowMoved(Window*window, const Vector2f&position)
	{
		//
	}

	void WindowEventListener::onWindowResized(Window*window, const Vector2u&size, bool external)
	{
		//
	}

	void WindowEventListener::onWindowMinimize(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowMaximize(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowRestore(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowMouseEnter(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowMouseLeave(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowFocusGained(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowFocusLost(Window*window)
	{
		//
	}

	void WindowEventListener::onWindowClose(Window*window)
	{
		//
	}
}