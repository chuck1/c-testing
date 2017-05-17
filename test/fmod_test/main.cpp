#include <unistd.h>
#include <stdio.h>

#include "../../fmod/api/inc/fmod.hpp"
#include "../../fmod/api/inc/fmod_errors.h"

inline void errcheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
}

int main()
{

	FMOD_RESULT result;
	FMOD::System *system;

	result = FMOD::System_Create(&system);		// Create the main system object.
	errcheck(result);

	result = system->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
	errcheck(result);

	FMOD::Sound *sound;

	result = system->createSound("../../fmod/fmoddesignerapi/examples/media/ambient_one_four.ogg", FMOD_DEFAULT, 0, &sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	errcheck(result);

	int delay = 200 * 1000;

	FMOD::Channel *channel;
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	errcheck(result);

	usleep(delay);

	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	errcheck(result);

	usleep(delay);

	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	errcheck(result);

	usleep(delay);

	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	errcheck(result);

	usleep(delay);

	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	errcheck(result);

	usleep(3000 * 1000);

}
