/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    acb

\brief    


\date     $Date: 2006/06/18 12:56:50,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "acb"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sCSA_Handle.hpp>
#include  <sCSHandleList.hpp>
#include  <sEBI.hpp>
#include  <sPCSHandle.hpp>
#include  <sacb.hpp>
#include  <seb_SubBase.hpp>
#include  <sacb.hpp>

int32 acb_count = 0;

/******************************************************************************/
/**
\brief  CheckVersion - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckVersion"

logical acb :: CheckVersion ( )
{

  return ( version_number != CUR_VERSION && 
           version_number < version       ? YES : NO );

 

}

/******************************************************************************/
/**
\brief  CopyTo - 



\param  srceacb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyTo"

void acb :: CopyTo (acb *srceacb )
{

  memcpy(&acbieh,&srceacb->get_acbieh(),(int)srceacb->get_acbieh().get_iehlen()+sizeof(ieh));
  version      = srceacb->get_version();
  locate_exact = srceacb->get_locate_exact();
  ws_level     = srceacb->get_ws_level();
  ws_number    = srceacb->get_ws_number();


}

/******************************************************************************/
/**
\brief  Create - 


\return acbptr - 

\param  longlen - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

acb *__cdecl acb :: Create (int32 longlen, uint16 version_nr )
{
  acb       *acbptr = NULL;
BEGINSEQ
  if ( !(acbptr = (acb *)msmgs(longlen)) )          SDBERR(95)
  
  acbptr->set_version(version_nr);
//  acbptr->active_handles.Initialize();
RECOVER

ENDSEQ
acb_count++;
  return(acbptr);
}

/******************************************************************************/
/**
\brief  GenerateEvent - 


\return term - Termination code

\param  ev_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical acb :: GenerateEvent (EntryEvent *ev_ptr )
{

  return ( active_handles.GenerateEvent(ev_ptr) );

}

/******************************************************************************/
/**
\brief  ILock - 


\return term - Termination code

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ILock"

logical acb :: ILock (logical wait )
{

  return(active_handles.ILock(wait));

}

/******************************************************************************/
/**
\brief  IUnlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IUnlock"

logical acb :: IUnlock ( )
{

  return(active_handles.IUnlock());

}

/******************************************************************************/
/**
\brief  IsInstance - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInstance"

logical acb :: IsInstance ( )
{

  return ( acbieh.get_iehtyp() == IDB_INS ? YES : NO );

}

/******************************************************************************/
/**
\brief  RegActHandles - 



\param  pcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegActHandles"

void acb :: RegActHandles (PCSHandle *pcs_handle )
{

  if ( pcs_handle )
    active_handles.Add(pcs_handle);

}

/******************************************************************************/
/**
\brief  Remove - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void acb :: Remove ( )
{
  void *ptr = (void *)this;
  if ( ptr )
  {
    active_handles.Close();
    msmfs(&ptr);
    acb_count--;
  }

}

/******************************************************************************/
/**
\brief  ResetACB - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetACB"

void acb :: ResetACB ( )
{
  int64       null = 0;
  mb_number      = 0;
  mb_ebsnum      = 0;
  cluster_number = 0;
  if ( !locate_exact )
  {
    ws_level = 0;
    ws_number = 0;
  }
  StoreBigInt(&ebi_position,null);


}

/******************************************************************************/
/**
\brief  SetIEH - 



\param  instlen - 
\param  sid - 
\param  otyp - 
\param  version - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIEH"

void acb :: SetIEH (int32 instlen, int16 sid, char otyp, uint16 version )
{

  acbieh.set_iehlen(instlen);
  acbieh.set_iehsid(sid);
  acbieh.set_iehtyp(otyp);
  acbieh.set_iehver(version);

}

/******************************************************************************/
/**
\brief  SetLength - 



\param  instlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLength"

void acb :: SetLength (int32 instlen )
{

  acbieh.set_iehlen(instlen);


}

/******************************************************************************/
/**
\brief  Uninitialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Uninitialize"

void acb :: Uninitialize ( )
{

  if ( this )
    active_handles.Close();


}

/******************************************************************************/
/**
\brief  UnregActHandles - 



\param  pcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnregActHandles"

void acb :: UnregActHandles (PCSHandle *pcs_handle )
{

  if ( pcs_handle )
    active_handles.Remove(pcs_handle);

}

/******************************************************************************/
/**
\brief  acb - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  entnr - 
\param  clnumb - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "acb"

     acb :: acb (EB_Number entnr, EB_Number clnumb, uint16 version_nr )
                     : EBI (),
  ebsnum(entnr),
  mb_number(UNDEF),
  mb_ebsnum(),
  cluster_number(clnumb),
  version_number(version_nr),
  ws_level(0),
  locate_exact(NO),
  ws_number(0),
  is_pif(NO),
  reserved(NO),
  acbieh()
{
  int64       null = 0;
  StoreBigInt(&ebi_position,null);

acb_count++;
}

/******************************************************************************/
/**
\brief  i02 - 


\param  entnr - 
\param  clnumb - 
\param  wslevel - 
\param  wsnumber - 
\param  loc_exact - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "acb"

     acb :: acb (EB_Number entnr, EB_Number clnumb, uint8 wslevel, int32 wsnumber, logical loc_exact, uint16 version_nr )
                     : EBI (),
  ebsnum(entnr),
  mb_number(UNDEF),
  mb_ebsnum(),
  cluster_number(clnumb),
  version_number(version_nr),
  ws_level(wslevel),
  locate_exact(loc_exact),
  ws_number(wsnumber),
  reserved(NO),
  is_pif(NO),
  acbieh()

{
  int64       null = 0;
  StoreBigInt(&ebi_position,null);
acb_count++;
}

/******************************************************************************/
/**
\brief  i1 - 


\param  acbref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "acb"

     acb :: acb (acb &acbref )
                     : EBI (),
  ebsnum(acbref.get_ebsnum()),
  mb_number(acbref.get_mb_number()),
  mb_ebsnum(acbref.get_mb_ebsnum()),
  cluster_number(acbref.get_cluster_number()),
  version_number(acbref.get_version_number()),
  ws_level(acbref.get_ws_level()),
  locate_exact(acbref.get_locate_exact()),
  ws_number(acbref.get_ws_number()),
  is_pif(acbref.IsPIF()),
  reserved(NO),
  acbieh(acbref.get_acbieh())
{
  int64       null = 0;
  StoreBigInt(&ebi_position,null);

acb_count++;
}

/******************************************************************************/
/**
\brief  get_ebi_position - 


\return ebipos64 - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_ebi_position"

int64 acb :: get_ebi_position ( )
{
  int64      ebipos64;
  LoadBigInt(ebipos64,&ebi_position);
  return(ebipos64);
}

/******************************************************************************/
/**
\brief  operator= - 


\return acbref - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  acb_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

acb &acb :: operator= (const acb &acb_refc )
{

  *(EBI *)this   = *(EBI *)&acb_refc;
  ebsnum         = acb_refc.ebsnum;
  ebi_position   = acb_refc.ebi_position;
  mb_ebsnum      = acb_refc.mb_ebsnum;
  cluster_number = acb_refc.cluster_number;
  version_number = acb_refc.version_number;
  mb_number      = acb_refc.mb_number;
  ws_level       = acb_refc.ws_level;
  locate_exact   = acb_refc.locate_exact;
  ws_number      = acb_refc.ws_number;
  
  if ( active_handles.get_conn_handle() &&  acb_refc.active_handles.get_conn_handle() )
  {
    active_handles.Clear();
    active_handles.Copy(acb_refc.active_handles);
  }
  acbieh         = acb_refc.acbieh;
// das dürfen wir nicht, da sonst acb nicht mehr abgemeldet wird (im cache)
//  reserved       = NO;

  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

acb &acb :: operator= (acb *acbptr )
{

  *(EBI *)this   = *(EBI *)acbptr;
  ebsnum         = acbptr->get_ebsnum();
  ebi_position   = acbptr->get_ebi_position();
  mb_ebsnum      = acbptr->get_mb_ebsnum();
  cluster_number = acbptr->get_cluster_number();
  version_number = acbptr->get_version_number();
  mb_number      = acbptr->get_mb_number();
  ws_level       = acbptr->get_ws_level();
  locate_exact   = acbptr->get_locate_exact();
  ws_number      = acbptr->get_ws_number();

//  acbieh         = acbptr->get_acbieh();
  return(*this);
}

/******************************************************************************/
/**
\brief  set_ebi_position - 



\param  ebipos64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ebi_position"

void acb :: set_ebi_position (int64 ebipos64 )
{

  StoreBigInt(&ebi_position,ebipos64);

}

/******************************************************************************/
/**
\brief  set_ebsnum - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ebsnum"

void acb :: set_ebsnum (EB_Number entnr )
{
  int64       null = 0;
  ebsnum       = entnr;
  mb_ebsnum    = 0;
  StoreBigInt(&ebi_position,null);
  *(EBI *)this = EBI();

}

/******************************************************************************/
/**
\brief  set_locate_exact - 



\param  loc_exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_locate_exact"

void acb :: set_locate_exact (logical loc_exact )
{

  locate_exact = loc_exact;

}

/******************************************************************************/
/**
\brief  set_reserved - 


\return reserved - 

\param  is_reserved - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_reserved"

uint8 acb :: set_reserved (logical is_reserved )
{

BEGINSEQ
  if ( !reserved && !is_reserved )                  SDBERR(99)
  
  if ( is_reserved )
    reserved++;
  else 
    reserved--;

RECOVER

ENDSEQ
  return(reserved);
}

/******************************************************************************/
/**
\brief  set_version - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_version"

void acb :: set_version (uint16 version_nr )
{

  version_number = version_nr;


}

/******************************************************************************/
/**
\brief  set_ws_level - 



\param  wslevel - 
\param  wsnumber_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ws_level"

void acb :: set_ws_level (uint8 wslevel, int32 wsnumber_w )
{

BEGINSEQ
  if ( wslevel == ws_level && (wsnumber_w == AUTO || wsnumber_w == ws_number) )
                                                     LEAVESEQ
  set_ebi_position(0);
  ws_level  = wslevel;
  
  if ( wsnumber_w != AUTO )
    ws_number = wsnumber_w;

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~acb - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~acb"

     acb :: ~acb ( )
{


acb_count--;
}


