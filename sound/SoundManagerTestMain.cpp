#include "fssimplewindow.h"
#include "yssimplesound.h"
#include "SoundManager.h"



int main(void)
{
	FsOpenWindow(0,0,800,600,0);

    SoundManager soundManager;
    soundManager.Initialize();

	soundManager.player.Start();
	soundManager.PlayMusic();

	for(;;)
	{
		FsPollDevice();

		//soundManager.player.KeepPlaying();  // <- This line is only needed for Linux ALSA.

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
	}

	return 0;
}
