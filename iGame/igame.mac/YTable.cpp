// implementation of y table class

#include <stdio.h>
#include <stdlib.h>
#include "iGame.h"

CYtable::CYtable()
{
    mLine = NULL;
}

CYtable::~CYtable()
{
	if (mLine!=NULL) free(mLine);		
}

CYtable::CYtable(unsigned long size, unsigned long resolution)
{

	unsigned long t1;

	if ( (mLine=(unsigned long*)malloc (size))==NULL) printf("Error - too big YTable!\n");

	for (t1=0;t1<size;t1++)
	{
		mLine[t1]= resolution * t1;		// 1*800, 2*800, 3*800
	}

}

