#pragma once
#include "DxLib.h"
#include "../Common.h"

#define STICK_LEFT -1
#define STICK_RIGHT -2
#define L_TRIGGER 100
#define R_TRIGGER 200

//DInput
// L_STICK X,Y Yは上がマイナス
// R_STICK Z,Rz Rzは上がマイナス
//ボタン
constexpr int D_INPUT_BUTTON_X = 0;
constexpr int D_INPUT_BUTTON_A = 1;
constexpr int D_INPUT_BUTTON_B = 2;
constexpr int D_INPUT_BUTTON_Y = 3;
constexpr int D_INPUT_BUTTON_L1 = 4;
constexpr int D_INPUT_BUTTON_R1 = 5;
constexpr int D_INPUT_BUTTON_L2 = 6;
constexpr int D_INPUT_BUTTON_R2 = 7;
constexpr int D_INPUT_BUTTON_BACK = 8;
constexpr int D_INPUT_BUTTON_START = 9;
constexpr int D_INPUT_BUTTON_L3 = 10;
constexpr int D_INPUT_BUTTON_R3 = 11;

constexpr int D_INPUT_BUTTON_UP = 12;
constexpr int D_INPUT_BUTTON_LEFT_UP = 13;
constexpr int D_INPUT_BUTTON_LEFT = 14;
constexpr int D_INPUT_BUTTON_LEFT_DOWN = 15;
constexpr int D_INPUT_BUTTON_DOWN = 16;
constexpr int D_INPUT_BUTTON_RIGHT_DOWN = 17;
constexpr int D_INPUT_BUTTON_RIGHT = 18;
constexpr int D_INPUT_BUTTON_RIGHT_UP = 19;

constexpr int TRIGGER_DEADZONE_X = 5;
constexpr int STICK_DEADZONE_X = 2000;
constexpr int STICK_DEADZONE_D = 100;

constexpr int Log_MAX = 100;

enum class InputButton
{
	Decide,
	Back,

	Menu,

	Move_W,
	Move_A,
	Move_S,
	Move_D,

	Dash,
	Jump,
	Target,

	UniqueAction,
	BindAttack,

	ShotMode,
	Shot,
	Attack,

	KindNum
};

constexpr int DEFAULT_BUTTON[static_cast<int>(InputButton::KindNum)][3] =
{
	//Decide
	{
		KEY_INPUT_RETURN,
		XINPUT_BUTTON_A,
		D_INPUT_BUTTON_A,
	},

	//Back
	{
		KEY_INPUT_BACK,
		XINPUT_BUTTON_BACK,
		D_INPUT_BUTTON_BACK,
	},

	//Menu
	{
		KEY_INPUT_ESCAPE,
		XINPUT_BUTTON_START,
		D_INPUT_BUTTON_START,
	},

	//Move_W
	{
		KEY_INPUT_W,
		STICK_LEFT,
		STICK_LEFT,
	},

	//Move_A
	{
		KEY_INPUT_A,
		STICK_LEFT,
		STICK_LEFT,
	},

	//Move_S
	{
		KEY_INPUT_S,
		STICK_LEFT,
		STICK_LEFT,
	},

	//Move_D
	{
		KEY_INPUT_D,
		STICK_LEFT,
		STICK_LEFT,
	},

	//Dash
	{
		KEY_INPUT_LSHIFT,
		XINPUT_BUTTON_LEFT_SHOULDER,
		D_INPUT_BUTTON_L1,
	},

	//Jump
	{
		KEY_INPUT_SPACE,
		XINPUT_BUTTON_A,
		D_INPUT_BUTTON_A,
	},

	//Target
	{
		KEY_INPUT_T,
		XINPUT_BUTTON_DPAD_UP,
		D_INPUT_BUTTON_UP,
	},

	//UniqueAction
	{
		KEY_INPUT_E,
		XINPUT_BUTTON_B,
		D_INPUT_BUTTON_B,
	},

	//BindAttack
	{
		KEY_INPUT_Q,
		XINPUT_BUTTON_Y,
		D_INPUT_BUTTON_Y,
	},

	//ShotMode
	{
		MOUSE_INPUT_RIGHT,
		L_TRIGGER,
		D_INPUT_BUTTON_L2,
	},

	//Shot
	{
		MOUSE_INPUT_LEFT,
		R_TRIGGER,
		D_INPUT_BUTTON_R2,
	},

	//Attack
	{
		MOUSE_INPUT_LEFT,
		XINPUT_BUTTON_X,
		D_INPUT_BUTTON_X,
	},
};

class Log
{
public:
	struct LogData {
		int frame;

		char key_log[KEY_BUF_LEN];
		int mouse_log;

		float mouse_move_len[2];

		bool joyPadFlag;
		bool XpadFlag;
		XINPUT_STATE XInputState;
		DINPUT_JOYSTATE DInputState;
	};
private:
	static int playerID;

	static unsigned int currentFrame;

	static LogData logData[PLAYER_NUM][Log_MAX];

public:
	static int GetplayerID() { return playerID; }
	static void SetplayerID(int playerID) { Log::playerID = playerID; }
	
	static int GetcurrentFrame() { return currentFrame; }
	static void SetcurrentFrame(int currentFrame) { Log::currentFrame = currentFrame; }

	static void Init();
	static void SetNextData();

	static LogData* GetData(int player = playerID, unsigned int frame = currentFrame);

	static bool IsKeyDown(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsKeyPush(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsKeyKeep(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsKeyRelease(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());

	static bool PressAnyKey(int player = Log::GetplayerID(),
		unsigned int frame = Log::GetcurrentFrame());

	static bool IsMouseDown(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsMousePush(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsMouseKeep(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsMouseRelease(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());

	static bool IsUsePad(int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsPadDown(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsPadPush(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsPadKeep(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsPadRelease(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());

	static VECTOR IsPadStickData(int key_code,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());


	static bool IsButtonDown(InputButton button_code, bool isMouse = false,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsButtonPush(InputButton button_code, bool isMouse = false,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsButtonKeep(InputButton button_code, bool isMouse = false,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
	static bool IsButtonRelease(InputButton button_code, bool isMouse = false,
		int player = Log::GetplayerID(), unsigned int frame = Log::GetcurrentFrame());
};

class InputButtonInfo
{
private:

	//[0] = キーボード
	//[1] = XInput
	//[2] = DInput
	static int buttonInfo[static_cast<int>(InputButton::KindNum)][3];

public:
	static void Init();
	static int GetInfo(InputButton button, int control);
};