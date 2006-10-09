/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Staat

\brief    


\date     $Date: 2006/06/29 13:04:42,40 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Staat"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Staat.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Staat - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Staat"

     pc0_s_Staat :: pc0_s_Staat (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Staat"

     pc0_s_Staat :: pc0_s_Staat (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Staat",accopt)
{



}


