/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstancePool

\brief    


\date     $Date: 2006/03/12 19:17:37,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "InstancePool"

#include  <popa7.h>
#include  <sEBI.hpp>
#include  <sObjectEntry.hpp>
#include  <sObjectEntryList.hpp>
#include  <sacb.hpp>
#include  <seb_RootBase.hpp>
#include  <sieh.hpp>
#include  <sInstancePool.hpp>


/******************************************************************************/
/**
\brief  CreateInstance - 


\return iehptr -

\param  iehptr -
\param  oldieh -
\param  no_data - IEH has no data
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

ieh *InstancePool :: CreateInstance (ieh *iehptr, ieh *oldieh, logical no_data )
{
  logical                 term = NO;
  if ( oldieh )
  {
    if ( iehptr->get_iehlen() != oldieh->get_iehlen() )
    {
      used_size += (iehptr->get_iehlen() - oldieh->get_iehlen());
      msmcs((void **)&oldieh,iehptr->get_iehlen()+IEH);
    }
  }
  else
  {
    oldieh = (ieh *)msmgs(iehptr->get_iehlen()+IEH);
    used_size += (iehptr->get_iehlen() + IEH + sizeof(ObjectEntry));
  }

  if ( no_data )
  {
    *oldieh = *iehptr;
    memset(oldieh+1,0,iehptr->get_iehlen());
  }
  else
    iehptr->Copy(oldieh);

  if ( max_size <= used_size )
    object_entries->Reorganize();
  return(oldieh);
}

/******************************************************************************/
/**
\brief  InstancePool - 



\param  object_list -
\param  maxi_size -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstancePool"

                        InstancePool :: InstancePool (ObjectEntryList *object_list, uint32 maxi_size )
                     : max_size(maxi_size),
  used_size(0),
  root_base(object_list->get_root_base()),
  work_acb(NULL),
  max_inst_size(8096),
  object_entries(object_list)
{

BEGINSEQ
  if ( !(work_acb = acb::Create(max_inst_size)) )  SDBERR(95)

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  RemoveInstance - 


\return term - Termination code

\param  iehptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveInstance"

logical InstancePool :: RemoveInstance (ieh *iehptr )
{
  logical                 term = NO;
  msmfs((void **)&iehptr);
  return(term);
}

/******************************************************************************/
/**
\brief  StoreInstance - 


\return term - Termination code

\param  entnr -
\param  ebiptr -
\param  iehptr -
\param  cluster_number -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreInstance"

logical InstancePool :: StoreInstance (EB_Number entnr, EBI *ebiptr, ieh *iehptr, int32 cluster_number )
{
  logical                 term = NO;
BEGINSEQ
  if ( iehptr->get_iehlen() > max_inst_size )
  {
    delete work_acb;
    max_inst_size = iehptr->get_iehlen();
    if ( !(work_acb = acb::Create(max_inst_size+sizeof(acb))) ) 
                                                     SDBERR(95)
  }

  work_acb->set_ebsnum(entnr);
  work_acb->set_cluster_numb(cluster_number);
  *(EBI *)work_acb = *ebiptr;
  memcpy(&work_acb->get_acbieh(),iehptr,(int)iehptr->get_iehlen()+sizeof(ieh));
  work_acb->set_version(ebiptr->get_version());

  term = root_base->UpdateIntern(work_acb,iehptr->get_iehlen()+sizeof(ieh),0);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateInstance - 


\return term - Termination code

\param  oldieh -
\param  newieh -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateInstance"

logical InstancePool :: UpdateInstance (ieh *oldieh, char newieh )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ~InstancePool - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~InstancePool"

                        InstancePool :: ~InstancePool ( )
{

  msmfs((void **)&work_acb);


}


