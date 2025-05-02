#include "SoundManager.h"
#include "../../Time/Time.h"

int SoundManager::soundHandle[(int)SoundKind::KindNum];
float SoundManager::vol[(int)SoundKind::KindNum];
float SoundManager::fadeInSpeed[(int)SoundKind::KindNum];
float SoundManager::fadeOutSpeed[(int)SoundKind::KindNum];

SoundManager::SoundManager()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		soundHandle[i] = -1;
		vol[i] = 0.0f;
		fadeInSpeed[i] = 0.0f;
		fadeOutSpeed[i] = 0.0f;
	}
}
SoundManager::~SoundManager()
{
	Fin();
}

void SoundManager::Init()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		fadeInSpeed[i] = 0.0f;
		fadeOutSpeed[i] = 0.0f;
		SetVolume(static_cast<SoundKind>(i), 1.0f);
	}
	SetVolume(SoundKind::SE_ATTACK, 0.6f);
}

void SoundManager::Step()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		if (fadeInSpeed[i] > 0.0f && fadeOutSpeed[i] > 0.0f)
		{
			fadeInSpeed[i] = 0.0f;
			fadeOutSpeed[i] = 0.0f;
			Stop(static_cast<SoundKind>(i));
			SetVolume(static_cast<SoundKind>(i), 1.0f);

		}

		if (IsPlay(static_cast<SoundKind>(i)))
		{
			if (fadeInSpeed[i] > 0.0f)
			{
				float nextVol = vol[i] + fadeInSpeed[i] * Time::GetRoleDelta(-1);
				if (nextVol >= 1.0f)
				{
					nextVol = 1.0f;
					fadeInSpeed[i] = 0.0f;
				}
				SetVolume(static_cast<SoundKind>(i), nextVol);
			}
			else if (fadeOutSpeed[i] > 0.0f)
			{
				float nextVol = vol[i] - fadeOutSpeed[i] * Time::GetRoleDelta(-1);
				if (nextVol <= 0.0f)
				{
					Stop(static_cast<SoundKind>(i));

					SetVolume(static_cast<SoundKind>(i), 1.0f);
					fadeOutSpeed[i] = 0.0f;
				}
				else
					SetVolume(static_cast<SoundKind>(i), nextVol);
			}
		}
		else
		{
			if (fadeInSpeed[i] > 0.0f)
			{
				SetVolume(static_cast<SoundKind>(i), fadeInSpeed[i] * Time::GetRoleDelta(-1));
				Play(static_cast<SoundKind>(i), DX_PLAYTYPE_LOOP);
			}
			else if (fadeOutSpeed[i] > 0.0f)
			{
				fadeOutSpeed[i] = 0.0f;
				SetVolume(static_cast<SoundKind>(i), 1.0f);
			}
		}
	}
}

void SoundManager::Fin()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		if (soundHandle[i] != -1)
		{
			DeleteSoundMem(soundHandle[i]);
			soundHandle[i] = -1;
		}
		vol[i] = 0.0f;
		fadeInSpeed[i] = 0.0f;
		fadeOutSpeed[i] = 0.0f;
	}
}

bool SoundManager::LoadAllData()
{
	bool isAllDataSet = true;
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
	{
		soundHandle[i] = LoadSoundMem(SE_FILE_PATH[i]);

		if(soundHandle[i] != -1) isAllDataSet = false;
	}

	return isAllDataSet;
}

int SoundManager::GetSoundTime(SoundKind soundID)
{
	return (int)GetSoundCurrentTime(soundHandle[(int)soundID]);
}

int SoundManager::GetSoundAllTime(SoundKind soundID)
{
	return (int)GetSoundTotalTime(soundHandle[(int)soundID]);
}

bool SoundManager::IsPlay(SoundKind soundID)
{
	return CheckSoundMem(soundHandle[(int)soundID]) == 1 ? true : false;
}

void SoundManager::SetStartTime(SoundKind soundID, int startTime)
{
	int Freq = GetFrequencySoundMem(soundHandle[(int)soundID]) * startTime / 1000;
	SetFrequencySoundMem(Freq, soundHandle[(int)soundID]);
}

void SoundManager::SetVolume(SoundKind soundID, float Volume)
{
	if (Volume < 0.f || Volume > 1.f) return;

	vol[(int)soundID] = Volume;
	ChangeVolumeSoundMem((int)(255.f * vol[(int)soundID]), soundHandle[(int)soundID]);
}

int SoundManager::Play(SoundKind soundID, int playType, bool isStart)
{
	return PlaySoundMem(soundHandle[(int)soundID], playType, isStart);
}

int SoundManager::Stop(SoundKind soundID)
{
	if (IsPlay(soundID))
		return StopSoundMem(soundHandle[(int)soundID]);
	else
		return 0;
}

void SoundManager::StopAll()
{
	for (int i = 0; i < (int)SoundKind::KindNum; i++)
		StopSoundMem(soundHandle[i]);
}

void SoundManager::SetFadeIn(SoundKind soundID, float spd)
{
	if(spd > 0.0f)
		fadeInSpeed[(int)soundID] = spd;
}

void SoundManager::SetFadeOut(SoundKind soundID, float spd)
{
	if(spd > 0.0f)
		fadeOutSpeed[(int)soundID] = spd;
}