/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ACBaseStruct

\brief    


\date     $Date: 2006/08/25 13:26:30,89 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACBaseStruct"

#include  <popa7.h>
#include  <sCTX_Base.hpp>
#include  <sDBFieldDef.hpp>
#include  <snode.hpp>
#include  <sACBaseStruct.hpp>


/******************************************************************************/
/**
\brief  ACBaseStruct - 



\param  nodeptr - 
\param  dbfield_ptr - Property definition
\param  highctx - 
\param  instptr - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACBaseStruct"

     ACBaseStruct :: ACBaseStruct (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, PIACC accopt )
                     : ACAttribute (nodeptr,dbfield_ptr,highctx,instptr,accopt)
{

  nodetype = NT_ACBaseStruct;

}

/******************************************************************************/
/**
\brief  ~ACBaseStruct - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACBaseStruct"

     ACBaseStruct :: ~ACBaseStruct ( )
{

  if ( nodeidnt == NODE_ID )
    Close();

}


