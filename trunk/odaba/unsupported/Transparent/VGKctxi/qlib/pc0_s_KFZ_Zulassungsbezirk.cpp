/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_KFZ_Zulassungsbezirk

\brief    


\date     $Date: 2006/07/03 16:09:15,03 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_s_KFZ_Zulassungsbezirk"

#include  <pvgkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_s_KFZ_Zulassungsbezirk.hpp>


/******************************************************************************/
/**
\brief  pc0_s_KFZ_Zulassungsbezirk - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_KFZ_Zulassungsbezirk"

     pc0_s_KFZ_Zulassungsbezirk :: pc0_s_KFZ_Zulassungsbezirk (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc0_s_KFZ_Zulassungsbezirk"

     pc0_s_KFZ_Zulassungsbezirk :: pc0_s_KFZ_Zulassungsbezirk (DatabaseHandle &dbhandle, PIACC accopt )
                     : pc0_Stammdaten(dbhandle,"s_KFZ_Zulassungsbezirk",accopt)
{



}


