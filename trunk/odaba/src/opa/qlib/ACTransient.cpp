/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    ACTransient

\brief    


\date     $Date: 2006/03/29 21:26:56,10 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACTransient"

#include  <popa7.h>
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sDBStructDef.hpp>
#include  <sdisel.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sACTransient.hpp>


/******************************************************************************/
/**
\brief  ACTransient - 



\param  obhandle - Database Object handle
\param  dbstrdef - Structure definition
\param  key_name_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACTransient"

                        ACTransient :: ACTransient (ACObject *obhandle, DBStructDef *dbstrdef, char *key_name_w )
                     : ACNode ()
{

BEGINSEQ
  if ( InitTempExtent(dbstrdef,key_name_w) )         ERROR
  
  if ( Open(obhandle,NULL,nodefield,NULL,obhandle->GetAccess()) )
                                                     ERROR
  nodetype = NT_ACTransient;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CreateInti - 


\return intiptr - 

\param  nodeptr - 
\param  strdef_ptr - Internal data structure definition
\param  instptr - 
\param  init_nodes - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *ACTransient :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  inti        *intiptr = NULL;
BEGINSEQ
  if ( !noderefp )
    if ( InitReference() )                            ERROR
  
  if ( !(intiptr = new disel(nodeptr,strdef_ptr,instptr,noderefp,init_nodes)) )
                                                      SDBERR(95)
                                                      SDBCERR

RECOVER
  intiptr = NULL;
ENDSEQ
  return(intiptr);
}

/******************************************************************************/
/**
\brief  ~ACTransient - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACTransient"

                        ACTransient :: ~ACTransient ( )
{

  if ( nodeidnt == NODE_ID )
    Close();
  
  delete nodefield;
  nodefield = NULL;

}


