// strlen zwraca dlugosc lancucha, a sizeof(nazwa[]) zwraca ile w pamieci zajmuje ten wskaznik


#include "eventsnd.h"

//=== konstruktor 

CEventSND::CEventSND(char cNazwa[], unsigned char ucType)
{
    m_pNazwa = new char[1+strlen(cNazwa)]; // zarezerwuj pamiec na nazwe
    strcpy(m_pNazwa,cNazwa);
    m_ucType = ucType;
    m_iCount = 0;
    printf("[EventSND] name: %s type:%d size: %d\n",m_pNazwa,m_ucType,strlen(m_pNazwa));    
}

//=== destruktor

CEventSND::~CEventSND()
{
    delete m_pNazwa;
    
    // kasowanie wave
    
    for (int i=0; i<m_iCount; i++)
    {
	Mix_FreeChunk(m_pWave[i]);
	m_pWave[i]=NULL;
    }
    
}

//=== dodanie dzwieku do tablicy

void CEventSND::Add(char cWaveName[])
{
    printf("[EventSND] adding wave...%s ",cWaveName);
    m_pWave[m_iCount] = Mix_LoadWAV(cWaveName);
    m_iCount++;	// mamy o jeden dzwiek wiecej
    printf("ok! current count %d\n",m_iCount);
}

// odegraj konkretny numer wave

void CEventSND::PlayNo(int iNo)
{
    Mix_PlayChannel(-1,m_pWave[iNo],0);
}

// odegraj losowy dzwiek

void CEventSND::PlayRandom(int iNo)
{
    Mix_PlayChannel(-1,m_pWave[iNo%m_iCount],0);
}