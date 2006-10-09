/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSTree

\brief    


\date     $Date: 2006/03/13 21:33:59,87 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSTree_HPP
#define   ODSTree_HPP

class     ODSTree;

#define  _ACCEPT_PTR                               logical (QObject::*Accept)( ODS& )
class     ItemData;
class     ODSTreeHandler;
class     ODataWidget;
class     OEHControlData;
class     OEHControlList;
class     OEHDataWidget;
class     OListCtl;
class     OTreeLayout;
#include  <sODS.hpp>
#include  <sODSRegion.hpp>
#pragma pack(4)

class  ODSTree :public ODSRegion
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //
protected  :         ODSTreeHandler                              *handler;                                                   //

public     :
                     ODSTreeHandler                              *get_handler() { return(handler); }
public     :                                     void AfterDataFill ( );
public     :                                     void AfterDataSet ( );
public     :                                     logical BeforeDataFill ( );
public     :                                     logical BeforeDataSet ( );
public     :                                     OListCtl *GetListControl ( ) const;
public     :                                     logical IsCurItem (ItemData *pItemData, logical recursive );
public     :                                     logical IsItemExpanded (ItemData *pItemData );
public     :                                                             ODSTree (OEHControlData *pOEHControlData );
public     :                                                             ODSTree (OEHControlData *pOEHControlData, OTreeLayout *pOTreeLayout );
public     :                                     signals: void OnBeforeDataFill (logical *pterm );
public     :                                     signals: void OnBeforeDataSet (logical *pterm );
public     :                                     void ResetCurItem (ItemData *pItemData, logical recursive );
public     :                                     void SetCurItem (ItemData *pItemData );
public     :                                     void SetHandler (ODSTreeHandler *pODSTreeHandler );
public     :                                     void SetLastID (int32 inst_id );
public     :                                                             ~ODSTree ( );
};

#pragma pack()
#endif
