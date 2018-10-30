#ifndef PLATFORM_FILE_BUFFER_H_
#define PLATFORM_FILE_BUFFER_H_

#include <memory>

namespace sprite {

class FileBuffer
{
public:
	FileBuffer(const unsigned int size);
	~FileBuffer();
	unsigned int GetBufferSize() const;
	unsigned char* GetAddress() const;

private:
	unsigned char* m_buffer;
	unsigned int m_bufferSize;
};

typedef std::shared_ptr<FileBuffer> FileBufferPtr;

} // namespace sprite

#endif
