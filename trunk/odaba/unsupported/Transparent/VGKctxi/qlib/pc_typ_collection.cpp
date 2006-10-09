/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc_typ_collection

\brief    


\date     $Date: 2006/06/20 20:44:00,57 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_typ_collection"

#include  <pvgkctxi.h>
#include  <spc_typ_collection.hpp>


/******************************************************************************/
/**
\brief  SetupCollectionByTyp - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCollectionByTyp"

logical pc_typ_collection :: SetupCollectionByTyp ( )
{
  PropertyHandle   *typ   = GPH("typ");
  int32             value = 0;
  int32             indx0 = 0;
  logical           term  = NO;
BEGINSEQ
  if ( !typ )                                       ERROR

  PropertyHandle   typs(GetDictionary(),typ->GetType(),PI_Read);
                                                    SDBCERR
  while ( typs.Get(indx0++) )
    if ( value = typs.GetInt("code") ) 
      Provide(Key((char *)&value));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_typ_collection - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_typ_collection"

     pc_typ_collection :: pc_typ_collection (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


