// parsowanie pliku xml

#ifndef _IGAME__XML_FILE_
#define _IGAME__XML_FILE_

#include "xml_node.h"	// wezel w pliku xml

class CXmlFile
{
public:
	CXmlFile(char filename[]);
	~CXmlFile(void);
	
	int iGetFileSize();	// return size of file and store it in m_iFileSize;

	int iSortNodes();	// alfabetic sorting
	int iWrite(char filename[]);	// write xml file as new one	

	int iCreateNodes();	// create xml nodes, return number of nodes

	int iGetNodeCount();	// podaj ilosc wezlow
	
	char *cGetNodeName(int iNode);	// podaj nazwe wezla

private:

	FILE *m_pFile;			// parsowany plik
	char *m_pFileBuffer;		// dane z pliku w pamieci

	int m_iFileSize;		// rozmiar pliku

	int m_iNodeCount;		// licznik wezlow
	int m_iNodeLevel;		// licznik poziomu wezla

	CXmlNode *m_pMainNode;	// glowny wezel
	CXmlNode **m_pNodeList;	// wskaznik na tablice wezlow

	char pTagName[1024];	// dane z jednej linii

	char *cTempNode1;	// potrzebne do sortowania
	char *cTempNode2;
	char *cTempNode3;
};


#endif 
