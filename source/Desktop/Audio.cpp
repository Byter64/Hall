#include <Hall/Audio.h>
extern "C" 
{
	#include "raylib.h"
}
#include <iostream>

//Sound does not behave exactly as on wueHans


struct Channel
{
	::Sound sound;
	bool isLooping;
	float currentPosition;
	float loopStart;
	float loopEnd;
};

Channel channels[8];
bool startPlayingOnFrame[8];

void _UpdateAudio(float frameTime)
{
	//This implements looping audio :/
	for(int i = 0; i < 8; i++)
	{
		if (startPlayingOnFrame[i])
		{
			channels[i].currentPosition = 0;
			::PlaySound(channels[i].sound);
			startPlayingOnFrame[i] = false;
		}

		Channel& channel = channels[i];
		if(::IsSoundPlaying(channel.sound))
		{
			channel.currentPosition += frameTime;
			if(channel.isLooping && channel.currentPosition >= channel.loopEnd)
			{
				::StopSound(channel.sound);
				::PlaySound(channel.sound);
				channel.currentPosition = 0;
			}
		}
	}
}

static float VolumeCon(unsigned char volume)
{
	return (float)volume / 255.0f;
}

void Hall::SetGlobalVolume(unsigned char volume)
{
	//volume = 255 is max volume
	float volume_f = VolumeCon(volume);
	::SetMasterVolume(volume_f);
}

void Hall::SetupMono(int channelID, const Sample* data, int sampleCount, unsigned char volume)
{
	::Wave wave;
	wave.channels = 1;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 1);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));

	channels[channelID].sound = sound;
	channels[channelID].isLooping = false;
}

void Hall::SetupMono(int channelID, const Sample* data, int sampleCount, unsigned int loopStart, unsigned int loopEnd, unsigned char volume)
{
	if(loopStart != 0)
		std::cout << "loopStart != 0 IS NOT SUPPORTED IN DESKTOP VERSION OF HALL" << std::endl;

	::Wave wave;
	wave.channels = 1;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 1);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));


	channels[channelID].sound = sound;
	channels[channelID].isLooping = true;
	channels[channelID].currentPosition = 0;
	channels[channelID].loopStart = loopStart / (float)32000;
	channels[channelID].loopEnd = loopEnd / (float)32000;
}

void Hall::SetupStereo(int channelID_left, int channelID_right, const Sample* data, int sampleCount, unsigned char volume)
{
	::Wave wave;
	wave.channels = 2;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 2);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));

	channels[channelID_left].sound = sound;
	channels[channelID_left].isLooping = false;
}

void Hall::SetupStereo(int channelID_left, int channelID_right, const Sample* data, int sampleCount, unsigned int loopStart, unsigned int loopEnd, unsigned char volume)
{
	if(loopStart != 0)
		std::cout << "loopStart != 0 IS NOT SUPPORTED IN DESKTOP VERSION OF HALL" << std::endl;

	::Wave wave;
	wave.channels = 2;
	wave.data = (void*)data;
	//A frame seems to be exactly one point in time. So a frame consists of one sample per channel
	wave.frameCount = (sampleCount / 2);
	wave.sampleRate = 32000;
	wave.sampleSize = 16;

	::Sound sound = ::LoadSoundFromWave(wave);
	::SetSoundVolume(sound, VolumeCon(volume));


	channels[channelID_left].sound = sound;
	channels[channelID_left].isLooping = true;
	channels[channelID_left].currentPosition = 0;
	channels[channelID_left].loopStart = loopStart / (float)32000;
	channels[channelID_left].loopEnd = loopEnd / (float)32000;
}

void Hall::Play(unsigned char channelSelect)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			//If audio is longer than 5 secs, only preload the audio and play it on the text frame
			if (channels[i].sound.frameCount >= 5 * 32000)
			{
				//Loading sounds takes time so we only load them here
				//Audio starts in sync with the frame
				::PlaySound(channels[i].sound);
				::PauseSound(channels[i].sound);
				startPlayingOnFrame[i] = true;
			}
			else
			{
				::PlaySound(channels[i].sound);
				channels[i].currentPosition = 0;
			}
		}
	}
}

void Hall::Pause(unsigned char channelSelect)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			::PauseSound(channels[i].sound);
			channels[i].currentPosition = 0;
		}
	}
}

void Hall::SetData(unsigned char channelSelect, Sample* data)
{
	std::cout << "Hall::SetData IS NOT SUPPORTED IN DESKTOP VERSION OF HALL" << std::endl;
}

void Hall::SetLoop(unsigned char channelSelect, bool isLooping)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			channels[i].isLooping = isLooping;
		}
	}
}

void Hall::SetLoopBoundaries(unsigned char channelSelect, int start, int end)
{
	if(start != 0)
		std::cout << "loopStart != 0 IS NOT SUPPORTED IN DESKTOP VERSION OF HALL" << std::endl;

	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			channels[i].loopStart = start / 32000.0f;
			channels[i].loopStart = end / 32000.0f;
		}
	}
}

void Hall::SetPosition(unsigned char channelSelect, int position)
{
	std::cout << "Hall::SetPosition IS NOT SUPPORTED IN DESKTOP VERSION OF HALL" << std::endl;
}

void Hall::SetSample(unsigned char channelSelect, short sample)
{
	std::cout << "Hall::SetSample IS NOT SUPPORTED IN DESKTOP VERSION OF HALL" << std::endl;
}

void Hall::SetVolume(unsigned char channelSelect, unsigned char volume)
{
	for(int i = 0; i < 8; i++)
	{
		bool select = (channelSelect >> i) & 1;
		if(select)
		{
			::SetSoundVolume(channels[i].sound, VolumeCon(volume));
		}
	}
}