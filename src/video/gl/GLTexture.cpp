#include "GLTexture.h"

#include "../../math/Util.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcomma"
#define STB_IMAGE_IMPLEMENTATION
#include "../../utilities/stb/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../../utilities/stb/stb_image_resize.h"
#pragma clang diagnostic pop

namespace sprite {

TexturePtr Texture::Create(
	const VideoPtr& video,
	const FileManagerPtr fileManager,
	const std::string& fileName)
{
	return std::make_shared<GLTexture>(video, fileManager, fileName);
}

GLTexture::GLTexture(
	const VideoPtr& video,
	const FileManagerPtr fileManager,
	const std::string& fileName)
{
	int width, height, nrChannels;

	FileBufferPtr fileBuffer;
	fileManager->GetFileBuffer(fileName, fileBuffer);

	stbi_uc* data = stbi_load_from_memory(
		(stbi_uc*)fileBuffer->GetAddress(),
		fileBuffer->GetBufferSize(),
		&width,
		&height,
		&nrChannels,
		0);

	if (data == NULL)
	{
		video->Log("GLTexture couldn't load file " + fileName, Video::LMT_ERROR);
		return;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	GLint format;
	switch (nrChannels)
	{
		case 1: format = GL_RED; break;
		case 2: format = GL_RG; break;
		case 3: format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
		default:
			stbi_image_free(data);
			glDeleteTextures(1, &m_texture);
			video->Log("GLTexture invalid format for file " + fileName, Video::LMT_ERROR);
			return;
	}
	
	m_resolution.x = (float)width;
	m_resolution.y = (float)height;

	if (math::Util::IsPowerOfTwo(width) && math::Util::IsPowerOfTwo(height))
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		const int newWidth  = math::Util::FindNextPowerOfTwoValue(width);
		const int newHeight = math::Util::FindNextPowerOfTwoValue(height);

		unsigned char* output = new unsigned char [newWidth * newHeight * nrChannels];
		stbir_resize_uint8(data, width, height, 0, output, newWidth, newHeight, 0, nrChannels);

		glTexImage2D(GL_TEXTURE_2D, 0, format, newWidth, newHeight, 0, format, GL_UNSIGNED_BYTE, output);

		delete [] output;
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &m_texture);
}

GLuint GLTexture::GetTexture() const
{
	return m_texture;
}

math::Vector2 GLTexture::GetResolution() const
{
	return m_resolution;
}

} // namespace sprite
