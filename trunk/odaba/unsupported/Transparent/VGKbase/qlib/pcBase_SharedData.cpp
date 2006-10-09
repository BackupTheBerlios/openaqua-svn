/******************************** Class Source Code *****************************************************/
/**
\class pcBase_SharedData

\brief 

\date $Date: 2006/07/12 19:55:12,98 $
\dbsource q:\transparent\transparent.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#define    OBJ_ID  "pcBase_SharedData"

#include  <pVGKbase.h>
#include  <spcBase_SharedData.hpp>


/******************************************************************************/
/**
\brief  CalculateIdentKey - 



\return term - Abbruchbedingung

\param  keyarea - 
\param  size - 
\param  kenner - 
\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateIdentKey"

logical __cdecl pcBase_SharedData :: CalculateIdentKey (char *keyarea, int32 size, char kenner, int32 id )
{
  logical     term = NO;
BEGINSEQ
  memset(keyarea,0,size);
  if ( size < 5 )                                   ERROR

  memcpy(keyarea,&id,4);
  keyarea[4] = kenner;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSharedData - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSharedData"

logical pcBase_SharedData :: CreateSharedData ( )
{
  logical     term = NO;
BEGINSEQ
  Add(GetInitInstance());                                SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateID - 



\return term - Abbruchbedingung

\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateID"

logical pcBase_SharedData :: LocateID (char *string )
{
  char        kenner  = ' ';
  int32       id      = 0;
  char        ik_area[40];
  logical     term    = NO;
BEGINSEQ
  if ( !string || !*string )                        ERROR

  if ( *string < 'A' || *string > 'Z' )             ERROR
  kenner = *string;
  string++;
  if ( !*string )                                   ERROR

  if ( *string == '-' )
  {
    string++;
    if ( !*string )                                 ERROR
  }

  if ( (id = atol(string)) <= 0 )                   ERROR

  if ( CalculateIdentKey(ik_area,sizeof(ik_area),kenner,id) )
                                                    ERROR
  if ( !Get(Key(ik_area)) )                         ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pcBase_SharedData - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pcBase_SharedData"

     pcBase_SharedData :: pcBase_SharedData (PropertyHandle *prophdl )
                     : pcBase_NotizHaving(prophdl)
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
#define    MOD_ID  "pcBase_SharedData"

     pcBase_SharedData :: pcBase_SharedData (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : pcBase_NotizHaving(dbhandle,extnames,accopt)
{



}


