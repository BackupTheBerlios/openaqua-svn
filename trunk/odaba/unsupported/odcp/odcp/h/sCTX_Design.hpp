/********************************* Class Declaration ***************************/
/**
\package  ODCP - 
\class    CTX_Design

\brief    


\date     $Date: 2006/08/25 11:05:04,28 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Design_HPP
#define   CTX_Design_HPP

class     CTX_Design;

class     DesignerModeControl;
class     ODControl;
#include  <sCTX_Control.hpp>
class  CTX_Design :public CTX_Control
{
protected  :         PropertyHandle                              *control_ph;                                                // 
protected  :         DesignerModeControl                         *designer;                                                  // 

public     :
                     PropertyHandle                              *get_control_ph() { return(control_ph); }
                     DesignerModeControl                         *get_designer() { return(designer); }
public     :                  ODCPImpExp                 CTX_Design ( );
public     :                  ODCPImpExp            logical DeleteField (ODControl *ctrl );
public     : virtual          ODCPImpExp            int8 DoAfterOpen ( );
public     : virtual          ODCPImpExp            logical EditField (ODControl *ctrl );
public     : virtual          ODCPImpExp            logical EditField (PropertyHandle *field_ph );
public     :                  ODCPImpExp            logical EditFieldControl (ODControl *ctrl );
public     : virtual          ODCPImpExp            logical EditFieldLabel (ODControl *ctrl );
public     : virtual          ODCPImpExp            logical EditFieldLabel (PropertyHandle *field_ph );
public     :                  ODCPImpExp            logical EnableFieldDesignMode (CTX_Control *field_context );
public     :                  ODCPImpExp            PropertyHandle *GetControlPH ( );
public     :                  ODCPImpExp            PropertyHandle *GetFieldPH (ODControl *ctrl );
public     :                  ODCPImpExp            PropertyHandle *GetFieldPH (char *ref_name, char *name );
public     :                                        logical HasPreview ( );
public     :                  ODCPImpExp            void InitDesigner ( );
public     :                  ODCPImpExp            PropertyHandle LoadControlAttribute (char *name );
public     :                  ODCPImpExp            PropertyHandle LoadFieldAttribute (ODControl *ctrl, char *attr_name );
public     :                  ODCPImpExp            PropertyHandle LoadFieldAttribute (char *ref_name, char *fld_name, char *attr_name );
public     :                  ODCPImpExp            PropertyHandle LoadFieldAttribute (PropertyHandle *field_ph, char *attr_name );
public     : virtual          ODCPImpExp            logical OpenFieldControl (PropertyHandle *field_ph, PropertyHandle *field_control_ph );
public     :                                        logical Preview (logical pv );
public     :                                        logical RefreshControl ( );
public     :                  ODCPImpExp            logical RefreshField (ODControl *ctrl, logical focused=NO );
public     : virtual          ODCPImpExp            void ResetControl ( );
public     : virtual          ODCPImpExp            logical SelectField (ODControl *ctrl );
public     : virtual          ODCPImpExp            logical SelectField (PropertyHandle *field_ph );
public     :                  ODCPImpExp            void SetControlPH (PropertyHandle *ph_ptr );
public     :                  ODCPImpExp            logical StoreControlAttribute (char *name, PropertyHandle value );
public     :                  ODCPImpExp            logical StoreFieldAttribute (ODControl *ctrl, char *attr_name, PropertyHandle value );
public     :                  ODCPImpExp            logical StoreFieldAttribute (char *ref_name, char *fld_name, char *attr_name, PropertyHandle value );
public     :                  ODCPImpExp            logical StoreFieldAttribute (PropertyHandle *field_ph, char *attr_name, PropertyHandle value );
public     :                  ODCPImpExp                 ~CTX_Design ( );
};

#endif
