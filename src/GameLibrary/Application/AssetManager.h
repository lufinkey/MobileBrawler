
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
		ArrayList<String> secondaryRoots;
		
	public:
		AssetManager(Window&window, const String&root="", const ArrayList<String>&secondaryRoots=ArrayList<String>());
		~AssetManager();
		
		void setRootDirectory(const String&);
		const String& getRootDirectory() const;
		
		void addSecondaryRoot(const String&);
		const ArrayList<String>& getSecondaryRoots() const;
		void removeSecondaryRoot(const String&);
		
		Window* getWindow() const;
		
		bool loadTexture(const String&path, String*error=nullptr);
		bool loadTexture(const String&path, const Image&compositeMask, String*error=nullptr);
		void unloadTexture(const String&path);
		void unloadTextures();
		TextureImage* getTexture(const String&path);
		void addTexture(const String&path, TextureImage*image);
		
		bool loadFont(const String&path, String*error=nullptr);
		void unloadFont(const String&path);
		void unloadFonts();
		Font* getFont(const String&path);
		void addFont(const String&path, Font*font);
		
		unsigned int reload();
		void unload();
	};
}