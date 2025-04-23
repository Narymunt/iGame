
#ifndef _IGAME__XML_NODE_
#define _IGAME__XML_NODE_

class CXmlNode
{
public:
	CXmlNode(char cNodeName[]);
	~CXmlNode(void);

	int iSetNodeRoot(int iNo);	// set root node for this node
	int iGetNodeRoot();

	int iSetNodeLevel(int iNo); 	// set node level
	int iGetNodeLevel();

	int iSetNodeSize(int iSize); // ustaw rozmiar nazwy wezla
	int iGetNodeSize(); // pokaz rozmiar wezla

	void SetNodeName(char cNodeName[]);	// set or get node name
	char *cGetNodeName();
	char *cGetShortNodeName();

private:
	int m_iNodeRoot;	// which node is upper, 1 = top level
	char *m_pNodeName;	// name of node without tags ie html, xml instead of <html>,<xml>
	int m_iNodeLevel;	// which node in file
	int m_iNodeSize;	// ile zajmuje ciag 

	char m_cType;
	char m_cTmpNode[1024];
};

#endif
