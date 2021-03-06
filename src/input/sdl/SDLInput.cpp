#include "SDLInput.h"

#include "../../video/sdl/SDLVideo.h"

namespace sprite {

InputPtr Input::Create()
{
	return std::make_shared<SDLInput>(true);
}

SDLInput::SDLInput(const bool showJoystickWarnings) :
	SDLJoystick(showJoystickWarnings),
	m_cursorPos(math::Vector2(Input::NO_TOUCH)),
	m_lastCursorPos(math::Vector2(0.0f)),
	m_mouseBits(0)
{
	m_sdlKeyID[K_UP] = SDL_SCANCODE_UP;
	m_sdlKeyID[K_DOWN] = SDL_SCANCODE_DOWN;
	m_sdlKeyID[K_LEFT] = SDL_SCANCODE_LEFT;
	m_sdlKeyID[K_RIGHT] = SDL_SCANCODE_RIGHT;
	m_sdlKeyID[K_CTRL] = SDL_SCANCODE_LCTRL;
	m_sdlKeyID[K_ALT] = SDL_SCANCODE_LALT;
	m_sdlKeyID[K_SHIFT] = SDL_SCANCODE_LSHIFT;
	m_sdlKeyID[K_PAGEDOWN] = SDL_SCANCODE_PAGEDOWN;
	m_sdlKeyID[K_PAGEUP] = SDL_SCANCODE_PAGEUP;
	m_sdlKeyID[K_SPACE] = SDL_SCANCODE_SPACE;
	m_sdlKeyID[K_ENTER] = SDL_SCANCODE_RETURN;
	m_sdlKeyID[K_DELETE] = SDL_SCANCODE_DELETE;
	m_sdlKeyID[K_HOME] = SDL_SCANCODE_HOME;
	m_sdlKeyID[K_END] = SDL_SCANCODE_END;
	m_sdlKeyID[K_INSERT] = SDL_SCANCODE_INSERT;
	m_sdlKeyID[K_PAUSE] = SDL_SCANCODE_PAUSE;
	m_sdlKeyID[K_ESC] = SDL_SCANCODE_ESCAPE;
	m_sdlKeyID[K_BACK] = SDL_SCANCODE_BACKSPACE;
	m_sdlKeyID[K_TAB] = SDL_SCANCODE_TAB;
	m_sdlKeyID[K_PRINTSCREEN] = SDL_SCANCODE_PRINTSCREEN;
	m_sdlKeyID[K_SUBTRACT] = SDL_SCANCODE_MINUS;
	m_sdlKeyID[K_ADD] = SDL_SCANCODE_KP_PLUS; // this is messed up
	m_sdlKeyID[K_F1] = SDL_SCANCODE_F1;
	m_sdlKeyID[K_F2] = SDL_SCANCODE_F2;
	m_sdlKeyID[K_F3] = SDL_SCANCODE_F3;
	m_sdlKeyID[K_F4] = SDL_SCANCODE_F4;
	m_sdlKeyID[K_F5] = SDL_SCANCODE_F5;
	m_sdlKeyID[K_F6] = SDL_SCANCODE_F6;
	m_sdlKeyID[K_F7] = SDL_SCANCODE_F7;
	m_sdlKeyID[K_F8] = SDL_SCANCODE_F8;
	m_sdlKeyID[K_F9] = SDL_SCANCODE_F9;
	m_sdlKeyID[K_F10] = SDL_SCANCODE_F10;
	m_sdlKeyID[K_F11] = SDL_SCANCODE_F11;
	m_sdlKeyID[K_F12] = SDL_SCANCODE_F12;
	m_sdlKeyID[K_F13] = SDL_SCANCODE_F13;
	m_sdlKeyID[K_F14] = SDL_SCANCODE_F14;
	m_sdlKeyID[K_F15] = SDL_SCANCODE_F15;
	m_sdlKeyID[K_F16] = SDL_SCANCODE_F16;
	m_sdlKeyID[K_F17] = SDL_SCANCODE_F17;
	m_sdlKeyID[K_F18] = SDL_SCANCODE_F18;
	m_sdlKeyID[K_F19] = SDL_SCANCODE_F19;
	m_sdlKeyID[K_F20] = SDL_SCANCODE_F20;
	m_sdlKeyID[K_F21] = SDL_SCANCODE_F21;
	m_sdlKeyID[K_F22] = SDL_SCANCODE_F22;
	m_sdlKeyID[K_F23] = SDL_SCANCODE_F23;
	m_sdlKeyID[K_F24] = SDL_SCANCODE_F24;
	m_sdlKeyID[K_A] = SDL_SCANCODE_A;
	m_sdlKeyID[K_B] = SDL_SCANCODE_B;
	m_sdlKeyID[K_C] = SDL_SCANCODE_C;
	m_sdlKeyID[K_D] = SDL_SCANCODE_D;
	m_sdlKeyID[K_E] = SDL_SCANCODE_E;
	m_sdlKeyID[K_F] = SDL_SCANCODE_F;
	m_sdlKeyID[K_G] = SDL_SCANCODE_G;
	m_sdlKeyID[K_H] = SDL_SCANCODE_H;
	m_sdlKeyID[K_I] = SDL_SCANCODE_I;
	m_sdlKeyID[K_J] = SDL_SCANCODE_J;
	m_sdlKeyID[K_K] = SDL_SCANCODE_K;
	m_sdlKeyID[K_L] = SDL_SCANCODE_L;
	m_sdlKeyID[K_M] = SDL_SCANCODE_M;
	m_sdlKeyID[K_N] = SDL_SCANCODE_N;
	m_sdlKeyID[K_O] = SDL_SCANCODE_O;
	m_sdlKeyID[K_P] = SDL_SCANCODE_P;
	m_sdlKeyID[K_Q] = SDL_SCANCODE_Q;
	m_sdlKeyID[K_R] = SDL_SCANCODE_R;
	m_sdlKeyID[K_S] = SDL_SCANCODE_S;
	m_sdlKeyID[K_T] = SDL_SCANCODE_T;
	m_sdlKeyID[K_U] = SDL_SCANCODE_U;
	m_sdlKeyID[K_V] = SDL_SCANCODE_V;
	m_sdlKeyID[K_W] = SDL_SCANCODE_W;
	m_sdlKeyID[K_X] = SDL_SCANCODE_X;
	m_sdlKeyID[K_Y] = SDL_SCANCODE_Y;
	m_sdlKeyID[K_Z] = SDL_SCANCODE_Z;
	m_sdlKeyID[K_1] = SDL_SCANCODE_1;
	m_sdlKeyID[K_2] = SDL_SCANCODE_2;
	m_sdlKeyID[K_3] = SDL_SCANCODE_3;
	m_sdlKeyID[K_4] = SDL_SCANCODE_4;
	m_sdlKeyID[K_5] = SDL_SCANCODE_5;
	m_sdlKeyID[K_6] = SDL_SCANCODE_6;
	m_sdlKeyID[K_7] = SDL_SCANCODE_7;
	m_sdlKeyID[K_8] = SDL_SCANCODE_8;
	m_sdlKeyID[K_9] = SDL_SCANCODE_9;
	m_sdlKeyID[K_0] = SDL_SCANCODE_0;
	m_sdlKeyID[K_NUMPAD0] = SDL_SCANCODE_KP_0;
	m_sdlKeyID[K_NUMPAD1] = SDL_SCANCODE_KP_1;
	m_sdlKeyID[K_NUMPAD2] = SDL_SCANCODE_KP_2;
	m_sdlKeyID[K_NUMPAD3] = SDL_SCANCODE_KP_3;
	m_sdlKeyID[K_NUMPAD4] = SDL_SCANCODE_KP_4;
	m_sdlKeyID[K_NUMPAD5] = SDL_SCANCODE_KP_5;
	m_sdlKeyID[K_NUMPAD6] = SDL_SCANCODE_KP_6;
	m_sdlKeyID[K_NUMPAD7] = SDL_SCANCODE_KP_7;
	m_sdlKeyID[K_NUMPAD8] = SDL_SCANCODE_KP_8;
	m_sdlKeyID[K_NUMPAD9] = SDL_SCANCODE_KP_9;
	m_sdlKeyID[K_MINUS] = SDL_SCANCODE_KP_MINUS;
	m_sdlKeyID[K_PLUS] = SDL_SCANCODE_KP_PLUS;
	m_sdlKeyID[K_COMMA] = SDL_SCANCODE_COMMA;
	m_sdlKeyID[K_DOT] = SDL_SCANCODE_PERIOD;
	m_sdlKeyID[K_META] = SDL_SCANCODE_LGUI;

	// not used:
	m_sdlKeyID[K_RMOUSE] = SDL_NUM_SCANCODES;
	m_sdlKeyID[K_LMOUSE] = SDL_NUM_SCANCODES;
	m_sdlKeyID[K_MMOUSE] = SDL_NUM_SCANCODES;

	UpdateCursorPos();
	m_lastCursorPos = m_cursorPos;
}

void SDLInput::Update()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	for (std::size_t t = 0; t < K_NUM_KEYS; t++)
	{
		m_keyStates[t].Update(IsKeyPressed((KEY)t, keystate));
	}

