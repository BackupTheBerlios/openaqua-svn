/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_Stammdaten

\brief    


\date     $Date: 2006/06/28 15:04:35,60 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_Stammdaten"

#include  <pvgkctxi.h>
#include  <spc0_Stammdaten.hpp>


/******************************************************************************/
/**
\brief  CheckValidExistance - 


\return term - Abbruchbedingung

\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValidExistance"

logical pc0_Stammdaten :: CheckValidExistance (int32 id )
{

  return ( Get(Key((char *)&id)) ? YES : NO );

}

/******************************************************************************/
/**
\brief  pc0_Stammdaten - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_Stammdaten"

     pc0_Stammdaten :: pc0_Stammdaten (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_Stammdaten"

     pc0_Stammdaten :: pc0_Stammdaten (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : PropertyHandle(dbhandle,extnames,accopt)
{



}


