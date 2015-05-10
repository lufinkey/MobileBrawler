
#pragma once

#include "../Graphics/TextureImage.h"
#include "../Utilities/Font/Font.h"

#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"

namespace GameLibrary
{
	class Window;
	
	/*! Manages various Application resources, such as TextureImage or Font objects.*/
	class AssetManager
	{
	public:
		/*! Constructs an AssetManager for the specified Window, in the specified root folder and secondary root folders.
			\param window the Window that the assets will be used for
			\param root the root folder to load assets
			\param secondaryRoots alternate root folders to search if an asset cannot be loaded inside the main root folder*/
		explicit AssetManager(Window&window, const String&root="", const ArrayList<String>&secondaryRoots=ArrayList<String>());
		/*! virtual destructor*/
		~AssetManager();
		
		
		/*! Sets the primary root directory to load assets.
			\param root the path to the root folder to use*/
		void setRootDirectory(const String&root);
		/*! Gets the primary root directory for loading assets.
			\returns a const String reference representing the path to the root folder*/
		const String& getRootDirectory() const;
		
		
		/*! Adds a secondary directory to load from if an asset cannot load from the primary directory.
			\param root the path to the secondary directory*/
		void addSecondaryRoot(const String&root);
		/*! Gets an ArrayList<String> of the secondary directories to load from if the primary directory fails.
			\returns a const ArrayList<String> reference*/
		const ArrayList<String>& getSecondaryRoots() const;
		/*! Removes one of the secondary load directories. \see GameLibrary::AssetManager::addSecondaryRoot(const String&)
			\param root the directory to remove from the list of secondary directories*/
		void removeSecondaryRoot(const String&root);
		
		
		/*! Gets the Window that assets are being loaded for.
			\returns a Window pointer*/
		Window* getWindow() const;
		
		
		/*! Loads and stores a TextureImage from the given path.
			\param path the path to load the TextureImage, relative to the AssetManager root
			\param error a pointer to store an error string, if an error occurs
			\returns true if the TextureImage was successfully loaded, or was already stored in the AssetManager, and false if an error occurred*/
		bool loadTexture(const String&path, String*error=nullptr);
		/*! Loads and stores a TextureImage from the given path.
			\param path the path to load the TextureImage, relative to the AssetManager root
			\param compositeMask an Image to create a composite mask on the loaded pixels \see GameLibrary::Image::applyCompositeMask(const GameLibrary::Image&)
			\param error a pointer to store an error string, if an error occurs
			\returns true if the TextureImage was successfully loaded, or was already stored in the AssetManager, and false if an error occurred*/
		bool loadTexture(const String&path, const Image&compositeMask, String*error=nullptr);
		/*! Unloads and deallocates a stored TextureImage. If a TextureImage with the given path is not stored, the function returns.
			\param path the path that the TextureImage was loaded from, or the path given in AssetManager::addTexture*/
		void unloadTexture(const String&path);
		/*! Unloads and deallocates all stored TextureImage objects.*/
		void unloadTextures();
		/*! Gets a stored TextureImage.
			\param path the path that the TextureImage was loaded from, or the path given in AssetManager::addTexture
			\returns a TextureImage pointer, or null if there is no TextureImage is stored with that path.*/
		TextureImage* getTexture(const String&path);
		/*! Adds a TextureImage to be stored and managed. Once added, the TextureImage's memory is handled by AssetManager, and will be deallocated if the TextureImage is unloaded.
			If a TextureImage is already stored with the given path, that TextureImage is deallocated and replaced with the new one.
			\throws GameLibrary::IllegalArgumentException if the TextureImage is null
			\param path a path to identify the TextureImage
			\param image the TextureImage pointer to add*/
		void addTexture(const String&path, TextureImage*image);
		
		
		/*! Loads and stores a Font from the given path.
			\param path the path to load the Font, relative to the AssetManager root
			\param error a pointer to store an error string, if an error occurs
			\returns true if the Font was successfully loaded, or was already stored in the AssetManager, and false if an error occurred*/
		bool loadFont(const String&path, String*error=nullptr);
		/*! Unloads and deallocates a stored Font. If a Font with the given path is not stored, the function returns.
			\param path the path that the Font was loaded from, or the path given in AssetManager::addTexture*/
		void unloadFont(const String&path);
		/*! Unloads and deallocates all stored Font objects.*/
		void unloadFonts();
		/*! Gets a stored Font.
			\param path the path that the Font was loaded from, or the path given in AssetManager::addTexture
			\returns a Font pointer, or null if there is no Font is stored with that path.*/
		Font* getFont(const String&path);
		/*! Adds a Font to be stored and managed. Once added, the Font's memory is handled by AssetManager, and will be deallocated if the Font is unloaded.
			If a Font is already stored with the given path, that Font is deallocated and replaced with the new one.
			\throws GameLibrary::IllegalArgumentException if the Font is null
			\param path a path to identify the Font
			\param image the Font pointer to add*/
		void addFont(const String&path, Font*font);
		
		
		/*! Reloads and re-stores all stored assets from their paths.
			\returns the total amount of successfully reloaded assets*/
		unsigned int reload();
		/*! Unloads and deallocates all stored assets.*/
		void unload();
		
	private:
		Window*window;
		
		ArrayList<Pair<String,TextureImage*> > textures;
		ArrayList<Pair<String,Font*> > fonts;
		
		String rootdir;
		ArrayList<String> secondaryRoots;
	};
}