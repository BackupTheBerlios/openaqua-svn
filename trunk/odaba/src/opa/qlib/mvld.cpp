/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvld

\brief    


\date     $Date: 2006/03/12 19:18:59,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvld"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sRefAccess.hpp>
#include  <sbinti.hpp>
#include  <sdisel.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <smvld.hpp>


/******************************************************************************/
/**
\brief  AddExt - 


\return lindx0 -

\param  ebsnum -
\param  skey -
\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExt"

int32 mvld :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  logical   extlock = stsclck();

BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( !exd_area )
    if ( GetTable() )                                ERROR
  if ( CheckVersion() )                              ERROR

  if ( !mvlchk(AUTO) )                               ERROR
  
  memset(ext_area,0,mvlsrt->srtlen());
  if ( mvlsrt->srtkln() )
  {
    if ( mvlsrt->srtssr(skey) )
    {
      SetKeyErrorVariables(skey);
      SDBERR(64)
    }
    refsakcb->get_key_def()->SetKey(ext_area,skey);
    lindx0 = mvlsrt->srtkad(ext_area) - 1;
    memcpy(mvlpenty,skey,mvlsrt->srtkln());
  }
  else
    if ( mvlsrt->srtiad(lindx0+1,ext_area) )         ERROR
    
  refcuri = lindx0;
  Modify();
RECOVER
  lindx0 = AUTO;
ENDSEQ
  if ( Unlock(extlock) )
    lindx0 = AUTO;
  return(lindx0);

}

/******************************************************************************/
/**
\brief  AddID - 


\return term - Termination code

\param  intiptr -
\param  entnr -
\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical mvld :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  logical      extlock = stsclck();
  logical      term = NO;
BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( CheckVersion() )                              ERROR
  if ( ref::AddID(intiptr,entnr,lindx0) )            ERROR

  WriteIndexEntry(refcuri,((binti *)intiptr)->GetExtInst());
RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  CheckVersion

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckVersion"

logical mvld :: CheckVersion ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( cur_struct != struct_access->get_struct_def() )
                                                     SDBERR(383)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ConvertInstVersion

\return term - Termination code

\param  instptr -
\param  oldinst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertInstVersion"

logical mvld :: ConvertInstVersion (void *instptr, void *oldinst )
{
  DBStructDef    *struct_def = struct_access->get_struct_def();
  logical         update = NO;
  logical         term = NO;
BEGINSEQ
  if ( cur_struct != struct_def )
  {
#ifdef __sun__
               // versionierung auf UNIX muss bezueglich der ausrichtungsschwierigkeiten 
  SDBERR(999)  // externer Instanzen noch ueberarbeitet werden
               // DBFieldDef::CopyExtInst(_dtd)
#endif
    if ( struct_def->ConvInstVersion(ob_handle,oldinst,cur_struct->get_schema_ver(),&update) )
                                                     ERROR
    memcpy(instptr,struct_def->get_ext_area(),struct_def->get_ext_length());
  } 

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteID - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  intiptr -
\param  oldinst -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical mvld :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return( !CheckVersion() 
          ? ref::DeleteID(intiptr,oldinst,entnr)
          : YES );

}

/******************************************************************************/
/**
\brief i1


\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical mvld :: DeleteID (EB_Number entnr )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  EBSNumToIndex - 


\return lindx0 -

\param  ebsnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EBSNumToIndex"

int32 mvld :: EBSNumToIndex (EB_Number ebsnum )
{

//  return(ebsnum.get_ebsnum()-1); 
  return(ebsnum.get_ebsnum()-refrex->get_ebsnum()); // das ist nicht immer eindeutig und sollte in der 64-bit variante anders aussehen ...

}

/******************************************************************************/
/**
\brief  FillIndexEntry - 


\return term - Termination code

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillIndexEntry"

logical mvld :: FillIndexEntry (int32 lindx0 )
{
  logical   term = NO;
  kcb      *kcbptr;
BEGINSEQ
  if ( lindx0 < 0 )                                      ERROR
  
  if ( refcuri != lindx0 )
  {   
    if ( Refresh() )                                     ERROR
    if ( lindx0 >= mvlsrt->srtcnt() )                    ERROR

    if ( kcbptr = refsakcb->get_key_def() )
      kcbptr->GetKey((char *)mvlsrt->srtigt(lindx0+1),(char *)mvlpenty);
    refcuri = lindx0;
  }

RECOVER
  refcuri = AUTO;
  term    = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum -

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number mvld :: GetID (int32 lindx0 )
{
  EB_Number      ebsnum;
BEGINSEQ
  if ( lindx0 == AUTO )
    lindx0 = refcuri;
    
  if ( refcuri != lindx0 )                      
  {
    if ( Refresh() )                                       ERROR
    if ( FillIndexEntry(lindx0) )                          ERROR
  }  
  
  ebsnum = IndexToEBSNum(refcuri);

RECOVER

ENDSEQ
  return(ebsnum);
}

/******************************************************************************/
/**
\brief  GetIndex - 


\return lindx0 -
-------------------------------------------------------------------------------
\brief REFNGT_K


\param  skey -
\param  ebsnum -
\param  exact -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 mvld :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  int32        indx0;
BEGINSEQ
  if ( !mvlsrt->srtkln() )                           ERROR
    
  if ( Refresh() )                                   ERROR
  indx0 = mvlsrt->srtbsr(skey)-1;
//  indx0 = mvlsrt->srtbsr(mvlsrt->srtkps() != 1 ? skey : (char *)&ebsnum)-1;
  if ( exact && mvlsrt->stscerr() )                  ERROR
  if ( FillIndexEntry(indx0) )                       ERROR
RECOVER
  refcuri = AUTO;
ENDSEQ
  mvlsrt->stsrerr();
  return(refcuri);  

}

/******************************************************************************/
/**
\brief i1


\param  ebsnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 mvld :: GetIndex (EB_Number ebsnum )
{

  return(AUTO);

}

/******************************************************************************/
/**
\brief  GetKey - 


\return skey -

\param  lindx0 -
\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *mvld :: GetKey (int32 lindx0, char *keyptr )
{

BEGINSEQ
  if ( !mvlsrt->srtkln() )                           ERROR
  if ( !keyptr )                                     SDBERR(99)
  
  if ( lindx0 == AUTO )
  {
    if ( refcuri == AUTO )                           ERROR
  }
  else   
    if ( FillIndexEntry(lindx0) )                    ERROR

  memcpy(keyptr,mvlpenty,mvlsrt->srtkln());

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  IndexToEBSNum - 


\return ebsnum -

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IndexToEBSNum"

EB_Number mvld :: IndexToEBSNum (int32 lindx0 )
{

//  return(lindx0+1); 
  return(refrex->get_ebsnum()+lindx0); // das ist nicht immer eindeutig und sollte in der 64-bit variante anders aussehen ...

}

/******************************************************************************/
/**
\brief  ReadIndexEntry - 


\return term - Termination code

\param  lindx0 -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadIndexEntry"

logical mvld :: ReadIndexEntry (int32 lindx0, void *instptr )
{
  void           *curinst;
  logical         term = NO;
BEGINSEQ
  if ( lindx0 == AUTO )
    lindx0 = refcuri;
  if ( lindx0 == AUTO )                              ERROR
  curinst = mvlsrt->srtigt(lindx0+1);

  if ( struct_access->get_struct_def() == cur_struct )
    memcpy(instptr,curinst,mvlsrt->srtlen());
  else
    if ( ConvertInstVersion(instptr,curinst) )       ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical mvld :: Refresh ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !mod_count || refrex->IsEmpty(ob_handle->get_pif()) || 
       !exd_area || *refrex != exd_area->get_exdebsn()     ||
       ( // exd_area->get_use_count() == 1 &&           22.6.00
       refcuri == AUTO) )                            // 29.1.00
  {
    mvlrefi = YES;  // sonst wird nicht gelesen!  29.1.00
    term = mvlp::Refresh();
  }
  else if ( mvlchck() )                               SDBERR(99)
  SetCurrentStructDef();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCurrentStructDef

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurrentStructDef"

logical mvld :: SetCurrentStructDef ( )
{
  DBStructDef    *struct_def = struct_access->get_struct_def();
  logical         term = NO;
BEGINSEQ
  cur_struct = struct_def;
  if ( struct_def->get_schema_ver() > exd_area->get_schemaver() )
    if ( !(cur_struct = struct_def->GetStrDefVersion(ob_handle->GetDictionary(),exd_area->get_schemaver())) )
                                                     SDBERR(99)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateID - 


\return term - Termination code

\param  intiptr -
\param  oldinst -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical mvld :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  logical                 term = NO;
BEGINSEQ
  if ( refcuri == AUTO )                             ERROR
    
//if ( ref::UpdateID(intiptr,oldinst,refcuri+1) )    ERROR
  if ( ref::UpdateID(intiptr,oldinst,entnr) )        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WriteIndexEntry - 


\return term - Termination code

\param  lindx0 -
\param  instptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteIndexEntry"

logical mvld :: WriteIndexEntry (int32 lindx0, void *instptr )
{
  logical   extlock = stsclck();
  logical   term    = NO;
BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( lindx0 == AUTO )
    lindx0 = refcuri;
  if ( lindx0 == AUTO )                              ERROR
  if ( CheckVersion() )                              ERROR
  
  memcpy(mvlsrt->srtigt(lindx0+1),instptr,mvlsrt->srtlen());

  refmod = YES;
RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  mvld - 



\param  lobhandle -
\param  extref -
\param  clnumb -
\param  akcbptr -
\param  maxl -
\param  globind -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvld"

                        mvld :: mvld (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 maxl, logical globind )
                     : mvlp(lobhandle,extref,clnumb,IDB_MVLD,0,maxl,
     akcbptr,globind),
  ext_area(NULL)
{

  ext_area = new char[mvlsrt->srtlen()];
  memset(ext_area,0,mvlsrt->srtlen());
  cur_struct = struct_access->get_struct_def();

}

/******************************************************************************/
/**
\brief  ~mvld - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvld"

                        mvld :: ~mvld ( )
{

  delete ext_area;


}


