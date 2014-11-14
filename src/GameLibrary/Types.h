
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
	class GameLibraryException;
		class OutOfBoundsException;
			class ArrayListOutOfBoundsException;
			class BitsetOutOfBoundsException;
	
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
		class Rectangle;
		class Circle;
	class Bitset;
	class Dictionary;
	class Math;
	class String;
}

typedef unsigned char byte;
typedef bool boolean;
