
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	class MenuAssetManager : public fgl::AssetManager
	{
	public:
		MenuAssetManager(fgl::Window* window, const fgl::String& rootDir);
		virtual ~MenuAssetManager();
		
		bool loadImage(const fgl::String& path, fgl::String* error=nullptr);
		void unloadImage(const fgl::String& path);
		void unloadImages();
		fgl::Image* getImage(const fgl::String& path) const;
		void addImage(const fgl::String& path, fgl::Image* image);
		
		bool loadMaskedTexture(const fgl::String& path, fgl::Image* imageMask, fgl::String* error = nullptr);
		
		virtual void unload() override;
		
	private:
		fgl::ArrayList<std::pair<fgl::String, fgl::Image*>> images;
	};
}
