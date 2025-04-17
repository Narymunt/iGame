// TODO :
// - load sprite
// - free memory in destructor
// - render sprite
// - render sprite to pointer

#define NN_DEBUGINFO 1

#include <stdio.h>
#include <stdlib.h>
#include "iGame.h"


//=== class construktor ===

Sprite::Sprite(void)
{


}

//=== class destructor ===

Sprite::~Sprite(void)
{

}

//=== render sprite ===

void Sprite::Render()
{

}

//=== set alpha blending ===

void Sprite::SetAlpha(unsigned char ucValue)
{

  ucAlpha=ucValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetAlpha : %d\n",ucValue);
  fclose(pFile);
  #endif
}

//=== get alpha blending ===

unsigned char Sprite::ucGetAlpha(void)
{
  return ucAlpha;
}

//=== increase alpha blending ===

void Sprite::IncAlpha(unsigned char ucValue)
{

  unsigned int uiTemp;

  uiTemp=ucValue+ucAlpha;

  if (uiTemp>255) uiTemp=255;  

  ucAlpha = (unsigned char) uiTemp;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncAlpha : + %ld , current %ld\n",ucValue, ucAlpha);
  fclose(pFile);
  #endif
}

//=== decrease alpha blending ===

void Sprite::DecAlpha(unsigned char ucValue)
{

  signed int iTemp;

  iTemp=ucAlpha-ucValue;

  if (iTemp<0) iTemp=0;

  ucAlpha = (unsigned char) iTemp;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.DecAlpha : - %ld , current %ld\n",ucValue, ucAlpha);
  fclose(pFile);
  #endif
}

//=== set alpha switch ===

void Sprite::SetAlphaSwitch(unsigned char ucValue)
{

  ucAlphaSwitch=ucValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetAlphaSwitch : %ld\n",ucValue);
  fclose(pFile);
  #endif
}

//=== get alpha switch ===

unsigned char Sprite::ucGetAlphaSwitch(void)
{
  return ucAlphaSwitch;
}

//=== set frame count, you do not need this in fact ===

void Sprite::SetFrameCount(unsigned long ulValue)
{

  ulFrameCount = ulValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetFrameCount : + %ld\n",ulValue);
  fclose(pFile);
  #endif
}

//=== get frame count ===

unsigned long Sprite::ulGetFrameCount(void)
{
  return ulFrameCount;
}

//=== set frame size ===

void Sprite::SetFrameXSize(unsigned long ulFrame, unsigned long ulSize)
{

  ulFrameXSize[ulFrame]=ulSize;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetFrameXSize : ulFrame %ld , ulSize %ld\n",ulFrame, ulSize);
  fclose(pFile);
  #endif
}

//=== set frame size ===

void Sprite::SetFrameYSize(unsigned long ulFrame, unsigned long ulSize)
{
  ulFrameYSize[ulFrame]=ulSize;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetFrameYSize : ulFrame %ld , ulSize %ld\n",ulFrame, ulSize);
  fclose(pFile);
  #endif
}

//=== set x and y size ===

void Sprite::SetFrameXYSize(unsigned long ulFrame, unsigned long ulSizeX, unsigned long ulSizeY)
{

  ulFrameXSize[ulFrame]=ulSizeX;
  ulFrameYSize[ulFrame]=ulSizeY;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetFrameXYSize : ulFrame %ld , ulSizeX %ld , ulSizeY %ld\n",ulFrame, ulSizeX, ulSizeY);
  fclose(pFile);
  #endif
}

//=== get x size of frame ===

unsigned long Sprite::ulGetFrameXSize(unsigned long ulFrame)
{
  return ulFrameXSize[ulFrame];
}

//=== get y size of frame ===

unsigned long Sprite::ulGetFrameYSize(unsigned long ulFrame)
{
  return ulFrameYSize[ulFrame];
}

//=== set sprite type ===

void Sprite::SetSpriteType(unsigned char ucValue)
{
  ucType=ucValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetSpriteType : %ld\n",ucValue);
  fclose(pFile);
  #endif
}

//=== get sprite type ===

unsigned char Sprite::ucGetSpriteType(void)
{
  return ucType;
}

//=== set sprite position (when static) ===

void Sprite::SetSpriteXPosition(signed int siPosition)
{
  siXPosition=siPosition;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetSpriteXPosition : %ld\n",siPosition);
  fclose(pFile);
  #endif
}

//=== set sprite position (when static) ===

void Sprite::SetSpriteYPosition(signed int siPosition)
{
  siYPosition=siPosition;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetSpriteYPosition : %ld\n",siPosition);
  fclose(pFile);
  #endif
}

//=== get sprite position ===

signed int Sprite::siGetSpriteXPosition(void)
{
  return siXPosition;
}

//=== get sprite position ===

signed int Sprite::siGetSpriteYPosition(void)
{
  return siYPosition;
}

//=== set sprite mass ===

void Sprite::SetMass(double dValue)
{
  dMass=dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetMass : %lf\n",dValue);
  fclose(pFile);
  #endif
}

//=== get sprite mass ===

double Sprite::dGetMass(void)
{
  return dMass;
}

//=== increase sprite mass ===

void Sprite::IncMass(double dValue)
{
  dMass = dMass+dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncMass : dValue %lf , dMass %lf\n", dValue, dMass);
  fclose(pFile);
  #endif
}

//=== decrease sprite mass, cannot be <0 ===

