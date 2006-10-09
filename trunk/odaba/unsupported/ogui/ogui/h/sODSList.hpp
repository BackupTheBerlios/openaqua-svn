/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSList

\brief    


\date     $Date: 2006/03/13 21:33:58,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODSList_HPP
#define   ODSList_HPP

class     ODSList;

#include  <sDLL.h>
class     ODSList;
class     ODataWidget;
class     OEHControlData;
class     OEHDataWidget;
class     OFont;
class     OListLayout;
#include  <sODS.hpp>
#include  <sODSList.hpp>
#include  <sbsts.hpp>
#pragma pack(4)

class  ODSList :public ODS,
public bsts
{
protected  :         OListLayout                                 *layout;                                                    //
protected  :         DLL(ODSList)                                *columns;                                                   //
protected  :         OEHControlData                              *data_widget;                                               //
protected  :         int16                                        pos;                                                       //

public     :
                     OListLayout                                 *get_layout() { return(layout); }
                     DLL(ODSList)                                *get_columns() { return(columns); }
                     OEHControlData                              *get_data_widget() { return(data_widget); }
                     int16                                        get_pos() { return(pos); }
public     :                                     void Activate ( );
public     :                                     void BlockSignals (logical block_opt );
public     :                                     void Clear ( );
public     :                                     ODSList *Column (int column );
public     :                                     int32 ColumnCount ( );
public     :                                     void Deactivate ( );
public     :                                     QColor *GetBackgroundColor ( );
public     :                                     QFont *GetFont ( );
public     :                                     char *GetHelp ( );
public     :                                     QIcon *GetIcon ( );
public     :                                     char *GetStaticText ( );
public     :                                     QColor *GetTextColor ( );
public     :                                     char *GetToolTip ( );
public     : virtual                             ODSList *ListODS ( );
public     :                                                             ODSList (int16 col_pos );
public     :                                     void RemoveDataWidget ( );
public     :                                     void ResetChildStates ( );
public     :                                     void ResetStates ( );
public     :                                     void SetControlData (OEHControlData *pOEHControlData );
public     :                                     logical SetDataWidget (OEHControlData *pOEHControlData );
public     :                                     logical SetLayout (OListLayout *pOListLayout );
public     :                                                             ~ODSList ( );
};

#pragma pack()
#endif
