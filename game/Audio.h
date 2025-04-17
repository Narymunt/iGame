// Audio.h: interface for the CAudio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIO_H__9E58F2AE_535B_4976_B58A_E0623B26DE2B__INCLUDED_)
#define AFX_AUDIO_H__9E58F2AE_535B_4976_B58A_E0623B26DE2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <d3d8.h>
#include <d3dx8.h>
#include <dshow.h>
#include <dmusicc.h>
#include <dmusici.h>

class CAudio  
{
public:
	CAudio();
	virtual ~CAudio();

	IDirectMusicLoader8		 *g_pMusicLoader;
	
	IDirectMusicSegment8     *g_pMusicSegment_Music;	
	
	IDirectMusicPerformance8 *g_pPerformance_Audio;

	virtual HRESULT			Init(char pCurrentDirectory[200]); // inicjalizacja 

	virtual HRESULT PlayMusic(WCHAR wstrFileName[MAX_PATH]/*char Filename[]*/);	// odtwarzaj muzyke
};

#endif // !defined(AFX_AUDIO_H__9E58F2AE_535B_4976_B58A_E0623B26DE2B__INCLUDED_)
