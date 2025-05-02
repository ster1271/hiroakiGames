#include "memory"
#include "Log.h"

int Log::playerID;
unsigned int Log::currentFrame;
Log::LogData Log::logData[PLAYER_NUM][Log_MAX];

int InputButtonInfo::buttonInfo[static_cast<int>(InputButton::KindNum)][3];

void Log::Init()
{
	playerID = 0;
	currentFrame = 0;
	memset(logData, 0, sizeof(LogData[PLAYER_NUM][Log_MAX]));
}

void Log::SetNextData()
{
	if (currentFrame == UINT_MAX)
		currentFrame = 0;
	else
		currentFrame++;

	for (int player_index = 0; player_index < PLAYER_NUM; player_index++)
	{
		for (int log_index = 0; log_index < Log_MAX - 1; log_index++)
		{
			logData[player_index][Log_MAX - 1 - log_index] = logData[player_index][Log_MAX - 2 - log_index];
		}
		memset(&logData[player_index][0], 0, sizeof(LogData));
		logData[player_index][0].frame = currentFrame;
	}
}

Log::LogData* Log::GetData(int player, unsigned int frame)
{
	if (player >= 0 && player < PLAYER_NUM)
	{
		for (int i = 0; i < Log_MAX; i++)
		{
			if (logData[player][i].frame == frame)
				return &logData[player][i];
		}
	}
	

	return nullptr;
}

bool Log::IsKeyDown(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;

	if (currentData->key_log[key_code])
		return true;

	return false;
}

