#ifndef MACOS_PLATFORM_FILE_IO_HUB_H_
#define MACOS_PLATFORM_FILE_IO_HUB_H_

#include "../FileIOHub.h"

namespace sprite {

class MacOSFileIOHub : public FileIOHub
{
	std::string m_resourceDirectory;
	std::string m_externalStorageDirectory;

public:
	MacOSFileIOHub();

	std::string GetResourceDirectory() const;
	std::string GetExternalStorageDirectory() const;
};

} // namespace sprite

#endif
