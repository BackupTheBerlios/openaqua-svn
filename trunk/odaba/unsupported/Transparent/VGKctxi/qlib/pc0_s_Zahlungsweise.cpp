/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Zahlungsweise

\brief    


\date     $Date: 2006/06/28 22:41:24,68 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Zahlungsweise"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Zahlungsweise.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Zahlungsweise - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Zahlungsweise"

     pc0_s_Zahlungsweise :: pc0_s_Zahlungsweise (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Zahlungsweise"

     pc0_s_Zahlungsweise :: pc0_s_Zahlungsweise (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Zahlungsweise",accopt)
{



}


