/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OEHControlValue

\brief    


\date     $Date: 2006/03/13 21:34:12,14 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OEHControlValue_HPP
#define   OEHControlValue_HPP

class     OEHControlValue;

class     ODS;
class     ODataWidget;
#include  <sOEHControlData.hpp>
#pragma pack(4)

class  OEHControlValue :public OEHControlData
{

public     :
public     : virtual                             logical Activate ( );
public     :                                     logical ActivateValue (logical coll_opt, logical ignore_evthandling=NO );
public     : virtual                             logical Deactivate (logical data_only=NO );
public     :                                     logical DeactivateValue (logical coll_opt, logical ignore_evthandling=NO, logical data_only=NO );
public     :         OGUI7ImpExp                                         OEHControlValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w=NULL );
public     :         OGUI7ImpExp                                         OEHControlValue (ODataWidget *pODataWidget, ODataWidget *oODataWidget, logical create_ods );
public     :                                     logical getEnabled ( );
};

#pragma pack()
#endif
