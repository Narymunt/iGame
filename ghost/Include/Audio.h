// Audio.h: interface for the CAudio class.
// 
// przechwytywanie urz�dzenia audio i odtwarzanie g��wnego d�wi�ku 
// czyli np muzyki, poza tym kontrola g�o�no�ci
// po konstruktorze trzeba wywolac init
//////////////////////////////////////////////////////////////////////

#ifndef _GHOSTAUDIO_
#define _GHOSTAUDIO_

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <dmusicc.h>
#include <dmusici.h>

class __declspec(dllexport) CAudio  
{

public:
	
	CAudio();				// konstruktor czysci zmienne (NULL)
	virtual ~CAudio();		// destruktor zwalnia pamiec i urzadzenie

	// inicjalizacja urz�dzenia

	virtual HRESULT		Init(char pCurrentDirectory[200],char cAddDirectory[]);	
	virtual HRESULT		PlayMusic(WCHAR wstrFileName[MAX_PATH]);	// odtwarzaj WAV
	virtual HRESULT		StopMusic(int iDelay);

	IDirectMusicLoader8		 *g_pMusicLoader;			// loader dla directx 8
	IDirectMusicPerformance8 *g_pPerformance_Audio;		// demon odtwarzaj�cy
	IDirectMusicSegment8     *g_pMusicSegment_Music;	// segment odtwarzanych danych

};

#endif 
