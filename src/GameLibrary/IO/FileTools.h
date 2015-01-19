
#pragma once

#include "../Utilities/String.h"
#include "../Utilities/ArrayList.h"
#include "../Exception/IllegalArgumentException.h"

namespace GameLibrary
{
	class FileTools
	{
	public:
		typedef enum
		{
			ITEMTYPE_FILE,
			ITEMTYPE_FOLDER,
			ITEMTYPE_LINK_FILE,
			ITEMTYPE_LINK_FOLDER,
			ITEMTYPE_UNKNOWN
		} DirectoryItemType;
	
		typedef struct
		{
			String name;
			DirectoryItemType type;
		} DirectoryItem;

		static String getCurrentWorkingDirectory();
		static bool getItemsInDirectory(const String&directory, ArrayList<DirectoryItem>*items, String*error=nullptr);
	};
}
