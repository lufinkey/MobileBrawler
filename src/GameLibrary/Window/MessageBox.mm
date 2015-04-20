
#ifdef __OBJC__

#include "MessageBox.h"
#include "../Utilities/Thread.h"
#include <SDL.h>

#if defined(TARGETPLATFORM_IOS)
	#import <UIKit/UIKit.h>
#endif

namespace GameLibrary
{
	#if defined(TARGETPLATFORM_IOS)
	unsigned int MessageBox::show(Window*parent, const String&title, const String&message)
	{
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:(const char*)title]
														message:[NSString stringWithUTF8String:(const char*)message]
														delegate:nil
														cancelButtonTitle:@"OK"
														otherButtonTitles:nil];
		[alert show];
		EventManager::update();
		while(alert.visible)
		{
			Thread::sleep(16);
			EventManager::update();
		}
		#if !__has_feature(objc_arc)
			[alert release];
		#endif
		return 0;
	}
	
	@interface MessageBoxDelegate : NSObject <UIAlertViewDelegate>
	{
		NSInteger result;
	}
	@property (nonatomic) NSInteger result;
	@end
	
	@implementation MessageBoxDelegate
	@synthesize result;
	-(id)init
	{
		if(self = [super init])
		{
			result = (NSInteger)-1;
		}
		return self;
	}
	- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex
	{
		result = buttonIndex;
	}
	- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
	{
		result = buttonIndex;
	}
	@end
	
	unsigned int MessageBox::show(Window*parent, const String&title, const String&message, const ArrayList<String>&options)
	{
		MessageBoxDelegate*messageDelegate = [[MessageBoxDelegate alloc] init];
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:(const char*)title]
														message:[NSString stringWithUTF8String:(const char*)message]
														delegate:messageDelegate
														cancelButtonTitle:nil
														otherButtonTitles:nil];
		for(int i=0; i<numOptions; i++)
		{
			[alert addButtonWithTitle:[NSString stringWithUTF8String:options[i]]];
		}
		[alert show];
		EventManager::update();
		while(alert.visible)
		{
			Thread::sleep(16);
			EventManager::update();
		}
		NSInteger result = [messageDelegate result];
		#if !__has_feature(objc_arc)
			[alert release];
			[messageDelegate release];
		#endif
		return (unsigned int)result;
	}
	#endif
}

#endif
