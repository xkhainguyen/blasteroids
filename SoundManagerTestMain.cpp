#include <iostream>
#include "mmlplayer.h"
#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "SoundManager.h"



int main(void)
{
	FsOpenWindow(0,0,800,600,0);

    SoundManager soundManager;
    soundManager.Initialize();

	soundManager.player.Start();

	YsSoundPlayer::Stream stream;
	soundManager.player.StartStreaming(stream);

	YsSoundPlayer::SoundData nextWave;
	auto rawWave=soundManager.mmlplayer.GenerateWave(100);  // Create for next 100ms
	nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

	if(0!=soundManager.mmlplayer.GetLastErrorCode())
	{
		for(auto msg : soundManager.mmlplayer.GetLastError().Format())
		{
			std::cout << msg << std::endl;
		}
	}

    

	for(;;)
	{
		FsPollDevice();

		soundManager.player.KeepPlaying();  // <- This line is only needed for Linux ALSA.

		auto key=FsInkey();
		if(FSKEY_ESC==key)
		{
			break;
		}
        if(FSKEY_SPACE==key)
        {
            soundManager.PlaySound(true, false, false, false);
        }
        if(FSKEY_UP==key)
        {
            soundManager.PlaySound(false, true, false, false);
        }
        if(FSKEY_DOWN==key)
        {
            soundManager.PlaySound(false, false, true, false);
        }
        if(FSKEY_LEFT==key)
        {
            soundManager.PlaySound(false, false, false, true);
        }

		if(YSTRUE==soundManager.player.StreamPlayerReadyToAcceptNextSegment(stream,nextWave))
		{
			soundManager.player.AddNextStreamingSegment(stream,nextWave);
			auto rawWave=soundManager.mmlplayer.GenerateWave(1000);  // Create for next 100ms
			nextWave.CreateFromSigned16bitStereo(YM2612::WAVE_SAMPLING_RATE,rawWave);

			if(0!=soundManager.mmlplayer.GetLastErrorCode())
			{
				for(auto msg : soundManager.mmlplayer.GetLastError().Format())
				{
					std::cout << msg << std::endl;
				}
			}
		}
	}

	//soundManager.player.End();

	return 0;
}
