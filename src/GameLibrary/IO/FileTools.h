
#pragma once

#include "../Utilities/String.h"
#include "../Utilities/ArrayList.h"
#include "../Exception/IllegalArgumentException.h"

namespace GameLibrary
{
	/*! Handles reading directories and file structures from the disk*/
	class FileTools
	{
	public:
		/*! A type of directory item in a directory*/
		typedef enum
		{
			/*! A regular file*/
			ENTRYTYPE_FILE,
			/*! A regular folder*/
			ENTRYTYPE_FOLDER,
			/*! A symbolic link to a file*/
			ENTRYTYPE_LINK_FILE,
			/*! A symbolic link to a folder*/
			ENTRYTYPE_LINK_FOLDER,
			/*! A symbolic link whose type is unknown*/
			ENTRYTYPE_LINK,
			/*! An unknown directory entry*/
			ENTRYTYPE_UNKNOWN
		} DirectoryEntryType;
		
		
		/*! Holds information about an entry in a directory*/
		typedef struct
		{
			/*! The name of the directory entry*/
			String name;
			/*! The type of directory entry*/
			DirectoryEntryType type;
		} DirectoryEntry;
		
		
		/*! Gets the user home directory
			\returns a String containing the path to the current user's home directory, or an empty String if an error occured*/
		static String getUserHomeDirectory();
		
		
		/*! Gets the path of the current working directory.
			\returns a String containing the path to the working directory*/
		static String getCurrentWorkingDirectory();
		/*! Stores a list of items in a directory inside of an ArrayList of DirectoryEntry objects.
			\param directory the directory to read entries
			\param entries a pointer to an ArrayList<DirectoryEntry> to store the entries; This should not be null
			\param error an optional String pointer to store the error message if the function fails
			\returns true if all entries were successfully read from the directory, or false if an error is encountered
			\throws GameLibrary::IllegalArgumentException if items is null*/
		static bool readEntriesFromDirectory(const String&directory, ArrayList<DirectoryEntry>*entries, String*error=nullptr);
		
		
		/*! Combines two path strings into a single path.
			\param first the first half of the path
			\param second the second half of the path
			\returns a String containing a full path from the two given paths*/
		static String combinePathStrings(const String&first, const String&second);
		
		
		/*! Opens up the native file chooser to select a file.
			\param startingDir the path to open the file picker window to; default value is the user home directory
			\returns a String representing the selected path, or an empty String, if the operation was cancelled*/
		static String openFilePicker(const String&title="Open", const String&startingDir=FileTools::getUserHomeDirectory());
		
		
		/*! Opens up the native file chooser to select a folder.
			\param startingDir the path to open the file picker window to; default value is the user home directory
			\returns a String representing the selected path, or an empty String, if the operation was cancelled*/
		static String openFolderPicker(const String&title="Open", const String&startingDir=FileTools::getUserHomeDirectory());
	};
}
