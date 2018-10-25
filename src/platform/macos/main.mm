#include "../sdl/SDLVideo.h"

int main(int argc, const char * argv[])
{
	using namespace sprite;
	
	VideoPtr video = Video::Create("Sprite", math::Vector2(800.0f, 600.0f), false);
	
	Application::APP_STATUS status;
	while ((status = video->HandleEvents()) != Application::AS_QUIT)
	{
		if (status == Application::AS_SKIP)
			continue;
	}
	return 0;
}
