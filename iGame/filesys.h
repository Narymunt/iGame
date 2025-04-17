
#ifndef _IGAME__FILESYS_
#define _IGAME__FILESYS_

#define Filesystem_COMPR_NONE 0
#define Filesystem_COMPR_LZSS 1
#define Filesystem_COMPR_LZAR 2

#define N 4096
#define F 18
#define THRESHOLD 2
#define F2 60
#define M 15
#define Q1 (1UL<<M)
#define Q2 (2*Q1)
#define Q3 (3*Q1)
#define Q4 (4*Q1)
#define MAX_CUM (Q1-1)
#define N_CHAR (256-THRESHOLD)

class CFilesystem 
{

    public : 
	
	CFilesystem(char cArchiveName[]);
	virtual ~CFilesystem();
	
	virtual long SearchFile(char cFilename[]);	// search for file inside archive
	virtual void LoadIn(unsigned char *uc_pBuffer);
	virtual void Load(unsigned char *uc_pBuffer, char cFilename[]);	// load file from archive
	
    protected :

      unsigned long ulLow;
      unsigned long ulHigh;
      unsigned long ulValue;
      
      int iChar_To_Sym[N_CHAR];
      int iSym_To_Char[N_CHAR+1];
      int iShifts;

      unsigned int uiSym_Freq[N_CHAR+1];
      unsigned int uiSym_Cum[N_CHAR+1];
      unsigned int uiPosition_Cum[N+1];
      
      unsigned char ucTextBuf[N+F2-1];
      
      unsigned char *ucpFromBuffer;
      unsigned char *ucpToBuffer;
      
      unsigned long ulFromPointer;
      unsigned long ulFromMax;
      unsigned long ulToPointer;
      unsigned long ulTextSize;
      unsigned long ulCodeSize;
       
	unsigned int ui_PBBuffer;
	unsigned int ui_PBMask;
	unsigned int ui_GBBuffer;
	unsigned int ui_GBMask;      

	FILE *lz_fptr;
	
	char *cpArchiveName;
	
	char cHeader[8];	// identifier
	short sVersion;		// file version
	unsigned long ulNumberFiles;	// number of files inside archive
	
	char cName[13]; // packed file name
	unsigned long ulLocation; //offset of filedata from end of .exe file
	unsigned long ulLength; // filesize
	unsigned long ulOriginalLength; // filesize without compression
	short sCompression; // compression type
	
};

#endif
