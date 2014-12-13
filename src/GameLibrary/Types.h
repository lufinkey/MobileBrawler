
#pragma once

namespace GameLibrary
{
	//Actor
	class ActorType;
		class Actor;
		class TextActor;
		class WireframeActor;

	//Application
	class Application;
	class ApplicationData;
	class AssetManager;
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
		class OutOfBoundsException;
			class ArrayListOutOfBoundsException;
			class BitListOutOfBoundsException;
			class BitSetOutOfBoundsException;
			class DataPacketOutOfBoundsException;
			class ImageOutOfBoundsException;
			class StringOutOfBoundsException;
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
		class Screen;
			class MenuScreen;
			class ScreenManager;
	
	//Utilities
		//Font
		class Font;
		//Geometry
		class Circle;
		class Polygon;
		class Rectangle;
		class RectangleF;
		class Transform;
		//Time
		class DateTime;
		class TimeInterval;
	class Any;
	class BitSet;
	class BitList;
	class DataPacket;
	class Dictionary;
	class Math;
	class String;
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
