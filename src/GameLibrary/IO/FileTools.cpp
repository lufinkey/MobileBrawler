
#include "FileTools.h"
#include "../Utilities/PlatformChecks.h"	

#include <dirent.h>
#include <sys/stat.h>

#if defined(TARGETPLATFORM_WINDOWS)
	#include <direct.h>
#else
	#include <unistd.h>
#endif

namespace GameLibrary
{
	String FileTools::getCurrentWorkingDirectory()
	{
		char buffer[FILENAME_MAX];
		buffer[0] = '\0';
		#if defined(TARGETPLATFORM_WINDOWS)
			if(_getcwd(buffer, FILENAME_MAX) == nullptr)
			{
				return "";
			}
		#else
			if(getcwd(buffer, FILENAME_MAX) == nullptr)
			{
				return "";
			}
		#endif
		return buffer;
	}
	
	bool FileTools::getItemsInDirectory(const String&directory, ArrayList<DirectoryItem>*items, String*error)
	{
		if(items == nullptr)
		{
			throw IllegalArgumentException("items argument in FileManager::getItemsInDirectory cannot be null");
		}
		DIR*dir = opendir(directory);
		if(dir==NULL)
		{
			//TODO add checking of errno
			if(error!=nullptr)
			{
				*error = "Unable to open directory";
			}
			return false;
		}
		items->clear();
		struct dirent *entry = readdir(dir);
		while (entry != NULL)
		{
			DirectoryItem item;
			item.name = entry->d_name;
			switch(entry->d_type)
			{
				case DT_REG:
				item.type = ITEMTYPE_FILE;
				break;
					
				case DT_DIR:
				item.type = ITEMTYPE_FOLDER;
				break;
					
				case DT_LNK:
				{
					struct stat s;
					String path = directory + '/' + item.name;
					if(stat(path, &s)==0)
					{
						if((s.st_mode&S_IFMT) == S_IFDIR)
						{
							item.type = ITEMTYPE_LINK_FOLDER;
						}
						else
						{
							item.type = ITEMTYPE_LINK_FILE;
						}
					}
					else
					{
						item.type = ITEMTYPE_LINK_FILE;
					}
				}
				break;
					
				default:
				item.type = ITEMTYPE_UNKNOWN;
				break;
			}
			if(!(item.name.equals(".") || item.name.equals("..")))
			{
				items->add(item);
			}
			entry = readdir(dir);
		}
		closedir(dir);
		return true;
	}
}
