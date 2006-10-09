/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Gesellschaft

\brief    


\date     $Date: 2006/06/28 15:05:08,56 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Gesellschaft"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Gesellschaft.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Gesellschaft - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Gesellschaft"

     pc0_s_Gesellschaft :: pc0_s_Gesellschaft (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Gesellschaft"

     pc0_s_Gesellschaft :: pc0_s_Gesellschaft (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Gesellschaft",accopt)
{



}


