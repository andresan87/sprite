#ifndef PLATFORM_FILE_IO_HUB_H_
#define PLATFORM_FILE_IO_HUB_H_

#include "FileManager.h"

namespace sprite {

class FileIOHub;

typedef std::shared_ptr<FileIOHub> FileIOHubPtr;

class FileIOHub
{
public:
	static FileIOHubPtr Create();

	virtual std::string GetResourceDirectory() const = 0;
	virtual std::string GetExternalStorageDirectory() const = 0;
};

} // namespace sprite

#endif
