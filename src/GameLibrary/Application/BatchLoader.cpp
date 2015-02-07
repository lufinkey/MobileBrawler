
#include "BatchLoader.h"
#include "../Window/Window.h"

namespace GameLibrary
{
	BatchLoader::BatchLoader(AssetManager*assetMgr)
	{
		assetManager = assetMgr;
		loadindex = 0;
		loadcurrent = 0;
		loadtotal = 0;
		loading = false;
	}

	BatchLoader::BatchLoader(const BatchLoader&batchLoader)
	{
		assetManager = batchLoader.assetManager;
		loadlist = batchLoader.loadlist;
		loadindex = batchLoader.loadindex;
		loadcurrent = batchLoader.loadcurrent;
		loadtotal = batchLoader.loadtotal;
		eventListeners = batchLoader.eventListeners;
		loading = batchLoader.loading;
	}

	BatchLoader::~BatchLoader()
	{
		//
	}
	
	AssetManager* BatchLoader::getAssetManager() const
	{
		return assetManager;
	}
	
	void BatchLoader::setAssetManager(AssetManager*assetMgr)
	{
		assetManager = assetMgr;
	}
	
	void BatchLoader::addEventListener(BatchLoaderEventListener*eventListener)
	{
		eventListeners.add(eventListener);
	}
	
	void BatchLoader::removeEventListener(BatchLoaderEventListener*eventListener)
	{
		unsigned int index = eventListeners.indexOf(eventListener);
		if(index != ARRAYLIST_NOTFOUND)
		{
			eventListeners.remove(index);
		}
	}

	void BatchLoader::addTexture(const String&path, unsigned int value)
	{
		LoadInfo info;
		info.path = path;
		info.type = LOADTYPE_TEXTURE;
		info.value = value;
		loadlist.add(info);
		loadtotal += value;
	}

	void BatchLoader::addFont(const String&path, unsigned int value)
	{
		LoadInfo info;
		info.path = path;
		info.type = LOADTYPE_FONT;
		info.value = value;
		loadlist.add(info);
		loadtotal += value;
	}

	unsigned int BatchLoader::getLoadCurrent()
	{
		return loadcurrent;
	}

	unsigned int BatchLoader::getLoadTotal()
	{
		return loadtotal;
	}

	void BatchLoader::loadAll()
	{
		if(!loading)
		{
			if(eventListeners.size()>0)
			{
				ArrayList<BatchLoaderEventListener*> listeners = eventListeners;
				for(unsigned int i = 0; i < listeners.size(); i++)
				{
					BatchLoaderEventListener*listener = listeners.get(i);
					listener->onBatchLoaderStart(this);
				}
			}
			loading = true;
			while(loadindex<loadlist.size() && loading)
			{
				loadNext();
				loadindex++;
			}
			loading = false;
			if(loadindex == (loadlist.size()-1))
			{
				ArrayList<BatchLoaderEventListener*> listeners = eventListeners;
				for(unsigned int i = 0; i < listeners.size(); i++)
				{
					BatchLoaderEventListener*listener = listeners.get(i);
					listener->onBatchLoaderFinish(this);
				}
			}
		}
	}

	void BatchLoader::loadNext()
	{
		if(loadindex < loadlist.size())
		{
			LoadInfo info = loadlist.get(loadindex);
			if(info.type == LOADTYPE_TEXTURE)
			{
				if(assetManager == nullptr)
				{
					throw IllegalStateException("AssetManager cannot be null while loading a BatchLoader");
				}
				String error;
				bool success = assetManager->loadTexture(info.path, &error);
				loadcurrent+=info.value;
				if(success)
				{
					ArrayList<BatchLoaderEventListener*> listeners = eventListeners;
					for(unsigned int i = 0; i < listeners.size(); i++)
					{
						BatchLoaderEventListener*listener = listeners.get(i);
						listener->onBatchLoaderLoadTexture(this, info.path, info.value);
					}
				}
				else
				{
					ArrayList<BatchLoaderEventListener*> listeners = eventListeners;
					for(unsigned int i = 0; i < listeners.size(); i++)
					{
						BatchLoaderEventListener*listener = listeners.get(i);
						listener->onBatchLoaderErrorTexture(this, info.path, info.value, error);
					}
				}
			}
			else if(info.type == LOADTYPE_FONT)
			{
				if(assetManager == nullptr)
				{
					throw IllegalStateException("AssetManager cannot be null while loading a BatchLoader");
				}
				String error;
				bool success = assetManager->loadFont(info.path, &error);
				loadcurrent+=info.value;
				if(success)
				{
					ArrayList<BatchLoaderEventListener*> listeners = eventListeners;
					for(unsigned int i = 0; i < listeners.size(); i++)
					{
						BatchLoaderEventListener*listener = listeners.get(i);
						listener->onBatchLoaderLoadFont(this, info.path, info.value);
					}
				}
				else
				{
					ArrayList<BatchLoaderEventListener*> listeners = eventListeners;
					for(unsigned int i = 0; i < listeners.size(); i++)
					{
						BatchLoaderEventListener*listener = listeners.get(i);
						listener->onBatchLoaderErrorFont(this, info.path, info.value, error);
					}
				}
			}
		}
	}

	void BatchLoader::stopLoad()
	{
		loading = false;
	}

	void BatchLoader::clear()
	{
		loading = false;
		loadlist.clear();
		loadindex = 0;
		loadcurrent = 0;
		loadtotal = 0;
	}
}
