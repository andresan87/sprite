#ifndef PLATFORM_SDL_INPUT_H_
#define PLATFORM_SDL_INPUT_H_

#include "SDLJoystick.h"

namespace sprite {

class SDLInput : public SDLJoystick
{
	math::Vector2 m_cursorPos;
	math::Vector2 m_lastCursorPos;

	KeyStateManager m_keyStates[K_NUM_KEYS];
	SDL_Scancode m_sdlKeyID[K_NUM_KEYS];
	Uint8 m_mouseBits;

	void UpdateCursorPos();
	bool IsKeyPressed(const KEY key, const Uint8* keystate);

public:
	SDLInput(const bool showJoystickWarnings);

	bool IsKeyDown(const KEY key) const;
	KEY_STATE GetKeyState(const KEY key) const;

	KEY_STATE GetLeftClickState() const;
	KEY_STATE GetRightClickState() const;
	KEY_STATE GetMiddleClickState() const;

	math::Vector2  GetMouseMove() const;

	math::Vector2 GetTouchPos(const unsigned int n, const VideoPtr& video = VideoPtr()) const;
	KEY_STATE  GetTouchState(const unsigned int n, const VideoPtr& video = VideoPtr()) const;
	unsigned int GetMaxTouchCount() const;
	math::Vector2 GetTouchMove(const unsigned int n) const;

	void SetCursorPosition(const math::Vector2& pos);
	math::Vector2 GetCursorPosition(const VideoPtr& video) const;

	float GetWheelState() const;

	void Update();

	std::string GetLastCharInput() const;

	math::Vector3 GetAccelerometerData() const;
};

} // namespace sprite

#endif
