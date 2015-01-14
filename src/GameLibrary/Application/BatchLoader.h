
#pragma once

#include "../Types.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include "../Utilities/Time/TimeInterval.h"

namespace GameLibrary
{
	class BatchLoaderEventListener;

	class BatchLoader
	{
	private:
		typedef enum
		{
			LOADTYPE_TEXTURE,
			LOADTYPE_FONT
		} LoadType;

		typedef struct
		{
			String path;
			LoadType type;
			unsigned int value;
		} LoadInfo;

		AssetManager*assetManager;

		ArrayList<LoadInfo> loadlist;
		unsigned int loadindex;

		unsigned int loadcurrent;
		unsigned int loadtotal;
		
		ArrayList<BatchLoaderEventListener*> eventListeners;

		bool loading;

	public:
		BatchLoader(AssetManager*assetManager);
		BatchLoader(const BatchLoader&);
		~BatchLoader();

		void addTexture(const String&path, unsigned int value=1);
		void addFont(const String&path, unsigned int value=1);

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