/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemCaps

\brief    


\date     $Date: 2006/03/13 21:33:57,48 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSItemCaps_HPP
#define   ODSItemCaps_HPP

class     ODSItemCaps;

class     ODSItem;
class     PropertyHandle;
#include  <sDBObjectHandle.hpp>
#include  <sODSItemCaps.hpp>
#include  <sODSPropPath.hpp>
class  ODSItemCaps
{
protected  :         ODSItem                                     *item;                                                      //

public     :
public     :         OGUI7ImpExp                                         ODSItemCaps (const ODSItemCaps &rcODSItemCaps );
public     :         OGUI7ImpExp                                         ODSItemCaps (PropertyHandle *property_handle, logical fOwnsProperty_NO=NO );
public     :         OGUI7ImpExp                                         ODSItemCaps (const ODSItemCaps &rcODSItemCaps, ODSPropPath &rODSPropPath, DBObjectHandle &ob_handle );
public     :         OGUI7ImpExp                 ODSItem *operator* ( ) const;
public     :         OGUI7ImpExp                 ODSItem *operator-> ( ) const;
public     :         OGUI7ImpExp                                         ~ODSItemCaps ( );
};

#endif
