/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    exdBBuffer

\brief    


\date     $Date: 2006/03/12 19:18:50,15 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "exdBBuffer"

#include  <popa7.h>
#include  <sBinArrayObjEntry.hpp>
#include  <sBinSArray.hpp>
#include  <sBinSArrayObjEntry.hpp>
#include  <sLACObject.hpp>
#include  <sStatistic.hpp>
#include  <sexd.hpp>
#include  <sexdBEntry.hpp>
#include  <sexdBBuffer.hpp>


/******************************************************************************/
/**
\brief  Clear - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical exdBBuffer :: Clear ( )
{
  exdBEntry    *b_entry;
  int32          indx = 0;
  while ( b_entry = (exdBEntry *)GetEntry(++indx) )
  {
    delete b_entry->get_inst_area();
    b_entry->set_inst_area(NULL);
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  Delete - 


\return exdarea -

\param  entnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

exd *exdBBuffer :: Delete (EB_Number entnum )
{
  exdBEntry   *buf_entry;
  exd         *exdptr = NULL;
  EB_Number    entnr = entnum.FromPIF(ob_handle->IsPIF());

  if ( buf_entry = (exdBEntry *)RemoveEntry(entnr.get_ebsnum()) )
  {
    exdptr = buf_entry->get_inst_area();
    buf_entry->set_inst_area(NULL);
  }
  return(exdptr);
}

/******************************************************************************/
/**
\brief  FreeObjEntry - 



\param  obj_entry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeObjEntry"

void exdBBuffer :: FreeObjEntry (BinSArrayObjEntry *obj_entry )
{

  BinArray::FreeObjEntry(obj_entry);
  ((exdBEntry *)obj_entry)->set_inst_area(NULL);

}

/******************************************************************************/
/**
\brief  GetExdEntry - 


\return exdarea -

\param  lindex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExdEntry"

exd *exdBBuffer :: GetExdEntry (int32 lindex )
{
  exdBEntry   *buf_entry;
  exd         *exdptr = NULL;
  if ( buf_entry = (exdBEntry *)GetEntry(lindex) )
    exdptr = buf_entry->get_inst_area();

  return(exdptr);
}

/******************************************************************************/
/**
\brief  InitObjEntry - 



\param  obj_entry -
\param  entry_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitObjEntry"

void exdBBuffer :: InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index )
{

  BinSArray::InitObjEntry(obj_entry,entry_index);
  ((exdBEntry *)obj_entry)->Init();

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

exd *exdBBuffer :: Locate (EB_Number entnum, EB_Number clnumb, char otyp, int32 instlen, uint16 version_nr )
{
  exd         *exdarea = NULL;
  exdBEntry   *buf_entry;
  EB_Number    ebsnum = entnum.FromPIF(ob_handle->IsPIF());
BEGINSEQ
//stats.Start();
  ILock();
  buf_entry = (exdBEntry *)ProvideEntry(ebsnum.get_ebsnum());
  
  if ( !instlen )
    instlen = inst_length;
  
  if ( !(exdarea = buf_entry->get_inst_area()) )
  {
    if ( !(exdarea = new exd(ob_handle,NULL,instlen,version_nr))) 
                                                      SDBERR(95)
    buf_entry->set_inst_area(exdarea);

    exdarea->SetIEH(0,UNDEF,otyp,UNDEF);
    
    exdarea->get_exdacb()->get_acbieh().set_iehtyp(otyp);
    exdarea->InitEXD(entnum,clnumb,NO,UNDEF,UNDEF);
    buf_entry->Reserve();
  }
  
  if ( exdarea->ChangeSize(instlen) != instlen )    ERROR
  exdarea = exdarea->VerifyVersion(version_nr);

RECOVER
  exdarea = NULL;
ENDSEQ
//stats.Stop();
  IUnlock();
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

exd *exdBBuffer :: Locate (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{
  exd         *exdarea = NULL;
  exdBEntry   *buf_entry;
  EB_Number    ebsnum = entnr.FromPIF(ob_handle->IsPIF());
BEGINSEQ
  if ( buf_entry = (exdBEntry *)ProvideEntry(ebsnum.get_ebsnum(),NO) )
    if ( exdarea = buf_entry->get_inst_area() )
      if ( version_nr != CUR_VERSION )
        exdarea = exdarea->LocateVersion(version_nr);
        
  if ( !exdarea )                                    ERROR
    
  if ( shadow_opt <= YES && exdarea->get_shadow_base() != shadow_opt )    
                                                     ERROR


RECOVER

ENDSEQ
  return(exdarea);
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

exd *exdBBuffer :: Replace (exd *exdarea )
{
  exd         *exdptr = NULL;
  logical      reserve;
  exdBEntry   *buf_entry;
  EB_Number    entnr(exdarea->get_exdebsn());
BEGINSEQ
  if ( !(buf_entry = (exdBEntry *)ProvideEntry(entnr.get_ebsnum(),NO)) )
                                                     ERROR
  if ( !(exdptr = buf_entry->get_inst_area()) )      ERROR
  
  reserve = ob_handle && !exdarea->get_use_count() && exdptr->get_use_count();
  if ( reserve )
    ob_handle->ReleaseInstance(exdptr->get_exdacb());
  buf_entry->set_inst_area(exdarea);
  if ( reserve )
    ob_handle->ReserveInstance(exdarea->get_exdacb());

RECOVER

ENDSEQ
  return(exdptr);
}

/******************************************************************************/
/**
\brief  Setup - 


\return term - Termination code

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical exdBBuffer :: Setup (EB_Number entnr )
{
  exd                    *exdarea;
  exdBEntry              *buf_entry;
  logical                 term = NO;
BEGINSEQ
  if ( !(exdarea = Locate(entnr,NO)) )               ERROR
  
  if ( !(buf_entry = (exdBEntry *)ProvideEntry(exdarea->get_exdebsn().get_ebsnum(),YES)) )
                                                     ERROR
  buf_entry->set_inst_area(exdarea);
  buf_entry->Reserve();
  Delete(entnr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  exdBBuffer - 



\param  lobhandle -
\param  maxcount -
\param  instlen -
\param  sid -
\param  version -
\param  auto_reorg -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "exdBBuffer"

                        exdBBuffer :: exdBBuffer (LACObject *lobhandle, int16 maxcount, int32 instlen, int16 sid, uint16 version, logical auto_reorg )
                     : BinArray (sizeof(exdBEntry),maxcount,12,auto_reorg),
  ob_handle(lobhandle),
  inst_length(instlen),
  struct_id(sid),
  schema_version(version)
{

BEGINSEQ
  if ( SOSERROR )                               SDBERR(95)
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

void exdBBuffer :: set_sid (int16 sid )
{

  struct_id = sid;

}

/******************************************************************************/
/**
\brief  ~exdBBuffer - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~exdBBuffer"

                        exdBBuffer :: ~exdBBuffer ( )
{

  Clear();

//  stats.Print("Locate",NO); // print without headline


}