	UpdateCursorPos();
	SDLJoystick::Update();
}

bool SDLInput::IsKeyPressed(const KEY key, const Uint8* keystate)
{
	switch (key)
	{
	case K_LMOUSE:
		return (m_mouseBits & SDL_BUTTON(1));
	case K_MMOUSE:
		return (m_mouseBits & SDL_BUTTON(2));
	case K_RMOUSE:
		return (m_mouseBits & SDL_BUTTON(3));
	default:
		// just preventing the warning
		break;
	};
	return (keystate[m_sdlKeyID[key]] != 0);
}

void SDLInput::UpdateCursorPos()
{
	m_lastCursorPos = m_cursorPos;
	int x, y;
	m_mouseBits = SDL_GetMouseState(&x, &y);
	m_cursorPos.x = x;
	m_cursorPos.y = y;
}

void SDLInput::SetCursorPosition(const math::Vector2& pos)
{
	m_cursorPos = pos;
	SDL_WarpMouseInWindow(NULL, static_cast<Uint16>(pos.x), static_cast<Uint16>(pos.y));
}

math::Vector2 SDLInput::GetCursorPosition(const VideoPtr& video) const
{
	return m_cursorPos;
}

unsigned int SDLInput::GetMaxTouchCount() const
{
	return 1;
}

