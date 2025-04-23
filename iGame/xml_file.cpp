#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xml_file.h"

CXmlFile::CXmlFile(char filename[])
{

	m_iFileSize = 0;	// rozmiar pliku, zwroci tez 0 jezeli jest zablokowany
//	m_pFileBuffer = NULL;	// zerowanie wskaznika
//	m_pFile = NULL;	// handler dla pliku

	
	m_pFile = fopen(filename,"rb");	// otwarcie pliku
	
	if (m_pFile == NULL)
	{
		printf(" Cannot open file : %s ! (does not exist?)\n",filename);
	}
	else
	{
		m_iFileSize = iGetFileSize(); // zapamietaj rozmiar pliku
		printf("XML: name: %s size: %d\n",filename,m_iFileSize);
		m_pFileBuffer = new char[1+m_iFileSize];
		fread(m_pFileBuffer,1,m_iFileSize,m_pFile); // wczytanie calego pliku do bufora
		fclose(m_pFile);
	}

}

// destruktor czysci bufor

CXmlFile::~CXmlFile(void)
{
	if (m_pFileBuffer!=NULL)	// zwolnienie bufora
	{
		delete[] m_pFileBuffer;
		m_pFileBuffer = NULL;
	}


// kasujemy wszystkie wskazniki 

//	for (int k=0; k<m_iNodeCount; k++)
//	{
//		if (m_pNodeList[k]!=NULL)
//		delete[] m_pNodeList[k];
//	}

	// kasujemy tablice wskaznikow

	if (m_pNodeList!=NULL)
	{
		delete [] m_pNodeList;
		m_pNodeList = NULL;
	}

// kasujemy wezel glowny

//	if (m_pMainNode!=NULL)
//	{
//		delete[] m_pMainNode;
//		m_pMainNode = NULL;
//	}

	delete cTempNode1;
	delete cTempNode2;
	delete cTempNode3;
}

// pobierz rozmiar pliku, musi juz byc otwarty

int CXmlFile::iGetFileSize()
{
	long curpos;

	curpos = ftell(m_pFile);
	fseek(m_pFile,0L, SEEK_END);
	m_iFileSize = ftell(m_pFile);
	fseek(m_pFile,curpos, SEEK_SET);
	return m_iFileSize;
}

// sortuj wezly

int CXmlFile::iSortNodes()
{
	char cModify = 1;
	int iCount = 0;

	while (cModify)
	{
		cModify =0;
		iCount = 0;
		for (int i=0; i<m_iNodeCount-1; i++) 
		{
			// sortujemy tylko na tym samym poziomie
			if (m_pNodeList[i]->iGetNodeLevel()==m_pNodeList[i+1]->iGetNodeLevel())
			{
				strcpy((char*)cTempNode1,m_pNodeList[i]->cGetNodeName());
				strcpy((char*)cTempNode2,m_pNodeList[i+1]->cGetNodeName());
				
				// sprawdzamy kazdy znaczek po kolei
				
				for (int k=0; k<m_pNodeList[i]->iGetNodeSize(); k++)
				{
					if (cTempNode1[k]<cTempNode2[k]) break;// a<b

					if (cTempNode1[k]>cTempNode2[k]) // trzeba zamienic
					{
						printf ("swap %d<->%d\n",i,i+1);
						// 2->3 1->2 3->1
						strcpy((char*)cTempNode3,(char*)cTempNode2);
						strcpy((char*)cTempNode2,(char*)cTempNode1);
						strcpy((char*)cTempNode1,(char*)cTempNode3);
						m_pNodeList[i]->SetNodeName(cTempNode1);
						m_pNodeList[i+1]->SetNodeName(cTempNode2);
						cModify=1;
						iCount++;
						break;
					}
				}
			} // if
		} // for
		//printf("...%d",iCount);
	} // while
	return 0;
}

// zapisujemy strukture drzewa do pliku

