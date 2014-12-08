
#include "../Graphics/TextureImage.h"
#include "../Utilities/Font/Font.h"

#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"

#pragma once

namespace GameLibrary
{
	class Window;

	class AssetManager
	{
	private:
		Window*window;

		ArrayList<Pair<String,TextureImage*> > textures;
		ArrayList<Pair<String,Font*> > fonts;

	public:
		AssetManager(Window&window);
		~AssetManager();

		bool loadTexture(const String&path, String&error);
		void unloadTexture(const String&path);
		TextureImage* getTexture(const String&path);

		bool loadFont(const String&path, String&error);
		void unloadFont(const String&path);
		Font* getFont(const String&path);
	};
}