math::Vector2 SDLInput::GetMouseMove() const
{
	return m_cursorPos - m_lastCursorPos;
}

math::Vector2 SDLInput::GetTouchMove(const unsigned int n) const
{
	if (n == 0)
	{
		return (IsKeyDown(K_LMOUSE)) ? GetMouseMove() : math::Vector2(0.0f);
	}
	else
	{
		return math::Vector2(0.0f);
	}
}

math::Vector2 SDLInput::GetTouchPos(const unsigned int n, const VideoPtr& video) const
{
	return GetCursorPosition(video);
}

math::Vector3 SDLInput::GetAccelerometerData() const
{
	return math::Vector3();
}

bool SDLInput::IsKeyDown(const KEY key) const
{
	const KEY_STATE state = m_keyStates[key].GetCurrentState();
	return (state == KS_DOWN || state == KS_HIT);
}

Input::KEY_STATE SDLInput::GetKeyState(const KEY key) const
{
	return m_keyStates[key].GetCurrentState();
}

Input::KEY_STATE SDLInput::GetLeftClickState() const
{
	return m_keyStates[K_LMOUSE].GetCurrentState();
}

Input::KEY_STATE SDLInput::GetRightClickState() const
{
	return m_keyStates[K_RMOUSE].GetCurrentState();
}

Input::KEY_STATE SDLInput::GetMiddleClickState() const
{
	return m_keyStates[K_MMOUSE].GetCurrentState();
}

Input::KEY_STATE SDLInput::GetTouchState(const unsigned int n, const VideoPtr& video) const
{
	return GetLeftClickState();
}

float SDLInput::GetWheelState() const
{
	return SDLVideo::m_mouseWheel;
}

std::string SDLInput::GetLastCharInput() const
{
	if (SDLVideo::m_lastCharInput.length() == 1)
	{
		const char c = SDLVideo::m_lastCharInput[0];
		switch (c)
		{
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:
		case 0x0E:
		case 0x0F:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1A:
		case 0x1B:
		case 0x7F:
			return "";
		}
	}
	return SDLVideo::m_lastCharInput;
}

} // namespace sprite
