
// sin^cos tables for integers

#ifndef _IGAME_SINTABLE_
#define _IGAME_SINTABLE_

class SinTable
{

    public : 
    
	SinTable();
	virtual ~SinTable();
    
    protected : 

    int iSin256[256];
    int iCos256[256];
    
    int iSin1024[1024];
    int iCos1024[1024];

    float fSin256[256];
    float fCos256[256];

    float fSin1024[1024];
    float fCos1024[1024];
    
};

#endif
