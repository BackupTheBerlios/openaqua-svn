/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Tarif

\brief    


\date     $Date: 2006/06/28 17:59:49,39 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Tarif"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Tarif.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Tarif - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Tarif"

     pc0_s_Tarif :: pc0_s_Tarif (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Tarif"

     pc0_s_Tarif :: pc0_s_Tarif (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Tarif",accopt)
{



}


