/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pcBase_NotizHaving

\brief    


\date     $Date: 2006/07/17 18:46:11,68 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pcBase_NotizHaving"

#include  <pVGKbase.h>
#include  <spc_Notiz.hpp>
#include  <spcBase_NotizHaving.hpp>


/******************************************************************************/
/**
\brief  CreateNotiz - 



\return prophdl - 

\param  typ_string - 
\param  betreff_text - 
\param  von_an - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNotiz"

PropertyHandle *pcBase_NotizHaving :: CreateNotiz (char *typ_string, char *betreff_text, char *von_an )
{
  PropertyHandle  *notizen = GPH("notizen");
BEGINSEQ
  if ( pc_Notiz(notizen).CreateNotiz(typ_string,betreff_text,NULL,von_an) )
                                                    ERROR
  Save();                                           SDBCERR

RECOVER
  notizen = NULL;
ENDSEQ
  return(notizen);
}

/******************************************************************************/
/**
\brief  CreateWiedervorlageNotiz - 



\return prophdl - 

\param  betreff_text - 
\param  von_an - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateWiedervorlageNotiz"

PropertyHandle *pcBase_NotizHaving :: CreateWiedervorlageNotiz (char *betreff_text, char *von_an )
{
  PropertyHandle  *notizen = GPH("notizen");
BEGINSEQ
  if ( pc_Notiz(notizen).CreateWiedervorlageNotiz(betreff_text,von_an) )
                                                    ERROR
  Save();                                           SDBCERR

RECOVER
  notizen = NULL;
ENDSEQ
  return(notizen);
}

/******************************************************************************/
/**
\brief  ResetWV - 



\return prophdl - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWV"

PropertyHandle *pcBase_NotizHaving :: ResetWV ( )
{
  PropertyHandle  *notizen = GPH("notizen");
BEGINSEQ
  if ( pc_Notiz(notizen).ResetWV() )                ERROR
  Save();                                           SDBCERR

RECOVER
  notizen = NULL;
ENDSEQ
  return(notizen);
}

/******************************************************************************/
/**
\brief  pcBase_NotizHaving - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pcBase_NotizHaving"

     pcBase_NotizHaving :: pcBase_NotizHaving (PropertyHandle *prophdl )
                     : pcBase(prophdl)
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
#define    MOD_ID  "pcBase_NotizHaving"

     pcBase_NotizHaving :: pcBase_NotizHaving (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : pcBase(dbhandle,extnames,accopt)
{



}


