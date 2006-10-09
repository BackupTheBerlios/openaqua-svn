/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cColorButton

\brief    


\date     $Date: 2006/06/03 15:05:21,21 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cColorButton_HPP
#define   cColorButton_HPP

class     cColorButton;

#include  <scNotifyHighContext.hpp>
class  cColorButton :public cNotifyHighContext
{

public     :
public     :                                        logical Changed ( );
public     :                                        logical ColorDialog ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        int8 DoBeforeFillData ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
};

#endif
