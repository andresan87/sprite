#include "FileManager.h"

#include <fstream>
#include <sstream>

#include "../utilities/utf8/utf8.h"

namespace sprite {

const uint16_t FileManager::UTF16LE_BOM = 0xFEFF;

bool FileManager::GetUTF8FileString(const FileBufferPtr& buffer, std::string& outStr)
{
	unsigned char* adr = buffer->GetAddress();
	const unsigned int bufferSize = buffer->GetBufferSize();
	
	if (bufferSize == 0)
		return false;

	// check for UTF8 BOM
	unsigned int firstChar = 0;
	if (utf8::starts_with_bom(&adr[0], &adr[bufferSize]))
	{
		firstChar = 3;
	}

	utf8::replace_invalid(&adr[firstChar], &adr[bufferSize], back_inserter(outStr));
	return true;
}

bool FileManager::GetUTF16FileString(const FileBufferPtr& buffer, std::string& outStr)
{
    if (!HasUTF16LEBOM(buffer))
        return false;

	const unsigned int bufferSize = buffer->GetBufferSize();
	const unsigned int bomSizeInBytes = sizeof(UTF16LE_BOM);

	const unsigned char* begin = &(buffer->GetAddress()[bomSizeInBytes]);
	const unsigned char* end   = &begin[bufferSize - bomSizeInBytes];
	utf8::utf16to8((uint16_t*)begin, (uint16_t*)end, back_inserter(outStr));
	return true;
}

bool FileManager::HasUTF16LEBOM(const FileBufferPtr& buffer)
{
	const unsigned int bufferSize = buffer->GetBufferSize();

	if (bufferSize < sizeof(UTF16LE_BOM))
		return false;
	
	const uint16_t* firstTwoBytes = (uint16_t*)buffer->GetAddress();
	return (*firstTwoBytes == UTF16LE_BOM);
}

bool FileManager::GetUTF8FileString(const std::string& fileName, std::string& out)
{
	FileBufferPtr buffer;
	if (GetFileBuffer(fileName, buffer))
	{
		return GetUTF8FileString(buffer, out);
	}
	else
	{
		return false;
	}
}

bool FileManager::GetUTF16FileString(const std::string& fileName, std::string& out)
{
	FileBufferPtr buffer;
	if (GetFileBuffer(fileName, buffer))
	{
		return GetUTF16FileString(buffer, out);
	}
	else
	{
		return false;
	}
}

bool FileManager::GetUTFFileString(const std::string& fileName, std::string& out)
{
	FileBufferPtr buffer;
	if (GetFileBuffer(fileName, buffer))
	{
        if (HasUTF16LEBOM(buffer))
            return GetUTF16FileString(buffer, out);
        else
            return GetUTF8FileString(buffer, out);
	}
	else
	{
		return false;
	}
}

bool FileManager::GetAnsiFileString(const std::string& fileName, std::string& out)
{
	FileBufferPtr buffer;
	if (GetFileBuffer(fileName, buffer))
	{
		std::stringstream ss;
		unsigned char *adr = buffer->GetAddress();
		for (unsigned long t = 0; t < buffer->GetBufferSize(); t++)
		{
			const char c = static_cast<char>(adr[t]);
			if (c != 0x0D) // remove all carriage return
			{
				ss << c;
			}
		}
		out = ss.str();
		return true;
	}
	else
	{
		return false;
	}
}

} // namespace sprite
