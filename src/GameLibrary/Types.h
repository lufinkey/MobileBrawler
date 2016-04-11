
#pragma once

namespace GameLibrary
{
	//Actor
	class Actor;
		class SpriteActor;
		class Animation;
		class TextActor;
		class WireframeActor;
	
	//Application
	class Application;
	class ApplicationData;
	class AssetManager;
	class BatchLoader;
	class EventManager;
	
	//Audio
	class Music;
	class Sound;
	
	//Exception
	class Exception;
		class BadCastException;
			class BadAnyCastException;
		class IllegalArgumentException;
			class IllegalFormatException;
				class IllegalDateTimeFormatException;
			class NumberFormatException;
		class IllegalNumberOperationException;
		class IllegalStateException;
		class InitializeLibraryException;
		class OutOfBoundsException;
			class ArrayListOutOfBoundsException;
			class BitListOutOfBoundsException;
			class BitSetOutOfBoundsException;
			class DataPacketOutOfBoundsException;
			class ImageOutOfBoundsException;
			class StringOutOfBoundsException;
		class RenderGlyphException;
		class ScreenNavigationException;
		class TextureImageCreateException;
		class TextureImageUpdateException;
		class UnsupportedImageFormatException;
	
	//Graphics
	class Graphics;
	class Color;
	class Image;
	class TextureImage;
	
	//Input
	class Keyboard;
	class Mouse;
	class Multitouch;
	
	//IO
	class Console;
	class FileTools;
	
	//Network
	class NetworkProtocol;
	
	//Screen
		//Transition
		class Transition;
			class FadeColorTransition;
			class FadeZoomTransition;
			class PopoverTransition;
			class SlideTransition;
	class ScreenElement;
		//UI
		class ActorMenuElement;
		class ImageElement;
		class ZoomPanElement;
		class TextInputElement;
	class Screen;
		class MenuScreen;
		class ScreenManager;
	
	//Utilities
		//Font
		class Font;
		//Time
		class DateTime;
		class TimeInterval;
	class Any;
	class BitList;
	class BitSet;
	class DataPacket;
	class Dictionary;
	class Math;
	class Number;
	class Thread;
	
	//View
	class View;
	class Window;
	
	typedef signed char Int8;
	typedef unsigned char Uint8;
	
	typedef signed short Int16;
	typedef unsigned short Uint16;
	
	typedef signed int Int32;
	typedef unsigned int Uint32;
	
	#if defined(_MSC_VER)
		typedef signed __int64 Int64;
		typedef unsigned __int64 Uint64;
	#else
		typedef signed long long Int64;
		typedef unsigned long long Uint64;
	#endif
	
	typedef Uint8 byte;
	typedef bool boolean;
	
//#define nullptr null
}
