#include "../../sprite/Sprite.h"

#include "../../input/Input.h"

#include "../../platform/FileIOHub.h"
#include "../../platform/StdFileManager.h"

#include "../../math/Color.h"

int main(int argc, const char * argv[])
{
	using namespace sprite;
	using namespace math;

	FileIOHubPtr fileIOHub = FileIOHub::Create();
	FileManagerPtr fileManager(new StdFileManager);

	VideoPtr video = Video::Create("Sprite", math::Vector2(1280.0f, 720.0f), false /*fullScreen*/);
	InputPtr input = Input::Create();

	SpritePtr spriteImage(new Sprite(video, fileManager, fileIOHub->GetResourceDirectory() + "sprite.jpg"));
	SpritePtr pixelPerfectSpaceShip(new Sprite(video, fileManager, fileIOHub->GetResourceDirectory() + "space-ship.png"));

	video->SetClearColor(Color(0xFF336699));

	float angle = 0.0f;
	bool flipX = false, flipY = false;

	Video::APP_STATUS status;
	while ((status = video->HandleEvents()) != Video::AS_QUIT)
	{
		if (status == Video::AS_SKIP)
			continue;

		input->Update();

		if (input->IsKeyDown(Input::K_Q))
			angle++;
		if (input->IsKeyDown(Input::K_A))
			angle--;

		if (input->GetKeyState(Input::K_X) == Input::KS_HIT)
			flipX = !flipX;

		if (input->GetKeyState(Input::K_Y) == Input::KS_HIT)
			flipY = !flipY;

		Sprite::SetVirtualScreenHeight(video->GetResolution(), 720.0f);

		video->BeginRendering();
		{
			spriteImage->Draw(Vector2(0.0f), Sprite::GetVirtualScreenResolution(), Vector2(0.0f), Color(0xFFFFFFFF), 0.0f, flipX, flipY);
			pixelPerfectSpaceShip->Draw(Vector2(0.0f), Vector2(0.5f), 1.0f, angle);
			pixelPerfectSpaceShip->Draw(Vector2(256.0f, 512.0f), Vector2(128.0f), Vector2(0.5f), Color(0x77FF0000), 90.0f, false, false);
			pixelPerfectSpaceShip->Draw(input->GetTouchPos(0), Vector2(0.5f, 1.0f), 1.5f, -angle);
		}
		video->EndRendering();
	}
	return 0;
}