void Sprite::DecMass(double dValue)
{

  dMass = dMass - dValue;

  if (dMass<0) dMass=0.0;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncMass : dValue %lf , dMass %lf\n", dValue, dMass);
  fclose(pFile);
  #endif
}

//=== set x acceleration ===

void Sprite::SetXAcceleration(double dValue)
{
  dXAcceleration = dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetXAcceleration : %lf\n", dValue);
  fclose(pFile);
  #endif
}

//=== set y acceleration ===

void Sprite::SetYAcceleration(double dValue)
{

  dYAcceleration = dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetYAcceleration : %lf\n", dValue);
  fclose(pFile);
  #endif
}

//=== get x acceleration ===

double Sprite::dGetXAcceleration(void)
{
  return dXAcceleration;
}

//=== get y acceleration ===

double Sprite::dGetYAcceleration(void)
{
  return dYAcceleration;
}

//=== increase x acceleration ===

void Sprite::IncXAcceleration(double dValue)
{

  dXAcceleration = dXAcceleration + dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncXAcceleration : dValue %lf , dXAcceleration %lf\n", dValue, dXAcceleration);
  fclose(pFile);
  #endif
}

//=== increase y acceleration ===

void Sprite::IncYAcceleration(double dValue)
{

  dYAcceleration = dYAcceleration + dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncYAcceleration : dValue %lf , dYAcceleration %lf\n", dValue, dYAcceleration);
  fclose(pFile);
  #endif
}

//=== decrease x acceleration, can be <0 ===

void Sprite::DecXAcceleration(double dValue)
{

  dXAcceleration = dXAcceleration - dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.DecXAcceleration : dValue %lf , dXAcceleration %lf\n", dValue, dXAcceleration);
  fclose(pFile);
  #endif
}

//=== decrease y acceleration, can be <0 ===

void Sprite::DecYAcceleration(double dValue)
{

  dYAcceleration = dYAcceleration - dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.DecYAcceleration : dValue %lf , dYAcceleration %lf\n", dValue, dYAcceleration);
  fclose(pFile);
  #endif
}

//=== set sharpness ===

void Sprite::SetSharpness(double dValue)
{

  dSharpness = dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetSharpness : %lf\n", dValue);
  fclose(pFile);
  #endif
}

//=== get sharpness ===

double Sprite::dGetSharpness(void)
{
  return dSharpness;
}

//=== increase sharpness ===

void Sprite::IncSharpness(double dValue)
{
  dSharpness = dSharpness + dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncSharpness : dValue %lf , dSharpness %lf\n", dValue, dSharpness);
  fclose(pFile);
  #endif
}

//=== decrease sharpness, cannot be <0 ===

void Sprite::DecSharpness(double dValue)
{

  dSharpness = dSharpness - dValue;

  if (dSharpness<0) dSharpness=0;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.DecSharpness : dValue %lf , dSharpness %lf\n", dValue, dSharpness);
  fclose(pFile);
  #endif
}

//=== set x add value ===

void Sprite::SetXAdd(double dValue)
{

  dXAdd = dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetXAdd : %lf\n", dValue);
  fclose(pFile);
  #endif
}

//=== set y add value ===

void Sprite::SetYAdd(double dValue)
{

  dYAdd = dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetYAdd : %lf\n", dValue);
  fclose(pFile);
  #endif
}

//=== get x add value ===

double Sprite::dGetXAdd(void)
{
  return dXAdd;
}

//=== get y add value ===

double Sprite::dGetYAdd(void)
{
  return dYAdd;
}

//=== increase x add value ===

void Sprite::IncXAdd(double dValue)
{

  dXAdd = dXAdd + dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncXAdd : dValue %lf , dXAdd %lf\n", dValue, dXAdd);
  fclose(pFile);
  #endif
}

//=== increase y add value ===

void Sprite::IncYAdd(double dValue)
{

  dYAdd = dYAdd + dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncYAdd : dValue %lf , dYAdd %lf\n", dValue, dYAdd);
  fclose(pFile);
  #endif
}

//=== decrease x add value ===

void Sprite::DecXAdd(double dValue)
{

  dXAdd = dXAdd - dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.DecXAdd : dValue %lf , dXAdd %lf\n", dValue, dXAdd);
  fclose(pFile);
  #endif

}

//=== decrease y add value ===

void Sprite::DecYAdd(double dValue)
{

  dYAdd = dYAdd - dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.DecYAdd : dValue %lf , dYAdd %lf\n", dValue, dYAdd);
  fclose(pFile);
  #endif
}

//=== set jumpness ===

void Sprite::SetJumpness(double dValue)
{
  dJumpness = dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.SetJumpness : %lf\n", dValue);
  fclose(pFile);
  #endif
}

//=== get jumpness ===

double Sprite::dGetJumpness(void)
{
  return dJumpness;
}

//=== increase jumpness ===

void Sprite::IncJumpness(double dValue)
{

  dJumpness = dJumpness + dValue;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.IncJumpness : dValue %lf , dJumpness %lf\n", dValue, dJumpness);
  fclose(pFile);
  #endif
}

//=== decrease jumpness, cannot be <0 ===

void Sprite::DecJumpness(double dValue)
{

  dJumpness = dJumpness - dValue;
      
  if (dJumpness<0) dJumpness = 0.0;

  #if (NN_DEBUGINFO==1)
  FILE *pFile;
  pFile=fopen("mml_debug.txt","at");
  fprintf(pFile,"NN_Sprite.DecJumpness : dValue %lf , dJumpness %lf\n", dValue, dJumpness);
  fclose(pFile);
  #endif
}
