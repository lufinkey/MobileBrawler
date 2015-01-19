
#pragma once

#include "../Graphics/TextureImage.h"
#include "../Utilities/Font/Font.h"

#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"

namespace GameLibrary
{
	class Window;

	class AssetManager
	{
	private:
		Window*window;

		ArrayList<Pair<String,TextureImage*> > textures;
		ArrayList<Pair<String,Font*> > fonts;
		
		String rootdir;
		
		String getFullPath(const String&path) const;

	public:
		AssetManager(Window&window, const String&root="");
		virtual ~AssetManager();
		
		void setRootDirectory(const String&);
		const String& getRootDirectory() const;
		
		Window* getWindow() const;

		virtual bool loadTexture(const String&path, String*error=nullptr);
		virtual void unloadTexture(const String&path);
		virtual void unloadTextures();
		virtual TextureImage* getTexture(const String&path);
		virtual void addTexture(const String&path, TextureImage*image);

		virtual bool loadFont(const String&path, String*error=nullptr);
		virtual void unloadFont(const String&path);
		virtual void unloadFonts();
		virtual Font* getFont(const String&path);
		virtual void addFont(const String&path, Font*font);
	};
}