bool Log::IsKeyPush(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if (currentData->key_log[key_code])
	{
		if (beforeData->key_log[key_code] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Log::IsKeyKeep(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if (currentData->key_log[key_code])
	{
		if (beforeData->key_log[key_code] == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Log::IsKeyRelease(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if (beforeData->key_log[key_code])
	{
		if (currentData->key_log[key_code] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Log::PressAnyKey(int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	for (int i = 0; i < KEY_BUF_LEN; i++)
	{
		if (currentData->key_log[i] &&
			beforeData->key_log[i] == 0)
		{
			return true;
		}
	}
	return false;
}

bool Log::IsMouseDown(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;

	if ((currentData->mouse_log & key_code) != 0)
	{
		//‰Ÿ‚³‚ê‚Ä‚¢‚é
		return true;
	}
	else
	{
		//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
		return false;
	}

}

bool Log::IsMousePush(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if ((currentData->mouse_log & key_code) != 0)
	{
		if ((beforeData->mouse_log & key_code) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Log::IsMouseKeep(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if ((currentData->mouse_log & key_code) != 0)
	{
		if ((beforeData->mouse_log & key_code) == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool Log::IsMouseRelease(int key_code, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if ((beforeData->mouse_log & key_code) != 0)
	{
		if ((currentData->mouse_log & key_code) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Log::IsUsePad(int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;
	
	if (currentData->joyPadFlag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Log::IsPadDown(int key_code, int player, unsigned int frame)
{
	if (key_code < 0)
		return false;

	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;
	if (currentData->XpadFlag)
	{
		if (key_code == L_TRIGGER || key_code == R_TRIGGER)
		{
			if (key_code == L_TRIGGER)
			{
				if (currentData->XInputState.LeftTrigger >= TRIGGER_DEADZONE_X)
				{
					//‰Ÿ‚³‚ê‚Ä‚¢‚é
					return true;
				}
				else
				{
					//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
					return false;
				}
			}
			if (key_code == R_TRIGGER)
			{
				if (currentData->XInputState.RightTrigger >= TRIGGER_DEADZONE_X)
				{
					//‰Ÿ‚³‚ê‚Ä‚¢‚é
					return true;
				}
				else
				{
					//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
					return false;
				}
			}
			return false;
		}
		else
		{
			if (currentData->XInputState.Buttons[key_code] != 0)
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚é
				return true;
			}
			else
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
				return false;
			}
		}
	}
	else
	{
		if (key_code >= D_INPUT_BUTTON_UP && key_code <= D_INPUT_BUTTON_RIGHT_UP)
		{
			if (currentData->DInputState.POV[0] != -1)
			{
				if (key_code == D_INPUT_BUTTON_UP)
				{
					if (currentData->DInputState.POV[0] == 0)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_UP)
				{
					if (currentData->DInputState.POV[0] == 31500)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT)
				{
					if (currentData->DInputState.POV[0] == 27000)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_DOWN)
				{
					if (currentData->DInputState.POV[0] == 22500)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_DOWN)
				{
					if (currentData->DInputState.POV[0] == 18000)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_DOWN)
				{
					if (currentData->DInputState.POV[0] == 13500)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT)
				{
					if (currentData->DInputState.POV[0] == 9000)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_UP)
				{
					if (currentData->DInputState.POV[0] == 4500)
					{
						return true;
					}
					else
					{
						return false;
					}
				}

				return false;
			}
			else
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
				return false;
			}
		}
		else
		{
			if (currentData->DInputState.Buttons[key_code] != 0)
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚é
				return true;
			}
			else
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
				return false;
			}
		}
	}
	return false;
}

bool Log::IsPadPush(int key_code, int player, unsigned int frame)
{
	if (key_code < 0)
		return false;

	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if (currentData->XpadFlag)
	{
		if (key_code == L_TRIGGER || key_code == R_TRIGGER)
		{
			if (key_code == L_TRIGGER)
			{
				if (currentData->XInputState.LeftTrigger >= TRIGGER_DEADZONE_X)
				{
					if (beforeData->XInputState.LeftTrigger < TRIGGER_DEADZONE_X)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			if (key_code == R_TRIGGER)
			{
				if (currentData->XInputState.RightTrigger >= TRIGGER_DEADZONE_X)
				{
					if (beforeData->XInputState.RightTrigger < TRIGGER_DEADZONE_X)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			if (currentData->XInputState.Buttons[key_code] != 0)
			{
				if (beforeData->XInputState.Buttons[key_code] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (key_code >= D_INPUT_BUTTON_UP && key_code <= D_INPUT_BUTTON_RIGHT_UP)
		{
			if (currentData->DInputState.POV[0] != -1)
			{
				if (key_code == D_INPUT_BUTTON_UP)
				{
					if (currentData->DInputState.POV[0] == 0)
					{
						if (beforeData->DInputState.POV[0] != 0)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_UP)
				{
					if (currentData->DInputState.POV[0] == 31500)
					{
						if (beforeData->DInputState.POV[0] != 31500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT)
				{
					if (currentData->DInputState.POV[0] == 27000)
					{
						if (beforeData->DInputState.POV[0] != 27000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_DOWN)
				{
					if (currentData->DInputState.POV[0] == 22500)
					{
						if (beforeData->DInputState.POV[0] != 22500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_DOWN)
				{
					if (currentData->DInputState.POV[0] == 18000)
					{
						if (beforeData->DInputState.POV[0] != 18000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_DOWN)
				{
					if (currentData->DInputState.POV[0] == 13500)
					{
						if (beforeData->DInputState.POV[0] != 13500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT)
				{
					if (currentData->DInputState.POV[0] == 9000)
					{
						if (beforeData->DInputState.POV[0] != 9000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_UP)
				{
					if (currentData->DInputState.POV[0] == 4500)
					{
						if (beforeData->DInputState.POV[0] != 4500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}

				return false;
			}
			else
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
				return false;
			}
		}
		else
		{
			
			if (currentData->DInputState.Buttons[key_code] != 0)
			{
				if (beforeData->DInputState.Buttons[key_code] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool Log::IsPadKeep(int key_code, int player, unsigned int frame)
{
	if (key_code < 0)
		return false;

	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if (currentData->XpadFlag)
	{
		if (key_code == L_TRIGGER || key_code == R_TRIGGER)
		{
			if (key_code == L_TRIGGER)
			{
				if (currentData->XInputState.LeftTrigger >= TRIGGER_DEADZONE_X)
				{
					if (beforeData->XInputState.LeftTrigger >= TRIGGER_DEADZONE_X)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			if (key_code == R_TRIGGER)
			{
				if (currentData->XInputState.RightTrigger >= TRIGGER_DEADZONE_X)
				{
					if (beforeData->XInputState.RightTrigger >= TRIGGER_DEADZONE_X)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			if (currentData->XInputState.Buttons[key_code])
			{
				if (beforeData->XInputState.Buttons[key_code])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (key_code >= D_INPUT_BUTTON_UP && key_code <= D_INPUT_BUTTON_RIGHT_UP)
		{
			if (currentData->DInputState.POV[0] != -1)
			{
				if (key_code == D_INPUT_BUTTON_UP)
				{
					if (currentData->DInputState.POV[0] == 0)
					{
						if (beforeData->DInputState.POV[0] == 0)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_UP)
				{
					if (currentData->DInputState.POV[0] == 31500)
					{
						if (beforeData->DInputState.POV[0] == 31500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT)
				{
					if (currentData->DInputState.POV[0] == 27000)
					{
						if (beforeData->DInputState.POV[0] == 27000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_DOWN)
				{
					if (currentData->DInputState.POV[0] == 22500)
					{
						if (beforeData->DInputState.POV[0] == 22500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_DOWN)
				{
					if (currentData->DInputState.POV[0] == 18000)
					{
						if (beforeData->DInputState.POV[0] == 18000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_DOWN)
				{
					if (currentData->DInputState.POV[0] == 13500)
					{
						if (beforeData->DInputState.POV[0] == 13500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT)
				{
					if (currentData->DInputState.POV[0] == 9000)
					{
						if (beforeData->DInputState.POV[0] == 9000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_UP)
				{
					if (currentData->DInputState.POV[0] == 4500)
					{
						if (beforeData->DInputState.POV[0] == 4500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}

				return false;
			}
			else
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
				return false;
			}
		}
		else
		{
			if (currentData->DInputState.Buttons[key_code])
			{
				if (beforeData->DInputState.Buttons[key_code])
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool Log::IsPadRelease(int key_code, int player, unsigned int frame)
{
	if (key_code < 0)
		return false;

	LogData* currentData = Log::GetData(player, frame);
	LogData* beforeData;
	if (frame == 0)
		beforeData = Log::GetData(player, UINT_MAX);
	else
		beforeData = Log::GetData(player, frame - 1);
	if (currentData == nullptr || beforeData == nullptr)
		return false;

	if (currentData->XpadFlag)
	{
		if (key_code == L_TRIGGER || key_code == R_TRIGGER)
		{
			if (key_code == L_TRIGGER)
			{
				if (beforeData->XInputState.LeftTrigger >= TRIGGER_DEADZONE_X)
				{
					if (currentData->XInputState.LeftTrigger < TRIGGER_DEADZONE_X)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			if (key_code == R_TRIGGER)
			{
				if (beforeData->XInputState.RightTrigger >= TRIGGER_DEADZONE_X)
				{
					if (currentData->XInputState.RightTrigger < TRIGGER_DEADZONE_X)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			if (beforeData->XInputState.Buttons[key_code])
			{
				if (currentData->XInputState.Buttons[key_code] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		if (key_code >= D_INPUT_BUTTON_UP && key_code <= D_INPUT_BUTTON_RIGHT_UP)
		{
			if (currentData->DInputState.POV[0] != -1)
			{
				if (key_code == D_INPUT_BUTTON_UP)
				{
					if (beforeData->DInputState.POV[0] == 0)
					{
						if (currentData->DInputState.POV[0] != 0)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_UP)
				{
					if (beforeData->DInputState.POV[0] == 31500)
					{
						if (currentData->DInputState.POV[0] != 31500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT)
				{
					if (beforeData->DInputState.POV[0] == 27000)
					{
						if (currentData->DInputState.POV[0] != 27000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_LEFT_DOWN)
				{
					if (beforeData->DInputState.POV[0] == 22500)
					{
						if (currentData->DInputState.POV[0] != 22500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_DOWN)
				{
					if (beforeData->DInputState.POV[0] == 18000)
					{
						if (currentData->DInputState.POV[0] != 18000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_DOWN)
				{
					if (beforeData->DInputState.POV[0] == 13500)
					{
						if (currentData->DInputState.POV[0] != 13500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT)
				{
					if (beforeData->DInputState.POV[0] == 9000)
					{
						if (currentData->DInputState.POV[0] != 9000)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				if (key_code == D_INPUT_BUTTON_RIGHT_UP)
				{
					if (beforeData->DInputState.POV[0] == 4500)
					{
						if (currentData->DInputState.POV[0] != 4500)
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}

				return false;
			}
			else
			{
				//‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
				return false;
			}
		}
		else
		{
			if (beforeData->DInputState.Buttons[key_code])
			{
				if (currentData->DInputState.Buttons[key_code] == 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

VECTOR Log::IsPadStickData(int key_code, int player, unsigned int frame)
{
	VECTOR ret = VGet(0.0f, 0.0f, 0.0f);

	if (!(key_code == STICK_LEFT || key_code == STICK_RIGHT))
		return ret;

	LogData* currentData = Log::GetData(player, frame);

	if (currentData == nullptr)
		return ret;

	if (currentData->XpadFlag)
	{
		if (key_code == STICK_LEFT)
		{
			if (static_cast<float>(currentData->XInputState.ThumbLX) > 0.0f)
			{
				ret.x = static_cast<float>(currentData->XInputState.ThumbLX)
					/ 32767.0f;
				if (ret.x >= 1.0f)
				{
					ret.x = 1.0f;
				}
			}
			else if (static_cast<float>(currentData->XInputState.ThumbLX) < 0.0f)
			{
				ret.x = static_cast<float>(currentData->XInputState.ThumbLX)
					/ 32768.0f;
				if (ret.x <= -1.0f)
				{
					ret.x = -1.0f;
				}
			}

			if (static_cast<float>(currentData->XInputState.ThumbLY) > 0.0f)
			{
				ret.y = static_cast<float>(currentData->XInputState.ThumbLY)
					/ 32767.0f;
				if (ret.y >= 1.0f)
				{
					ret.y = 1.0f;
				}
			}
			else if (static_cast<float>(currentData->XInputState.ThumbLY) < 0.0f)
			{
				ret.y = static_cast<float>(currentData->XInputState.ThumbLY)
					/ 32768.0f;
				if (ret.y <= -1.0f)
				{
					ret.y = -1.0f;
				}
			}

			if (!(ret.x == 0.0f && ret.y == 0.0f && ret.z == 0.0f))
			{
				ret = VNorm(ret);
			}
		}
		else if (key_code == STICK_RIGHT)
		{
			if (static_cast<float>(currentData->XInputState.ThumbRX) > 0.0f)
			{
				ret.x = static_cast<float>(currentData->XInputState.ThumbRX)
					/ 32767.0f;
				if (ret.x >= 1.0f)
				{
					ret.x = 1.0f;
				}
			}
			else if (static_cast<float>(currentData->XInputState.ThumbRX) < 0.0f)
			{
				ret.x = static_cast<float>(currentData->XInputState.ThumbRX)
					/ 32768.0f;
				if (ret.x <= -1.0f)
				{
					ret.x = -1.0f;
				}
			}

			if (static_cast<float>(currentData->XInputState.ThumbRY) > 0.0f)
			{
				ret.y = static_cast<float>(currentData->XInputState.ThumbRY)
					/ 32767.0f;
				if (ret.y >= 1.0f)
				{
					ret.y = 1.0f;
				}
			}
			else if (static_cast<float>(currentData->XInputState.ThumbRY) < 0.0f)
			{
				ret.y = static_cast<float>(currentData->XInputState.ThumbRY)
					/ 32768.0f;
				if (ret.y <= -1.0f)
				{
					ret.y = -1.0f;
				}
			}

			if (!(ret.x == 0.0f && ret.y == 0.0f && ret.z == 0.0f))
			{
				ret = VNorm(ret);
			}
		}

		return ret;
	}
	else
	{
		if (key_code == STICK_LEFT)
		{
			if (currentData->DInputState.X > 0)
			{
				ret.x = static_cast<float>(currentData->DInputState.X)
					/ 1000.0f;
				if (ret.x >= 1.0f)
				{
					ret.x = 1.0f;
				}
			}
			else if (currentData->DInputState.X < 0)
			{
				ret.x = static_cast<float>(currentData->DInputState.X)
					/ 1000.0f;
				if (ret.x <= -1.0f)
				{
					ret.x = -1.0f;
				}
			}

			if (currentData->DInputState.Y > 0)
			{
				ret.y = static_cast<float>(currentData->DInputState.Y)
					/ 1000.0f;
				if (ret.y >= 1.0f)
				{
					ret.y = 1.0f;
				}

				ret.y *= -1.0f;
			}
			else if (currentData->DInputState.Y < 0)
			{
				ret.y = static_cast<float>(currentData->DInputState.Y)
					/ 1000.0f;
				if (ret.y <= -1.0f)
				{
					ret.y = -1.0f;
				}

				ret.y *= -1.0f;
			}

			if (!(ret.x == 0.0f && ret.y == 0.0f && ret.z == 0.0f))
			{
				ret = VNorm(ret);
			}
		}
		else if (key_code == STICK_RIGHT)
		{
			if (currentData->DInputState.Z > 0)
			{
				ret.x = static_cast<float>(currentData->DInputState.Z)
					/ 1000.0f;
				if (ret.x >= 1.0f)
				{
					ret.x = 1.0f;
				}
			}
			else if (currentData->DInputState.Z < 0)
			{
				ret.x = static_cast<float>(currentData->DInputState.Z)
					/ 1000.0f;
				if (ret.x <= -1.0f)
				{
					ret.x = -1.0f;
				}
			}

			if (currentData->DInputState.Rz > 0)
			{
				ret.y = static_cast<float>(currentData->DInputState.Rz)
					/ 1000.0f;
				if (ret.y >= 1.0f)
				{
					ret.y = 1.0f;
				}

				ret.y *= -1.0f;
			}
			else if (currentData->DInputState.Rz < 0.0f)
			{
				ret.y = static_cast<float>(currentData->DInputState.Rz)
					/ 1000.0f;
				if (ret.y <= -1.0f)
				{
					ret.y = -1.0f;
				}

				ret.y *= -1.0f;
			}

			if (!(ret.x == 0.0f && ret.y == 0.0f && ret.z == 0.0f))
			{
				ret = VNorm(ret);
			}
		}

		return ret;
	}
}

bool Log::IsButtonDown(InputButton button_code, bool isMouse, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;
	if (currentData->joyPadFlag)
	{
		if (currentData->XpadFlag)
		{
			return IsPadDown(InputButtonInfo::GetInfo(button_code, 1), player, frame);
		}
		else
		{
			return IsPadDown(InputButtonInfo::GetInfo(button_code, 2), player, frame);
		}
	}
	else
	{
		if (isMouse)
			return IsMouseDown(InputButtonInfo::GetInfo(button_code, 0), player, frame);
		else
			return IsKeyDown(InputButtonInfo::GetInfo(button_code, 0), player, frame);
	}
}

bool Log::IsButtonPush(InputButton button_code, bool isMouse, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;
	if (currentData->joyPadFlag)
	{
		if (currentData->XpadFlag)
		{
			return IsPadPush(InputButtonInfo::GetInfo(button_code, 1), player, frame);
		}
		else
		{
			return IsPadPush(InputButtonInfo::GetInfo(button_code, 2), player, frame);
		}
	}
	else
	{
		if (isMouse)
			return IsMousePush(InputButtonInfo::GetInfo(button_code, 0), player, frame);
		else
			return IsKeyPush(InputButtonInfo::GetInfo(button_code, 0), player, frame);
	}
}

bool Log::IsButtonKeep(InputButton button_code, bool isMouse, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;
	if (currentData->joyPadFlag)
	{
		if (currentData->XpadFlag)
		{
			return IsPadKeep(InputButtonInfo::GetInfo(button_code, 1), player, frame);
		}
		else
		{
			return IsPadKeep(InputButtonInfo::GetInfo(button_code, 2), player, frame);
		}
	}
	else
	{
		if (isMouse)
			return IsMouseKeep(InputButtonInfo::GetInfo(button_code, 0), player, frame);
		else
			return IsKeyKeep(InputButtonInfo::GetInfo(button_code, 0), player, frame);
	}
}

bool Log::IsButtonRelease(InputButton button_code, bool isMouse, int player, unsigned int frame)
{
	LogData* currentData = Log::GetData(player, frame);
	if (currentData == nullptr)
		return false;
	if (currentData->joyPadFlag)
	{
		if (currentData->XpadFlag)
		{
			return IsPadRelease(InputButtonInfo::GetInfo(button_code, 1), player, frame);
		}
		else
		{
			return IsPadRelease(InputButtonInfo::GetInfo(button_code, 2), player, frame);
		}
	}
	else
	{
		if (isMouse)
			return IsMouseRelease(InputButtonInfo::GetInfo(button_code, 0), player, frame);
		else
			return IsKeyRelease(InputButtonInfo::GetInfo(button_code, 0), player, frame);
	}
}

void InputButtonInfo::Init()
{
	for (int i = 0; i < static_cast<int>(InputButton::KindNum); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buttonInfo[i][j] = DEFAULT_BUTTON[i][j];
		}
	}
}

int InputButtonInfo::GetInfo(InputButton button, int control)
{
	return buttonInfo[static_cast<int>(button)][control];
}