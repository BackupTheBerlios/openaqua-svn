/******************************** Class Source Code *****************************************************/
/**
\class pc0_s_Bank

\brief 

\date $Date: 2006/06/28 20:17:57,79 $
\dbsource q:\transparent\transparent.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#define    OBJ_ID  "pc0_s_Bank"

#include  <pvgkctxi.h>
#include  <spc0_s_Bank.hpp>


/******************************************************************************/
/**
\brief  CheckValidExistance - 


\return term - Abbruchbedingung

\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckValidExistance"

logical pc0_s_Bank :: CheckValidExistance (char *string )
{
  PropertyHandle  idkey(string);
  return ( Get(idkey) ? YES : NO );

}

/******************************************************************************/
/**
\brief  pc0_s_Bank - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_s_Bank"

     pc0_s_Bank :: pc0_s_Bank (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
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
#define    MOD_ID  "pc0_s_Bank"

     pc0_s_Bank :: pc0_s_Bank (DatabaseHandle &dbhandle, PIACC accopt )
                     : PropertyHandle(dbhandle,"s_Bank",accopt)
{



}


