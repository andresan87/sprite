#include "StdFileManager.h"

#include <fstream>

namespace sprite {

bool StdFileManager::IsLoaded() const
{
	return true;
}

bool StdFileManager::GetFileBuffer(const std::string& fileName, FileBufferPtr& outBuff)
{
	std::ifstream file(fileName, std::ios::binary | std::ios::ate);

	if (file.fail())
	{
		return false;
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	outBuff = FileBufferPtr(new FileBuffer((unsigned int)size));
	if (!file.read((char*)outBuff->GetAddress(), size).fail())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool StdFileManager::FileExists(const std::string& fileName) const
{
	std::ifstream file(fileName, std::ios::binary);
	return (!file.fail());
}

bool StdFileManager::IsPacked() const
{
	return false;
}

} // namespace sprite
