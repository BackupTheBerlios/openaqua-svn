/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_Portal

\brief    


\date     $Date: 2006/06/28 15:05:31,50 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_Portal"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_Portal.hpp>


/******************************************************************************/
/**
\brief  pc0_s_Portal - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Portal"

     pc0_s_Portal :: pc0_s_Portal (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_Portal"

     pc0_s_Portal :: pc0_s_Portal (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_Portal",accopt)
{



}


