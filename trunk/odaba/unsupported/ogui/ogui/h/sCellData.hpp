/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    CellData

\brief    


\date     $Date: 2006/03/13 21:33:33,54 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CellData_HPP
#define   CellData_HPP

class     CellData;

class     ItemData;
class     ODS;
class     ODSList;
class     ODataLayout;
class     OEHControlData;
class     PropertyHandle;
#include  <sODSItemState.hpp>
#include  <sODataLayoutRef.hpp>
class  CellData :public ODSItemState,
public ODataLayoutRef
{
public     :         ItemData                                    *item_data;                                                 //
protected  :         int                                          col;                                                       //
protected  :         QVariant                                     value;                                                     //

public     :
                     int                                         &get_col() { return(col); }
                     QVariant                                    &get_value() { return(value); }
public     :                                                             CellData (ItemData *pItemData, int column );
public     :                                     void ClearData ( );
public     :                                     logical FillData (logical init_opt );
public     :                                     QVariant GetBackgroundColor ( );
public     :                                     QVariant GetCheckState ( );
public     :                                     QVariant GetData ( );
public     :                                     OEHControlData *GetDataWidget ( );
public     :                                     QVariant GetFont ( );
public     :                                     QVariant GetHelp ( );
public     :                                     QVariant GetIcon ( );
public     :                                     QModelIndex GetModelIndex ( );
public     :                                     PropertyHandle *GetPropertyHandle ( );
public     :                                     QVariant GetTextAlignment ( );
public     :                                     QVariant GetTextColor ( );
public     :                                     QVariant GetToolTip ( );
public     :                                     logical IsReadOnly ( );
public     :                                     ItemData *Item ( );
public     :                                     ODSList *ListODS ( );
public     :                                     CellData *Parent ( );
public     :                                     logical SetData (const QVariant &qvariant );
public     :                                     void SetDataWidget (OEHControlData *pOEHControlData, ODSList *pODSList );
public     :                                     logical ToggleChecked ( );
public     :                                     void UpdateData ( );
public     : virtual                                                     ~CellData ( );
};

#endif
