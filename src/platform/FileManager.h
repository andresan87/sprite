#ifndef PLATFORM_FILE_MANAGER_H_
#define PLATFORM_FILE_MANAGER_H_

#include "FileBuffer.h"

#include <string>
#include <memory>
#include <cstdint>

namespace sprite {

class FileManager
{
	bool GetUTF8FileString(const FileBufferPtr& buffer, std::string& outStr);
	bool GetUTF16FileString(const FileBufferPtr& buffer, std::string& outStr);
	bool HasUTF16LEBOM(const FileBufferPtr& buffer);

public:
	bool GetAnsiFileString(const std::string& fileName, std::string& outStr);
	bool GetUTF8FileString(const std::string& fileName, std::string& outStr);
	bool GetUTF16FileString(const std::string& fileName, std::string& outStr);
	bool GetUTFFileString(const std::string& fileName, std::string& outStr);

	virtual bool IsLoaded() const = 0;
	virtual bool GetFileBuffer(const std::string& fileName, FileBufferPtr& outBuff) = 0;

	virtual bool FileExists(const std::string& fileName) const = 0;
	virtual bool IsPacked() const = 0;
    
	static const uint16_t UTF16LE_BOM;
};

typedef std::shared_ptr<FileManager> FileManagerPtr;

} // namespace sprite

#endif
