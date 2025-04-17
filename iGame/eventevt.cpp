
#include "eventevt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// wczytanie pliku 

CEventEVT::CEventEVT(char cFile[], char cEventName[])
{

    int		iOffset;	// gdzie teraz jestesmy w pliku
    
    FILE	*pPlikEVT;	// plik .evt ktory parsujemy
    char	*pBuforEVT;	// tutaj wczytane dane
    int		iRozmiarEVT;	// rozmiar pliku .evt
    
    char	*pPlikKlatki;	// pliki .001 .002 etc
    
    char	znakA, znakB, znakC;	// do generowania nazw

    pPlikEVT = fopen(cFile,"rb");
    fseek(pPlikEVT,0,SEEK_END); // ustaw na koniec pliku
    iRozmiarEVT = ftell(pPlikEVT);	// gdzie jestesmy?
    printf("EVT: %s size %d\n",cFile,iRozmiarEVT);
    fseek(pPlikEVT,0,SEEK_SET);
    
    // zaalokuj pamiec na plik .evt
    
    pBuforEVT = NULL;
    pBuforEVT = new char[1+iRozmiarEVT];
    if (pBuforEVT==NULL) printf("EVT: za malo pamieci na bufor evt\n");
    
    fread(pBuforEVT,1,iRozmiarEVT,pPlikEVT); // wczytaj dane
    fclose(pPlikEVT);
    
    iOffset = 0; // wyzeruj offset 
    
    m_ucVersion = pBuforEVT[iOffset]; // odczytaj wersje pliku
    printf("EVT: wersja %d\n",m_ucVersion);
    
    iOffset++;
    
    m_uiIloscKlatek = (unsigned int)( (pBuforEVT[iOffset+3]<<24) +
				      (pBuforEVT[iOffset+2]<<16) +
				      (pBuforEVT[iOffset+1]<<8)+
				      (pBuforEVT[iOffset+0])
				    ); // odczytaj ilosc klatek
				    
    printf("EVT: ilosc klatek %d\n",m_uiIloscKlatek);
    
    iOffset+=4;	//zwieksz offset
    
    m_uiIloscZdarzen = (unsigned int)( (pBuforEVT[iOffset+3]<<24) +
				      (pBuforEVT[iOffset+2]<<16) +
				      (pBuforEVT[iOffset+1]<<8)+
				      (pBuforEVT[iOffset+0])
				    ); // odczytaj ilosc zdarzen
				    
    iOffset+=4; // zwieksz offset
    
    printf("EVT: ilosc zdarzen %d\n",m_uiIloscZdarzen); 

    m_pEventFrames = new CBitmap * [m_uiIloscKlatek];
    
    printf("EVT: zaalokowano tablice bitmap\n");

    m_pEvent = new CEvent * [m_uiIloscZdarzen];
    
    printf("EVT: zaalokowano zdarzenia %d\n",m_uiIloscZdarzen);

    // odczytaj eventy
    
    for (unsigned int h1=0; h1<m_uiIloscZdarzen; h1++)
    {
	m_pEvent[h1] = new CEvent();	// nowe zdarzenie
	
	memcpy(m_pEvent[h1]->pGetNazwaZdarzenia(),&pBuforEVT[iOffset],256); // pobierz nazwe
	
	iOffset+=256;	// zwieksz offset
	
	// ustaw liczbe klatek
	
	m_pEvent[h1]->SetLiczbaKlatek((unsigned int)
	    ((pBuforEVT[iOffset+3]<<24)+
	     (pBuforEVT[iOffset+2]<<16)+
	     (pBuforEVT[iOffset+1]<<8)+
	     (pBuforEVT[iOffset+0])));
	     
	iOffset+=4;
	
	m_pEvent[h1]->AllocPositions();	// zaalokuj pamiec na klatki
	m_pEvent[h1]->AllocKlatki(); 	// zaalokuj pamiec na numery klatek
	m_pEvent[h1]->AllocWaveInfo();	// zaalokuj na znacznik odtwarzania wave

	// odczytaj animacje
	
	for (unsigned int h2=0; h2<m_pEvent[h1]->GetLiczbaKlatek(); h2++)
	{
	    m_pEvent[h1]->SetPositionX((unsigned long)h2,(int)
		(pBuforEVT[iOffset+3]<<24) +
		(pBuforEVT[iOffset+2]<<16) +
		(pBuforEVT[iOffset+1]<<8) +
		(pBuforEVT[iOffset+0]));	// ustaw X

	    m_pEvent[h1]->SetPositionY((unsigned long)h2,(int)
		(pBuforEVT[iOffset+7]<<24) +
		(pBuforEVT[iOffset+6]<<16) +
		(pBuforEVT[iOffset+5]<<8) +
		(pBuforEVT[iOffset+4]));	// ustaw X

	    m_pEvent[h1]->SetNrKlatki((unsigned long)h2,(int)
		(pBuforEVT[iOffset+11]<<24) +
		(pBuforEVT[iOffset+10]<<16) +
		(pBuforEVT[iOffset+9]<<8) +
		(pBuforEVT[iOffset+8]));	// ustaw X

	    iOffset+=12;	// zwieksz offset
	    
	    m_pEvent[h1]->SetPlayWaveInfo(h2,pBuforEVT[iOffset]); // ustaw znacznik
	    
	    iOffset++;

	    // jezeli sa dzwieki dla tej klatki to zaladuj nazwy plikow
	    
	    if (m_pEvent[h1]->GetPlayWaveInfo(h2)!=0)
	    {
		m_pEvent[h1]->AllocSFXBankNames();	// jest zdarzenie dzwiekowe
		memcpy(m_pEvent[h1]->pGetFileNazwaBanku(),&pBuforEVT[iOffset],256);
		memcpy(m_pEvent[h1]->pGetFileNazwaZdarzenia(),&pBuforEVT[iOffset+256],256);
	    }

	    iOffset+=512;	// zwieksz offset

	}	// koniec wczytywania animacji

    }	// koniec wczytywania zdarzen

    // teraz wczytujemy klatki, bo stracimy bufor
    
    pPlikKlatki = (char*) malloc(strlen(cEventName));
    strcpy(pPlikKlatki,cEventName);
    
    znakA=znakB=znakC='0';	// wyzeruj
    
    printf("EVT: wczytuje %d klatki...\n",m_uiIloscKlatek);
    
    for (int h1=0; h1<m_uiIloscKlatek; h1++)
    {
	pPlikKlatki[strlen(pPlikKlatki)-1]=znakA;
	pPlikKlatki[strlen(pPlikKlatki)-2]=znakB;
	pPlikKlatki[strlen(pPlikKlatki)-3]=znakC;
	
	m_pEventFrames[h1] = new CBitmap(pPlikKlatki,TGA);
	
	znakA++;
	
	if (znakA==':')
	{
	    znakA='0';
	    znakB++;
	}
	
	if (znakB==':')
	{
	    znakB='0';
	    znakC++;
	}
    }

    free(pPlikKlatki);

    delete []pBuforEVT;

}

