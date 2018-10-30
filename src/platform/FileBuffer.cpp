#include "FileBuffer.h"

namespace sprite {

FileBuffer::FileBuffer(const unsigned int size)
{
	assert(sizeof(unsigned char) == 1);
	m_buffer = 0;
	m_bufferSize = size;

	if (size > 0)
	{
		m_buffer = new unsigned char [size];
	}
}

FileBuffer::~FileBuffer()
{
	if (m_buffer)
	{
		delete [] m_buffer;
		m_buffer = 0;
	}
}

unsigned int FileBuffer::GetBufferSize() const
{
	return m_bufferSize;
}

unsigned char* FileBuffer::GetAddress() const
{
	return m_buffer;
}

} // namespace sprite
