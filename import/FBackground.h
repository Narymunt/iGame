// FBackground.h: interface for the FBackground class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FBACKGROUND_H__019CE582_3EF3_4FB7_9EEB_AC925D7A548E__INCLUDED_)
#define AFX_FBACKGROUND_H__019CE582_3EF3_4FB7_9EEB_AC925D7A548E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fox.h>

class FBackground  
{
public:
	
	
	FBackground(char csFilename[]);
	virtual ~FBackground();

	FOX_Surface	*image;		// tutaj jest obraz 

};

#endif // !defined(AFX_FBACKGROUND_H__019CE582_3EF3_4FB7_9EEB_AC925D7A548E__INCLUDED_)
