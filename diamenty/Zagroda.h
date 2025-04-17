// Zagroda.h: interface for the Zagroda class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZAGRODA_H__A6E98228_C651_4B22_9ACB_54F1B09FE39E__INCLUDED_)
#define AFX_ZAGRODA_H__A6E98228_C651_4B22_9ACB_54F1B09FE39E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Zagroda  
{
public:
	Zagroda();
	virtual ~Zagroda();

	unsigned char offset_x;		// rzutowanie terenu globalnego
	unsigned char offset_y;		// rzutowanie terenu globalnego

	unsigned char teren_global[80*50];	// 5x5 ekranow
	unsigned char teren[16*10];		// x * y

};

#endif // !defined(AFX_ZAGRODA_H__A6E98228_C651_4B22_9ACB_54F1B09FE39E__INCLUDED_)