int CXmlFile::iWrite(char filename[])
{
	FILE *pOutFile;

	pOutFile = fopen(filename,"wb");

	fprintf(pOutFile,"<?%s?>",m_pMainNode->cGetNodeName());

	for (int k=0; k<m_iNodeCount; k++) // odtwarzamy na podstawie otwierajacych tagow
	{
		// jezeli ten tag otwierajacy ma mniejszy poziom niz jego poprzednik
		// to dodajemy tag zamykajacy

		if (k>0 && k<m_iNodeCount)
		{
			if ((m_pNodeList[k]->iGetNodeLevel()<m_pNodeList[k-1]->iGetNodeLevel()))
			{
				fprintf(pOutFile,"</%s>",m_pNodeList[k-1]->cGetShortNodeName());
			}	
		}

		// jezeli nastepny tag otwierajacy ma taki sam poziom jak aktualny to 
		// uzupelniamy tagi zamykajace dla tylu poziomow ile jest przed naszym tagiem
		// czyli, pomiedzy <a> i <b> wstawiamy </a>

		for (int l=(k-1);l>0;l--) 
		{
			if (m_pNodeList[l]->iGetNodeLevel()==m_pNodeList[k]->iGetNodeLevel())
			{
				fprintf(pOutFile,"</%s>",m_pNodeList[l]->cGetShortNodeName());
				break;
			}
		}

		// tutaj wstawiamy juz normalnie tag otwierajacy

		if (k<m_iNodeCount)
		{
			fprintf(pOutFile,"\n<%s>",m_pNodeList[k]->cGetNodeName());
		}
	}

	// ostatni tag zamykajacy

	fprintf(pOutFile,"</%s>\n",m_pNodeList[m_iNodeCount-1]->cGetShortNodeName());

	// czy zostaly jakies niedomkniete tagi?

	for (int l=(m_iNodeCount-1);l>=0;l--)
	{
		int iLast = m_pNodeList[m_iNodeCount-1]->iGetNodeLevel();
		int iNow = m_pNodeList[l]->iGetNodeLevel();

		if (iLast>iNow)
		{
			fprintf(pOutFile,"</%s>\n",m_pNodeList[l]->cGetShortNodeName());
		}
	}

	fclose(pOutFile); // zamkniecie pliku
	
	printf ("XML: write %s ok!\n",filename);

	return 0;
}

// stworzenie wezlow, musi byc wczytany plik

