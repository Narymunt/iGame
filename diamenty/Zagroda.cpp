// Zagroda.cpp: implementation of the Zagroda class.
//
//////////////////////////////////////////////////////////////////////

#include "Zagroda.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Zagroda::Zagroda()
{
	
	for (int b1=0; b1<160; b1++) teren[b1]=1;	// wszedzie trawa

	teren[7]=5;	// murek bialy
	
	for (b1=115; b1<125; b1++) teren[b1]=5;

	for (b1=55; b1<62;b1++) teren[b1]=6;

	for (b1=87; b1<95; b1++) teren[b1]=0;

}

Zagroda::~Zagroda()
{

}
