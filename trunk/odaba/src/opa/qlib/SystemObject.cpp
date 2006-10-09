/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    SystemObject



\date     $Date: 2006/05/28 16:27:56,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SystemObject"

#include  <popa7.h>
#include  <idbd.h>
#ifndef   P_SDB_Extend_HPP
#define   P_SDB_Extend_HPP
#include  <sPI.hpp>
class       SDB_Extend;
PI_dcl     (SDB_Extend)
#endif
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDBHeader.hpp>
#include  <sLDBHandle.hpp>
#include  <sSDB_Extend.hpp>
#include  <sSDB_ObjectExt.hpp>
#include  <sSDB_Structure.hpp>
#include  <sexd.hpp>
#include  <sSystemObject.hpp>


/******************************************************************************/
/**
\brief  Version6

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Version6"

logical SystemObject :: Version6 ( )
{
  LACObject      *lobhandle = GetLocalACObject();
  LDBHandle      *ldbhandle = db_handle->GetLocalDBHandle();
  DBObjectHandle  obhandle(this);
  int32            indx0     = 0;
  logical         term      = NO;
BEGINSEQ
  if ( !ldbhandle )                                  SDBERR(99)
    
  if ( lobhandle->GetDBVersion() >= 6 )              LEAVESEQ
    
  if ( lobhandle->get_object_instance()->Read() )    SDBERR(99)
  
  
  ((SDB_ObjectExt *)lobhandle->get_object_instance()->GetInstance())->ConvertTo6(lobhandle->IsPIF());
  if ( lobhandle->get_access_mode() > PI_Read )    
    if ( ldbhandle->Write(lobhandle->get_object_instance()) )
                                                     SDBERR(99)

// version 6 wird nur für neue Datenbanken gesetzt
  access_mode = PI_Read;                             SDBSET(998)
// jetzt kann nur noch gelesen werden

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  VersionCheck

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionCheck"

logical SystemObject :: VersionCheck ( )
{
  LDBHandle *ldbhandle = db_handle->GetLocalDBHandle();
  logical    locked    = NO;
  logical    term      = NO;
BEGINSEQ
// diese Verfahrensweise geht nur solange, 
// wie eine Datenbank praktisch nur ein Objekt verwaltet.  

  if ( !ldbhandle )                                  SDBERR(99)
  if ( ldbhandle->get_db_header()->get_version() == CUR_DBVERSION )    
                                                     LEAVESEQ
  if ( ldbhandle->LockHeader() )                     ERROR
  locked = YES;
  if ( ldbhandle->get_db_header()->get_version() > CUR_DBVERSION )    
                                                     SDBERR(176)
  if ( Version6() )                                  ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( locked )
  {
    if ( access_mode == PI_Write )
      ldbhandle->WriteHeader();
    ldbhandle->UnlockHeader(); 
  }
  return(term);
}

/******************************************************************************/
/**
\brief  VersionChecka

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionChecka"

logical SystemObject :: VersionChecka ( )
{
  LDBHandle *ldbhandle = db_handle->GetLocalDBHandle();
  logical    locked    = NO;
  logical    term      = NO;
BEGINSEQ
// diese Verfahrensweise geht nur solange, 
// wie eine Datenbank praktisch nur ein Objekt verwaltet.  
  
  if ( !ldbhandle )                                  SDBERR(99)
  if ( ldbhandle->get_db_header()->get_version() == CUR_DBVERSION )    
                                                     LEAVESEQ
  if ( ldbhandle->LockHeader() )                     ERROR
  locked = YES;
  if ( ldbhandle->get_db_header()->get_version() > CUR_DBVERSION )    
                                                     SDBERR(176)
//  if ( Version5() )                                  ERROR

    

RECOVER
  term = YES;
ENDSEQ
  if ( locked )
  {
    if ( access_mode == PI_Write )
      ldbhandle->WriteHeader();
    ldbhandle->UnlockHeader(); 
  }
  return(term);
}


