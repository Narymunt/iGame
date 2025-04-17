// sprite class definition
//
// - sprite is only a list of sorted frames
// - sprite event plays animation with tracking

#ifndef _IGAME__SPRITE_
#define _IGAME__SPRITE_

#include "iGame.h"

class Sprite
{

  public :
      Sprite(void);             // constructor, initialize sprite
      virtual ~Sprite(void);    // destructor, deinitialize sprite                               

      //=== sprite drawing functions ===

      virtual void                Render();   // render sprite

      //=== alpha blending ===

      virtual void                SetAlpha(unsigned char ucValue);   // alpha blending
      virtual unsigned char       ucGetAlpha(void);

      virtual void                IncAlpha(unsigned char ucValue);
      virtual void                DecAlpha(unsigned char ucValue);

      //=== alpha switching ===

      virtual void                SetAlphaSwitch(unsigned char ucValue);
      virtual unsigned char       ucGetAlphaSwitch(void);

      //=== sprite data control ===

      virtual void                SetFrameCount(unsigned long ulValue);
      virtual unsigned long       ulGetFrameCount(void);       

      virtual void                SetFrameXSize(unsigned long ulFrame, unsigned long ulSize);
      virtual void                SetFrameYSize(unsigned long ulFrame, unsigned long ulSize);
      virtual void                SetFrameXYSize(unsigned long ulFrame, unsigned long ulSizeX, unsigned long ulSizeY);
      
      virtual unsigned long       ulGetFrameXSize(unsigned long ulFrame);            
      virtual unsigned long       ulGetFrameYSize(unsigned long ulFrame);

      //=== sprite type control ===

      virtual void                SetSpriteType(unsigned char ucValue);
      virtual unsigned char       ucGetSpriteType(void);

      //=== sprite position control ===

      virtual void                SetSpriteXPosition(signed int siPosition);
      virtual void                SetSpriteYPosition(signed int siPosition);

      virtual signed int          siGetSpriteXPosition(void);
      virtual signed int          siGetSpriteYPosition(void);

      //=== sprite physics control ===

      virtual void                SetMass(double dValue);
      virtual double              dGetMass(void);
      virtual void                IncMass(double dValue);
      virtual void                DecMass(double dValue);

      virtual void                SetXAcceleration(double dValue);
      virtual void                SetYAcceleration(double dValue);
      virtual double              dGetXAcceleration(void);
      virtual double              dGetYAcceleration(void);
      virtual void                IncXAcceleration(double dValue);
      virtual void                IncYAcceleration(double dValue);
      virtual void                DecXAcceleration(double dValue);
      virtual void                DecYAcceleration(double dValue);
      
      virtual void                SetSharpness(double dValue);
      virtual double              dGetSharpness(void);
      virtual void                IncSharpness(double dValue);
      virtual void                DecSharpness(double dValue);

      virtual void                SetXAdd(double dValue);
      virtual void                SetYAdd(double dValue);
      virtual double              dGetXAdd(void);
      virtual double              dGetYAdd(void);
      virtual void                IncXAdd(double dValue);
      virtual void                IncYAdd(double dValue);
      virtual void                DecXAdd(double dValue);
      virtual void                DecYAdd(double dValue);
      
      virtual void                SetJumpness(double dValue);
      virtual double              dGetJumpness(void);
      virtual void                IncJumpness(double dValue);
      virtual void                DecJumpness(double dValue);      
                             
  private :

      //=== alpha switch ===

      unsigned char ucAlphaSwitch;  // 0 no alpha at all
                                    // 1 alpha in sprite data
                                    // 2 alpha for all sprite
                                    // 3 alpha for sprite data and all sprite
      unsigned char ucAlpha;                                    
      
  
      //=== sprite data ===

      unsigned long ulFrameCount;   // how many frames

      unsigned long *ulFrameXSize;   // x size of each frame
      unsigned long *ulFrameYSize;   // y size of each frame

      unsigned char **ppucSpriteData; // x*y*4 (rgba)       

      //=== type and position ===
  
      unsigned char   ucType;     // 0 static
                                  // 1 track animated (track is saved)
                                  // x,y + xTrack,yTrack
                                  // 128 physical - if so, physics flags active
                                  // xTrack,yTrack + physics

      signed int      siXPosition;   // when <x_min or >x_max only visible part is painted
      signed int      siYPosition;   // when <y_min or >y_max only visible part is painted

                                
      //=== physics flags, activated only at type>128 ===
                                  
      double          dMass;     // how much does it weight

      double          dXAcceleration; // speed increase per frame
      double          dYAcceleration; // speed increase per frame
      
      double          dSharpness;  // speed decrease per frame

      double          dXAdd;    // x_add per frame
      double          dYAdd;    // y_add per frame

      double          dJumpness;   // how far can it jump
      
      // every frame if type>128 x_position+=(x_acceleration+x_add)
            
};

#endif
