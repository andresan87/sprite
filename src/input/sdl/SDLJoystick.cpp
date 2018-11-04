#include "SDLJoystick.h"

#include "../../math/Util.h"

namespace sprite {

const float SDLJoystick::SDL_MIN_JAXIS = -32768.0f;
const float SDLJoystick::SDL_MAX_JAXIS = 32767.0f;
const float SDLJoystick::JOYSTICK_MIN_ARROW_VALUE = 0.8f;

SDLJoystick::Joystick::Joystick() :
	sdlJoystick(0),
	status(Input::JS_INVALID),
	z(0.0f),
	rudder(0.0f),
	nButtons(0)
{
}

SDLJoystick::SDLJoystick(const bool showJoystickWarnings) :
	m_showJoystickWarnings(showJoystickWarnings),
	m_logger(Logger::Create())
{
	DetectJoysticks();
}

static bool IsArrowPressed(SDLJoystick::Joystick& joy, const Input::JOYSTICK_BUTTON button, float axisValue)
{
	if (((button == Input::J_DOWN || button == Input::J_RIGHT) && axisValue >= SDLJoystick::JOYSTICK_MIN_ARROW_VALUE) ||
		((button == Input::J_UP   || button == Input::J_LEFT ) && axisValue <=-SDLJoystick::JOYSTICK_MIN_ARROW_VALUE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

static void UpdateJoystickAxes(SDLJoystick::Joystick& joy)
{
	const int nAxes = SDL_JoystickNumAxes(joy.sdlJoystick);

	static Sint16 axes[6];
	for (int a = 0; a < 6; a++)
	{
		axes[a] = SDL_JoystickGetAxis(joy.sdlJoystick, a);
		if (math::Util::Abs((int)axes[a]) < 130)
			axes[a] = 0;
	}

	// update X and Y axis
	const float stride = (float)SDLJoystick::SDL_MAX_JAXIS;
	joy.xy.x = (float)axes[0] / stride;
	joy.xy.y = (float)axes[1] / stride;
	joy.xy.x = math::Util::Min(math::Util::Max(joy.xy.x, -1.0f), 1.0f);
	joy.xy.y = math::Util::Min(math::Util::Max(joy.xy.y, -1.0f), 1.0f);

	// update Z axis
	if (nAxes > 2)
	{
		joy.z = (float)axes[2] / stride;
		joy.z = math::Util::Min(math::Util::Max(joy.z, -1.0f), 1.0f);
	}

	// update Rudder axis
	if (nAxes > 3)
	{
		joy.rudder = (float)axes[3] / stride;
		joy.rudder = math::Util::Min(math::Util::Max(joy.rudder, -1.0f), 1.0f);
	}

	// update U and V axis
	if (nAxes > 4)
	{
		joy.uv.x = (float)axes[4] / stride;
		joy.uv.x = math::Util::Min(math::Util::Max(joy.uv.x, -1.0f), 1.0f);
	}
	if (nAxes > 5)
	{
		joy.uv.y = (float)axes[5] / stride;
		joy.uv.y = math::Util::Min(math::Util::Max(joy.uv.y, -1.0f), 1.0f);
	}

	joy.state[Input::J_LEFT ].Update(IsArrowPressed(joy, Input::J_LEFT,  joy.xy.x));
	joy.state[Input::J_RIGHT].Update(IsArrowPressed(joy, Input::J_RIGHT, joy.xy.x));
	joy.state[Input::J_UP   ].Update(IsArrowPressed(joy, Input::J_UP,    joy.xy.y));
	joy.state[Input::J_DOWN ].Update(IsArrowPressed(joy, Input::J_DOWN,  joy.xy.y));
}

void SDLJoystick::Update()
{
	if (m_nDetectedJoysticks != SDL_NumJoysticks())
		DetectJoysticks();

	for (int j = 0; j < m_nDetectedJoysticks; j++)
	{
		if (m_joysticks[j].status == JS_DETECTED)
		{
			m_joysticks[j].status = (SDL_JoystickGetAttached(m_joysticks[j].sdlJoystick)) ? JS_DETECTED : JS_NOTDETECTED;

			if (m_joysticks[j].status != JS_DETECTED)
			{
				continue;
			}

			for (unsigned int t = 0; t < J_MAX_BUTTONS; t++)
			{
				if (t < m_joysticks[j].nButtons)
				{
					const bool isPressed = SDL_JoystickGetButton(m_joysticks[j].sdlJoystick, (int)t);
					m_joysticks[j].state[t].Update(isPressed);
				}
			}
			UpdateJoystickAxes(m_joysticks[j]);
		}
	}
}

void SDLJoystick::ShowJoystickWarnings(const bool enable)
{
	m_showJoystickWarnings = enable;
}

bool SDLJoystick::IsShowingJoystickWarnings() const
{
	return m_showJoystickWarnings;
}

void SDLJoystick::DetectJoysticks()
{
	m_nDetectedJoysticks = SDL_NumJoysticks();

	if (m_nDetectedJoysticks <= 0)
	{
		if (IsShowingJoystickWarnings())
		{
			m_logger->Log("No joysticks were detected", Logger::LMT_INFO);
		}
	}

	m_joysticks.clear();
	m_joysticks.resize(m_nDetectedJoysticks);
	for (unsigned int t = 0; t < m_nDetectedJoysticks; t++)
	{
		m_joysticks[t].sdlJoystick = SDL_JoystickOpen(t);
		if (m_joysticks[t].sdlJoystick && SDL_JoystickGetAttached(m_joysticks[t].sdlJoystick))
		{
			m_joysticks[t].status = JS_DETECTED;
			m_joysticks[t].nButtons = SDL_JoystickNumButtons(m_joysticks[t].sdlJoystick);
		}
		else
		{
			m_joysticks[t].nButtons = 0;
			m_joysticks[t].status = JS_INVALID;
		}
	}
}

unsigned int SDLJoystick::GetMaxJoysticks() const
{
	return 4;
}

unsigned int SDLJoystick::GetNumJoysticks() const
{
	return static_cast<unsigned int>(m_joysticks.size());
}

Input::JOYSTICK_STATUS SDLJoystick::GetJoystickStatus(const unsigned int joystickId) const
{
	if (joystickId >= m_joysticks.size())
	{
		return JS_INVALID;
	}
	return m_joysticks[joystickId].status;
}

unsigned int SDLJoystick::GetNumJoyButtons(const unsigned int joystickId) const
{
	if (GetJoystickStatus(joystickId) != JS_DETECTED)
	{
		return 0;
	}
	return m_joysticks[joystickId].nButtons;
}

Input::KEY_STATE SDLJoystick::GetJoystickButtonState(const unsigned int joystickId, const JOYSTICK_BUTTON key) const
{
	if (GetJoystickStatus(joystickId) != JS_DETECTED)
	{
		return KS_UP;
	}
	return m_joysticks[joystickId].state[key].GetCurrentState();
}

bool SDLJoystick::IsJoystickButtonDown(const unsigned int joystickId, const JOYSTICK_BUTTON key) const
{
	const KEY_STATE state = GetJoystickButtonState(joystickId, key);
	return (state == KS_DOWN || state == KS_HIT);
}

Input::JOYSTICK_BUTTON SDLJoystick::GetFirstButtonDown(const unsigned int joystickId) const
{
	if (GetJoystickStatus(joystickId) != JS_DETECTED)
	{
		return J_NONE;
	}

	for (unsigned int t = 0; t < m_joysticks[joystickId].nButtons; t++)
	{
		if (IsJoystickButtonDown(joystickId, (JOYSTICK_BUTTON)t))
		{
			return (JOYSTICK_BUTTON)t;
		}
	}
	return J_NONE;
}

math::Vector2 SDLJoystick::GetJoystickXY(const unsigned int joystickId) const
{
	if (GetJoystickStatus(joystickId) != JS_DETECTED)
	{
		return math::Vector2();
	}
	return m_joysticks[joystickId].xy;
}

float SDLJoystick::GetJoystickZ(const unsigned int joystickId) const
{
	if (GetJoystickStatus(joystickId) != JS_DETECTED)
	{
		return 0.0f;
	}
	return m_joysticks[joystickId].z;
}

float SDLJoystick::GetJoystickRudder(const unsigned int joystickId) const
{
	if (GetJoystickStatus(joystickId) != JS_DETECTED)
	{
		return 0.0f;
	}
	return m_joysticks[joystickId].rudder;
}

math::Vector2 SDLJoystick::GetJoystickUV(const unsigned int joystickId) const
{
	if (GetJoystickStatus(joystickId) != JS_DETECTED)
	{
		return math::Vector2();
	}
	return m_joysticks[joystickId].uv;
}

} // namespace sprite
