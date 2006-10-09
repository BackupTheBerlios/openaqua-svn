/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cTableEditor

\brief    


\date     $Date: 2006/03/12 19:36:35,67 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cTableEditor_HPP
#define   cTableEditor_HPP

class     cTableEditor;

#include  <scSDBResource_Base.hpp>
class  cTableEditor :public cSDBResource_Base
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     int8 DoBeforeDrop ( );
public     :                                                             cTableEditor ( );
public     :                                                             ~cTableEditor ( );
};

#endif
