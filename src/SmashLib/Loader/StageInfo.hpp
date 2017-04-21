
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashLib
{
	class StageInfo
	{
	public:
		StageInfo();
		~StageInfo();
		
		StageInfo& operator=(const StageInfo&);
		
		bool loadFromPath(const fgl::String&path, fgl::String*error=nullptr);
		
		const fgl::String& getPath() const;
		const fgl::String& getName() const;
		const fgl::String& getCreator() const;
		const fgl::String& getMinimumSmashVersion() const;
		
		void setPath(const fgl::String&path);
		void setName(const fgl::String&name);
		void setCreator(const fgl::String&creator);
		void setMinimumSmashVersion(const fgl::String&minsmashversion);
		
	private:
		fgl::String path;
		fgl::String name;
		fgl::String creator;
		fgl::String version;
		fgl::String minsmashversion;
	};
}