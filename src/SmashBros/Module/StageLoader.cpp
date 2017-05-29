
#include "StageLoader.hpp"

namespace SmashBros
{
	StageLoader::StageLoader()
	{
		//
	}
	
	void StageLoader::addPath(const fgl::String& path)
		//TODO add ability to pass in ArrayList for error catching
	{
		//ensure duplicate path does not get added
		for(auto& cmpPath : paths)
		{
			if(path==cmpPath)
			{
				return;
			}
		}

		//add path
		paths.add(path);
		
		//load entries from path
		fgl::ArrayList<fgl::FileTools::DirectoryEntry> dirEntries;
		fgl::FileTools::readEntriesFromDirectory(path, &dirEntries);
		for(auto& dirEntry : dirEntries)
		{
			if(dirEntry.type==fgl::FileTools::ENTRYTYPE_FOLDER || dirEntry.type==fgl::FileTools::ENTRYTYPE_LINK_FOLDER)
			{
				StageInfo info;
				auto stagePath = fgl::FileTools::combinePathStrings(path, dirEntry.name);
				bool success = info.loadFromPath(stagePath);
				//TODO see if minsmashversion is compatible
				if(success)
				{
					if(!hasStage(info.getIdentifier()))
					{
						stages.add(info);
					}
				}
			}
		}
	}

	void StageLoader::reloadPaths()
	{
		stages.clear();
		for(auto& path : paths)
		{
			fgl::ArrayList<fgl::FileTools::DirectoryEntry> dirEntries;
			fgl::FileTools::readEntriesFromDirectory(path, &dirEntries);

			for(auto& dirEntry : dirEntries)
			{
				if(dirEntry.type==fgl::FileTools::ENTRYTYPE_FOLDER || dirEntry.type==fgl::FileTools::ENTRYTYPE_LINK_FOLDER)
				{
					StageInfo info;
					auto stagePath = fgl::FileTools::combinePathStrings(path, dirEntry.name);
					bool success = info.loadFromPath(stagePath);
					//TODO see if minsmashversion is compatible
					if(success)
					{
						if(!hasStage(info.getIdentifier()))
						{
							stages.add(info);
						}
					}
				}
			}
		}
	}

	const fgl::ArrayList<fgl::String>& StageLoader::getPaths() const
	{
		return paths;
	}

	const fgl::ArrayList<StageInfo>& StageLoader::getStages() const
	{
		return stages;
	}

	bool StageLoader::hasStage(const fgl::String& identifier) const
	{
		for(auto& stage : stages)
		{
			if(stage.getIdentifier()==identifier)
			{
				return true;
			}
		}
		return false;
	}

	const StageInfo& StageLoader::getStageInfo(const fgl::String& identifier) const
	{
		for(auto& stage : stages)
		{
			if(stage.getIdentifier()==identifier)
			{
				return stage;
			}
		}
		throw fgl::IllegalArgumentException("identifier", "no stage exists with the given identifier");
	}
	
	fgl::ArrayList<fgl::String> StageLoader::getIconPaths() const
	{
		fgl::ArrayList<fgl::String> iconPaths;
		iconPaths.reserve(stages.size());
		for(auto& stage : stages)
		{
			iconPaths.add(stage.getIconPath());
		}
		return iconPaths;
	}
	
	fgl::ArrayList<fgl::String> StageLoader::getPreviewPaths() const
	{
		fgl::ArrayList<fgl::String> previewPaths;
		previewPaths.reserve(stages.size());
		for(auto& stage : stages)
		{
			previewPaths.add(stage.getPreviewPath());
		}
		return previewPaths;
	}

	void StageLoader::registerStage(const fgl::String& identifier, const std::function<fl::Stage*(fgl::AssetManager*)>& initializer)
	{
		if(stageInitializers.has(identifier))
		{
			throw fgl::IllegalArgumentException("identifier", "stage has already been registered");
		}
		stageInitializers[identifier] = initializer;
	}

	void StageLoader::unregisterStage(const fgl::String& identifier)
	{
		stageInitializers.remove(identifier);
	}

	fl::Stage* StageLoader::createStage(const fgl::String& identifier, fgl::AssetManager* assetManager) const
	{
		return stageInitializers.get(identifier, [](fgl::AssetManager* assetManager) -> fl::Stage* {
			return nullptr;
		})(assetManager);
	}
}
