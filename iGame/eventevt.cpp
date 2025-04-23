
#include "eventevt.h"

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

    delete []pBuforEVT;

}

// destruktor, jezeli jakies wskazniki nie sa wyzerowane, to zwalniamy pamiec

CEventEVT::~CEventEVT()
{
    
}

void CEventEVT::Put(unsigned int uiNrKlatki, unsigned int uiNrEventu, unsigned char *pBuffer)
{

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
