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

	m_pRamka = NULL;

	for (int iLicznik=0; iLicznik<32; iLicznik++)
	{
			m_pKlocki[iLicznik]=NULL;
	}

	m_pKlocekRuch = NULL; // nie ma dzwieku

	m_pMysticLogo = NULL;

}

//=== destruktor zwalnia pamiec i zeruje wskazniki

CRotation::~CRotation()
{

	if (m_pMysticLogo!=NULL)
	{
		delete m_pMysticLogo;
		m_pMysticLogo=NULL;
	}

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

	// usun ramke jezeli uzywana

	if (m_pRamka != NULL)
	{
		delete m_pRamka;
		m_pRamka = NULL;
	}

	// usun wave

	if (m_pKlocekRuch!=NULL)
	{
		delete m_pKlocekRuch;
		m_pKlocekRuch = NULL;
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

void CRotation::Initialize(IDirect3DDevice8 *pDevice,char CurrentDirectory[200], CAudio *pAudio)
{
	m_pFile = new CFileSystem("Resource\\klocki.fox");
	m_pFile->Load("mystic.tga");
	m_pMysticLogo = new CSprite(255,255,255,255);
	m_pMysticLogo->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("mystic.tga"), pDevice);
	delete m_pFile;
	m_pFile = NULL;

	
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

	// wczytaj ramke

	m_pFile = new CFileSystem("Resource\\myszka.fox"); // otworz archiwum
	m_pFile->Load("ramka.tga"); // obiekt ramki dla klockow

	m_pRamka = new CSprite(255,255,255,255); // nowy obiekt

	m_pRamka->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ramka.tga"), pDevice);

	delete m_pFile;
	m_pFile = NULL;

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

	// losowanie klocków

	for (int iLicznik=0; iLicznik<28; iLicznik++)
	{
		m_ucKlocki[iLicznik]=rand()%31;
		m_ucKlockiRuch[iLicznik]=5;
	}

	m_cKlockiRuchOffset = 0; // mozna przestawiac
	m_ucClickedKlocek=255;	// zaden

	// wczytanie wave szuru bur

	m_pKlocekRuch = new CSound(CurrentDirectory, pAudio,L"0tambur2.wav");

	m_bActive = true;	// dane wczytane


}

//=== tak samo jak u gory, tylko zamiast literek puzzle

void CRotation::Initialize_Puzzle(IDirect3DDevice8 *pDevice,char CurrentDirectory[200], CAudio *pAudio)
{

	m_pFile = new CFileSystem("Resource\\klocki.fox");
	m_pFile->Load("mystic.tga");
	m_pMysticLogo = new CSprite(255,255,255,255);
	m_pMysticLogo->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("mystic.tga"), pDevice);
	delete m_pFile;
	m_pFile = NULL;

	m_pFile = new CFileSystem("Resource\\plansze.fox");	// otworz archiwum
	m_pFile->Load("rot002.bmp");	// wczytujemy tlo

	m_pBackground = new CSprite(255,255,255,255);	// nowy sprite

	m_pBackground->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("rot002.bmp"), pDevice);
		
	// zainicjalizuj przycisk exit

	m_pExitButton = new CButton("Resource\\przycisk.fox",
								"exit01.tga",
								"exit03.tga",
								"exit02.tga",pDevice);

	// koniec
	
	delete m_pFile;	// zwolnij system plikow
	m_pFile = NULL; // zeruj wskaznik

	// wczytaj ramke

	m_pFile = new CFileSystem("Resource\\myszka.fox"); // otworz archiwum
	m_pFile->Load("ramka2.tga"); // obiekt ramki dla klockow

	m_pRamka = new CSprite(255,255,255,255); // nowy obiekt

	m_pRamka->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ramka2.tga"), pDevice);

	delete m_pFile;
	m_pFile = NULL;

	// inicjalizacja klockow

	m_pFile = new CFileSystem("Resource\\klocki.fox");	// otworz

	m_pFile->Load("k01.bmp"); 
	m_pKlocki[0] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[0]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("a.bmp"), pDevice);

	m_pFile->Load("k02.bmp"); 
	m_pKlocki[1] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[1]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ai.bmp"), pDevice);

	m_pFile->Load("k03.bmp"); 
	m_pKlocki[2] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[2]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("b.bmp"), pDevice);

	m_pFile->Load("k04.bmp"); 
	m_pKlocki[3] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[3]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("c.bmp"), pDevice);
	
	m_pFile->Load("k05.bmp"); 
	m_pKlocki[4] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[4]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ci.bmp"), pDevice);

	m_pFile->Load("k06.bmp"); 
	m_pKlocki[5] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[5]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("d.bmp"), pDevice);

	m_pFile->Load("k07.bmp"); 
	m_pKlocki[6] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[6]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("e.bmp"), pDevice);

	m_pFile->Load("k08.bmp"); 
	m_pKlocki[7] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[7]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ei.bmp"), pDevice);

	m_pFile->Load("k09.bmp"); 
	m_pKlocki[8] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[8]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("f.bmp"), pDevice);

	m_pFile->Load("k10.bmp"); 
	m_pKlocki[9] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[9]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("g.bmp"), pDevice);

	m_pFile->Load("k11.bmp"); 
	m_pKlocki[10] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[10]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("h.bmp"), pDevice);

	m_pFile->Load("k12.bmp"); 
	m_pKlocki[11] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[11]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("i.bmp"), pDevice);

	m_pFile->Load("k13.bmp"); 
	m_pKlocki[12] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[12]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("j.bmp"), pDevice);

	m_pFile->Load("k14.bmp"); 
	m_pKlocki[13] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[13]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("k.bmp"), pDevice);

	m_pFile->Load("k15.bmp"); 
	m_pKlocki[14] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[14]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("l.bmp"), pDevice);

	m_pFile->Load("k16.bmp"); 
	m_pKlocki[15] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[15]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("li.bmp"), pDevice);

	m_pFile->Load("k17.bmp"); 
	m_pKlocki[16] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[16]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("m.bmp"), pDevice);

	m_pFile->Load("k18.bmp"); 
	m_pKlocki[17] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[17]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("n.bmp"), pDevice);

	m_pFile->Load("k19.bmp"); 
	m_pKlocki[18] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[18]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("ni.bmp"), pDevice);

	m_pFile->Load("k20.bmp"); 
	m_pKlocki[19] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[19]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("o.bmp"), pDevice);

	m_pFile->Load("k21.bmp"); 
	m_pKlocki[20] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[20]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("oi.bmp"), pDevice);

	m_pFile->Load("k22.bmp"); 
	m_pKlocki[21] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[21]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("p.bmp"), pDevice);

	m_pFile->Load("k23.bmp"); 
	m_pKlocki[22] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[22]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("r.bmp"), pDevice);

	m_pFile->Load("k24.bmp"); 
	m_pKlocki[23] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[23]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("s.bmp"), pDevice);

	m_pFile->Load("k25.bmp"); 
	m_pKlocki[24] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[24]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("si.bmp"), pDevice);

	m_pFile->Load("k26.bmp"); 
	m_pKlocki[25] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[25]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("t.bmp"), pDevice);

	m_pFile->Load("k27.bmp"); 
	m_pKlocki[26] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[26]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("u.bmp"), pDevice);

	m_pFile->Load("k28.bmp"); 
	m_pKlocki[27] = new CSprite(255,255,255,255); // nowy sprite
	m_pKlocki[27]->InitializeTGAinMemory((unsigned int*)m_pFile->pDataBuffer,
		m_pFile->Search("w.bmp"), pDevice);


	delete m_pFile;
	m_pFile = NULL;

	// losowanie klocków

	for (int iLicznik=0; iLicznik<28; iLicznik++)
	{
		m_ucKlocki[iLicznik]=iLicznik;
		m_ucKlockiRuch[iLicznik]=5;
	}

	m_cKlockiRuchOffset = 0; // mozna przestawiac
	m_ucClickedKlocek=255;	// zaden

	// wczytanie wave szuru bur

	m_pKlocekRuch = new CSound(CurrentDirectory, pAudio,L"0tambur2.wav");

	m_bActive = true;	// dane wczytane


}


