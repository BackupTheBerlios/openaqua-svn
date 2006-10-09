/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OComboListBox

\brief    Combo-Listbox
          A  combo listbox is used to display  collections. A combo list box has
          a  line edit and a  list containing one or  more columns. The list may
          display a key or instance attributes in the columns. 
          The  list is  usually ordered  according to  the selected order of the
          database  collection. The user may change the order by clicking on one
          of  the  columns  headings.  When  the  column  is  associated  with a
          database  order  the  list  will  be ordered according to the database
          order  (fast reorder). When  no sort order  is associated, the list is
          ordered  according  to  the  column content. This requires reading all
          instances  for  the  list,  which  may  take  some  while  for  large 
          collections. 
          The  edit  field  always  displays  the  key  value  according  to the
          selected  database  order.  This  key  is also used for table look-up.
          When  no database order is selected  the edit field displays the value
          for  the selected column, which can  be used for locating instances in
          the  table but not for creating new table instances in case of ordered
          collections. 
          The  combo list box  can be used  for collection properties or extents
          and  for attribute arrays. Combo list  boxes cannot be used for single
          attributes or single references.
          The  insert  action  will  add  an instance according to the key value
          entered  in  the  edit  field.  The  user  cannot  add  instances when
          applying the list box on an array.

\date     $Date: 2006/03/22 13:38:09,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OComboListBox_HPP
#define   OComboListBox_HPP

class     OComboListBox;

class     ODS;
class     ODataWidget;
class     OEHControlList;
class     OListCtl;
class     OListView;
class     OSingleLineEdit;
class     OTreeLayout;
#include  <cODSPropertyType.h>
#include  <sOEHControlListValue.hpp>
#pragma pack(4)

class  OComboListBox :public QWidget,
public OEHControlListValue
{
protected  :                                                      Q_OBJECT ATTR_ALIGN(4);                                    //
protected  :         OSingleLineEdit                             *edit;                                                      //
protected  :         OListView                                   *listbox;                                                   //
protected  :         logical                                      autofinding;                                               //

public     :
                     OSingleLineEdit                             *get_edit() { return(edit); }
                     OListView                                   *get_listbox() { return(listbox); }
public     : virtual OGUIImpExp                  logical Activate ( );
public     :                                     void BlockSignals (logical block_opt );
public     :                                     void ClearData ( );
public     :         OGUIImpExp                  int Count ( );
public     : virtual                             logical DA_FindEntry ( );
public     : virtual                             logical DA_FindEntry (char *skey, logical cur_opt=YES );
public     : virtual                             logical DA_Refresh ( );
public     : virtual OGUIImpExp                  logical Deactivate (logical data_only=NO );
protected  :                                     private slots: void FillList ( );
public     : virtual                             OListCtl *GetListControl ( );
public     : virtual OGUIImpExp                  OTreeLayout *GetListLayout ( );
public     : virtual                             OListCtl *ListControl ( );
public     :         OGUIImpExp                                          OComboListBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL, logical multi_sel_w=NO, int8 sort_order=0 );
public     : virtual                             logical SetDefaultReactions ( );
public     :                                     logical SetFilter (char *expression, logical enable_opt );
public     : virtual OGUIImpExp                  OTreeLayout *SetPath (char *prop_path, ODSPropertyType prop_type=PT_undefined );
public     :                                     void SetReadOnly (logical fReadOnly );
public     : virtual OGUIImpExp                  ODS *Value ( );
public     :                                     QWidget *WidgetQ ( );
protected  :                                     private slots: void editTextChanged (const QString &rcqsText );
public     : virtual                             bool eventFilter (QObject *watched, QEvent *pQEvent );
protected  :                                     logical getEnabled ( );
public     :                                     public slots: void updateValue (ItemData *pItemData );
public     : virtual OGUIImpExp                                          ~OComboListBox ( );
};

#pragma pack()
#endif
