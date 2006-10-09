/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemCaps

\brief    


\date     $Date: 2006/03/13 21:35:27,20 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSItemCaps"

#include  <pogui7.h>
#include  <sODSItem.hpp>
#include  <sPropertyHandle.hpp>
#include  <sODSItemCaps.hpp>


/******************************************************************************/
/**
\brief  ODSItemCaps - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  rcODSItemCaps -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemCaps"

                        ODSItemCaps :: ODSItemCaps (const ODSItemCaps &rcODSItemCaps )
                     : item(rcODSItemCaps.item)
{

  if ( item ) 
    item->Ref();

}

/******************************************************************************/
/**
\brief  i01


\param  property_handle -
\param  fOwnsProperty_NO -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemCaps"

                        ODSItemCaps :: ODSItemCaps (PropertyHandle *property_handle, logical fOwnsProperty_NO )
                     : item(ODSItem::Provide(
                 property_handle,
                 fOwnsProperty_NO,
                 (DBObjectHandle&)                   property_handle->GetObjectHandle(),
                 (ODSPropPath&)ODSPropPath()))
{



}

/******************************************************************************/
/**
\brief  i02


\param  rcODSItemCaps -
\param  rODSPropPath -
\param  ob_handle - Database object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemCaps"

                        ODSItemCaps :: ODSItemCaps (const ODSItemCaps &rcODSItemCaps, ODSPropPath &rODSPropPath, DBObjectHandle &ob_handle )
                     : item(ODSItem::Provide(*rcODSItemCaps,rODSPropPath,ob_handle ))
{



}

/******************************************************************************/
/**
\brief  operator* - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator*"

ODSItem *ODSItemCaps :: operator* ( ) const
{

  return item;

}

/******************************************************************************/
/**
\brief  operator-> - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator->"

ODSItem *ODSItemCaps :: operator-> ( ) const
{

  return item;

}

/******************************************************************************/
/**
\brief  ~ODSItemCaps - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSItemCaps"

                        ODSItemCaps :: ~ODSItemCaps ( )
{

  if ( item ) 
    item->Deref();

}


