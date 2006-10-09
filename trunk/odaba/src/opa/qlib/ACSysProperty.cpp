/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACSysProperty

\brief    


\date     $Date: 2006/03/29 21:27:14,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACSysProperty"

#include  <popa7.h>
#include  <sDBFieldDef.hpp>
#include  <snode.hpp>
#include  <sACSysProperty.hpp>


/******************************************************************************/
/**
\brief  ACSysProperty - 



\param  nodeptr - 
\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACSysProperty"

                        ACSysProperty :: ACSysProperty (node *nodeptr, DBFieldDef *fielddef )
                     : bnode ()
{

  nodetype = NT_ACSysProperty;
  
  switch ( type = fielddef->get_sys_field() )
  {
    case SPT_loid         : 
    case SPT_guid         : nodeacc = PI_Read;
                            break;
  }


}

/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  autoini - 
\param  acccheck - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical ACSysProperty :: Check (logical autoini, logical acccheck )
{

  return(node::Check(autoini,acccheck));

}

/******************************************************************************/
/**
\brief  Get - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG


\param  indx0 - Position in collection
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACSysProperty :: Get (int32 indx0, logical chknode )
{
  char     *instptr  = NULL;
  char     *key_val  = NULL;
  smcb     *smcbptr  = NULL;
  int32     inst_id;
  char     *string;
BEGINSEQ
  if ( !(instptr = (char *)GetArea()) )
  {
    AllocateArea();
    instptr = (char *)GetArea();
  }
  
  switch ( type )
  {
    case SPT_loid         : if ( (inst_id = nodenode->GetID(AUTO,NO,YES).get_ebsnum()) <= 0 )
                                                     ERROR
                            gvtxxtoa(inst_id,instptr,10);
                            break;
    case SPT_guid         : if ( !(string = nodenode->GetGUID()) )
                                                     ERROR
                            strcpy(instptr,string);
                            break;
    case SPT_type         : if ( !(string = nodenode->GetCurrentType()) )
                                                     ERROR
                            strcpy(instptr,string);
                            break;
    case SPT_sort_key     : if ( !(smcbptr = nodenode->GetSortKeySMCB()) ||
                                 !(key_val = nodenode->ExtractSortKey(NULL,NULL,NO)) )
                                                     ERROR
                            smcbptr->ConvertToString(key_val,instptr,nodefield->fmcbsize);
                            break;
    case SPT_key          : if ( !(smcbptr = nodenode->GetKeySMCB()) ||
                                 !(key_val = nodenode->ExtractKey(NULL,NULL,NO)) )
                                                     ERROR
                            smcbptr->ConvertToString(key_val,instptr,nodefield->fmcbsize);
                            break;
    default               : ERROR
  }
    
  GenerateEvent(DBO_Read);

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  i1


\param  skey - 
\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACSysProperty :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;

  return(instptr);
}

/******************************************************************************/
/**
\brief  i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACSysProperty :: Get ( )
{
  void                   *instptr = NULL;

  return(instptr);
}

/******************************************************************************/
/**
\brief  Modify - 


\return instptr - 

\param  chknode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void *ACSysProperty :: Modify (logical chknode )
{

  stssmod();
  return(flddata);
}

/******************************************************************************/
/**
\brief  Store - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical ACSysProperty :: Store ( )
{
  char               *instptr = NULL;
  logical             term    = NO;
BEGINSEQ
  if ( !stscmod() )                                  LEAVESEQ
  if ( nodeacc < PI_Update )                         SDBERR(28)
  if ( !(instptr = (char *)GetArea()) )              SDBERR(99)
  
  stsrmod();
  
  switch ( type )
  {
    case SPT_loid         : 
    case SPT_guid         : SDBERR(28)
                            break;
    case SPT_type         : if ( nodenode->SetType(instptr) )
                                                     ERROR
                            break;
    case SPT_sort_key     : if ( nodenode->SetSortKey(instptr,NULL) )
                                                     ERROR
                            break;
    case SPT_key          : if ( nodenode->SetKey(instptr,NULL) )
                                                     ERROR
                            break;
    default               : SDBERR(99)
  }
    
  bnode::Store();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACSysProperty - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACSysProperty"

                        ACSysProperty :: ~ACSysProperty ( )
{



}


