/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_Actor

\brief    


\date     $Date: 2006/07/17 19:02:23,45 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_Actor"

#include  <pVGKbase.h>
#include  <sPropertyHandle.hpp>
#include  <spc_Actor.hpp>


/******************************************************************************/
/**
\brief  CalculateBetreffAusgangsNotiz - 



\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffAusgangsNotiz"

char *pc_Actor :: CalculateBetreffAusgangsNotiz (NString &nstring )
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

char *pc_Actor :: GetIdentString (NString &nstring, logical key_opt, logical clear_opt )
{

BEGINSEQ
  if ( clear_opt )
    nstring = "";  
    
  if ( key_opt )
  {
    nstring += IDENT_Actor;  
    nstring += ':';  
  }

  if ( !IsPositioned() )                            ERROR
  
  nstring += GPH("kennung")->GetString();
  nstring += '-';
  nstring += GPH("__AUTOIDENT")->GetString();

RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  pc_Actor - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_Actor"

     pc_Actor :: pc_Actor (PropertyHandle *prophdl )
                     : pcBase_SharedData(prophdl)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  dbhandle - 
\param  extnames - 
\param  accopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_Actor"

     pc_Actor :: pc_Actor (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : pcBase_SharedData(dbhandle,extnames,accopt)
{



}


