/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Hunderasse

\brief    


\date     $Date: 2006/07/07 18:08:27,95 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Hunderasse"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Hunderasse.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Hunderasse - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Hunderasse"

     pc0_s_Hunderasse :: pc0_s_Hunderasse (PropertyHandle *prophdl )
                     : pc0_Stammdaten(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Hunderasse"

     pc0_s_Hunderasse :: pc0_s_Hunderasse (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Hunderasse",accopt)
{



}


