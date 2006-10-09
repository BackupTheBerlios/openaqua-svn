/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    vgkxi

\brief    


\date     $Date: 2006/07/21 12:14:09,35 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "vgkxi"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>

#include  <ivgkxi.h>

/******************************************************************************/
/**
\brief  CalculateEnumValue - 



\return id - 

\param  source_ph - 
\param  factor - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateEnumValue"

int32 __cdecl CalculateEnumValue (PropertyHandle *source_ph, int32 factor )
{
  double    enum_value = source_ph->GetDouble();

BEGINSEQ
  if ( !enum_value || !factor )                     LEAVESEQ

  if ( factor > 0 )
  {
    enum_value *= factor;
    if ( enum_value > 10000 )
      enum_value = 9999;
  }
  else
  {
    factor *= (-1);
    if ( enum_value > 10000*factor )
      enum_value = 9999;
    else
      enum_value /= factor;    
  }

ENDSEQ
  return(enum_value);
}

/******************************************************************************/
/**
\brief  Output - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

void __cdecl Output (char *string )
{

  SDBError().OutputMessage("","",string);

}

