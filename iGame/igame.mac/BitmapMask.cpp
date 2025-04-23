// bitmap mask class implementation

#include <stdio.h>
#include <stdlib.h>
#include "BitmapMask.h"

CBitmapMask::CBitmapMask()
{
    m_pBitmapMaskData = NULL;
}

CBitmapMask::~CBitmapMask()
{
    if (m_pBitmapMaskData!=NULL) free(m_pBitmapMaskData);
}

// od razu zaalokuj pamiec i wczytaj dane z pliku 

CBitmapMask::CBitmapMask(unsigned long size, char filename[])
{
    FILE *bmp_file;

    m_pBitmapMaskData = (unsigned char *) malloc (size);

    if ((bmp_file=fopen(filename,"rb"))==NULL) printf("Error opening %s file!\n",filename);
    fread(m_pBitmapMaskData,size,1,bmp_file);
    fclose(bmp_file);

}

// od razu zaalokuj pamiec

CBitmapMask::CBitmapMask(unsigned long size)
{
    m_pBitmapMaskData = (unsigned char *) malloc (size);
}
