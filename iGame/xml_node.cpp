#include "xml_node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// konstruktor od razu rezerwuje pamiec na nazwe wezla

CXmlNode::CXmlNode(char cNodeName[])
{
	m_iNodeSize = (int)strlen(cNodeName);
	m_pNodeName = new char[1+m_iNodeSize]; 
	strcpy(m_pNodeName,cNodeName);
	printf("CXmlNode: [new]: %s\n",cNodeName);
}

// destruktor zwalnia tablice z nazwa wezla

CXmlNode::~CXmlNode()
{
	delete []m_pNodeName;
}

// pobierz glebokosc wezla

int CXmlNode::iGetNodeLevel()
{
	return m_iNodeLevel;
}

// ustaw glebokosc wezla

int CXmlNode::iSetNodeLevel(int iNo)
{
	m_iNodeLevel = iNo;
	return 0;
}

// pobierz numer nadrzednego wezla

int CXmlNode::iGetNodeRoot()
{
	return m_iNodeRoot;
}

// ustaw wezel nadrzedny

int CXmlNode::iSetNodeRoot(int iNo)
{
	m_iNodeRoot = iNo;
	return 0;
}

// ustaw nazwe wezla

void CXmlNode::SetNodeName(char cNodeName[])
{
	int i = strlen(cNodeName);
	int j = strlen(m_pNodeName);

	// sprawdz najpierw czy nowa nazwa nie jest dluzsza od starszej
	delete[] m_pNodeName;
	m_pNodeName = new char[1+i];	// od razu rezerwujemy pamiec na nowy wezel

	m_iNodeSize = strlen(m_pNodeName);
	strcpy(m_pNodeName,cNodeName);
}

// pobierz nazwe wezla

char *CXmlNode::cGetNodeName()
{
	return m_pNodeName;
}

// pobierz uproszczona nazwe wezla

char *CXmlNode::cGetShortNodeName()
{

	int i=0;

	for ( i=0; i<m_iNodeSize;i++)
	{
		if (m_pNodeName[i]==' '||m_pNodeName[i]==0x0d||m_pNodeName[i]==0x0a)
	    break;
	}
	strncpy(m_cTmpNode,m_pNodeName,i);

	m_cTmpNode[i]=0;

	return m_cTmpNode;
}

// ustaw rozmiar wezla (po co?)

int CXmlNode::iSetNodeSize(int iSize)
{
	m_iNodeSize = iSize;
	return 0;
}

// pobierz rozmiar wezla

int CXmlNode::iGetNodeSize()
{
	return m_iNodeSize;
}


