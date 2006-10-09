/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_s_Gesellschaft

\brief    


\date     $Date: 2006/07/18 12:16:32,93 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_s_Gesellschaft"

#include  <pVGKbase.h>
#include  <spc_s_Gesellschaft.hpp>


/******************************************************************************/
/**
\brief  CalculateBetreffAusgangsNotiz - 



\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffAusgangsNotiz"

char *pc_s_Gesellschaft :: CalculateBetreffAusgangsNotiz (NString &nstring )
{

  nstring  = "";
  nstring.Append("Transparent ");
  GetIdentString(nstring,YES,NO);
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetIdentString - 



\return string - 

\param  nstring - 
\param  key_opt - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentString"

char *pc_s_Gesellschaft :: GetIdentString (NString &nstring, logical key_opt, logical clear_opt )
{

BEGINSEQ
  if ( clear_opt )
    nstring = "";  
    
  if ( key_opt )
  {
    nstring += IDENT_Versicherung;  
    nstring += ':';  
  }

  if ( !IsPositioned() )                            ERROR
  
  nstring += GPH("extern_id")->GetString();

RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  pc_s_Gesellschaft - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_s_Gesellschaft"

     pc_s_Gesellschaft :: pc_s_Gesellschaft (PropertyHandle *prophdl )
                     : pcBase_NotizHaving(prophdl)
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
#define    MOD_ID  "pc_s_Gesellschaft"

     pc_s_Gesellschaft :: pc_s_Gesellschaft (DatabaseHandle &dbhandle, PIACC accopt )
                     : pcBase_NotizHaving(dbhandle,"s_Gesellschaft",accopt)
{



}