// destruktor, jezeli jakies wskazniki nie sa wyzerowane, to zwalniamy pamiec

CEventEVT::~CEventEVT()
{
    delete []m_pEventFrames;
    delete []m_pEvent;
}

void CEventEVT::Put(unsigned int uiNrKlatki, unsigned int uiNrEventu, unsigned char *pBuffer)
{

    // jezeli klatka nie miesci sie w przedziale eventu to wyswietl ostatnia
    
    if (uiNrKlatki>=m_pEvent[uiNrEventu]->GetLiczbaKlatek())
	uiNrKlatki = m_pEvent[uiNrEventu]->GetLiczbaKlatek()-1;
	
    m_pEventFrames[m_pEvent[uiNrEventu]->GetNrKlatki(uiNrKlatki)]->Render(
	m_pEvent[uiNrEventu]->GetPositionX((unsigned long)uiNrKlatki),
	m_pEvent[uiNrEventu]->GetPositionY((unsigned long)uiNrKlatki),
	pBuffer);
	
}

void CEventEVT::Put(unsigned int uiNrKlatki, char cNazwa[], unsigned char *pBuffer)
{

}

void CEventEVT::Put(int iXScreen, int iYScreen, unsigned int uiNrKlatki, unsigned int uiNrEventu, unsigned char *pBuffer)
{

}

void CEventEVT::Put(int iXScreen, int iYScreen, unsigned int uiNrKlatki, char cNazwa[], unsigned char *pBuffer)
{

}
