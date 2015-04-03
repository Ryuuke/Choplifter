#include "soundManager.h"

void soundHelico()
{
	if(helico->positionWin.y + HELICO_HEIGHT < POSITION_BOTTOM-5)
	{
		if(timeAllowed(&previousTimeSoundHelico, 1300))
        	FMOD_System_PlaySound(sound_system, 1, sound_helico, 0, &canal_game);
	}
	else
		FMOD_Channel_Stop(canal_game);
}

void soundFire()
{
	FMOD_System_PlaySound(sound_system, 2, sound_fire, 0, NULL);
}

void soundFireTank()
{
	FMOD_System_PlaySound(sound_system, 3, sound_fire_tank, 0, NULL);
}

void soundExplosion()
{
	FMOD_System_PlaySound(sound_system, 4, sound_explosion, 0, NULL);
}