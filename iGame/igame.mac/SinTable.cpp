// sin^cos tables 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SinTable.h"

SinTable::SinTable(void)
{

    float fA, fC;
    
    fC=3.1415927/128.0;
    
    for (int iTemp=0, fA=0.0; iTemp<256; iTemp++, fA+=fC)
    {
	fSin256[iTemp] = (int)((sin(fA)*256.0)+0.5);
	fCos256[iTemp] = (int)((cos(fA)*256.0)+0.5);
    }

    fC=3.1415927/512.0;
    
    for (int iTemp=0, fA=0.0; iTemp<1024; iTemp++, fA+=fC)
    {
	fSin1024[iTemp] = (int)((sin(fA)*512.0)+0.5);
	fCos1024[iTemp] = (int)((cos(fA)*512.0)+0.5);
    }


}

SinTable::~SinTable(void)
{

}
    

