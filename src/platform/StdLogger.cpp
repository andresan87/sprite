#include "StdLogger.h"

#include <iostream>

namespace sprite {

LoggerPtr Logger::Create()
{
	return std::make_shared<StdLogger>();
}

void StdLogger::Log(const std::string& message, const Logger::LOG_MESSAGE_TYPE type)
{
	if (type == Logger::LMT_ERROR)
	{
		std::cerr << "ERROR" << " " << message << std::endl;
	}
	else
	{
		std::cout << message << std::endl;
	}
}

} // namespace sprite
