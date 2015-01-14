
#pragma once

#include "Actor/Actor.h"
#include "Actor/SpriteActor.h"
#include "Actor/TextActor.h"
#include "Actor/WireframeActor.h"

#include "Application/Application.h"
#include "Application/ApplicationData.h"
#include "Application/AssetManager.h"
#include "Application/BatchLoader.h"

#include "Audio/Music.h"
#include "Audio/Sound.h"

#include "Exception/Exception.h"
#include "Exception/BadCastException.h"
#include "Exception/IllegalArgumentException.h"
#include "Exception/IllegalFormatException.h"
#include "Exception/IllegalStateException.h"
#include "Exception/NumberFormatException.h"
#include "Exception/OutOfBoundsException.h"
#include "Exception/Graphics/ImageOutOfBoundsException.h"
#include "Exception/Graphics/TextureImageCreateException.h"
#include "Exception/Graphics/TextureImageUpdateException.h"
#include "Exception/Graphics/UnsupportedImageFormatException.h"
#include "Exception/Screen/ScreenNavigationException.h"
#include "Exception/Utilities/ArrayListOutOfBoundsException.h"
#include "Exception/Utilities/BadAnyCastException.h"
#include "Exception/Utilities/BitListOutOfBoundsException.h"
#include "Exception/Utilities/BitListOutOfBoundsException.h"
#include "Exception/Utilities/BitSetOutOfBoundsException.h"
#include "Exception/Utilities/DataPacketOutOfBoundsException.h"
#include "Exception/Utilities/StringOutOfBoundsException.h"
#include "Exception/Utilities/Font/RenderGlyphException.h"
#include "Exception/Utilities/Time/IllegalDateTimeFormatException.h"

#include "Graphics/Color.h"
#include "Graphics/Graphics.h"
#include "Graphics/Image.h"
#include "Graphics/TextureImage.h"

#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Input/Multitouch.h"

#include "IO/Console.h"

#include "Network/NetworkProtocol.h"

#include "Screen/Drawable.h"
#include "Screen/ScreenElement.h"
#include "Screen/Screen.h"
#include "Screen/ScreenManager.h"
#include "Screen/MenuScreen.h"
#include "Screen/Transition/Transition.h"
#include "Screen/Transition/FadeColorTransition.h"
#include "Screen/Transition/FadeZoomTransition.h"
#include "Screen/Transition/PopoverTransition.h"
#include "Screen/Transition/SlideTransition.h"
#include "Screen/UI/ImageElement.h"

#include "Utilities/Any.h"
#include "Utilities/ArrayList.h"
#include "Utilities/BitList.h"
#include "Utilities/BitSet.h"
#include "Utilities/DataPacket.h"
#include "Utilities/Dictionary.h"
#include "Utilities/Math.h"
#include "Utilities/PlatformChecks.h"
#include "Utilities/String.h"
#include "Utilities/Thread.h"
#include "Utilities/Font/Font.h"
#include "Utilities/Geometry/Circle.h"
#include "Utilities/Geometry/Polygon.h"
#include "Utilities/Geometry/Rectangle.h"
#include "Utilities/Geometry/Transform.h"
#include "Utilities/Geometry/Vector2.h"
#include "Utilities/Time/DateTime.h"
#include "Utilities/Time/TimeInterval.h"

#include "Window/Window.h"
#include "Window/View.h"

#ifndef main
	#define main GameLibrary_main
#endif
