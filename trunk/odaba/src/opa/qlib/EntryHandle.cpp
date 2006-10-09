/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    EntryHandle

\brief    


\date     $Date: 2006/03/29 19:18:43,67 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EntryHandle"

#include  <popa7.h>
#include  <sDBStructDef.hpp>
#include  <sLACObject.hpp>
#include  <sLNode.hpp>
#include  <sPCSHandle.hpp>
#include  <sStructAccess.hpp>
#include  <sexd.hpp>
#include  <sEntryHandle.hpp>


/******************************************************************************/
/**
\brief  CreateInstance - 


\return exdptr - 

\param  instlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

exd *EntryHandle :: CreateInstance (int32 instlen )
{

BEGINSEQ
  if ( exd_area )                                    LEAVESEQ
    
  if ( !(exd_area = struct_access->CreateInstance(mb_number,cluster_number,
                                                  instlen,GetVersion())) )
                                                     ERROR
  exd_area->set_write(NO);
  exd_area->ReserveInstance(active_handle);
  

RECOVER

ENDSEQ
  return(exd_area);
}

/******************************************************************************/
/**
\brief  EntryHandle - 


-------------------------------------------------------------------------------
\brief  i0


\param  lobhandle - 
\param  mbnumber - MainBase number
\param  clnumb - 
\param  pcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryHandle"

                        EntryHandle :: EntryHandle (LACObject *lobhandle, int16 mbnumber, EB_Number clnumb, PCSHandle *pcs_handle )
                     :   ob_handle(lobhandle),
  struct_access(NULL),
  exd_area(NULL),
  mb_number(mbnumber),
  cluster_number(clnumb),
  mod_count(0),
  version(CUR_VERSION),
  active_handle(pcs_handle)
{



}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryHandle"

                        EntryHandle :: EntryHandle ( )
                     :   ob_handle(NULL),
  struct_access(NULL),
  exd_area(NULL),
  mb_number(0),
  cluster_number(),
  mod_count(0),
  version(CUR_VERSION),
  active_handle(NULL)
{



}

/******************************************************************************/
/**
\brief  GetExtInstID - 


\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInstID"

EB_Number EntryHandle :: GetExtInstID ( )
{
  EB_Number               entnr = 0;
  if ( exd_area )
    entnr = exd_area->get_exdebsn();
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetInstance - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  instptr - 
\param  entnr - 
\param  instlen - 
\param  p_update - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

logical EntryHandle :: GetInstance (void *instptr, EB_Number entnr, int32 instlen, logical *p_update )
{
  uint16    version_nr;
  logical   reserve = YES;
  logical   term    = NO;

BEGINSEQ
  if ( exd_area )
  {
    if ( exd_area->get_exdebsn() != entnr )
      ResetEntry();
    else
      reserve = NO;
  }
  if ( !(exd_area = struct_access->GetInstance(entnr,
                            cluster_number,instptr,exd_area,instlen,GetVersion(),p_update)) )
                                                     ERROR
  exd_area->set_ob_handle(ob_handle);
  exd_area->set_write(NO);
  mod_count = exd_area->get_mod_count();
  
  if ( reserve )
    exd_area->ReserveInstance(active_handle);
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  i1


\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

logical EntryHandle :: GetInstance (char *extinst )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  GetVersion - 


\return version_nr - Internal version number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 EntryHandle :: GetVersion ( )
{

  return( version == CUR_VERSION 
          ? ob_handle->get_version()
          : version);

}

/******************************************************************************/
/**
\brief  HasWorkspace - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasWorkspace"

logical EntryHandle :: HasWorkspace ( )
{

  return(ob_handle->HasWorkspace());

}

/******************************************************************************/
/**
\brief  PutInstance - 


\return term - Termination code

\param  instptr - 
\param  instlen - 
\param  overwrite - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutInstance"

logical EntryHandle :: PutInstance (void *instptr, int32 instlen, logical overwrite, logical refresh_opt )
{
  DBStructDef  *struct_def = struct_access->get_struct_def();
  int32          len        = 0;
  logical       term       = NO;
BEGINSEQ
  exd_area->set_ob_handle(ob_handle);

  if ( overwrite != YES && 
       ( mod_count != exd_area->get_mod_count() || 
         (refresh_opt && (refresh_opt = exd_area->IsModified())) ) )
                                                     SDBERR(67)
  
  if ( struct_access->PutInstance(instptr,exd_area,instlen,refresh_opt) )
                                                     ERROR
  mod_count = exd_area->get_mod_count();
  cluster_number = exd_area->get_exdcln();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetEntry - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetEntry"

logical EntryHandle :: ResetEntry ( )
{

  if ( exd_area )
  {
    exd_area->ReleaseInstance(active_handle);
    exd_area  = NULL;
  }
  mod_count = 0;

  return(NO);
}

/******************************************************************************/
/**
\brief  SetInstance - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

logical EntryHandle :: SetInstance (exd *exdptr )
{
  logical   term    = NO;

BEGINSEQ
  if ( exd_area == exdptr )                          LEAVESEQ
  if ( exd_area )
    ResetEntry();
  
  exd_area = exdptr;
  mod_count = exd_area->get_mod_count();
  exd_area->ReserveInstance(active_handle);
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  i1


\param  extinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

logical EntryHandle :: SetInstance (char *extinst )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  SetShadowRead - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetShadowRead"

void EntryHandle :: SetShadowRead ( )
{

  exd_area->set_shadow_base(YES);

}

/******************************************************************************/
/**
\brief  SetShadowWrite - 



\param  shadow_write - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetShadowWrite"

void EntryHandle :: SetShadowWrite (logical shadow_write )
{

  exd_area->set_write_shadow(shadow_write);

}

/******************************************************************************/
/**
\brief  SetVersion - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void EntryHandle :: SetVersion (uint16 version_nr )
{

BEGINSEQ
  if ( version == version_nr )                       LEAVESEQ
    
  mod_count = 0;
  version = version_nr;
  if ( exd_area )
    exd_area = exd_area->VerifyVersion(version_nr != CUR_VERSION 
                                       ? version_nr 
                                       : ob_handle->get_version());

ENDSEQ

}

/******************************************************************************/
/**
\brief  set_cluster_numb - 



\param  clnumb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_cluster_numb"

void EntryHandle :: set_cluster_numb (EB_Number clnumb )
{

  cluster_number = clnumb;

}

/******************************************************************************/
/**
\brief  set_exd_area - 



\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_exd_area"

void EntryHandle :: set_exd_area (exd *exdptr )
{
 

  exd_area = exdptr;

 

}

/******************************************************************************/
/**
\brief  set_mb_number - 



\param  mbnumber - MainBase number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_mb_number"

void EntryHandle :: set_mb_number (int16 mbnumber )
{

  mb_number = mbnumber;

}

/******************************************************************************/
/**
\brief  set_mod_count - 



\param  modcount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_mod_count"

void EntryHandle :: set_mod_count (int16 modcount )
{

  mod_count = modcount;

}

/******************************************************************************/
/**
\brief  set_struct_acc - 



\param  structacc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_struct_acc"

void EntryHandle :: set_struct_acc (StructAccess *structacc )
{

  struct_access = structacc;

}

/******************************************************************************/
/**
\brief  ~EntryHandle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EntryHandle"

                        EntryHandle :: ~EntryHandle ( )
{



}


