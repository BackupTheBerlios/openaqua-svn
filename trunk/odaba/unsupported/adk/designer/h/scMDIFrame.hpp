/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cMDIFrame

\brief    


\date     $Date: 2006/03/12 19:36:27,84 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cMDIFrame_HPP
#define   cMDIFrame_HPP

class     cMDIFrame;

class     cControlFrame;
#include  <sPropertyHandle.hpp>
class  cMDIFrame :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     cControlFrame *GetControlFrame ( );
public     :                                     logical ShowControl (PropertyHandle *c_ph );
public     :                                                             cMDIFrame ( );
public     :                                                             ~cMDIFrame ( );
};

#endif
