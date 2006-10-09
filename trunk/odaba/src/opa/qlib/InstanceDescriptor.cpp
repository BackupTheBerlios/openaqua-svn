/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstanceDescriptor

\brief    


\date     $Date: 2006/03/12 19:17:37,60 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "InstanceDescriptor"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sInstanceDescriptor.hpp>
#include  <sacb.hpp>
#include  <seb_RootBase.hpp>
#include  <sieh.hpp>
#include  <sInstanceDescriptor.hpp>


/******************************************************************************/
/**
\brief  GetLength - Get Instance Length
        The  function return 0 if there is no instance allocated to the instance
        descriptor.

\return instlen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 InstanceDescriptor :: GetLength ( )
{

  return ( ext_inst ? ext_inst->get_iehlen() : 0 );

}

/******************************************************************************/
/**
\brief  GetOldInstance - 


\return inst_descriptor

\param  erootbase -
\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOldInstance"

InstanceDescriptor *InstanceDescriptor :: GetOldInstance (eb_RootBase *erootbase, acb *acbptr )
{
  InstanceDescriptor     *inst_descriptor = NULL;
  uint16                  version = acbptr->get_version_number();
  uint16                  cur_version = ebi.get_version();
BEGINSEQ
  if ( inst_descriptor = GetVersionInst(version) )   LEAVESEQ

  inst_descriptor = this;
  while ( cur_version > version && inst_descriptor )
  {
    acbptr->set_version(cur_version-1);
    acbptr->stsrusr3();
    if ( !erootbase->getEBI(acbptr) )                ERROR
    if ( acbptr->stscdel() )                         SDBERR(3)  // Version entry existiert nicht oder gelöscht
    cur_version = acbptr->get_version();
    prev_version = new InstanceDescriptor();
    prev_version->Initialize(acbptr);
    inst_descriptor = prev_version;
  }

RECOVER
  inst_descriptor = NULL;
ENDSEQ
  acbptr->set_version(version);
  return(inst_descriptor);
}

/******************************************************************************/
/**
\brief  GetVersionInst - 


\return inst_descriptor

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersionInst"

InstanceDescriptor *InstanceDescriptor :: GetVersionInst (uint16 version_nr )
{
  InstanceDescriptor     *inst_descriptor = this;
  while (inst_descriptor && inst_descriptor->get_ebi().get_version() > version_nr )
    inst_descriptor = inst_descriptor->get_prev_version();
  return(inst_descriptor);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  acbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void InstanceDescriptor :: Initialize (acb *acbptr )
{

  ebi = *(EBI *)acbptr;
  ebi.stssusr3();
  cluster_number = acbptr->get_cluster_number();

}

/******************************************************************************/
/**
\brief  InstanceDescriptor - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceDescriptor"

                        InstanceDescriptor :: InstanceDescriptor ( )
                     : ebi(),
  ext_inst(NULL),
  prev_version(NULL),
  cluster_number()
{



}

/******************************************************************************/
/**
\brief  Locate - 


\return area -

\param  acbptr -
\param  entlen -
\param  pif -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *InstanceDescriptor :: Locate (acb *acbptr, int32 entlen, logical pif )
{
  void         *area = &acbptr->get_acbieh();
  int32          len;
BEGINSEQ
  if ( acbptr->NewEntry() )                          LEAVESEQ
  if ( !ext_inst )                                   ERROR
    
  len = ext_inst->get_iehlen()+sizeof(ieh);
  entlen = entlen == AUTO ? len : MIN(entlen,len);
  memcpy(&acbptr->get_acbieh(),ext_inst,entlen);
  if ( pif )
    acbptr->SetPIF();
  

RECOVER
  area = NULL;
ENDSEQ
  return(area);
}

/******************************************************************************/
/**
\brief  SetArea - 


\return iehptr -

\param  iehptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetArea"

ieh *InstanceDescriptor :: SetArea (ieh *iehptr )
{

  return(ext_inst = iehptr);

}

/******************************************************************************/
/**
\brief  ~InstanceDescriptor - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~InstanceDescriptor"

                        InstanceDescriptor :: ~InstanceDescriptor ( )
{

  delete prev_version;
  prev_version = NULL;

// release ext_inst

}


