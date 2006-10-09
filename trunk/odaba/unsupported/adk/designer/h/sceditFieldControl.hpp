/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ceditFieldControl

\brief    


\date     $Date: 2006/06/01 17:04:08,31 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ceditFieldControl_HPP
#define   ceditFieldControl_HPP

class     ceditFieldControl;

#include  <scSDBResource_Base.hpp>
class  ceditFieldControl :public cSDBResource_Base
{

public     :
public     :                                        logical Check ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             ceditFieldControl ( );
public     : virtual                                     ~ceditFieldControl ( );
};

#endif
