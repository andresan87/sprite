#include "StdFileManager.h"

namespace sprite {

static FILE* LoadFile(const std::string& fileName)
{
	FILE* file = 0;
	#if _MSC_VER >= 1500
		fopen_s(&file, fileName.c_str(), "rb");
	#else
		file = fopen(fileName.c_str(), "rb");
	#endif
	return file;
}

bool StdFileManager::IsLoaded() const
{
	return true;
}

bool StdFileManager::GetFileBuffer(const std::string& fileName, FileBufferPtr& outBuff)
{
	FILE* file = LoadFile(fileName);
	if (!file)
	{
		return false;
	}
	
	fseek(file, 0, SEEK_END);
	const long len = ftell(file);
	fseek(file, 0, SEEK_SET);

	outBuff = FileBufferPtr(new FileBuffer((unsigned int)len));
	fread(outBuff->GetAddress(), len, 1, file);
	fclose(file);
	return true;
}

bool StdFileManager::FileExists(const std::string& fileName) const
{
	FILE* file = LoadFile(fileName);
	if (!file)
	{
		return false;
	}
	else
	{
		fclose(file);
		return true;
	}
}

bool StdFileManager::IsPacked() const
{
	return false;
}

} // namespace sprite
