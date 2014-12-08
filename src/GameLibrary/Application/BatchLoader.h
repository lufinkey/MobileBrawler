
#include "../Types.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include "../Utilities/Time/TimeInterval.h"

#pragma once

namespace GameLibrary
{
	class BatchLoaderEventListener;

	class BatchLoader
	{
	private:
		enum LoadType : byte
		{
			LOADTYPE_TEXTURE,
			LOADTYPE_FONT
		};

		typedef struct
		{
			String path;
			byte type;
			unsigned int value;
		} LoadInfo;

		Window*window;

		ArrayList<LoadInfo> loadlist;
		unsigned int loadindex;

		unsigned int loadcurrent;
		unsigned int loadtotal;
		
		unsigned long long sleeptime;

		TimeInterval loadTime;

		ArrayList<BatchLoaderEventListener*> eventListeners;

		bool lagCompensation;
		bool loading;

	public:
		BatchLoader(Window&window);
		~BatchLoader();

		void addTexture(const String&path, unsigned int value=1);
		void addFont(const String&path, unsigned int value=1);

		void setSleepTime(unsigned long long sleeptime);
		unsigned long long getSleepTime();
		void setLagCompensation(bool toggle);

		unsigned int getLoadCurrent();
		unsigned int getLoadTotal();

		void loadAll();
		void loadNext();
		void stopLoad();

		void clear();
	};

	class BatchLoaderEventListener
	{
	public:
		virtual ~BatchLoaderEventListener();

		virtual void onBatchLoaderLoadTexture(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderLoadFont(BatchLoader*batchLoader, const String&path, unsigned int value);
		virtual void onBatchLoaderErrorTexture(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderErrorFont(BatchLoader*batchLoader, const String&path, unsigned int value, const String&error);
		virtual void onBatchLoaderFinish(BatchLoader*batchLoader);
	};
}