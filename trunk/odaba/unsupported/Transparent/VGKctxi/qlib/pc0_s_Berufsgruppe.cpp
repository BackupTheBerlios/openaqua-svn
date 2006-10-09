/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Berufsgruppe

\brief    


\date     $Date: 2006/06/29 13:21:10,57 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Berufsgruppe"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Berufsgruppe.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Berufsgruppe - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Berufsgruppe"

     pc0_s_Berufsgruppe :: pc0_s_Berufsgruppe (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Berufsgruppe"

     pc0_s_Berufsgruppe :: pc0_s_Berufsgruppe (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Berufsgruppe",accopt)
{



}


