// Rotation.cpp: implementation of the CRotation class.
//
//////////////////////////////////////////////////////////////////////

#include "Rotation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//=== konstruktor zeruje wskazniki

CRotation::CRotation()
{
	// ustaw znacznik, ze dane nie sa jeszcze wczytane
	m_bActive = false;

	m_pBackground = NULL;	// zerujemy wskazniki
	m_pFile = NULL;
	m_pExitButton = NULL;

	for (int iLicznik=0; iLicznik<32; iLicznik++)
	{
			m_pKlocki[iLicznik]=NULL;
	}


}

//=== destruktor zwalnia pamiec i zeruje wskazniki

CRotation::~CRotation()
{
	// zwolnij tlo jezeli uzywane
	
	if (m_pBackground!=NULL)
	{
		delete m_pBackground;
		m_pBackground=NULL;
	}

	// zwolnij archiwum jezeli uzywane

	if (m_pFile!=NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}

	// zwolnij przycisk exit jezeli uzywane

	if (m_pExitButton!=NULL)
	{
		delete m_pExitButton;
		m_pExitButton=NULL;
	}

	// zwolnij klocki jezeli uzywane

	for (int iLicznik=0; iLicznik<32; iLicznik++)
	{
		if (m_pKlocki[iLicznik]!=NULL)
		{
			delete m_pKlocki[iLicznik];
			m_pKlocki[iLicznik]=NULL;
		}
	}

	// ustaw stan na nieaktywny (brak danych w pamieci)

	m_bActive = false;
}


//=== ustawianie aktywnosci - czy dane sa w pamieci

void CRotation::SetActive(bool bState)
{
	m_bActive = bState;
}

//=== zwraca informacje czy dane sa wczytane

bool CRotation::GetActive(void)
{
	return m_bActive;
}

//=== aktualizuje i wczytuje dane

void CRotation::Initialize(IDirect3DDevice8 *pDevice)
{
	
	m_pFile = new CFileSystem("Resource\\plansze.fox");	// otworz archiwum
	m_pFile->Load("rot001.bmp");	// wczytujemy tlo

	m_pBackground = new CSprite(255,255,255,255);	// nowy sprite

	m_pBackground->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("rot001.bmp"), pDevice);
		
	// zainicjalizuj przycisk exit

	m_pExitButton = new CButton("Resource\\przycisk.fox",
								"exit01.tga",
								"exit03.tga",
								"exit02.tga",pDevice);

	// koniec
	
	delete m_pFile;	// zwolnij system plikow
	m_pFile = NULL; // zeruj wskaznik

	// inicjalizacja klockow

	m_pFile = new CFileSystem("Resource\\klocki.fox");	// otworz

	m_pFile->Load("a.bmp"); 
	m_pKlocki[0] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[0]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("a.bmp"), pDevice);

	m_pFile->Load("ai.bmp"); 
	m_pKlocki[1] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[1]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ai.bmp"), pDevice);

	m_pFile->Load("b.bmp"); 
	m_pKlocki[2] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[2]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("b.bmp"), pDevice);

	m_pFile->Load("c.bmp"); 
	m_pKlocki[3] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[3]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("c.bmp"), pDevice);
	
	m_pFile->Load("ci.bmp"); 
	m_pKlocki[4] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[4]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ci.bmp"), pDevice);

	m_pFile->Load("d.bmp"); 
	m_pKlocki[5] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[5]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("d.bmp"), pDevice);

	m_pFile->Load("e.bmp"); 
	m_pKlocki[6] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[6]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("e.bmp"), pDevice);

	m_pFile->Load("ei.bmp"); 
	m_pKlocki[7] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[7]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ei.bmp"), pDevice);

	m_pFile->Load("f.bmp"); 
	m_pKlocki[8] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[8]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("f.bmp"), pDevice);

	m_pFile->Load("g.bmp"); 
	m_pKlocki[9] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[9]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("g.bmp"), pDevice);

	m_pFile->Load("h.bmp"); 
	m_pKlocki[10] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[10]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("h.bmp"), pDevice);

	m_pFile->Load("i.bmp"); 
	m_pKlocki[11] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[11]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("i.bmp"), pDevice);

	m_pFile->Load("j.bmp"); 
	m_pKlocki[12] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[12]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("j.bmp"), pDevice);

	m_pFile->Load("k.bmp"); 
	m_pKlocki[13] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[13]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("k.bmp"), pDevice);

	m_pFile->Load("l.bmp"); 
	m_pKlocki[14] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[14]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("l.bmp"), pDevice);

	m_pFile->Load("li.bmp"); 
	m_pKlocki[15] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[15]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("li.bmp"), pDevice);

	m_pFile->Load("m.bmp"); 
	m_pKlocki[16] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[16]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("m.bmp"), pDevice);

	m_pFile->Load("n.bmp"); 
	m_pKlocki[17] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[17]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("n.bmp"), pDevice);

	m_pFile->Load("ni.bmp"); 
	m_pKlocki[18] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[18]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ni.bmp"), pDevice);

	m_pFile->Load("o.bmp"); 
	m_pKlocki[19] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[19]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("o.bmp"), pDevice);

	m_pFile->Load("oi.bmp"); 
	m_pKlocki[20] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[20]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("oi.bmp"), pDevice);

	m_pFile->Load("p.bmp"); 
	m_pKlocki[21] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[21]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("p.bmp"), pDevice);

	m_pFile->Load("r.bmp"); 
	m_pKlocki[22] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[22]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("r.bmp"), pDevice);

	m_pFile->Load("s.bmp"); 
	m_pKlocki[23] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[23]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("s.bmp"), pDevice);

	m_pFile->Load("si.bmp"); 
	m_pKlocki[24] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[24]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("si.bmp"), pDevice);

	m_pFile->Load("t.bmp"); 
	m_pKlocki[25] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[25]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("t.bmp"), pDevice);

	m_pFile->Load("u.bmp"); 
	m_pKlocki[26] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[26]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("u.bmp"), pDevice);

	m_pFile->Load("w.bmp"); 
	m_pKlocki[27] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[27]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("w.bmp"), pDevice);

	m_pFile->Load("y.bmp"); 
	m_pKlocki[28] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[28]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("y.bmp"), pDevice);

	m_pFile->Load("z.bmp"); 
	m_pKlocki[29] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[29]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("z.bmp"), pDevice);

	m_pFile->Load("ze.bmp"); 
	m_pKlocki[30] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[30]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ze.bmp"), pDevice);

	m_pFile->Load("zi.bmp"); 
	m_pKlocki[31] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[31]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("zi.bmp"), pDevice);



	delete m_pFile;
	m_pFile = NULL;

	m_bActive = true;	// dane wczytane


}

