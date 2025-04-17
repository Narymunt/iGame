// if MML_DEBUG is defined, all data will be logged

#ifndef _IGAME__DEBUG_
#define _IGAME__DEBUG_

#include <stdlib.h>
#include <stdio.h>

// just rem this line if you don't want full debug info

#define DEBUG     1    

//=== send info to file ===

/*

void iGamePrint(char cDebugInfo[])
{

  FILE *pDebugFile;

  pDebugFile=fopen("iGame.log","at");
  fprintf(pDebugFile,cDebugInfo);
  fclose(pDebugFile);

}
*/

#endif