//=== deaktualizuje, ale trzyma znaczniki (zwalnia tylko textury)

void CRotation::DeInitialize(void)
{

	if (m_pMysticLogo!=NULL)
	{
		delete m_pMysticLogo;
		m_pMysticLogo=NULL;
	}

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

	// usun wave

	if (m_pKlocekRuch!=NULL)
	{
		delete m_pKlocekRuch;
		m_pKlocekRuch = NULL;
	}

	// usun ramke jezeli uzywana

	if (m_pRamka != NULL)
	{
		delete m_pRamka;
		m_pRamka = NULL;
	}


}

//=== rysuje pojedyncza klatke

int CRotation::DrawScene(long lTimer,float fMouseX, float fMouseY, 
					  bool bLeftButton, bool bCenterButton, bool bRightButton, CAudio *pAudio)
{

	unsigned char ucTempKlocek;

	// mozna klikac ? 

	if (m_cKlockiRuchOffset==0)
	{
			
			// szukamy klocka na ktory nacisnieto

			if ((bLeftButton||bRightButton) && fMouseX>=172 && fMouseX<236 && fMouseY>96 && fMouseY<96+64)
			{
				m_ucClickedKlocek=0;	// ten klikniety 
			}

			if ((bLeftButton||bRightButton) && fMouseX>=236 && fMouseX<300 && fMouseY>96 && fMouseY<96+64)
			{
				m_ucClickedKlocek=1;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=300 && fMouseX<364 && fMouseY>96 && fMouseY<96+64)
			{
				m_ucClickedKlocek=2;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=364 && fMouseX<428 && fMouseY>96 && fMouseY<96+64)
			{
				m_ucClickedKlocek=3;	// ten klikniety
			}
			
			if ((bLeftButton||bRightButton) && fMouseX>=428 && fMouseX<492 && fMouseY>96 && fMouseY<96+64)
			{
				m_ucClickedKlocek=4;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=492 && fMouseX<556 && fMouseY>96 && fMouseY<96+64)
			{
				m_ucClickedKlocek=5;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=556 && fMouseX<620 && fMouseY>96 && fMouseY<96+64)
			{
				m_ucClickedKlocek=5;	// ten klikniety
			}


			if ((bLeftButton||bRightButton) && fMouseX>=172 && fMouseX<236 && fMouseY>160 && fMouseY<224)
			{
				m_ucClickedKlocek=7;	// ten klikniety 
			}

			if ((bLeftButton||bRightButton) && fMouseX>=236 && fMouseX<300 && fMouseY>160 && fMouseY<224)
			{
				m_ucClickedKlocek=8;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=300 && fMouseX<364 && fMouseY>160 && fMouseY<224)
			{
				m_ucClickedKlocek=9;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=364 && fMouseX<428 && fMouseY>160 && fMouseY<224)
			{
				m_ucClickedKlocek=10;	// ten klikniety
			}
			
			if ((bLeftButton||bRightButton) && fMouseX>=428 && fMouseX<492 && fMouseY>160 && fMouseY<224)
			{
				m_ucClickedKlocek=11;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=492 && fMouseX<556 && fMouseY>160 && fMouseY<224)
			{
				m_ucClickedKlocek=12;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=556 && fMouseX<620 && fMouseY>160 && fMouseY<224)
			{
				m_ucClickedKlocek=12;	// ten klikniety
			}


			if ((bLeftButton||bRightButton) && fMouseX>=172 && fMouseX<236 && fMouseY>224 && fMouseY<288)
			{
				m_ucClickedKlocek=14;	// ten klikniety 
			}

			if ((bLeftButton||bRightButton) && fMouseX>=236 && fMouseX<300 && fMouseY>224 && fMouseY<288)
			{
				m_ucClickedKlocek=15;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=300 && fMouseX<364 && fMouseY>224 && fMouseY<288)
			{
				m_ucClickedKlocek=16;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=364 && fMouseX<428 && fMouseY>224 && fMouseY<288)
			{
				m_ucClickedKlocek=17;	// ten klikniety
			}
			
			if ((bLeftButton||bRightButton) && fMouseX>=428 && fMouseX<492 && fMouseY>224 && fMouseY<288)
			{
				m_ucClickedKlocek=18;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=492 && fMouseX<556 && fMouseY>224 && fMouseY<288)
			{
				m_ucClickedKlocek=19;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=556 && fMouseX<620 && fMouseY>224 && fMouseY<288)
			{
				m_ucClickedKlocek=19;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=172 && fMouseX<236 && fMouseY>288 && fMouseY<352)
			{
				m_ucClickedKlocek=14;	// ten klikniety 
			}

			if ((bLeftButton||bRightButton) && fMouseX>=236 && fMouseX<300 && fMouseY>288 && fMouseY<352)
			{
				m_ucClickedKlocek=15;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=300 && fMouseX<364 && fMouseY>288 && fMouseY<352)
			{
				m_ucClickedKlocek=16;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=364 && fMouseX<428 && fMouseY>288 && fMouseY<352)
			{
				m_ucClickedKlocek=17;	// ten klikniety
			}
			
			if ((bLeftButton||bRightButton) && fMouseX>=428 && fMouseX<492 && fMouseY>288 && fMouseY<352)
			{
				m_ucClickedKlocek=18;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=492 && fMouseX<556 && fMouseY>288 && fMouseY<352)
			{
				m_ucClickedKlocek=19;	// ten klikniety
			}

			if ((bLeftButton||bRightButton) && fMouseX>=556 && fMouseX<620 && fMouseY>288 && fMouseY<352)
			{
				m_ucClickedKlocek=19;	// ten klikniety
			}


			// wybierz tor lotu

			if (m_ucClickedKlocek!=255&&bLeftButton)
			{
				m_ucKlockiRuch[m_ucClickedKlocek]=2;	// w dol
				m_ucKlockiRuch[m_ucClickedKlocek+1]=4;	// w lewo
				m_ucKlockiRuch[m_ucClickedKlocek+7]=6;	// w prawo
				m_ucKlockiRuch[m_ucClickedKlocek+8]=8;	// w gore
				m_cKlockiRuchOffset+=3;	// zwieksz offset
				m_pKlocekRuch->Play(pAudio,0,0,0);
			}

			if (m_ucClickedKlocek!=255&&bRightButton)
			{
				m_ucKlockiRuch[m_ucClickedKlocek]=6;	// w prawo
				m_ucKlockiRuch[m_ucClickedKlocek+1]=2;	// w dol
				m_ucKlockiRuch[m_ucClickedKlocek+8]=4;	// w lewo
				m_ucKlockiRuch[m_ucClickedKlocek+7]=8;	// w gore
				m_cKlockiRuchOffset+=3;	// zwieksz offset
				m_pKlocekRuch->Play(pAudio,0,0,0);
			}

	}
	else // trwa ruch
	{
		if (m_lLastTimer!=lTimer)
		{
			m_cKlockiRuchOffset+=3;

			if (m_cKlockiRuchOffset>64)
			{
						if (m_ucKlockiRuch[m_ucClickedKlocek]==2) // obrot przeciw zegarowi
						{
							ucTempKlocek=m_ucKlocki[m_ucClickedKlocek];
							m_ucKlocki[m_ucClickedKlocek]=m_ucKlocki[m_ucClickedKlocek+1];
							m_ucKlocki[m_ucClickedKlocek+1]=m_ucKlocki[m_ucClickedKlocek+8];
							m_ucKlocki[m_ucClickedKlocek+8]=m_ucKlocki[m_ucClickedKlocek+7];
							m_ucKlocki[m_ucClickedKlocek+7]=ucTempKlocek;
							
							m_ucKlockiRuch[m_ucClickedKlocek]=5;	// w dol
							m_ucKlockiRuch[m_ucClickedKlocek+1]=5;	// w lewo
							m_ucKlockiRuch[m_ucClickedKlocek+7]=5;	// w prawo
							m_ucKlockiRuch[m_ucClickedKlocek+8]=5;	// w gore

							m_cKlockiRuchOffset=0;		// bez ruchu
							m_ucClickedKlocek=255;		// zaden nie klikniety
						}

						if (m_ucKlockiRuch[m_ucClickedKlocek]==6)	// obrot zgodnie ze wskazowkami zegara
						{
							ucTempKlocek=m_ucKlocki[m_ucClickedKlocek];
							m_ucKlocki[m_ucClickedKlocek]=m_ucKlocki[m_ucClickedKlocek+7];
							m_ucKlocki[m_ucClickedKlocek+7]=m_ucKlocki[m_ucClickedKlocek+8];
							m_ucKlocki[m_ucClickedKlocek+8]=m_ucKlocki[m_ucClickedKlocek+1];
							m_ucKlocki[m_ucClickedKlocek+1]=ucTempKlocek;	

							m_ucKlockiRuch[m_ucClickedKlocek]=5;	// w dol
							m_ucKlockiRuch[m_ucClickedKlocek+1]=5;	// w lewo
							m_ucKlockiRuch[m_ucClickedKlocek+7]=5;	// w prawo
							m_ucKlockiRuch[m_ucClickedKlocek+8]=5;	// w gore

							m_cKlockiRuchOffset=0;		// bez ruchu
							m_ucClickedKlocek=255;		// zaden nie klikniety
						}

			}
		}
	}
	
	m_pBackground->Render();	// rysuj tlo

	// rysuj scenke

	for (int iY=0; iY<4; iY++)
	{
		for (int iX=0; iX<7; iX++)
		{
			
			switch (m_ucKlockiRuch[7*iY+iX])
			{

			// nie rusza sie

			case 5 : m_pKlocki[m_ucKlocki[7*iY+iX]]->SetTranslation((float)172+(64*iX),(float)96+(64*iY));
					 break;

			// przesuwa sie w lewo
			
			case 4 : m_pKlocki[m_ucKlocki[7*iY+iX]]->SetTranslation((float)172+(64*iX-m_cKlockiRuchOffset),(float)96+(64*iY));
					 break;

			// przesuwa sie w prawo 

			case 6 : m_pKlocki[m_ucKlocki[7*iY+iX]]->SetTranslation((float)172+(64*iX+m_cKlockiRuchOffset),(float)96+(64*iY));
					 break;

			// przesuwa sie do gory

			case 8 : m_pKlocki[m_ucKlocki[7*iY+iX]]->SetTranslation((float)172+(64*iX),(float)96+(64*iY-m_cKlockiRuchOffset));
					 break;

			// przesuwa sie w dol 

			case 2 : m_pKlocki[m_ucKlocki[7*iY+iX]]->SetTranslation((float)172+(64*iX),(float)96+(64*iY+m_cKlockiRuchOffset));
					 break;

			}
			
			m_pKlocki[m_ucKlocki[7*iY+iX]]->Render();
		}
	}

	// ramka

	if (fMouseX>=172 && fMouseX<236 && fMouseY>96 && fMouseY<96+64)
	{
		m_pRamka->SetTranslation(172,96);
		m_pRamka->Render();
	}

	if (fMouseX>=236 && fMouseX<300 && fMouseY>96 && fMouseY<96+64)
	{
		m_pRamka->SetTranslation(236,96);
		m_pRamka->Render();
	}

	if (fMouseX>=300 && fMouseX<364 && fMouseY>96 && fMouseY<96+64)
	{
		m_pRamka->SetTranslation(300,96);
		m_pRamka->Render();
	}

	if (fMouseX>=364 && fMouseX<428 && fMouseY>96 && fMouseY<96+64)
	{
		m_pRamka->SetTranslation(364,96);
		m_pRamka->Render();
	}
			
	if (fMouseX>=428 && fMouseX<492 && fMouseY>96 && fMouseY<96+64)
	{
		m_pRamka->SetTranslation(428,96);
		m_pRamka->Render();
	}

	if (fMouseX>=492 && fMouseX<620 && fMouseY>96 && fMouseY<96+64)
	{
		m_pRamka->SetTranslation(492,96);
		m_pRamka->Render();
	}

	if (fMouseX>=172 && fMouseX<236 && fMouseY>160 && fMouseY<224)
	{
		m_pRamka->SetTranslation(172,160);
		m_pRamka->Render();
	}

	if (fMouseX>=236 && fMouseX<300 && fMouseY>160 && fMouseY<224)
	{
		m_pRamka->SetTranslation(236,160);
		m_pRamka->Render();
	}

	if (fMouseX>=300 && fMouseX<364 && fMouseY>160 && fMouseY<224)
	{
		m_pRamka->SetTranslation(300,160);
		m_pRamka->Render();
	}

	if (fMouseX>=364 && fMouseX<428 && fMouseY>160 && fMouseY<224)
	{
		m_pRamka->SetTranslation(364,160);
		m_pRamka->Render();
	}
			
	if (fMouseX>=428 && fMouseX<492 && fMouseY>160 && fMouseY<224)
	{
		m_pRamka->SetTranslation(428,160);
		m_pRamka->Render();
	}

	if (fMouseX>=492 && fMouseX<620 && fMouseY>160 && fMouseY<224)
	{
		m_pRamka->SetTranslation(492,160);
		m_pRamka->Render();
	}

	if (fMouseX>=172 && fMouseX<236 && fMouseY>224 && fMouseY<288)
	{
		m_pRamka->SetTranslation(172,224);
		m_pRamka->Render();
	}

	if (fMouseX>=236 && fMouseX<300 && fMouseY>224 && fMouseY<288)
	{
		m_pRamka->SetTranslation(236,224);
		m_pRamka->Render();
	}

	if (fMouseX>=300 && fMouseX<364 && fMouseY>224 && fMouseY<288)
	{
		m_pRamka->SetTranslation(300,224);
		m_pRamka->Render();
	}

	if (fMouseX>=364 && fMouseX<428 && fMouseY>224 && fMouseY<288)
	{
		m_pRamka->SetTranslation(364,224);
		m_pRamka->Render();
	}
			
	if (fMouseX>=428 && fMouseX<492 && fMouseY>224 && fMouseY<288)
	{
		m_pRamka->SetTranslation(428,224);
		m_pRamka->Render();
	}

	if (fMouseX>=492 && fMouseX<620 && fMouseY>224 && fMouseY<288)
	{
		m_pRamka->SetTranslation(492,224);
		m_pRamka->Render();
	}

	if (fMouseX>=172 && fMouseX<236 && fMouseY>288 && fMouseY<352)
	{
		m_pRamka->SetTranslation(172,224);
		m_pRamka->Render();
	}

	if (fMouseX>=236 && fMouseX<300 && fMouseY>288 && fMouseY<352)
	{
		m_pRamka->SetTranslation(236,224);
		m_pRamka->Render();
	}

	if (fMouseX>=300 && fMouseX<364 && fMouseY>288 && fMouseY<352)
	{
		m_pRamka->SetTranslation(300,224);
		m_pRamka->Render();
	}

	if (fMouseX>=364 && fMouseX<428 && fMouseY>288 && fMouseY<352)
	{
		m_pRamka->SetTranslation(364,224);
		m_pRamka->Render();
	}
			
	if (fMouseX>=428 && fMouseX<492 && fMouseY>288 && fMouseY<352)
	{
		m_pRamka->SetTranslation(428,224);
		m_pRamka->Render();
	}

	if (fMouseX>=492 && fMouseX<620 && fMouseY>288 && fMouseY<352)
	{
		m_pRamka->SetTranslation(492,224);
		m_pRamka->Render();
	}

	m_pMysticLogo->SetTranslation(32,472);
	m_pMysticLogo->Render();

	// reszta

	m_pExitButton->SetPosition(672,472);	// prawy dolny rog

	m_lLastTimer=lTimer;	// zapamietaj czas

	m_pExitButton->Draw(fMouseX,fMouseY,bLeftButton,bCenterButton,bRightButton); // przycisk

	if (bLeftButton&&bRightButton) return 2;

	return 0;

}
//end
