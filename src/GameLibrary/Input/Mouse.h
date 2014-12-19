
#include "../Window/Window.h"
#include "../Exception/IllegalArgumentException.h"

#pragma once

namespace GameLibrary
{
	class MouseEventListener;
	
	/*Represents the Mouse and all Mouse Button states on the Mouse*/
	class Mouse
	{
		friend class EventManager;
	public:
		/*Constant that represents a Mouse Button*/
		enum Button
		{
			UNKNOWN_BUTTON,
			BUTTON_LEFT,
			BUTTON_MIDDLE,
			BUTTON_RIGHT
		};
		typedef enum Button Button;
		
		/*Returns true if Button is currently in a pressed state.
		window: the window containing the mouse instance, or null for the currently mouse-focused window
		mouseIndex: the mouse index
		button: the Mouse Button to check*/
		static bool isButtonPressed(Window*window, unsigned int mouseIndex, Button button);
		/*returns the current frame's Mouse coordinates (relative to the specified Window).
		window: the window containing the mouse instance, or null for the currently mouse-focused window
		mouseIndex: the mouse index*/
		static Vector2f getPosition(Window*window, unsigned int mouseIndex);
		/*returns the current frame's Mouse x coordinate (relative to the specified Window).
		window: the window containing the mouse instance, or null for the currently mouse-focused window
		mouseIndex: the mouse index*/
		static float getX(Window*window, unsigned int mouseIndex);
		/*returns the current frame's Mouse y coordinate (relative to the specified Window).
		window: the window containing the mouse instance, or null for the currently mouse-focused window
		mouseIndex: the mouse index*/
		static float getY(Window*window, unsigned int mouseIndex);
		/*sets the position of the Mouse, relative to the specified window.
		window: the window to move the mouse in, or null for the currently mouse-focused window
		mouseIndex: the mouse index
		pos: the coordinates to move the mouse pointer to*/
		static void setPosition(Window*window, unsigned int mouseIndex, const Vector2f&pos);
		/*[NOTE: currently not implemented] sets the position of the Mouse, relative to the entire screen.
		mouseIndex: the mouse index
		pos: the coordinates to move the mouse pointer to*/
		static void setPosition(unsigned int mouseIndex, const Vector2f&pos);
		
		/*Returns true if Button was in a pressed state in the previous frame*/
		static bool wasButtonPressed(Window*window, unsigned int mouseIndex, Button button);
		/*returns the previous frame's Mouse coordinates (relative to the specified Window)*/
		static Vector2f getPreviousPosition(Window*window, unsigned int mouseIndex);
		/*returns the previous frame's Mouse x coordinate (relative to the specified Window)*/
		static float getPreviousX(Window*window, unsigned int mouseIndex);
		/*returns the previous frame's Mouse y coordinate (relative to the specified Window)*/
		static float getPreviousY(Window*window, unsigned int mouseIndex);
		
		/*Returns true if Button was just pressed (released state in the previous frame, pressed state in the current frame)*/
		static bool didButtonPress(Window*window, unsigned int mouseIndex, Button button);
		/*Returns true if Button was just released (pressed state in the previous frame, released state in the current frame)*/
		static bool didButtonRelease(Window*window, unsigned int mouseIndex, Button button);
		
		/*Adds a MouseEventListener to handle Mouse events*/
		static void addEventListener(MouseEventListener*);
		/*Removes a previously added MouseEventListener*/
		static void removeEventListener(MouseEventListener*);
		
	private:
		/*Handles Mouse movement events sent from EventManager*/
		static void handleMouseMovement(Window*window, unsigned int mouseIndex, const Vector2f&pos, const Vector2f&dif);
		/*Handles button press events sent from EventManager*/
		static void handleButtonPress(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&pos);
		/*Handles button release events sent from EventManager*/
		static void handleButtonRelease(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&pos);
		
		/*Removes a Window from the Window list stored in Mouse*/
		static void removeWindow(Window*window);
		
		/*Updates all button states. Called once per frame from the main thread.*/
		static void update();
	};
	
	/*Event listener that handles Mouse events*/
	class MouseEventListener
	{
	public:
		/*Event called when a Mouse::Button state changes to pressed.
		window: the window that has mouse focus. May or may not be null
		mouseIndex: the mouse index
		button: the constant that represents the mouse button
		mousepos: the mouse coordinates relative to the window. If window is null, these coordinates will be invalid.*/
		virtual void onMouseButtonPress(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&mousepos);
		/*Event called when a Mouse::Button state changes to released.
		window: the window that has mouse focus. May or may not be null
		mouseIndex: the mouse index
		button: the constant that represents the mouse button
		mousepos: the mouse coordinates relative to the window. If window is null, these coordinates will be invalid.*/
		virtual void onMouseButtonRelease(Window*window, unsigned int mouseIndex, Mouse::Button button, const Vector2f&mousepos);
		/*Event called when the Mouse moves.
		window: the window that has mouse focus. May or may not be null
		mouseIndex: the mouse index
		mousepos: the mouse coordinates relative to the window. If window is null, these coordinates will be invalid.
		mousedif: the change in mouse coordinates*/
		virtual void onMouseMove(Window*window, unsigned int mouseIndex, const Vector2f&mousepos, const Vector2f&mousedif);
		
		/*destructor*/
		virtual ~MouseEventListener();
	};
}