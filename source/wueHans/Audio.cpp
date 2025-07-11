#include <Hall/Audio.h>

volatile char* AUDIO_START 				= (char*) 0x2000100;
const Hall::Sample** AUDIO_START_ADDRESS= (const Hall::Sample**)(AUDIO_START + 4);
int* AUDIO_SAMPLE_COUNT 				= (int*)(AUDIO_START + 8);
int* AUDIO_LOOP_START 					= (int*)(AUDIO_START + 12);
int* AUDIO_LOOP_END 					= (int*)(AUDIO_START + 16);
volatile int* AUDIO_CURRENT_POSITION 		= (volatile int*)(AUDIO_START + 20);
volatile short* AUDIO_LAST_SAMPLE 		= (volatile short*)(AUDIO_START + 24);
unsigned char* AUDIO_VOLUME 			= (unsigned char*)(AUDIO_START + 28);
bool* AUDIO_IS_LOOPING 					= (bool*)(AUDIO_START + 32);
volatile bool* AUDIO_IS_PLAYING 		= (volatile bool*)(AUDIO_START + 36);
bool* AUDIO_IS_MONO 					= (bool*)(AUDIO_START + 40);
bool* AUDIO_IS_RIGHT 					= (bool*)(AUDIO_START + 44);
unsigned char* AUDIO_GLOBAL_VOLUME 		= (unsigned char*)(AUDIO_START + 48); //I think we can skip volatile for these two
unsigned char* AUDIO_CHANNEL_SELECT 	= (unsigned char*)(AUDIO_START + 52); //Because they will never change and always address the same value


void Hall::SetGlobalVolume(unsigned char volume)
{
	*AUDIO_GLOBAL_VOLUME = volume;
}

void Hall::SetupMono(int channelID, const Sample* data, int sampleCount, unsigned char volume)
{
	*AUDIO_CHANNEL_SELECT = 1 << channelID;
	*AUDIO_START_ADDRESS = data;
	*AUDIO_SAMPLE_COUNT = sampleCount;
	*AUDIO_CURRENT_POSITION = 0;
	*AUDIO_VOLUME = volume;
	*AUDIO_IS_LOOPING = false;
	*AUDIO_IS_PLAYING = false;
	*AUDIO_IS_MONO = true;
}

void Hall::SetupMono(int channelID, const Sample* data, int sampleCount, unsigned int loopStart, unsigned int loopEnd, unsigned char volume)
{
	*AUDIO_CHANNEL_SELECT = 1 << channelID;
	*AUDIO_START_ADDRESS = data;
	*AUDIO_SAMPLE_COUNT = sampleCount;
	*AUDIO_CURRENT_POSITION = 0;
	*AUDIO_VOLUME = volume;
	*AUDIO_IS_LOOPING = true;
	*AUDIO_LOOP_START = loopStart;
	*AUDIO_LOOP_END = loopEnd;
	*AUDIO_IS_PLAYING = false;
	*AUDIO_IS_MONO = true;
}

void Hall::SetupStereo(int channelID_left, int channelID_right, const Sample* data, int sampleCount, unsigned char volume)
{
	*AUDIO_CHANNEL_SELECT = (1 << channelID_left) | (1 << channelID_right);
	*AUDIO_START_ADDRESS = data;
	*AUDIO_SAMPLE_COUNT = sampleCount;
	*AUDIO_CURRENT_POSITION = 0;
	*AUDIO_VOLUME = volume;
	*AUDIO_IS_LOOPING = false;
	*AUDIO_IS_PLAYING = false;
	*AUDIO_IS_MONO = false;
	*AUDIO_IS_RIGHT = false;

	*AUDIO_CHANNEL_SELECT = 1 << channelID_right;
	*AUDIO_IS_RIGHT = true;
}

void Hall::SetupStereo(int channelID_left, int channelID_right, const Sample* data, int sampleCount, unsigned int loopStart, unsigned int loopEnd, unsigned char volume)
{
	*AUDIO_CHANNEL_SELECT = (1 << channelID_left) | (1 << channelID_right);
	*AUDIO_START_ADDRESS = data;
	*AUDIO_SAMPLE_COUNT = sampleCount;
	*AUDIO_CURRENT_POSITION = 0;
	*AUDIO_VOLUME = volume;
	*AUDIO_LOOP_START = loopStart;
	*AUDIO_LOOP_END = loopEnd;
	*AUDIO_IS_LOOPING = true;
	*AUDIO_IS_PLAYING = false;
	*AUDIO_IS_MONO = false;
	*AUDIO_IS_RIGHT = false;

	*AUDIO_CHANNEL_SELECT = 1 << channelID_right;
	*AUDIO_IS_RIGHT = true;

}

void Hall::Play(unsigned char channelSelect)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_IS_PLAYING = true;
}

void Hall::Pause(unsigned char channelSelect)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_IS_PLAYING = false;
}

void Hall::SetData(unsigned char channelSelect, Sample* data)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_START_ADDRESS = data;
}

void Hall::SetLoop(unsigned char channelSelect, bool isLooping)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_IS_LOOPING = true;
}

void Hall::SetLoopBoundaries(unsigned char channelSelect, int start, int end)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_LOOP_START = start;
	*AUDIO_LOOP_END = end;
}

void Hall::SetPosition(unsigned char channelSelect, int position)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_CURRENT_POSITION = position;
}

void Hall::SetSample(unsigned char channelSelect, short sample)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_LAST_SAMPLE = sample;
}

void Hall::SetVolume(unsigned char channelSelect, unsigned char volume)
{
	*AUDIO_CHANNEL_SELECT = channelSelect;
	*AUDIO_VOLUME = volume;
}
