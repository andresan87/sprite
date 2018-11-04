#include "Input.h"

namespace sprite {

const math::Vector2 Input::NO_TOUCH(0xFFFFFFFF);

Input::KeyStateManager::KeyStateManager() :
	m_pressingElapsedFrameCount(0),
	m_currentState(Input::KS_UP)
{
}

void Input::KeyStateManager::Update(const bool isPressed)
{
	if (isPressed)
	{
		m_pressingElapsedFrameCount++;
	}
	else if (m_pressingElapsedFrameCount > 0)
	{
		m_pressingElapsedFrameCount = 0;
		m_currentState = KS_RELEASE;
		return;
	}
	else if (m_pressingElapsedFrameCount == 0)
	{
		m_currentState = KS_UP;
		return;
	}

	if (m_pressingElapsedFrameCount == 1)
	{
		m_currentState = KS_HIT;
		return;
	}
	m_currentState = KS_DOWN;
}

Input::KEY_STATE Input::KeyStateManager::GetCurrentState() const
{
	return m_currentState;
}

} // namespace sprite
