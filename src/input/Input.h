#ifndef SPRITE_INPUT_H_
#define SPRITE_INPUT_H_

#include "../video/Video.h"

#include "../math/Vector3.h"

namespace sprite {

class Input;

typedef std::shared_ptr<Input> InputPtr;

class Input
{
public:
	static const math::Vector2 NO_TOUCH;

	static InputPtr Create();

	enum KEY
	{
		K_UP,
		K_DOWN,
		K_LEFT,
		K_RIGHT,
		K_PAGEDOWN,
		K_PAGEUP,
		K_SPACE,
		K_ENTER,
		K_DELETE,
		K_HOME,
		K_END,
		K_INSERT,
		K_PAUSE,
		K_ESC,
		K_BACK,
		K_TAB,
		K_PRINTSCREEN,
		K_SUBTRACT,
		K_ADD,
		K_F1,
		K_F2,
		K_F3,
		K_F4,
		K_F5,
		K_F6,
		K_F7,
		K_F8,
		K_F9,
		K_F10,
		K_F11,
		K_F12,
		K_F13,
		K_F14,
		K_F15,
		K_F16,
		K_F17,
		K_F18,
		K_F19,
		K_F20,
		K_F21,
		K_F22,
		K_F23,
		K_F24,
		K_A,
		K_B,
		K_C,
		K_D,
		K_E,
		K_F,
		K_G,
		K_H,
		K_I,
		K_J,
		K_K,
		K_L,
		K_M,
		K_N,
		K_O,
		K_P,
		K_Q,
		K_R,
		K_S,
		K_T,
		K_U,
		K_V,
		K_W,
		K_X,
		K_Y,
		K_Z,
		K_0,
		K_1,
		K_2,
		K_3,
		K_4,
		K_5,
		K_6,
		K_7,
		K_8,
		K_9,
		K_MINUS,
		K_PLUS,
		K_COMMA,
		K_DOT,
		K_CTRL,
		K_ALT,
		K_SHIFT,
		K_RMOUSE,
		K_LMOUSE,
		K_MMOUSE,
		K_NUMPAD0,
		K_NUMPAD1,
		K_NUMPAD2,
		K_NUMPAD3,
		K_NUMPAD4,
		K_NUMPAD5,
		K_NUMPAD6,
		K_NUMPAD7,
		K_NUMPAD8,
		K_NUMPAD9,
		K_META,
		K_NUM_KEYS,
		K_BACKSPACE = K_BACK,
		K_MAC_DELETE = K_BACK,
		K_RETURN = K_ENTER,
		K_NO_KEY
	};

	enum JOYSTICK_STATUS
	{
		JS_DETECTED,
		JS_NOTDETECTED,
		JS_INVALID
	};

	enum JOYSTICK_BUTTON
	{
		J_01,
		J_02,
		J_03,
		J_04,
		J_05,
		J_06,
		J_07,
		J_08,
		J_09,
		J_10,
		J_11,
		J_12,
		J_13,
		J_14,
		J_15,
		J_16,
		J_17,
		J_18,
		J_19,
		J_20,
		J_21,
		J_22,
		J_23,
		J_24,
		J_25,
		J_26,
		J_27,
		J_28,
		J_29,
		J_30,
		J_31,
		J_32,
		J_UP,
		J_DOWN,
		J_LEFT,
		J_RIGHT,
		J_NONE,
		J_MAX_BUTTONS
	};

	enum KEY_STATE
	{
		KS_UP,
		KS_HIT,
		KS_DOWN,
		KS_RELEASE
	};

	class KeyStateManager
	{
		int m_pressingElapsedFrameCount;
		KEY_STATE m_currentState;

	public:
		KeyStateManager();
		void Update(const bool isPressed);
		KEY_STATE GetCurrentState() const;
	};

	virtual bool IsKeyDown(const KEY key) const = 0;
	virtual KEY_STATE GetKeyState(const KEY key) const = 0;

	virtual KEY_STATE GetLeftClickState() const = 0;
	virtual KEY_STATE GetRightClickState() const = 0;
	virtual KEY_STATE GetMiddleClickState() const = 0;

	virtual math::Vector2  GetMouseMove() const = 0;

	virtual math::Vector2 GetTouchPos(const unsigned int n, const VideoPtr& video = VideoPtr()) const = 0;
	virtual KEY_STATE  GetTouchState(const unsigned int n, const VideoPtr& video = VideoPtr()) const = 0;
	virtual unsigned int GetMaxTouchCount() const = 0;
	virtual math::Vector2 GetTouchMove(const unsigned int n) const = 0;

	virtual void SetCursorPosition(const math::Vector2& pos) = 0;
	virtual math::Vector2  GetCursorPosition(const VideoPtr& video) const = 0;

	virtual unsigned int GetMaxJoysticks() const = 0;
	virtual float GetWheelState() const = 0;

	virtual void Update() = 0;

	virtual void ShowJoystickWarnings(const bool enable) = 0;
	virtual bool IsShowingJoystickWarnings() const = 0;

	virtual std::string GetLastCharInput() const = 0;

	virtual KEY_STATE GetJoystickButtonState(const unsigned int joystickId, const JOYSTICK_BUTTON key) const = 0;
	virtual bool IsJoystickButtonDown(const unsigned int joystickId, const JOYSTICK_BUTTON key) const = 0;
	virtual void DetectJoysticks() = 0;
	virtual JOYSTICK_STATUS GetJoystickStatus(const unsigned int joystickId) const = 0;
	virtual unsigned int GetNumJoyButtons(const unsigned int joystickId) const = 0;
	virtual math::Vector2 GetJoystickXY(const unsigned int joystickId) const = 0;
	virtual float GetJoystickZ(const unsigned int joystickId) const = 0;
	virtual float GetJoystickRudder(const unsigned int joystickId) const = 0;
	virtual math::Vector2 GetJoystickUV(const unsigned int joystickId) const = 0;
	virtual JOYSTICK_BUTTON GetFirstButtonDown(const unsigned int joystickId) const = 0;
	virtual unsigned int GetNumJoysticks() const = 0;

	virtual math::Vector3 GetAccelerometerData() const = 0;
};

} // namespace sprite

#endif
