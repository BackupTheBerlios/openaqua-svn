/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstanceCache

\brief    


\date     $Date: 2006/03/12 19:17:37,18 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "InstanceCache"

#include  <popa7.h>
#ifndef   GSRT_ICEntry_HPP
#define   GSRT_ICEntry_HPP
#include  <sICEntry.hpp>
#include  <sGSRT.h>
#endif
#ifndef   DLL_inti_HPP
#define   DLL_inti_HPP
#include  <sinti.hpp>
#include  <sDLL.h>
#endif
#include  <sICEntry.hpp>
#include  <sbnode.hpp>
#include  <sinti.hpp>
#include  <sInstanceCache.hpp>


/******************************************************************************/
/**
\brief  AddEntry - 


\return iceptr -

\param  intiptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEntry"

ICEntry *InstanceCache :: AddEntry (inti *intiptr )
{
  int32                    indx;
  ICEntry                *iceptr = NULL;

BEGINSEQ
// stats.Stop();
  iceptr = (ICEntry *)msmgs(entry_len);

  if ( !(intiptr = node_ref->CreateInti(NULL,node_ref->get_nodefield()->GetDBStruct(),NULL,NO)) )
                                                     ERROR
  inti_array->AddTail(intiptr);
  intiptr->CopyBufferInstance(node_ref->get_nodeinst()); 
  
  if ( node_ref->stscmod() || node_ref->stscsav() )
    intiptr->stssmod();
    
  iceptr->Initialize(node_ref,intiptr);
  iceptr->SetLastUse(use_count);
  use_count++;
  indx = ordered_list->AddEntry(iceptr);
  
  if ( size <= ordered_list->GetCount() )
  {
    Flush(YES);
    node_ref->Get(iceptr->get_key());
    indx = ordered_list->srtssr(iceptr->get_key());
  }

  msmfs((void **)&iceptr);
  iceptr = ordered_list->GetEntry(indx);

RECOVER
  iceptr = NULL;
ENDSEQ
// stats.Stop();
  return(iceptr);
}

/******************************************************************************/
/**
\brief  ChangeOrder - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeOrder"

logical InstanceCache :: ChangeOrder ( )
{

  return( Resize(size) );

}

/******************************************************************************/
/**
\brief  Find - 


\return iceptr -

\param  entnr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

ICEntry *InstanceCache :: Find (EB_Number entnr )
{
  int32                    count = ordered_list->GetCount();
  ICEntry                *iceptr = NULL;
BEGINSEQ
  while ( count )
    if ( iceptr = ordered_list->GetEntry(count--) )  
      if ( iceptr->get_entry_number() == entnr )     LEAVESEQ

  ERROR
RECOVER
  iceptr = NULL;
ENDSEQ
  return(iceptr);
}

/******************************************************************************/
/**
\brief  Flush - 


\return term - Termination code

\param  remove -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Flush"

logical InstanceCache :: Flush (logical remove )
{
  int32                    count = ordered_list->GetCount();
  ICEntry                *iceptr;
  logical                 rem;
  int32                    use_cnt = use_count;
  logical                 term = NO;
// stats.Stop();
  while ( count )
  {
    if ( iceptr = ordered_list->GetEntry(count--) )  
    {
      rem = remove && iceptr->get_last_use() <= use_cnt-size+1;
      if ( iceptr->get_inti_ref()->IsModified() )
      {
//        node_ref->get_nodeinst()->CopyBufferInstance(iceptr->get_inti_ref());    
        node_ref->Switch(AUTO);
        node_ref->Get(iceptr->get_key());
        node_ref->SetMod();
        node_ref->Save(NO,NO,NO);
        iceptr->get_inti_ref()->CopyBufferInstance(node_ref->get_nodeinst());    
      }
      if ( rem )
        RemoveEntry(iceptr);
    }
  }

// stats.Stop();
  return(term);
}

/******************************************************************************/
/**
\brief  InstanceCache - 



\param  bnodeptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InstanceCache"

                        InstanceCache :: InstanceCache (bnode *bnodeptr )
                     : size(0),
  inti_array(NULL),
  node_ref(bnodeptr),
  stats(),
  ordered_list(NULL),
  use_count(0),
  mod_count(0),
  mod_max(0),
  entry_len(0)

{

  inti_array = new DLL(inti)();

}

/******************************************************************************/
/**
\brief  Locate - 


\return instptr -

\param  skey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

void *InstanceCache :: Locate (char *skey )
{
  ICEntry                *iceptr;
  void                   *instptr = NULL;
// stats.Start();
  if ( iceptr = ordered_list->GetEntry(skey) )
  {
    SetInstance(iceptr);
    instptr = node_ref->get_nodeinst()->get_iselarea();
  }

// stats.Stop();
  return(instptr);
}

/******************************************************************************/
/**
\brief  RemoveEntry - 


\return term - Termination code

\param  iceptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEntry"

logical InstanceCache :: RemoveEntry (ICEntry *iceptr )
{
  inti                   *intiptr;
  logical                 term = NO;
  if ( iceptr && (intiptr = iceptr->get_inti_ref()) )
    if ( inti_array->Find(intiptr) )
    {
      delete intiptr;
      inti_array->RemoveAt();
    }
  ordered_list->DeleteEntry(get_ordered_list()->srtssr(iceptr->get_key()));
  return(term);
}

/******************************************************************************/
/**
\brief  Resize - 


\return term - Termination code

\param  bufnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Resize"

logical InstanceCache :: Resize (int16 bufnum )
{
  int                     klen;
  ICEntry                *iceptr;
  inti                   *intiptr;
  logical                 term = NO;
BEGINSEQ
  if ( bufnum < size )
  {
    Flush(NO);
    while ( intiptr = inti_array->GetTail() )
    {
      inti_array->RemoveTail();
      delete intiptr;
    }
  }
    
  delete ordered_list;
  ordered_list = NULL;

  if ( size = bufnum )
  {
    if ( !(klen = node_ref->GetSortKeyLength(NO)) )
      if ( !(klen = node_ref->GetKeyLength()) )      SDBERR(358)
    entry_len = sizeof(ICEntry)-2+klen;
    ordered_list = new GSRT(ICEntry)(size,entry_len,klen,entry_len-klen+1,'C',NO);
  
    iceptr = (ICEntry *)msmgs(entry_len);

    inti_array->GoTop();
    while ( intiptr = inti_array->GetNext() )
    {
      if ( bufnum-- )
      {
        iceptr->Initialize(node_ref,intiptr);
        ordered_list->AddEntry(iceptr);
      }
      else
      {
        Save(intiptr);
        inti_array->RemoveAt();
        delete intiptr;
      }
    }
    msmfs((void **)&iceptr);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

\param  intiptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical InstanceCache :: Save (inti *intiptr )
{
  ICEntry                *iceptr;
  logical                 term = NO;
BEGINSEQ
  if ( !(iceptr = Find(intiptr->GetID())) )          ERROR

  iceptr->get_inti_ref()->CopyBufferInstance(node_ref->get_nodeinst());    
  if ( node_ref->stscmod() || node_ref->stscsav() )
  {
    iceptr->get_inti_ref()->stssmod();
    mod_count++;
  }
  if ( mod_max && mod_count > mod_max )
    Flush(NO);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetInstance - 



\param  iceptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

void InstanceCache :: SetInstance (ICEntry *iceptr )
{

// stats.Start();
  node_ref->Switch(AUTO);
  node_ref->get_nodeinst()->CopyBufferInstance(iceptr->get_inti_ref());    
  iceptr->SetLastUse(use_count);
  use_count++;

// stats.Stop();

}

/******************************************************************************/
/**
\brief  ~InstanceCache - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~InstanceCache"

                        InstanceCache :: ~InstanceCache ( )
{

  Resize(0);
  delete inti_array;

// stats.Print("Get",YES); // print with headline


}