//=== deaktualizuje, ale trzyma znaczniki (zwalnia tylko textury)

void CRotation::DeInitialize(void)
{

	// zwolnij tlo jezeli uzywane
	
	if (m_pBackground!=NULL)
	{
		delete m_pBackground;
		m_pBackground=NULL;
	}

	// zwolnij archiwum jezeli uzywane

	if (m_pFile!=NULL)
	{
		delete m_pFile;
		m_pFile = NULL;
	}

	// zwolnij klocki jezeli uzywane

	for (int iLicznik=0; iLicznik<32; iLicznik++)
	{
		if (m_pKlocki[iLicznik]!=NULL)
		{
			delete m_pKlocki[iLicznik];
			m_pKlocki[iLicznik]=NULL;
		}
	}

}

//=== rysuje pojedyncza klatke

int CRotation::DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bRightButton, bool bCenterButton)
{
	m_pBackground->Render();	// rysuj tlo

	m_pKlocki[22]->SetTranslation(64*2,200);
	m_pKlocki[22]->Render();

	m_pKlocki[19]->SetTranslation(64*3,200);
	m_pKlocki[19]->Render();

	m_pKlocki[30]->SetTranslation(64*4,200);
	m_pKlocki[30]->Render();

	m_pKlocki[28]->SetTranslation(64*5,200);
	m_pKlocki[28]->Render();

	m_pKlocki[18]->SetTranslation(64*6,200);
	m_pKlocki[18]->Render();

	m_pKlocki[23]->SetTranslation(64*7,200);
	m_pKlocki[23]->Render();

	m_pKlocki[13]->SetTranslation(64*8,200);
	m_pKlocki[13]->Render();

	m_pKlocki[11]->SetTranslation(64*9,200);
	m_pKlocki[11]->Render();


	m_pExitButton->SetPosition(732,532);	// prawy dolny rog
	return m_pExitButton->Draw(fMouseX,fMouseY,bLeftButton,bRightButton,bCenterButton); // przycisk

}
//end
