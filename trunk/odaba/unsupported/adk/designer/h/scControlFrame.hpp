/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cControlFrame

\brief    


\date     $Date: 2006/08/25 10:53:05,30 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cControlFrame_HPP
#define   cControlFrame_HPP

class     cControlFrame;

class     cControlEdit;
class     cPropertyTable;
#include  <sPropertyHandle.hpp>
class  cControlFrame :public CTX_Control
{
protected  :         cControlEdit                                *control;                                                   // 
protected  :         PropertyHandle                               class_ph;                                                  // 
protected  :         PropertyHandle                               control_ph;                                                // 
protected  :         PropertyHandle                               field_ph;                                                  // 
protected  :         logical                                      dived;                                                     // 

public     :
public     :                                        logical CloseFieldControl ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        int8 DoAfterEnter ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        PropertyHandle *GetControlPH ( );
public     :                                        PropertyHandle *GetFieldPH ( );
public     :                                        cPropertyTable *GetPropertiesContext ( );
public     :                                        logical OpenFieldControl (PropertyHandle *ctrl_ph, const DPoint &pos );
public     :                                        logical ReloadControl ( );
public     :                                        logical ShowControl (PropertyHandle *c_ph );
public     :                                        logical SizeChanged ( );
public     :                                        logical UpdatePropertiesPH (PropertyHandle *ph_ptr );
public     :                                             cControlFrame ( );
public     :                                             ~cControlFrame ( );
};

#endif
