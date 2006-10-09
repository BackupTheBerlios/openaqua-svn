/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassInputHelp

\brief    


\date     $Date: 2006/06/21 16:42:36,24 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassInputHelp_HPP
#define   cClassInputHelp_HPP

class     cClassInputHelp;

#include  <scInputHelpBase.hpp>
class  cClassInputHelp :public cInputHelpBase
{
protected  :         logical                                      my_class;                                                  // 

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterDataSet ( );
public     : virtual                                int8 DoAfterShow ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical SetAsMyClass ( );
public     :                                             cClassInputHelp ( );
public     : virtual                                     ~cClassInputHelp ( );
};

#endif
