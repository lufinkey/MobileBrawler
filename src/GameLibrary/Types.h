
#pragma once

namespace GameLibrary
{
	class Application;
	class AssetManager;
	
	//Actor
	class ActorType;
		class Actor;
		class TextActor;
		class WireframeActor;
	
	//Audio
	class Music;
	class Sound;
	
	//Exception
	class Exception;
		class OutOfBoundsException;
			class ArrayListOutOfBoundsException;
			class BitListOutOfBoundsException;
			class BitSetOutOfBoundsException;
			class DataPacketOutOfBoundsException;
			class ImageOutOfBoundsException;
			class StringOutOfBoundsException;
		class BadCastException;
			class BadAnyCastException;
		class IllegalArgumentException;
			class IllegalFormatException;
				class IllegalDateTimeFormatException;
			class NumberFormatException;
		class UnsupportedImageFormatException;
	
	//Graphics
	class Graphics;
	class Color;
	class Image;
	class TextureImage;
	
	//IO
	class Console;
	class Keyboard;
	class Mouse;
	class Multitouch;
	
	//Network
	class NetworkProtocol;
	
	//Screen
	class ScreenManager;
	class Screen;
		class MenuScreen;
	
	//Utilities
		//Geometry
		class Circle;
		class Polygon;
		class Rectangle;
		class RectangleF;
		class Transform;
	class Any;
	class BitSet;
	class Dictionary;
	class Font;
	class Math;
	class String;

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
