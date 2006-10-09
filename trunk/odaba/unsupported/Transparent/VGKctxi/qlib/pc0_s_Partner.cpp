/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Partner

\brief    


\date     $Date: 2006/07/03 23:56:48,20 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Partner"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Partner.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Partner - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Partner"

     pc0_s_Partner :: pc0_s_Partner (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Partner"

     pc0_s_Partner :: pc0_s_Partner (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Werbepartner",accopt)
{



}


