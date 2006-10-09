/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    pc0Base_local

\brief    


\date     $Date: 2006/07/24 22:36:50,01 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0Base_local"

#include  <pvgkctxi.h>
#include  <sTP_ImportGlobals.hpp>
#include  <spc0Base_local.hpp>


/******************************************************************************/
/**
\brief  Add - 



\return term - Abbruchbedingung

\param  key - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical pc0Base_local :: Add (Key key, TP_ImportGlobals *imp_globals )
{

  PropertyHandle::Add(key);
  return ( Message(GetPropertyPath(),
                   "konnte nicht angelegt werden",imp_globals,YES) );


}

/******************************************************************************/
/**
\brief  Import - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Import"

logical pc0Base_local :: Import (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ImportAlle - 



\return term - Abbruchbedingung

\param  source_ph - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ImportAlle"

logical pc0Base_local :: ImportAlle (PropertyHandle *source_ph, TP_ImportGlobals *imp_globals )
{
  int32       indx0 = 0;
  logical     term  = NO;
  while ( source_ph->Get(indx0++) )
    if ( Import(source_ph,imp_globals) )
      term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  Message - 



\return term - Abbruchbedingung

\param  typ_string - 
\param  text - 
\param  imp_globals - 
\param  check_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Message"

logical pc0Base_local :: Message (char *typ_string, char *text, TP_ImportGlobals *imp_globals, logical check_opt )
{
  NString     nstring;
  char       *str  = NULL;
  logical     term = NO;
BEGINSEQ
  if ( check_opt && !SDBERROR )                     LEAVESEQ

  nstring  = "'";
  nstring += (char*)(typ_string ? typ_string : "");
  nstring += "' ";
  nstring += text;
  imp_globals->Message(nstring);

  ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Provide - 



\return term - Abbruchbedingung
-------------------------------------------------------------------------------
\brief  i00 - 



\param  indx0 - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

logical pc0Base_local :: Provide (int32 indx0, TP_ImportGlobals *imp_globals )
{

  PropertyHandle::Provide(indx0);
  return ( Message(GetPropertyPath(),
                   "konnte nicht angelegt werden",imp_globals,YES) );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  typ_string - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide"

logical pc0Base_local :: Provide (char *typ_string, TP_ImportGlobals *imp_globals )
{
  PropertyHandle   typ_key(typ_string);
  PropertyHandle::Provide(typ_key);
  return ( Message(typ_string,
                   "konnte nicht angelegt werden",imp_globals,YES) );


}

/******************************************************************************/
/**
\brief  Save - 



\return term - Abbruchbedingung

\param  typ_string - 
\param  imp_globals - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical pc0Base_local :: Save (char *typ_string, TP_ImportGlobals *imp_globals )
{

  PropertyHandle::Save();
  return ( Message(typ_string ? typ_string : GetPropertyPath(),
                   "konnte nicht gespeichert werden",imp_globals,YES) );

}

/******************************************************************************/
/**
\brief  pc0Base_local - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0Base_local"

     pc0Base_local :: pc0Base_local (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


