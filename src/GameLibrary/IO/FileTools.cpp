
#ifdef _WIN32
	#define _CRT_SECURE_NO_WARNINGS
#endif

#include "FileTools.h"
#include "../Utilities/PlatformChecks.h"	

#include <dirent.h>
#include <sys/stat.h>

#if defined(TARGETPLATFORM_WINDOWS)
	#include <direct.h>
	#include <Windows.h>
	#include <ShlObj.h>
#else
	#include <unistd.h>
#endif

namespace GameLibrary
{
	String FileTools::getUserHomeDirectory()
	{
		#if defined(TARGETPLATFORM_WINDOWS)
			const char* homedir = getenv("HOMEPATH");
		#else
			const char* homedir = getenv("HOME");
		#endif
		if(homedir == nullptr)
		{
			return "";
		}
		return homedir;
	}
	
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
	
	bool FileTools::readEntriesFromDirectory(const String&directory, ArrayList<DirectoryEntry>*entries, String*error)
	{
		if(entries == nullptr)
		{
			throw IllegalArgumentException("entries", "null");
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
		entries->clear();
		struct dirent *entry = readdir(dir);
		while (entry != NULL)
		{
			DirectoryEntry item;
			item.name = entry->d_name;
			switch(entry->d_type)
			{
				case DT_REG:
				item.type = ENTRYTYPE_FILE;
				break;
					
				case DT_DIR:
				item.type = ENTRYTYPE_FOLDER;
				break;
					
				case DT_LNK:
				{
					struct stat s;
					String path = directory + '/' + item.name;
					if(stat(path, &s)==0)
					{
						if((s.st_mode&S_IFMT) == S_IFDIR)
						{
							item.type = ENTRYTYPE_LINK_FOLDER;
						}
						else if((s.st_mode&S_IFMT) == S_IFREG)
						{
							item.type = ENTRYTYPE_LINK_FILE;
						}
						else
						{
							item.type = ENTRYTYPE_LINK;
						}
					}
					else
					{
						item.type = ENTRYTYPE_LINK;
					}
				}
				break;
					
				default:
				item.type = ENTRYTYPE_UNKNOWN;
				break;
			}
			if(!(item.name.equals(".") || item.name.equals("..")))
			{
				entries->add(item);
			}
			entry = readdir(dir);
		}
		closedir(dir);
		return true;
	}
	
	bool FileTools::isDirectoryEmpty(const String&directory)
	{
		DIR*dir = opendir(directory);
		if(dir==NULL)
		{
			return false;
		}
		struct dirent *entry = readdir(dir);
		while (entry != NULL)
		{
			if(entry->d_type==DT_REG || entry->d_type==DT_DIR || entry->d_type==DT_LNK)
			{
				String itemName = entry->d_name;
				if(!itemName.equals(".") && !itemName.equals(".."))
				{
					closedir(dir);
					return false;
				}
			}
			entry = readdir(dir);
		}
		return true;
	}
	
	String FileTools::combinePathStrings(const String&first, const String&second)
	{
		String fullpath;
		if(first.length() == 0)
		{
			fullpath = second;
		}
		else
		{
			if(first.charAt(first.length()-1)=='/')
			{
				fullpath = first + second;
			}
			else
			{
				fullpath = first + '/' + second;
			}
		}
		return fullpath;
	}
	
	#if !defined(TARGETPLATFORM_MAC) && !defined(TARGETPLATFORM_IOS)
	String FileTools::openFilePicker(const String&title, const String&startingDir)
	{
		#if defined(TARGETPLATFORM_WINDOWS)
			//OSVERSIONINFO vi;
			//memset(&vi, 0, sizeof(vi));
			//vi.dwOSVersionInfoSize = sizeof(vi);
			//if(vi.dwMajorVersion >= 6)
			//Vista or greater
			//{

			//}
			//else
			//XP or lower
			{
				std::basic_string<TCHAR> default_dir = (std::basic_string<TCHAR>)startingDir;
				std::basic_string<TCHAR> dialog_title = (std::basic_string<TCHAR>)title;
				TCHAR filenameBuffer[MAX_PATH];
				filenameBuffer[0] = '\0';
				OPENFILENAME ofn;
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.lpstrFile = filenameBuffer;
				ofn.nMaxFile = MAX_PATH;
				ofn.lpstrInitialDir = default_dir.c_str();
				ofn.lpstrTitle = dialog_title.c_str();
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
				BOOL result = GetOpenFileName(&ofn);
				if(result)
				{
					return (String)ofn.lpstrFile;
				}
				return "";
			}
		#elif defined(TARGETPLATFORM_LINUX)
			//TODO implement linux file picker
			return "";
		#else
			return "";
		#endif
	}
	#endif
	
	#if defined(TARGETPLATFORM_WINDOWS)
	INT CALLBACK FileTools_openFolderPicker_BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
	{
		switch(uMsg)
		{
			case BFFM_INITIALIZED:
			{
				if (NULL != lpData)
				{
					SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
				}
			}
		}
		return 0; // The function should always return 0.
	}
	#endif
	
	#if !defined(TARGETPLATFORM_MAC) && !defined(TARGETPLATFORM_IOS)
	String FileTools::openFolderPicker(const String&title, const String&startingDir)
	{
		#if defined(TARGETPLATFORM_WINDOWS)
			std::basic_string<TCHAR> dialog_title = (std::basic_string<TCHAR>)title;
			std::basic_string<TCHAR> default_dir = (std::basic_string<TCHAR>)startingDir;
			BROWSEINFO bi;
			ZeroMemory(&bi, sizeof(bi));
			TCHAR folderdisplaynameBuffer[MAX_PATH];
			bi.pszDisplayName = folderdisplaynameBuffer;
			bi.lpszTitle = dialog_title.c_str();
			bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
			bi.lpfn = FileTools_openFolderPicker_BrowseCallbackProc;
			bi.lParam = (LPARAM)default_dir.c_str();
			LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
			if (pidl!=nullptr)
			{
				TCHAR path[MAX_PATH];
				path[0] = NULL;
				BOOL success = SHGetPathFromIDList(pidl, path);
				CoTaskMemFree(pidl);
				if(success==FALSE)
				{
					return "";
				}
				return (String)path;
			}
			return "";
		#elif defined(TARGETPLATFORM_LINUX)
			//TODO implement linux folder picker
			return "";
		#else
			return "";
		#endif
	}
	#endif
}
