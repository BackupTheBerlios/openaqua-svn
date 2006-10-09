/********************************* Class Declaration ***************************/
/**
\package  OGUI - 
\class    OEHControlListValue

\brief    


\date     $Date: 2006/07/05 16:37:41,48 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHControlListValue_HPP
#define   OEHControlListValue_HPP

class     OEHControlListValue;

class     OListCtl;
class     OStringList;
#include  <sODS.hpp>
#include  <sODSPropPath.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHControlList.hpp>
#include  <sOEHControlValue.hpp>
#include  <sOEHDataWidget.hpp>
#pragma pack(4)

class  OEHControlListValue :public OEHControlList
{
protected  :         logical                                      ods_attribute;                                             // Selected list value
protected  :         logical                                      ods_multi_ref;                                             // 
protected  :         logical                                      list_as_ods;                                               // 

public     :
                     logical                                      get_ods_attribute() { return(ods_attribute); }
                     logical                                      get_ods_multi_ref() { return(ods_multi_ref); }
public     : virtual                                logical Activate ( );
public     :                                        logical ActivateListValue (logical ignore_evthandling=NO );
public     : virtual                                logical Deactivate (logical data_only=NO );
public     :                                        logical DeactivateListValue (logical ignore_evthandling=NO, logical data_only=NO );
public     : virtual                                void HandleActivated ( );
public     : public slots:                          void HandleOpened (logical chk_visible );
public     : virtual          OGUIImpExp            ODS *List ( );
public     : virtual                                OListCtl *ListControl ( );
public     :                  OGUIImpExp                 OEHControlListValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                  OGUIImpExp                 OEHControlListValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS );
public     : virtual                                void UpdateControl ( );
public     :                                        void ValueInserted ( );
protected  :                                        logical ValueLocate ( );
protected  : virtual                                logical ValueSelected ( );
public     : virtual                                void ValueUpdated ( );
public     : virtual                                     ~OEHControlListValue ( );
};

#pragma pack()
#endif