int CXmlFile::iCreateNodes()
{
	// search for xml opening tags
	char cStartTag[5];
	char cEndTag[2];
	int iStart = 0;	// <?xml offset
	int iEnd = 0; // ?>
	int i=0,j=0;
	char cHit=0;
	int iMax=0;

	while (i<m_iFileSize) // szukaj lancucha <?xml
	{
		strncpy((char*)cStartTag,m_pFileBuffer+i,5);
		if (cStartTag[0]=='<' &&
			cStartTag[1]=='?' &&
			cStartTag[2]=='x' &&
			cStartTag[3]=='m' &&
			cStartTag[4]=='l')
		{
			iStart = i;
			cHit=1; // znaleziono lancuch
			break;
		}
		i++;
	}

	while ((iEnd<1) && (i<m_iFileSize)) // szukaj lancucha zamykajacego ?>
	{
		strncpy((char*)cEndTag,m_pFileBuffer+i,2);		
		if (cEndTag[0]=='?'&&cEndTag[1]=='>') iEnd=i;
		i++;
	}

	// lancuch <?xml?> otwarty albo zamkniety ? 
	
	if (cHit==0 || iEnd<1)
	{
		printf("XML:  Cannot find <?xml> opening tag - this is not XML file ?\n");
		return -1;
	} 

	printf("XML: start offset %d , end offset %d\n",iStart,iEnd);

	for (int z=0; z<1024; z++) pTagName[z]=0;
	strncpy((char*)pTagName,m_pFileBuffer+iStart+2,iEnd-iStart-2); // skopiuj linie do bufora tymczasowego

	m_pMainNode = new CXmlNode(pTagName); // glowny wezel
	m_pMainNode->iSetNodeRoot(0); // this is main node, no level up
	m_pMainNode->iSetNodeLevel(1);	// first node

	// search and count tags

	iStart = i;
	m_iNodeCount = 0;

	while (i<m_iFileSize) // przeszukaj caly plik
	{
		if (m_pFileBuffer[i]=='<'&&m_pFileBuffer[i+1]!='/'&&m_pFileBuffer[i+1]!='!') // open tags
		{
			m_iNodeCount++;
		}
		i++;
	}

	printf ("XML: %d nodes\n",m_iNodeCount);

	// reserve memory for all nodes

	m_pNodeList = new CXmlNode*[m_iNodeCount];

	// parse tags

	m_iNodeCount = 0;
	m_iNodeLevel = 0;
	i = iStart;
	while (i<m_iFileSize)
	{
		if (m_pFileBuffer[i]=='<'&&m_pFileBuffer[i+1]!='/'&&m_pFileBuffer[i+1]!='!') // open tags
		{
			for (j=i; j<m_iFileSize;j++)
			{
				if ((m_pFileBuffer[j]=='>')||
				    (m_pFileBuffer[j]=='/'&&m_pFileBuffer[j+1]=='>')
				   ) break;
				
			}
			
			for (int k=0; k<(j-i); k++) pTagName[k] = m_pFileBuffer[i+1+k];
			pTagName[j-i-1]=0;
	
			m_pNodeList[m_iNodeCount] = new CXmlNode(pTagName);
			if (iMax<m_pNodeList[m_iNodeCount]->iGetNodeSize())
				iMax = m_pNodeList[m_iNodeCount]->iGetNodeSize();
			m_iNodeCount++;

			m_iNodeLevel++;
			m_pNodeList[m_iNodeCount-1]->iSetNodeLevel(m_iNodeLevel);
/*
			printf("+");
			for (int k=0; k<m_iNodeLevel; k++) printf("-");
			printf("%d <%s>\n",m_iNodeCount,pTagName);
*/
		}

		// tagi zamykajace 
		
		if ((m_pFileBuffer[i]=='/' && m_pFileBuffer[i+1]=='>')||
		    (m_pFileBuffer[i]=='<' && m_pFileBuffer[i+1]=='/')) 
		{
/*			printf("+");
			for (int k=0; k<m_iNodeLevel; k++) printf("-");
			printf("%d </%s>\n",m_iNodeCount,pTagName);
*/			m_iNodeLevel--;	// odejmij poziom galezi
		}
		i++;
	}

/*
if (!SILENT)
{
	printf("---XML\n");
	printf("- deconstruct -\n");
	

	for (int k=0; k<m_iNodeCount; k++) // odtwarzamy na podstawie otwierajacych tagow
	{
		// jezeli ten tag otwierajacy ma mniejszy poziom niz jego poprzednik
		// to dodajemy tag zamykajacy

		if (k>0 && k<m_iNodeCount)
		{
			if ((m_pNodeList[k]->iGetNodeLevel()<m_pNodeList[k-1]->iGetNodeLevel()))
			{
				printf("no1: %d lvl: %d name: </%s>\n",k-1,m_pNodeList[k-1]->iGetNodeLevel(),m_pNodeList[k-1]->cGetShortNodeName());
			}	
		}

		// jezeli nastepny tag otwierajacy ma taki sam poziom jak aktualny to 
		// uzupelniamy tagi zamykajace dla tylu poziomow ile jest przed naszym tagiem
		// czyli, pomiedzy <a> i <b> wstawiamy </a>

		for (int l=(k-1);l>0;l--) 
		{
			if (m_pNodeList[l]->iGetNodeLevel()==m_pNodeList[k]->iGetNodeLevel())
			{
			printf("no2: %d lvl: %d name: </%s>\n",k,m_pNodeList[l]->iGetNodeLevel(),m_pNodeList[l]->cGetShortNodeName());
			break;
			}
		}

		// tutaj wstawiamy juz normalnie tag otwierajacy

		if (k<m_iNodeCount)
		{
			printf("no3: %d lvl: %d name: <%s>\n",k,m_pNodeList[k]->iGetNodeLevel(),m_pNodeList[k]->cGetNodeName());
		}
	}

	// ostatni tag zamykajacy

	printf("no4: -1 lvl : %d name: </%s>\n",m_pNodeList[m_iNodeCount-1]->iGetNodeLevel(),m_pNodeList[m_iNodeCount-1]->cGetShortNodeName());

	// czy zostaly jakies niedomkniete tagi?

	for (int l=(m_iNodeCount-1);l>=0;l--)
	{
		int iLast = m_pNodeList[m_iNodeCount-1]->iGetNodeLevel();
		int iNow = m_pNodeList[l]->iGetNodeLevel();

		if (iLast>iNow)
		{
		printf("no : %d lvl: %d name: </%s>\n",l,m_pNodeList[l]->iGetNodeLevel(),m_pNodeList[l]->cGetShortNodeName());
		}
	}
} // !SILENT
*/
	printf("XML: max node size %d\n",iMax);
	
	cTempNode1 = new char[1+iMax];
	cTempNode2 = new char[1+iMax];
	cTempNode3 = new char[1+iMax];

	return 0;
}
