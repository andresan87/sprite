#include "../../video/sdl/SDLVideo.h"

int main(int argc, const char * argv[])
{
	using namespace sprite;
	
	VideoPtr video = Video::Create("Sprite", math::Vector2(800.0f, 600.0f), false);
	
	Video::APP_STATUS status;
	while ((status = video->HandleEvents()) != Video::AS_QUIT)
	{
		if (status == Video::AS_SKIP)
			continue;
	}
	return 0;
}
