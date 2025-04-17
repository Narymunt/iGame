
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
    
    int iSin1024[256];
    int iCos1024[256];

};

#endif
