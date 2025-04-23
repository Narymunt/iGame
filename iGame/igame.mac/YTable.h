// y table for fast precalc
// zamiast 320*y+x bierzemy ytable[y]+x

#ifndef _IGAME__Y__TABLE_
#define _IGAME__Y__TABLE_

class CYtable  
{
						// do przeliczania wartosci
public:

	unsigned long	*mLine;

	CYtable();
	CYtable(unsigned long size, unsigned long resolution);	// size * resolution

	virtual ~CYtable();

};

#endif
