/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSchemaTreeProvider

\brief    


\date     $Date: 2006/03/13 21:36:13,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSchemaTreeProvider"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sODS.hpp>
#include  <sOSchemaTreeProvider.hpp>


/******************************************************************************/
/**
\brief  AddCollection - 


\return term -

\param  pvoidParent -
\param  pODSRelation -
\param  pCaseMatcher -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddCollection"

void *OSchemaTreeProvider :: AddCollection (void *pvoidParent, ODSRelation *pODSRelation, CaseMatcher *pCaseMatcher )
{

return new CollectionDefNode( (CustomDefNode*) ( pvoidParent ? pvoidParent : defroot ), pODSRelation, pCaseMatcher );

}

/******************************************************************************/
/**
\brief  AddInstance - 


\return term -

\param  pvoidParent -
\param  pODSRelation -
\param  pCaseMatcher -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInstance"

void *OSchemaTreeProvider :: AddInstance (void *pvoidParent, ODSRelation *pODSRelation, CaseMatcher *pCaseMatcher )
{

return new InstanceDefNode( (CustomDefNode*) ( pvoidParent ? pvoidParent : defroot ), pODSRelation, pCaseMatcher );

}

/******************************************************************************/
/**
\brief  AddRecursion - 


\return term -

\param  pvoidParent -
\param  pvoidTo -
\param  pCaseMatcher -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRecursion"

void *OSchemaTreeProvider :: AddRecursion (void *pvoidParent, void *pvoidTo, CaseMatcher *pCaseMatcher )
{

return new RecursionDefNode( (CustomDefNode*) (pvoidParent ? pvoidParent : defroot), (CustomDefNode*) pvoidTo, pCaseMatcher );

}

/******************************************************************************/
/**
\brief  AddVirtual - 


\return term -

\param  pvoidParent -
\param  pCaseMatcher -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddVirtual"

void *OSchemaTreeProvider :: AddVirtual (void *pvoidParent, CaseMatcher *pCaseMatcher )
{

return new VirtualDefNode( (CustomDefNode*) (pvoidParent ? pvoidParent : defroot), pCaseMatcher );

}

/******************************************************************************/
/**
\brief  GetFactory - 


\return term -

\param  pvoidNode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFactory"

void *OSchemaTreeProvider :: GetFactory (void *pvoidNode )
{

return ((SchemaNode*) pvoidNode)->factory;

}

/******************************************************************************/
/**
\brief  OSchemaTreeProvider - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSchemaTreeProvider"

                        OSchemaTreeProvider :: OSchemaTreeProvider ( )
                     : OTreeProvider ()
{

defroot= new VirtualDefNode( NULL, NULL );
root= new SchemaNode( NULL, (CustomDefNode*) defroot );

}

/******************************************************************************/
/**
\brief  doFinalizeODS - 


\return term -

\param  rOTreeProviderState -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doFinalizeODS"

logical OSchemaTreeProvider :: doFinalizeODS (OTreeProviderState &rOTreeProviderState )
{

((SchemaNode*) rOTreeProviderState.currentNode)->FinalizeODS( &rOTreeProviderState );

}

/******************************************************************************/
/**
\brief  doGetChildren - 


\return term -

\param  rOTreeProviderState -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doGetChildren"

logical OSchemaTreeProvider :: doGetChildren (OTreeProviderState &rOTreeProviderState )
{

((SchemaNode*) rOTreeProviderState.currentNode)->GetChildren( &rOTreeProviderState );

}

/******************************************************************************/
/**
\brief  doGetODS - 


\return term -

\param  rOTreeProviderState -
\param  pvoidNode -
\param  podsOld -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doGetODS"

ODS *OSchemaTreeProvider :: doGetODS (OTreeProviderState &rOTreeProviderState, void *pvoidNode, ODS *podsOld )
{

return ((SchemaNode*) pvoidNode)->GetODS( &rOTreeProviderState, podsOld );

}

/******************************************************************************/
/**
\brief  doHasChildren - 


\return cond -

\param  rOTreeProviderState -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doHasChildren"

logical OSchemaTreeProvider :: doHasChildren (OTreeProviderState &rOTreeProviderState )
{

return ((SchemaNode*) rOTreeProviderState.currentNode)->HasChildren( &rOTreeProviderState );

}

/******************************************************************************/
/**
\brief  ~OSchemaTreeProvider - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSchemaTreeProvider"

                        OSchemaTreeProvider :: ~OSchemaTreeProvider ( )
{

delete (CustomDefNode*) defroot;

}


