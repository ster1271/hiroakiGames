#pragma once
#include "DxLib.h"

#include "../Shapes/Shapes.h"
#include "../Log/Log.h"

class Input
{
private:
	static char key_buf[KEY_BUF_LEN];
	static int mouse_buf;

	//マウス関連
	static Object Mouse;
	static int MouseWheelRota;
	static bool mouse_flag[2];

	static bool joyPadFlag;
	static bool XpadFlag;
	static XINPUT_STATE XInputState;
	static DINPUT_JOYSTATE DInputState;

public:
	static void Init();

	static void DataSet();
	
	//マウス関連
	static VECTOR GetMousePos() { return Mouse.Get_pos(); }
	static int GetMouseWheelRota() { return MouseWheelRota; }

	static void Mouse_SetCenter();

	static void Mouse_Disappear();

	static bool Mouse_on_the_Rect(Rect_Data& rect, float ExRate);

	static bool ClickRect(Rect_Data& rect, float ExRate = 1.0f);

	static void SetPadInfo();

	static bool XpadDownAnyButton();
	static bool DpadDownAnyButton();
};