#include "DxLib.h"
#include "Input.h"
#include "../Common.h"
#include "../FrameRate/FrameRate.h"

char Input::key_buf[KEY_BUF_LEN];
int Input::mouse_buf;

//マウス関連
Object Input::Mouse;
int Input::MouseWheelRota;
bool Input::mouse_flag[2];

//パッド関連
bool Input::joyPadFlag;
bool Input::XpadFlag;
XINPUT_STATE Input::XInputState;
DINPUT_JOYSTATE Input::DInputState;

void Input::Init()
{
	for (int i = 0; i < KEY_BUF_LEN; i++)
	{
		key_buf[i] = 0;
	}

	Mouse.Set_pos(VGet(0.0f, 0.0f, 0.0f));

	MouseWheelRota = 0;

	mouse_flag[0] = false;
	mouse_flag[1] = false;

	mouse_buf = 0;

	if (GetJoypadNum() > 0)
	{
		joyPadFlag = true;
	}
	else
	{
		joyPadFlag = false;
	}

	XpadFlag = false;
	memset(&XInputState, 0, sizeof(XINPUT_STATE));
	memset(&DInputState, 0, sizeof(DINPUT_JOYSTATE));
}

void Input::DataSet()
{
	GetHitKeyStateAll(key_buf);
	mouse_buf = GetMouseInput();

	if (CheckHitKeyAll(DX_CHECKINPUT_KEY) || CheckHitKeyAll(DX_CHECKINPUT_MOUSE))
	{
		joyPadFlag = false;
	}

	SetPadInfo();

	if (Log::GetData() != nullptr)
		memcpy_s(Log::GetData()->key_log,
			sizeof(char[KEY_BUF_LEN]), key_buf, sizeof(char[KEY_BUF_LEN]));

	if (Log::GetData() != nullptr)
		Log::GetData()->mouse_log = mouse_buf;

	if (Log::GetData() != nullptr)
	{
		Log::GetData()->joyPadFlag = joyPadFlag;
		Log::GetData()->XpadFlag = XpadFlag;
		Log::GetData()->XInputState = XInputState;
		Log::GetData()->DInputState = DInputState;
	}

	int x_buf = 0, y_buf = 0;
	GetMousePoint(&x_buf, &y_buf);
	int a = max(100, x_buf - SCREEN_SIZE_X / 2);
	Log::GetData()->mouse_move_len[0] += static_cast<float>(
		min(max(x_buf - SCREEN_SIZE_X / 2, -100), 100) * 0.25f / FRAME_RATE);
	Log::GetData()->mouse_move_len[1] -= static_cast<float>(
		min(max(y_buf - SCREEN_SIZE_Y / 2, -100), 100) * 0.25f / FRAME_RATE);

	SetMousePoint(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
	
	Mouse.Set_posX((float)x_buf);
	Mouse.Set_posY((float)y_buf);

	MouseWheelRota = GetMouseWheelRotVol();
}

//マウス関連
void Input::Mouse_SetCenter()
{
	SetMouseDispFlag(true);
	SetMousePoint(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
}

void Input::Mouse_Disappear()
{
	SetMouseDispFlag(false);
}

bool Input::Mouse_on_the_Rect(Rect_Data& rect, float ExRate)
{
	VECTOR r_pos = rect.Get_pos();
	int r_sizeX_2 = (int)(rect.Get_sizeW() / 2 * ExRate);
	int r_sizeY_2 = (int)(rect.Get_sizeH() / 2 * ExRate);

	VECTOR m_pos = Mouse.Get_pos();

	if (m_pos.x >= r_pos.x - r_sizeX_2 && m_pos.x <= r_pos.x + r_sizeX_2 &&
		m_pos.y >= r_pos.y - r_sizeY_2 && m_pos.y <= r_pos.y + r_sizeY_2)
	{
		//矩形の中にある
		return true;
	}
	else
	{
		//矩形の中にない
		return false;
	}
}

bool Input::ClickRect(Rect_Data& rect, float ExRate)
{
	if (Mouse_on_the_Rect(rect, ExRate))
	{
		//矩形の中にある
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//押されている
			if (mouse_flag[0] == false)
			{
				//押されつづけていない
				mouse_flag[0] = true;
				return true;
			}
			return false;
		}
		else
		{
			//押されていない
			mouse_flag[0] = false;
			return false;
		}
	}
	else
	{
		//矩形の中にない
		return false;
	}
}

void Input::SetPadInfo()
{
	if (GetJoypadNum() > 0)
	{
		int padType = GetJoypadType(DX_INPUT_PAD1);
		if (padType == DX_PADTYPE_XBOX_360 || padType == DX_PADTYPE_XBOX_ONE)
		{
			if (GetJoypadXInputState(DX_INPUT_PAD1, &XInputState) == 0)
			{
				XpadFlag = true;
				if (abs(XInputState.ThumbLX) < STICK_DEADZONE_X)
					XInputState.ThumbLX = 0;
				if (abs(XInputState.ThumbLY) < STICK_DEADZONE_X)
					XInputState.ThumbLY = 0;
				if (abs(XInputState.ThumbRX) < STICK_DEADZONE_X)
					XInputState.ThumbRX = 0;
				if (abs(XInputState.ThumbRY) < STICK_DEADZONE_X)
					XInputState.ThumbRY = 0;

				if (XpadDownAnyButton())
				{
					joyPadFlag = true;
				}
			}
			else
			{
				joyPadFlag = false;
				XpadFlag = false;
				memset(&XInputState, 0, sizeof(XINPUT_STATE));
				memset(&DInputState, 0, sizeof(DINPUT_JOYSTATE));
			}
		}
		else
		{
			XpadFlag = false;
			if (GetJoypadDirectInputState(DX_INPUT_PAD1, &DInputState) == 0)
			{
				if (abs(DInputState.X) < STICK_DEADZONE_D)
					DInputState.X = 0;
				if (abs(DInputState.Y) < STICK_DEADZONE_D)
					DInputState.Y = 0;
				if (abs(DInputState.Z) < STICK_DEADZONE_D)
					DInputState.Z = 0;
				if (abs(DInputState.Rz) < STICK_DEADZONE_D)
					DInputState.Rz = 0;

				if (DpadDownAnyButton())
				{
					joyPadFlag = true;
				}
			}
			else
			{
				joyPadFlag = false;
				XpadFlag = false;
				memset(&XInputState, 0, sizeof(XINPUT_STATE));
				memset(&DInputState, 0, sizeof(DINPUT_JOYSTATE));
			}
		}
	}
	else
	{
		joyPadFlag = false;
		XpadFlag = false;
		memset(&XInputState, 0, sizeof(XINPUT_STATE));
		memset(&DInputState, 0, sizeof(DINPUT_JOYSTATE));
	}
}

bool Input::XpadDownAnyButton()
{
	for (int i = 0; i < 16; i++)
	{
		if (XInputState.Buttons[i])
		{
			return true;
		}
	}

	if (XInputState.LeftTrigger > TRIGGER_DEADZONE_X)
		return true;

	if (XInputState.RightTrigger > TRIGGER_DEADZONE_X)
		return true;

	if (XInputState.ThumbLX != 0)
		return true;

	if (XInputState.ThumbLY != 0)
		return true;

	if (XInputState.ThumbRX != 0)
		return true;

	if (XInputState.ThumbRY != 0)
		return true;

	return false;
}

bool Input::DpadDownAnyButton()
{
	for (int i = 0; i < 32; i++)
	{
		if (DInputState.Buttons[i])
		{
			return true;
		}
	}

	if (DInputState.POV[0] != -1)
		return true;

	if (DInputState.X != 0)
		return true;

	if (DInputState.Y != 0)
		return true;

	if (DInputState.Z != 0)
		return true;

	if (DInputState.Rz != 0)
		return true;

	return false;
}