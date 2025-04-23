
#include "eventsnd.h"

//=== konstruktor 

CEventSND::CEventSND(char cNazwa[], unsigned char ucType)
{
    m_pNazwa = new char[1+sizeof(cNazwa)]; // zarezerwuj pamiec na nazwe
    strcpy(m_pNazwa,cNazwa);
    m_ucType = ucType;
    
    printf("[EventSND] name: %s type:%d size: %d\n",m_pNazwa,m_ucType,sizeof(m_pNazwa));    
}

//=== destruktor


CEventSND::~CEventSND()
{
    delete m_pNazwa;
}
