/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_Action

\brief    


\date     $Date: 2006/07/21 14:26:02,26 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_Action"

#include  <pVGKbase.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ActionStatus.hpp>
#include  <spc_Actor.hpp>
#include  <spc_Action.hpp>


/******************************************************************************/
/**
\brief  CalculateAblauf - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateAblauf"

logical pc_Action :: CalculateAblauf ( )
{
  dbdt        datum;
  logical     term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  datum = GPH("versicherungs_beginn")->GetDate();
  datum.PlusYear(GPH("fuenfjahresvertrag")->IsTrue() ? 5 : 1);
  
  *GPH("ablauf") = datum;
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CalculateBetreffAusgangsNotiz - 



\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffAusgangsNotiz"

char *pc_Action :: CalculateBetreffAusgangsNotiz (NString &nstring )
{
  PropertyHandle    *versicherungsnehmer = GPH("versicherungsnehmer");
  nstring  = "";
  nstring.Append("Transparent ");
  GetIdentString(nstring,YES,NO);
  nstring.Append(", ");
  
  versicherungsnehmer->Get(FIRST_INSTANCE);
  pc_Actor(versicherungsnehmer).GetIdentString(nstring,YES,NO);

  return(nstring);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  nstring - 
\param  kenner - 
\param  id - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffAusgangsNotiz"

char *pc_Action :: CalculateBetreffAusgangsNotiz (NString &nstring, char kenner, int32 id, logical clear_opt )
{
  char *   string = NULL;
  if ( clear_opt )
    nstring = "";  
    
  ExecutePropertyAction("GetSparte",NULL);
  nstring += GetActionResult();
  nstring += ' ';
  nstring += kenner;
  nstring += '-';
  nstring += id;

  return(string);
}

/******************************************************************************/
/**
\brief  CalculateBetreffPoliceNotiz - 



\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffPoliceNotiz"

char *pc_Action :: CalculateBetreffPoliceNotiz (NString &nstring )
{

  GetIdentString(nstring,NO,NO);
  nstring += ", - Police hinterlegt";

  return(nstring);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  nstring - 
\param  kenner - 
\param  id - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffPoliceNotiz"

char *pc_Action :: CalculateBetreffPoliceNotiz (NString &nstring, char kenner, int32 id, logical clear_opt )
{
  char *   string = NULL;
  if ( clear_opt )
    nstring = "";  
    
  ExecutePropertyAction("GetSparte",NULL);
  nstring += GetActionResult();
  nstring += ' ';
  nstring += kenner;
  nstring += '-';
  nstring += id;

  return(string);
}

/******************************************************************************/
/**
\brief  CalculateBetreffUebermittlungsNotiz - 



\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffUebermittlungsNotiz"

char *pc_Action :: CalculateBetreffUebermittlungsNotiz (NString &nstring )
{

  nstring  = "";
  nstring.Append("Online Abschluss ");
  GetIdentString(nstring,YES,NO);
  nstring += ", - bitte policieren";
  return(nstring);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  nstring - 
\param  kenner - 
\param  id - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateBetreffUebermittlungsNotiz"

char *pc_Action :: CalculateBetreffUebermittlungsNotiz (NString &nstring, char kenner, int32 id, logical clear_opt )
{
  char *   string = NULL;
  if ( clear_opt )
    nstring = "";  
    
  ExecutePropertyAction("GetSparte",NULL);
  nstring += GetActionResult();
  nstring += ' ';
  nstring += kenner;
  nstring += '-';
  nstring += id;

  return(string);
}

/******************************************************************************/
/**
\brief  CheckForPolice - 



\return errnum - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckForPolice"

int32 pc_Action :: CheckForPolice ( )
{
  DEFLOCALERR
  pc_ActionStatus   status(GPH("status"));
  logical           term        = NO;
BEGINSEQ
  if ( NoWrite() )                                  LOCALERR(24)

  if ( status.CheckStatus(2) )                      LOCALERR(14)
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  CheckForPolicierung - 



\return errnum - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckForPolicierung"

int32 pc_Action :: CheckForPolicierung ( )
{
  DEFLOCALERR
  pc_ActionStatus   status(GPH("status"));
  int32             import_status = GPH("import_status")->GetInt();
  logical           term        = NO;
BEGINSEQ
  if ( NoWrite() )                                  LOCALERR(24)

  if ( status.CheckStatus(1) )                      LOCALERR(14)

  if ( import_status != IMPORT_erfolgreich_beendet &&
       import_status != IMPORT_nein       )         LOCALERR(14)
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  GetIdentString - 



\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  nstring - 
\param  key_opt - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentString"

char *pc_Action :: GetIdentString (NString &nstring, logical key_opt, logical clear_opt )
{

BEGINSEQ
  if ( clear_opt )
    nstring = "";  
    
  if ( key_opt )
  {
    nstring += IDENT_Action;  
    nstring += ':';  
  }

  if ( !IsPositioned() )                            ERROR
  
  nstring += GPH("sparte")->GetString();
  nstring += ' ';
  nstring += GPH("kennung")->GetString();
  nstring += '-';
  nstring += GPH("extern_id")->GetString();

RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  nstring - 
\param  kenner - 
\param  id - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentString"

char *pc_Action :: GetIdentString (NString &nstring, char kenner, int32 id, logical clear_opt )
{
  char *   string = NULL;
  if ( clear_opt )
    nstring = "";  
    
  ExecutePropertyAction("GetSparte",NULL);
  nstring += GetActionResult();
  nstring += ' ';
  nstring += kenner;
  nstring += '-';
  nstring += id;

  return(string);
}

/******************************************************************************/
/**
\brief  SetImportStatus - 



\return term - Abbruchbedingung

\param  import_status - 
\param  reset_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetImportStatus"

logical pc_Action :: SetImportStatus (ImportStatus import_status, logical reset_opt )
{
  PropertyHandle   *status = GPH("import_status");
  logical           term   = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR
  
  if ( !reset_opt )
    if ( status->GetInt() > import_status )         LEAVESEQ
    
  *status = import_status;
  Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPoliciert - 



\return errnum - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPoliciert"

int32 pc_Action :: SetPoliciert ( )
{

  return ( SetStatus(3) );

}

/******************************************************************************/
/**
\brief  SetStatus - 



\return errnum - 

\param  status - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatus"

int32 pc_Action :: SetStatus (int32 status )
{
  DEFLOCALERR
  char        keyarea[40];
  Key         idkey(keyarea);
BEGINSEQ
  if ( NoWrite() )                                   LOCALERR(24)
  if ( GetParentProperty()->IsA("ActionStatus") )
  {
    pc_Action   actions(GetDBHandle(),"Action",PI_Update); 
                                                     SDBCERR
    ExtractKey(idkey);
    Delete();
    if ( !actions.Get(idkey) )                       LOCALERR(99)
    actions.SetStatus(status);
  }
  else
  {
    pc_ActionStatus(GPH("status")).SetStatus(status);
    Save();
  }
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  SetZurPolicierung - 



\return errnum - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetZurPolicierung"

int32 pc_Action :: SetZurPolicierung ( )
{
  DEFLOCALERR

BEGINSEQ
  if ( LOCALERROR = SetStatus(2) )                  ERROR
  
  RemoveFromSpecialExtent("ActionNeu");

RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  pc_Action - 



-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_Action"

     pc_Action :: pc_Action (PropertyHandle *prophdl )
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
#define    MOD_ID  "pc_Action"

     pc_Action :: pc_Action (DatabaseHandle &dbhandle, char *extnames, PIACC accopt )
                     : pcBase_SharedData(dbhandle,extnames,accopt)
{



}


