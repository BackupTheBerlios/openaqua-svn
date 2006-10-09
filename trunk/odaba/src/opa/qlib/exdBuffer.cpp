/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdBuffer

\brief    


\date     $Date: 2006/03/12 19:18:50,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "exdBuffer"

#include  <popa7.h>
#include  <sBTIterator.hpp>
#include  <sBinTree.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <sexd.hpp>
#include  <sexdBuffer.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  entnr -
\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical exdBuffer :: Add (EB_Number entnr, exd *exdarea )
{
  logical                 term = NO;
BEGINSEQ
  exd_tree->Lock(YES);
  
  exdarea->set_exd_ebsnum(entnr);
  if ( exd_tree->CreateEntry(exdarea) )              ERROR
  ins_count++;
RECOVER
  delete exdarea;
  term = YES;

ENDSEQ
  exd_tree->Unlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Clear - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical exdBuffer :: Clear ( )
{
  exd    *exdarea;
  exd_tree->Lock(YES);
  
  while ( exdarea = (exd *)GetTail() )
  {
    Delete(exdarea);
    delete exdarea;
  }
  while ( exdarea = free_exds.RemoveTail() )
    delete exdarea;
  exd_tree->Unlock();
  return(NO);
}

/******************************************************************************/
/**
\brief  Delete

\return term - Termination code

\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical exdBuffer :: Delete (exd *exdarea )
{
  logical         term = NO;
  term = exd_tree->DeleteEntry(exdarea);
  return(term);
}

/******************************************************************************/
/**
\brief  Locate - 


\return buffer -
-------------------------------------------------------------------------------
\brief i0


\param  entnum -
\param  clnumb -
\param  otyp -
\param  instlen -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *exdBuffer :: Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr )
{
  exd         *exdarea = NULL;
  logical      reinit = NO;
  int32         wsl;
  int32         index;
BEGINSEQ
  exd_tree->Lock();
  loc_count++;
  if ( !instlen )
    instlen = inst_length;
  
  if ( !(exdarea = (exd *)Get((char *)&entnum,YES)) )
  {
    if ( !(exdarea = free_exds.RemoveTail()) )
      if ( !(exdarea = new exd(ob_handle,this,instlen,version_nr))) 
                                                     SDBERR(95)
    if ( Add(entnum,exdarea) )                       ERROR

    exdarea->SetIEH(0,struct_id,otyp,schema_version);
    reinit = YES;
  }
  
  if ( exdarea->get_exdacb()->get_ws_level() > ob_handle->GetWorkspaceLevel() )
    reinit = YES;
  if ( reinit )
  {
    exdarea->get_exdacb()->get_acbieh().set_iehtyp(otyp);
    exdarea->InitEXD(entnum,clnumb,locate_exact,shadow_base,write_shadow);
    exdarea->ReleasePIF();
    exdarea->ResetPIF();
  }
  if ( exdarea->ChangeSize(instlen) != instlen )    ERROR
  exdarea = exdarea->VerifyVersion(version_nr);
RECOVER
  exdarea = NULL;
ENDSEQ
  exd_tree->Unlock();
  return(exdarea);
}

/******************************************************************************/
/**
\brief i1


\param  entnr -
\param  shadow_opt -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

exd *exdBuffer :: Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{
  exd         *exdarea = NULL;
  int32         index;
BEGINSEQ
  if ( !(exdarea = (exd *)Get((char *)&entnr,YES)) ) ERROR    
    
  if ( shadow_opt <= YES && exdarea->get_shadow_base() != shadow_opt )    
                                                     ERROR
    
  if ( version_nr != CUR_VERSION )
    exdarea = exdarea->LocateVersion(version_nr);


RECOVER
  exdarea = NULL;
ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  Optimize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Optimize"

void exdBuffer :: Optimize ( )
{
  int32              tree_count = GetCount();
  exd               *exdarea;
  if ( tree_count < 5 )
    tree_count = 5;
    
  if ( tree_count<<2 < free_exds.GetCount() )
    while ( tree_count < free_exds.GetCount() )
    {
      exdarea = free_exds.RemoveHead();
      delete exdarea;
    }


}

/******************************************************************************/
/**
\brief  Release - 



\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void exdBuffer :: Release (exd *exdarea )
{

  Delete(exdarea);
  free_exds.AddTail(exdarea);

  Optimize();

}

/******************************************************************************/
/**
\brief  Replace - 


\return exdptr -

\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replace"

exd *exdBuffer :: Replace (exd *exdarea )
{
  exd         *exdptr = NULL;
  EB_Number    entnr(exdarea->get_exdebsn());
  int32         index;
BEGINSEQ
  exd_tree->Lock(YES);
  
  if ( exd_tree->DeleteEntry((char *)&entnr) )       ERROR
  if ( exd_tree->CreateEntry(exdarea) )              SDBERR(99)

RECOVER

ENDSEQ
  exd_tree->Unlock();
  return(exdptr);
}

/******************************************************************************/
/**
\brief  Setup - 


\return term - Termination code

\param  oldent -
\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical exdBuffer :: Setup (EB_Number oldent, EB_Number entnr )
{
  exd         *exdarea;
  logical      term = NO;
BEGINSEQ
  exd_tree->Lock(YES);
  
  if ( !(exdarea = (exd *)Get((char *)&oldent,YES)) )ERROR
  
  if ( oldent == entnr )
  {
    exdarea->set_exdebsn(entnr);      // für neue buffer entries
    LEAVESEQ
  }
  
  if ( !oldent.IsEmpty() )
    exd_tree->DeleteEntry(exdarea);
  exdarea->set_exdebsn(entnr);
  if ( exd_tree->CreateEntry(exdarea) )              ERROR

RECOVER
  term = YES;
ENDSEQ
  exd_tree->Unlock();
  return(term);
}

/******************************************************************************/
/**
\brief  exdBuffer - 



\param  lobhandle -
\param  maxcount -
\param  instlen -
\param  sid -
\param  version -
\param  shadow_read -
\param  shadow_write -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exdBuffer"

                        exdBuffer :: exdBuffer (LACObject *lobhandle, int16 maxcount, int32 instlen, int16 sid, uint16 version, logical shadow_read, logical shadow_write )
                     : BTIterator(NULL),
  ob_handle(lobhandle),
  inst_length(instlen),
  struct_id(sid),
  schema_version(version),
  loc_count(0),
  ins_count(0),
  del_count(0),
  empty_count(0),
  del_proz(10),
  shadow_base(shadow_read),
  write_shadow(shadow_write),
  locate_exact(UNDEF),
  exd_tree(NULL),
  free_exds(512)
{

BEGINSEQ
//  if ( SOSERROR )                               SDBERR(95)

  exd_tree = new BinTree(sizeof(exd),offsetof(exd,exd_ebsnum),sizeof(EB_Number),'I',256);
  SetTree(exd_tree);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  set_sid - 



\param  sid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_sid"

void exdBuffer :: set_sid (int16 sid )
{

  struct_id = sid;

}

/******************************************************************************/
/**
\brief  ~exdBuffer - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~exdBuffer"

                        exdBuffer :: ~exdBuffer ( )
{

  Clear();

  SetTree(NULL);
  delete exd_tree;
  exd_tree = NULL;

}


