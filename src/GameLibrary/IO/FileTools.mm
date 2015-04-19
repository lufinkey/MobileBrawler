
#ifdef __OBJC__

#include "FileTools.h"

namespace GameLibrary
{
#if defined(TARGETPLATFORM_MAC)
	
	String FileTools::openFilePicker(const String&title, const String&startingDir)
	{
		NSOpenPanel *panel = [NSOpenPanel openPanel];
		[panel setCanChooseFiles:YES];
		[panel setCanChooseDirectories:NO];
		[panel setAllowsMultipleSelection:NO];
		[panel setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:(const char*)startingDir] isDirectory:YES]];
		[panel setTitle:[NSString stringWithUTF8String:(const char*)title]];
		NSInteger clicked = [panel runModal];
		if(clicked == NSFileHandlingPanelOKButton)
		{
			NSURL* url = [panel URL];
			return [[url path] UTF8String];
		}
		return "";
	}
	
	String FileTools::openFolderPicker(const String&title, const String&startingDir)
	{
		NSOpenPanel *panel = [NSOpenPanel openPanel];
		[panel setCanChooseFiles:NO];
		[panel setCanChooseDirectories:YES];
		[panel setAllowsMultipleSelection:NO];
		[panel setDirectoryURL:[NSURL fileURLWithPath:[NSString stringWithUTF8String:(const char*)startingDir] isDirectory:YES]];
		[panel setTitle:[NSString stringWithUTF8String:(const char*)title]];
		NSInteger clicked = [panel runModal];
		if(clicked == NSFileHandlingPanelOKButton)
		{
			NSURL* url = [panel URL];
			return [[url path] UTF8String];
		}
		return "";
	}
	
#elif defined(TARGETPLATFORM_IOS)
	
	String FileTools::openFilePicker(const String&title, const String&startingDir)
	{
		//TODO implement ios file picker
		return "";
	}
	
	String FileTools::openFolderPicker(const String&title, const String&startingDir)
	{
		//TODO implement ios folder picker
		return "";
	}
	
#endif
}

#endif
