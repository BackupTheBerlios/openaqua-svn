/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    RefAccess

\brief    


\date     $Date: 2006/07/12 19:15:56,14 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "RefAccess"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sLDBHandle.hpp>
#include  <iNetConversion.h>
#include  <sRefAccess.hpp>
#include  <seb_RootBase.hpp>
#include  <sexd.hpp>
#include  <sexdBuffer.hpp>
#include  <sisel.hpp>
#include  <sRefAccess.hpp>


/******************************************************************************/
/**
\brief  ChangeEXDSize - 



\return longlen - 

\param  exdarea - 
\param  longlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeEXDSize"

int32 RefAccess :: ChangeEXDSize (exd *exdarea, int32 longlen )
{

  return(exdarea->ChangeSize(longlen));

}

/******************************************************************************/
/**
\brief  CreateEBI - 



\return entnr - 

\param  mbnumber - MainBase number
\param  clnumb - 
\param  sbnumber - SubBase number
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEBI"

EB_Number RefAccess :: CreateEBI (int16 mbnumber, EB_Number clnumb, uint16 sbnumber, uint16 version_nr )
{

  return(ob_handle->CreateEntry(mbnumber,
            sbnumber == USHORTMAX ? struct_def->get_sb_number() : sbnumber,
            clnumb,version_nr));

}

/******************************************************************************/
/**
\brief  GetDBEntryLength - 



\return longlen - 

\param  ebsnum - 
\param  wslevel - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBEntryLength"

int32 RefAccess :: GetDBEntryLength (EB_Number ebsnum, uint8 wslevel, uint16 version_nr )
{
  acb       acbenty(ebsnum,0,version_nr);
  if ( wslevel != 255 )
  {
    acbenty.set_locate_exact(YES);
    acbenty.set_ws_level(wslevel);
  } 
  
  return(ob_handle->GetLength(&acbenty));

}

/******************************************************************************/
/**
\brief  GetDBUsedLength - 



\return longlen - 

\param  ebsnum - 
\param  wslevel - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBUsedLength"

int32 RefAccess :: GetDBUsedLength (EB_Number ebsnum, uint8 wslevel, uint16 version_nr )
{
  acb       acbenty(ebsnum,0,version_nr);
  if ( wslevel != 255 )
  {
    acbenty.set_locate_exact(YES);
    acbenty.set_ws_level(wslevel);
  } 
  
  return(ob_handle->GetUsedLength(&acbenty));

}

/******************************************************************************/
/**
\brief  GetEXD - 



\return exdptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  exdarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEXD"

exd *RefAccess :: GetEXD (exd *exdarea )
{
  exd       *exdptr = NULL;
  if ( exdarea->GetIEH()->get_iehtyp() != IDB_INS )
    exdptr = ref_buffer->Locate(exdarea->get_exdebsn(),exdarea->get_shadow_base(),exdarea->get_exdacb()->get_version_number());
  return(exdptr);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  entnr - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEXD"

exd *RefAccess :: GetEXD (EB_Number entnr, uint16 version_nr )
{

  return ( ref_buffer->Locate(entnr,AUTO,version_nr) );

}

/******************************************************************************/
/**
\brief  GetRefAccess - 



\return ref_acc - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefAccess"

RefAccess *RefAccess :: GetRefAccess ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  GetTempEBNr - 



\return ebi_number - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTempEBNr"

int64 RefAccess :: GetTempEBNr ( )
{
  int64        ebi_number;
  ILock(YES);
  ebi_number = BigToPIF(--temp_entnr,ob_handle->get_pif());
  IUnlock();
  return(ebi_number);
}

/******************************************************************************/
/**
\brief  IsNet - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNet"

logical RefAccess :: IsNet ( )
{

  return ( ob_handle->get_db_handle()->get_net_option() );

}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical RefAccess :: Lock (EB_Number ebsnum )
{
  acb       acbenty(ebsnum,0);
  return(ob_handle->Lock(&acbenty));

}

/******************************************************************************/
/**
\brief  ProvideEXD - 



\return extinst - 

\param  ebsnum - 
\param  clnumb - 
\param  longlen - 
\param  otyp - 
\param  bwrite_opt - 
\param  support_diff_list - 
\param  version_nr - Internal version number
\param  w_trans_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEXD"

exd *RefAccess :: ProvideEXD (EB_Number ebsnum, EB_Number clnumb, int32 longlen, char otyp, logical bwrite_opt, logical support_diff_list, uint16 version_nr, logical w_trans_opt )
{
  logical newentry = ebsnum.IsEmpty(pif);
  exd    *extinst = NULL;
BEGINSEQ
  if ( newentry )
    ebsnum = GetTempEBNr();
  
  if ( !(extinst = ref_buffer->Locate(ebsnum,clnumb,otyp,longlen,version_nr)) )
                                                      ERROR
  extinst->LockUntilReserveInstance();
  if ( w_trans_opt )
    extinst->stsstrans();
  extinst->get_exdacb()->set_locate_exact(support_diff_list);
    
  extinst->set_write_shadow(!ref_buffer->get_shadow_base() && !support_diff_list && ob_handle->HasWorkspace());
    
  extinst->set_write(bwrite_opt);
  if ( newentry || extinst->NewEntry() )
    extinst->SetLength(0);
RECOVER

ENDSEQ
  return(extinst);
}

/******************************************************************************/
/**
\brief  RefAccess - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  lobhandle - 
\param  strdefptr - 
\param  maxcount - 
\param  shadow_read - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefAccess"

     RefAccess :: RefAccess (LACObject *lobhandle, DBStructDef *strdefptr, int16 maxcount, logical shadow_read )
                     : StructAccess (strdefptr),
  ob_handle(lobhandle),
  ref_buffer(NULL),
  temp_entnr(0)
{

BEGINSEQ
  if ( !(ref_buffer = new exdBuffer(ob_handle,
                                    maxcount,UNDEF,strdefptr->smcbityp,
                                    strdefptr->get_schema_ver(),
                                    shadow_read,NO)) )
                                                     SDBERR(95)
  
  if ( lobhandle->IsPIF() )
    pif = YES;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefAccess"

     RefAccess :: RefAccess ( )
                     : StructAccess (NULL),
  ob_handle(NULL),
  ref_buffer(NULL),
  temp_entnr(0)
{



}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Termination code

\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical RefAccess :: Unlock (EB_Number ebsnum )
{
  acb       acbenty(ebsnum,0);
  return(ob_handle->Unlock(&acbenty));

}

/******************************************************************************/
/**
\brief  WriteEXD - 



\return ebsnum - 

\param  exdarea - 
\param  l_size - 
\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteEXD"

EB_Number RefAccess :: WriteEXD (exd *exdarea, int32 l_size, int16 mbnumber, uint16 sbnumber, int32 offset )
{
  EB_Number    entnr  = exdarea->get_exdebsn();
  EB_Number    oldent = entnr;
BEGINSEQ
  if ( oldent.IsEmpty(pif) )
  {
    if ( sbnumber == AUTO )
      sbnumber = struct_def->get_sb_number();

    if ( (entnr = CreateEBI(mbnumber,exdarea->get_exdcln(),sbnumber,
                            exdarea->get_exdacb()->get_version_number())).IsEmpty() )
                                                     ERROR
    ref_buffer->Setup(oldent,entnr);
    ob_handle->GetDBHandle()->GetLocalDBHandle()->GetRootBase(AUTO)->GetEBI(exdarea->get_exdacb());
    
    if ( exdarea->get_use_count() )
      ob_handle->ReserveInstance(exdarea->get_exdacb());
    offset = AUTO;
  }
  if ( exdarea->Write(l_size,offset) )               ERROR
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  ~RefAccess - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~RefAccess"

     RefAccess :: ~RefAccess ( )
{

  delete ref_buffer;
  ref_buffer = NULL;

}


