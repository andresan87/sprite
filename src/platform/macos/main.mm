#include "../../sprite/Sprite.h"
#include "../../sprite/SpriteRects.h"

#include "../../input/Input.h"

#include "../../platform/FileIOHub.h"
#include "../../platform/StdFileManager.h"

#include "../../math/Color.h"
#include "../../math/Util.h"

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
	SpritePtr demon(new Sprite(video, fileManager, fileIOHub->GetResourceDirectory() + "spider_demon.png"));

	SpriteRects demonRects;
	demonRects.SetRects(4, 1);
	unsigned int demonFrame = 0;

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

		if (input->GetKeyState(Input::K_E) == Input::KS_HIT)
			demonFrame--;

		if (input->GetKeyState(Input::K_R) == Input::KS_HIT)
			demonFrame++;

		Sprite::SetVirtualScreenHeight(video->GetResolution(), 720.0f);
		Sprite::SetParallaxIntensity(2.0f);

		video->BeginRendering();
		{
			spriteImage->Draw(Vector3(0.0f), Sprite::GetVirtualScreenResolution(), Vector2(0.0f), Color(0xFFFFFFFF), 0.0f, flipX, flipY);
			pixelPerfectSpaceShip->Draw(Vector3(0.0f), Vector2(0.5f), 1.0f, angle);
			pixelPerfectSpaceShip->Draw(Vector3(256.0f, 512.0f, 0.0f), Vector2(128.0f), Vector2(0.5f), Color(0x77FF0000), 90.0f, false, false);
			
			for (float z = -20.0f; z <= 20.0f; z += 2.0f)
			{
				pixelPerfectSpaceShip->Draw(Vector3(input->GetTouchPos(0), z), Vector2(0.5f, 1.0f), 1.5f, -angle);
			}

			for (float z = -80.0f; z <= 80.0f; z += 8.0f)
			{
				const Color solidColor(0.0f, 0.4f, 0.6f, Util::Clamp(z / 80.0f, 0.0f, 1.0f));
				pixelPerfectSpaceShip->Draw(
					Vector3(Vector2(1040.0f, 480.0f), z),
					pixelPerfectSpaceShip->GetSize(),
					Vector2(0.5f),
					Color(1.0f, 1.0f, 1.0f, 1.0f),
					-angle,
					false,
					false,
					&solidColor);
			}

			demon->SetRect(demonRects.GetRect(demonFrame));
			demon->Draw(Vector3(800.0f, 0.0f, 0.0f), Vector2(0.5f, 0.0f), 1.0f);
		}
		video->EndRendering();
	}
	return 0;
}
