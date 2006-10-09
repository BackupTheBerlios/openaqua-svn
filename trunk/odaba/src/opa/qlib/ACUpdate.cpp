/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACUpdate

\brief    


\date     $Date: 2006/03/12 19:16:18,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACUpdate"

#include  <popa7.h>
#ifndef   DLL_DBVProperty_HPP
#define   DLL_DBVProperty_HPP
#include  <sDBVProperty.hpp>
#include  <sDLL.h>
#endif
#include  <sDBVProperty.hpp>
#include  <sACUpdate.hpp>


/******************************************************************************/
/**
\brief  ACUpdate - 



\param  view_def - Internal view definition
\param  access_mode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACUpdate"

                        ACUpdate :: ACUpdate (DBViewDef &view_def, PIACC access_mode )
                     : ACView()
{


BEGINSEQ
  nodetype = NT_ACUpdate;
  
  if ( InitViewParent(view_def) )                    ERROR
    
  nodenode = view_base->get_nodenode();
  view_base->SetPIRef((PropertyHandle *)&view_base);
  
  if ( InitUpdateFields(view_def) )                  ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ACUpdate :: Execute ( )
{
  logical                 term = NO;
// hier müssen alle Updates ausgeführt werden ...
  return(term);
}

/******************************************************************************/
/**
\brief  InitUpdateFields - 


\return term - Termination code

\param  view_def - Internal view definition
\param  access_mode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitUpdateFields"

logical ACUpdate :: InitUpdateFields (DBViewDef &view_def, PIACC access_mode )
{
  DBVProperty     *property;
  PropAllocation  *prop_alloc;
  logical          term = NO;
BEGINSEQ
// ist nur 'ne Skizze!!
  
  DLL(DBVProperty) properties(*view_def.get_properties());
  properties.GoTop();
  while ( property = properties.GetNext() )
  {
    if ( !(prop_alloc = property->CreateAllocation(view_base,this,view_def.get_name())) )
                                                     ERROR
    if ( prop_alloc->get_is_reference() )
      has_references = YES;
    allocations.AddTail(prop_alloc);
  }

//  *(ACNode *)this = *nodenode;
  ChangeMode(access_mode);
  
  allocations.GoTop();  
  while ( prop_alloc = allocations.GetNext() )
    prop_alloc->SetTarget(this);


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACUpdate - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACUpdate"

                        ACUpdate :: ~ACUpdate ( )
{

  if ( nodeidnt == NODE_ID )
    Close();



}


