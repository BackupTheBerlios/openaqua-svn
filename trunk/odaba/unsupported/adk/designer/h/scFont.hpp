/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cFont

\brief    


\date     $Date: 2006/06/03 15:05:23,09 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cFont_HPP
#define   cFont_HPP

class     cFont;

#include  <scNotifyHighContext.hpp>
class  cFont :public cNotifyHighContext
{

public     :
public     :                                        logical Changed ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        int8 DoBeforeFillData ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
};

#endif
