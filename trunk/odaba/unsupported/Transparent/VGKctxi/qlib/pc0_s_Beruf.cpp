/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Beruf

\brief    


\date     $Date: 2006/06/29 13:22:40,01 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Beruf"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Beruf.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Beruf - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Beruf"

     pc0_s_Beruf :: pc0_s_Beruf (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Beruf"

     pc0_s_Beruf :: pc0_s_Beruf (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Beruf",accopt)
{



}


