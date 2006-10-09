/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cControlEdit

\brief    


\date     $Date: 2006/06/03 15:05:21,54 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cControlEdit_HPP
#define   cControlEdit_HPP

class     cControlEdit;

class     cControlFrame;
#include  <sCTX_Design.hpp>
#include  <sPropertyHandle.hpp>
class  cControlEdit :public CTX_Design
{

public     :
public     :                                        CTX_Control *AddField (PropertyHandle *drop_ph, const DPoint &pos );
public     :                                        logical CloseFieldControl ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        int8 DoAfterEnter ( );
public     :                                        int8 DoBeforeDrop ( );
public     :                                        logical EditField (PropertyHandle *field_ph );
public     :                                        logical EditFieldLabel (PropertyHandle *field_ph );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        cControlFrame *GetFrameContext ( );
public     : virtual                                logical OpenFieldControl (PropertyHandle *field_ph, PropertyHandle *field_control_ph );
public     :                                        logical Refresh ( );
public     : virtual                                logical SelectField (PropertyHandle *field_ph );
public     :                                        logical SizeChanged ( );
public     :                                             cControlEdit ( );
public     :                                             ~cControlEdit ( );
};

#endif
