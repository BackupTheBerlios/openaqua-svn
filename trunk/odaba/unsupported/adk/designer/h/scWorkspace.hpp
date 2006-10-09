/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cWorkspace

\brief    


\date     $Date: 2006/03/12 19:36:36,67 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cWorkspace_HPP
#define   cWorkspace_HPP

class     cWorkspace;

class     PropertyHandle;
class  cWorkspace :public CTX_Control
{

public     :
public     :                                     int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                     void ShowControl (PropertyHandle *c_ph );
public     :                                                             cWorkspace ( );
public     :                                                             ~cWorkspace ( );
};

#endif
