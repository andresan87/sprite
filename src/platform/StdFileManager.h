#ifndef PLATFORM_STD_FILE_MANAGER_H_
#define PLATFORM_STD_FILE_MANAGER_H_

#include "FileManager.h"

namespace sprite {

class StdFileManager : public FileManager
{
public:
	bool IsLoaded() const;
	bool GetFileBuffer(const std::string& fileName, FileBufferPtr& outBuff);
	bool FileExists(const std::string& fileName) const;
	bool IsPacked() const;
};

typedef std::shared_ptr<StdFileManager> StdFileManagerPtr;

} // namespace sprite

#endif
