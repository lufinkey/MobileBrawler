
#include "View.h"
#include "../Graphics/Image.h"
#include "../Graphics/Graphics.h"
#include "../Utilities/String.h"
#include "../Utilities/Geometry/Vector2.h"

#pragma once

namespace GameLibrary
{
	class WindowSettings
	{
		friend class Window;
	private:
		Vector2i position;
		Vector2u size;
		String title;
		Image*icon;
		void*icondata;
		byte style;
		
	public:
		WindowSettings();
		WindowSettings(const Vector2i& position, const Vector2u& size, const String&title="", Image*icon=nullptr, byte style=0);
		~WindowSettings();
		
		void setPosition(const Vector2i&);
		const Vector2i& getPosition() const;
		
		void setSize(const Vector2u&);
		const Vector2u& getSize() const;
		
		void setTitle(const String&);
		const String& getTitle() const;
		
		void setIcon(Image*);
		const Image* getIcon() const;
		
		void setStyle(byte);
		byte getStyle() const;
	};

	class Window
	{
		friend class Graphics;
	private:
		void*windowdata;
		View*view;
		Graphics*graphics;
		WindowSettings settings;
		Vector2u windowed_size;
		
	public:
		enum WindowStyle : byte
		{
			STYLE_DEFAULT = 0x00000000,
			STYLE_BORDERLESS = 0x00000001,
			STYLE_FULLSCREEN = 0x00000002,
			STYLE_HIDDEN = 0x00000004,
			STYLE_RESIZABLE = 0x00000008,
			STYLE_MINIMIZED = 0x00000010,
			STYLE_MAXIMIZED = 0x00000020
		};

		enum WindowPosition : int
		{
			POSITION_UNDEFINED = 0x0fffffff,
			POSITION_CENTERED = 0x0ffffffe
		};

		Window();
		virtual ~Window();
		
		void create(const WindowSettings&settings);
		void update();
		void destroy();
		
		Image*capture();
		Graphics& getGraphics();

		static Rectangle getDisplayBounds(unsigned int displayIndex);
		
		const Vector2i& getPosition();
		void setPosition(const Vector2i&);
		
		const Vector2u& getSize();
		void setSize(const Vector2u&);

		const String& getTitle();
		void setTitle(const String&);

		const Image* getIcon();
		void setIcon(Image*);
		
		bool isOpen();
		bool isFocused();
		bool isVisible();
		void setVisible(bool);
		bool isFullscreen();
		void setFullscreen(bool);
		void setFullscreen(bool toggle, unsigned int width, unsigned int height);
	};
}
