#include "../../sprite/Sprite.h"

#include "../../input/Input.h"

#include "../../platform/FileIOHub.h"
#include "../../platform/StdFileManager.h"

int main(int argc, const char * argv[])
{
	using namespace sprite;

	FileIOHubPtr fileIOHub = FileIOHub::Create();
	FileManagerPtr fileManager(new StdFileManager);

	VideoPtr video = Video::Create("Sprite", math::Vector2(1280.0f, 720.0f), false /*fullScreen*/);
	InputPtr input = Input::Create();

	SpritePtr pixelPerfectSpaceShip(new Sprite(video, fileManager, fileIOHub->GetResourceDirectory() + "space-ship.png"));

	video->SetClearColor(Color(0xFF336699));

	Video::APP_STATUS status;
	while ((status = video->HandleEvents()) != Video::AS_QUIT)
	{
		if (status == Video::AS_SKIP)
			continue;

		input->Update();

		Sprite::SetVirtualScreenHeight(video->GetResolution(), 720.0f);

		video->BeginRendering();
		{
			pixelPerfectSpaceShip->Draw(math::Vector2(0.0f), math::Vector2(0.5f));
			
			pixelPerfectSpaceShip->Draw(input->GetTouchPos(0), math::Vector2(0.5f, 1.0f));
		}
		video->EndRendering();
	}
	return 0;
}
