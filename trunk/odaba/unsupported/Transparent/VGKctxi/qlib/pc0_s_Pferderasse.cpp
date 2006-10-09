/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Pferderasse

\brief    


\date     $Date: 2006/07/07 17:25:54,42 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Pferderasse"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Pferderasse.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Pferderasse - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Pferderasse"

     pc0_s_Pferderasse :: pc0_s_Pferderasse (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Pferderasse"

     pc0_s_Pferderasse :: pc0_s_Pferderasse (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Pferderasse",accopt)
{



}


