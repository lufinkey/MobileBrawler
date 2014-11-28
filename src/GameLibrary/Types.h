
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
			class BitSetOutOfBoundsException;
			class StringOutOfBoundsException;
		class BadCastException;
			class BadAnyCastException;
		class IllegalArgumentException;
			class IllegalFormatException;
				class IllegalDateTimeFormatException;
			class NumberFormatException;
	
	//Graphics
	class Graphics;
	class Color;
	class Image;
	class BufferedImage;
	
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

	typedef unsigned char byte;
	typedef bool boolean;
}
