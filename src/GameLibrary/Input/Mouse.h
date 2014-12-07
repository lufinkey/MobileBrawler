
#include "../Window/Window.h"

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

		/*Returns true if Button is currently in a pressed state*/
		bool isButtonPressed(Button button);
		/*Returns true if Button is currently in a released state*/
		bool isButtonReleased(Button button);
		/*returns the current frame's Mouse coordinates (relative to the specified Window)*/
		static Vector2f getPosition(Window*window);
		/*returns the current frame's Mouse x coordinate (relative to the specified Window)*/
		static float getX(Window*window);
		/*returns the current frame's Mouse y coordinate (relative to the specified Window)*/
		static float getY(Window*window);
		/*sets the position of the Mouse, relative to the specified window.
		pos: the coordinates to move the mouse pointer to
		window: the window to move the mouse in, or null for the currently mouse-focused window*/
		static void setPosition(const Vector2f&pos, Window*window);
		/*sets the position of the Mouse, relative to the entire screen.
		pos: the coordinates to move the mouse pointer to*/
		static void setPosition(const Vector2f&pos);

		/*Returns true if Button was in a pressed state in the previous frame*/
		bool wasButtonPressed(Button button);
		/*Returns true if Button was in a released state in the previous frame*/
		bool wasButtonReleased(Button button);
		/*returns the previous frame's Mouse coordinates (relative to the specified Window)*/
		static Vector2f getPreviousPosition(Window*window);
		/*returns the previous frame's Mouse x coordinate (relative to the specified Window)*/
		static float getPreviousX(Window*window);
		/*returns the previous frame's Mouse y coordinate (relative to the specified Window)*/
		static float getPreviousY(Window*window);

		/*Returns true if Button was just pressed (released state in the previous frame, pressed state in the current frame)*/
		bool didButtonPress(Button button);
		/*Returns true if Button was just released (pressed state in the previous frame, released state in the current frame)*/
		bool didButtonRelease(Button button);

		/*Adds a MouseEventListener to handle Mouse events*/
		static void addEventListener(MouseEventListener*);
		/*Removes a previously added MouseEventListener*/
		static void removeEventListener(MouseEventListener*);

	private:
		/*Handles Mouse movement events sent from EventManager*/
		static void handleMouseMovement(unsigned int mouseIndex, Window*window, const Vector2f&pos, const Vector2f&dif);
		/*Handles button press events sent from EventManager*/
		static void handleButtonPress(unsigned int mouseIndex, Mouse::Button button);
		/*Handles button release events sent from EventManager*/
		static void handleButtonRelease(unsigned int mouseIndex, Mouse::Button button);

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
		mouseIndex: the mouse index
		button: the constant that represents the mouse button*/
		virtual void onMouseButtonPress(unsigned int mouseIndex, Mouse::Button button);
		/*Event called when a Mouse::Button state changes to released.
		mouseIndex: the mouse index
		button: the constant that represents the mouse button*/
		virtual void onMouseButtonRelease(unsigned int mouseIndex, Mouse::Button button);
		/*Event called when the Mouse moves.
		mouseIndex: the mouse index
		window: the window that has mouse focus. May or may not be null
		mousepos: the mouse coordinates relative to the window. If window is null, these coordinates will be invalid.
		mousedif: the change in mouse coordinates*/
		virtual void onMouseMove(unsigned int mouseIndex, Window*window, const Vector2f&mousepos, const Vector2f&mousedif);

		/*destructor*/
		virtual ~MouseEventListener();
	};
}