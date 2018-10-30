#include "MacOSFileIOHub.h"

#import <AppKit/AppKit.h>

namespace sprite {

FileIOHubPtr FileIOHub::Create()
{
	return std::make_shared<MacOSFileIOHub>();
}

bool CreateDirectoryNS(NSString* dir)
{
	bool r;
	@autoreleasepool {
		NSFileManager* fileManager = [NSFileManager defaultManager];
		r = ([fileManager createDirectoryAtPath:dir withIntermediateDirectories:YES attributes:nil error:nil] == YES);
	}
	return r;
}

MacOSFileIOHub::MacOSFileIOHub()
{
	@autoreleasepool {
		// prepare resource directory
		NSString* resourceDir = [[NSBundle mainBundle] resourcePath];
		resourceDir = [resourceDir stringByAppendingString:@"/assets/"];
		m_resourceDirectory = [resourceDir cStringUsingEncoding:1];

		// prepare external storage directory
		NSString* externalStorageDir = [NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES) objectAtIndex:0];
		externalStorageDir = [externalStorageDir stringByAppendingString:@"/"];
		CreateDirectoryNS(externalStorageDir);
		m_externalStorageDirectory = [externalStorageDir cStringUsingEncoding:1];
	}
}

std::string MacOSFileIOHub::GetResourceDirectory() const
{
	return m_resourceDirectory;
}

std::string MacOSFileIOHub::GetExternalStorageDirectory() const
{
	return m_externalStorageDirectory;
}

} // namespace sprite
