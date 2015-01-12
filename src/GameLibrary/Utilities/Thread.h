
#pragma once

#include "ArrayList.h"
#include "Pair.h"

namespace GameLibrary
{
	typedef void(*ThreadCallback)(void*);

	class Thread
	{
	private:
		typedef Pair<ThreadCallback,Pair<void*,void*> > MainThreadCallback;
		static ArrayList<MainThreadCallback> mainThreadCallbacks;

		void* threaddata;

	public:
		Thread();
		virtual ~Thread();

		/*Event called when thread runs (override this with any processing you want to do in this Thread)*/
		virtual void run();

		/*Call this function to start the Thread.*/
		void start();
		/*Call this function to join the Thread with the calling Thread, and wait until the Thread finishes.
		Thread::join() can only be called from one Thread. It will return false if it is already joined with another Thread.*/
		bool join();

		/*Returns true if the Thread is currently running*/
		bool isAlive();

		/*Causes the calling thread to wait for a specified number of milliseconds*/
		static void sleep(unsigned long long milliseconds);
		static void sleep(unsigned long long milliseconds, unsigned long nanoseconds);

		/*Runs a given callback in the main thread. Setting wait to true causes the function to not return until the callback finishes running*/
		static void runCallbackInMainThread(ThreadCallback callback, void*data=nullptr, bool wait=false);
		/*Runs a givem callback in a new thread.*/
		static void runCallbackInThread(ThreadCallback callback, void*data=nullptr);
		/*Returns true if the current thread is the main thread*/
		static bool isMainThread();

		/*Calls all main thread callbacks (if calling thread is main thread)*/
		static void update();
	};
}