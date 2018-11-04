#ifndef SPRITE_SDL_JOYSTICK_H_
#define SPRITE_SDL_JOYSTICK_H_

#include "../Input.h"

#include "../../platform/Logger.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#include <vector>

namespace sprite {

class SDLJoystick : virtual public Input
{
	bool m_showJoystickWarnings;
	unsigned int m_nDetectedJoysticks;

	LoggerPtr m_logger;

public:

	static const float SDL_MIN_JAXIS;
	static const float SDL_MAX_JAXIS;
	static const float JOYSTICK_MIN_ARROW_VALUE;

	class Joystick
	{
	public:
		Joystick();
		SDL_Joystick* sdlJoystick;
		Input::JOYSTICK_STATUS status;
		math::Vector2 xy;
		float z;
		float rudder;
		math::Vector2 uv;
		KeyStateManager state[Input::J_MAX_BUTTONS];
		int nButtons;
	};

	SDLJoystick(const bool showJoystickWarnings);

	void Update();

	void ShowJoystickWarnings(const bool enable);
	bool IsShowingJoystickWarnings() const;
	unsigned int GetMaxJoysticks() const;

	KEY_STATE GetJoystickButtonState(const unsigned int joystickId, const JOYSTICK_BUTTON key) const;
	bool IsJoystickButtonDown(const unsigned int joystickId, const JOYSTICK_BUTTON key) const;
	void DetectJoysticks();
	JOYSTICK_STATUS GetJoystickStatus(const unsigned int joystickId) const;
	unsigned int GetNumJoyButtons(const unsigned int joystickId) const;
	math::Vector2 GetJoystickXY(const unsigned int joystickId) const;
	float GetJoystickZ(const unsigned int joystickId) const;
	float GetJoystickRudder(const unsigned int joystickId) const;
	math::Vector2 GetJoystickUV(const unsigned int joystickId) const;
	JOYSTICK_BUTTON GetFirstButtonDown(const unsigned int joystickId) const;
	unsigned int GetNumJoysticks() const;

private:
	std::vector<Joystick> m_joysticks;
};

} // namespace sprite

#endif
