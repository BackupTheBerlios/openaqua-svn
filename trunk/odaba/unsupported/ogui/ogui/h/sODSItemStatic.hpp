/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemStatic

\brief    


\date     $Date: 2006/03/13 21:33:58,15 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSItemStatic_HPP
#define   ODSItemStatic_HPP

class     ODSItemStatic;

class     ODSItem;
#include  <sExtentCache.hpp>
#include  <sODSItemWatcher.hpp>
class  ODSItemStatic
{
protected  :         friend class                                 ODSItemWatcher;                                            //
public     :         ODSItem                                     *root;                                                      //
public     :         ODSItemWatcher                               watcher;                                                   //
public     :         std::vector<ODSItem*>                        items;                                                     //
public     :         ExtentCache                                  extentCache;                                               //

public     :
public     :                                     logical Deinit ( );
public     :                                     logical Init ( );
public     :                                                             ODSItemStatic ( );
protected  : static                              void __cdecl checkItems ( );
public     :                                     logical remove (ODSItem *pODSItem );
public     :                                                             ~ODSItemStatic ( );
};

#endif
