/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OComboBox

\brief    Drop down Combo Box
          A  combo  list  is  a  drop  list,  which  displays  the  value for an
          attribute  or the key  for a single  reference. The drop list contains
          the set of permisable values for the attribute or reference. 
          The  edit field  can be  enabled or  disabled for editing. It displays
          the  key  value  or  a  selected  attribute  from  the  the  instance 
          (referenced  instance) or  the attribute  value. For single references
          the  drop list usually contains the instances, which can be associated
          with  the property (base collection). For attributes enumerated values
          can  be displayed as well as a  list of possible string values from an
          instance collection (base collection). 
          When  using a combobox  for enumerated attributes  the edit field will
          not  accept  other  values  than  defined in the drop list. For single
          references  the value in the  edit field might not  be a member of the
          list  when  being  displayed,  but  only  members  of  the list can be
          entered  in  the  list.  When  the value is not member of the droplist
          when  leaving the field the original value is restored. Otherwise, the
          instance  represented by the value is linked to the reference. You may
          add a non existing value in the list using the insert action.
          When  using the combo  box for text  attributes the list may contain a
          number  of  proposed  values  for  the attribute. In this case you may
          enter  also  a  field  not  contained  in  the  list without causing a
          conflict.  You  may  also  add  the value to the list using the insert
          action. 
          The  droplist contains a single  column, which displays instances from
          the  base collection. It  displays either an  assigned key value or an
          attribute  for the instances. For  enumerations, the enumerator string
          is displayed.

\date     $Date: 2006/07/06 14:08:06,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OComboBox_HPP
#define   OComboBox_HPP

class     OComboBox;

class     ODS;
class     ODataWidget;
class     OEHControlList;
class     OListCtl;
class     OListView;
class     OTreeLayout;
class     OTreeView;
#include  <sOEHControlListValue.hpp>
#pragma pack(4)

class  OComboBox :public QComboBox,
public OEHControlListValue
{
protected  :                                                      Q_OBJECT;                                                  // 
protected  :         QObject                                     *ef;                                                        // 
protected  :         OListView                                   *listbox;                                                   // 
protected  :         logical                                      in_clear;                                                  // 

public     :
                     OListView                                   *get_listbox() { return(listbox); }
                     logical                                      get_in_clear() { return(in_clear); }
public     : virtual          OGUIImpExp            logical Activate ( );
public     :                                        void BlockSignals (logical block_opt );
protected  : private slots:                         void ClearData ( );
public     : virtual                                logical DA_FindEntry ( );
public     : virtual                                logical DA_FindEntry (char *skey, logical cur_opt=YES );
public     : virtual                                logical DA_Refresh ( );
public     : virtual                                logical DA_StoreEntry ( );
public     : virtual          OGUIImpExp            logical Deactivate (logical data_only=NO );
protected  : private slots:                         void FillData ( );
protected  : private slots:                         void FillList ( );
public     : virtual                                OListCtl *GetListControl ( );
public     : virtual          OGUIImpExp            OTreeLayout *GetListLayout ( );
public     :                                        logical Initialize ( );
public     : virtual                                OListCtl *ListControl ( );
public     : public slots:                          void ListCurrentChanged ( );
public     :                  OGUIImpExp                 OComboBox (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL, logical editable_w=YES, int8 sort_order=0 );
public     :                  OGUIImpExp                 OComboBox (QWidget *pQWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL, logical editable_w=YES, int8 sort_order=0 );
public     :                                        logical ProvideContextMenu (QObject *watched );
public     : public slots:                          void SelectionChanged ( );
public     :                                        logical SetBasePath (char *base_path );
public     : virtual                                logical SetDefaultReactions ( );
public     :                                        logical SetFilter (char *expression, logical enable_opt );
public     :                                        logical SetFlat (bool toggle=FALSE );
protected  :                                        void SetReadOnly (logical fReadOnly );
public     :                                        QWidget *WidgetQ ( );
protected  : private slots:                         void storeToValue ( );
public     : virtual          OGUIImpExp                 ~OComboBox ( );
};

#pragma pack()
#endif
