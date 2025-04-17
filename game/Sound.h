// Sound.h: interface for the CSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUND_H__F16FA03D_37B8_4601_BD7F_D86275D814F5__INCLUDED_)
#define AFX_SOUND_H__F16FA03D_37B8_4601_BD7F_D86275D814F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSound  
{
public:
	CSound(CAudio *currentAudio, WCHAR wstrFilename[MAX_PATH]);
	virtual ~CSound();

	IDirectMusicSegment8     *g_pMusicSegmentData;
	
	IDirectSound3DBuffer8	 *pDirectSoundBuffer;
	IDirectMusicAudioPath8	 *pDirectAudioPath;

	IDirectMusicPerformance8 *pMusic_Performance;  
	
	Play(CAudio *currentAudio,float x_sound, float y_sound, float z_sound);
	
};

#endif // !defined(AFX_SOUND_H__F16FA03D_37B8_4601_BD7F_D86275D814F5__INCLUDED_)
