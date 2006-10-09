/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pcBase

\brief    


\date     $Date: 2006/07/12 18:55:18,09 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pcBase"

#include  <pVGKbase.h>
#include  <spcBase.hpp>


/******************************************************************************/
/**
\brief  ProvideInSpecialExtent - 



\return term - Abbruchbedingung

\param  extnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideInSpecialExtent"

logical pcBase :: ProvideInSpecialExtent (char *extnames )
{
  char       *cur_extent = GetExtentName();
  logical     term       = NO;
BEGINSEQ
  if ( !cur_extent || !extnames )                   LEAVESEQ
  if ( !Exist() )                                   ERROR
  
  if ( strcmp(cur_extent,extnames) )
  {
    PropertyHandle   extent(GetDBHandle(),extnames,PI_Write);
                                                    SDBCERR
// waere besser, aber der vertraegt weak-typed nicht
//    extent.Provide(ExtractKey());                   SDBCERR

    if ( !extent.Get(ExtractKey()) )
      extent.AddReference(*this);                   SDBCERR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveFromSpecialExtent - 



\return term - Abbruchbedingung

\param  extnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveFromSpecialExtent"

logical pcBase :: RemoveFromSpecialExtent (char *extnames )
{
  char       *cur_extent = GetExtentName();
  logical     term       = NO;
BEGINSEQ
  if ( !cur_extent || !extnames )                   LEAVESEQ
  if ( !Exist() )                                   ERROR
  
  if ( strcmp(cur_extent,extnames) )
  {
    PropertyHandle   extent(GetDBHandle(),extnames,PI_Write);
                                                    SDBCERR
    if ( extent.Get(ExtractKey()) )
      extent.Delete();
  }
  else 
    Delete();                                       SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pcBase - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pcBase"

     pcBase :: pcBase (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  extnames - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pcBase"

     pcBase :: pcBase (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : PropertyHandle(dbhandle,extnames,accopt)
{



}


