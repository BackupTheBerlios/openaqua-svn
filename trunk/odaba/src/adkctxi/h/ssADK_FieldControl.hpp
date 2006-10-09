/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi
\class    sADK_FieldControl



\date     $Date: 2006/06/01 16:00:27,29 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sADK_FieldControl_HPP
#define   sADK_FieldControl_HPP

class     sADK_FieldControl;

#include  <ssLanguageDependendBase.hpp>
class  sADK_FieldControl :public sLanguageDependendBase
{

public     :
public     :                                        logical AddColumn ( );
public     :                                        logical AddField ( );
public     :                                        logical AddRegion ( );
public     :                                        logical AddTabControl ( );
public     :                                        int32 Create (CTX_Structure **strctx_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             sADK_FieldControl ( );
public     : virtual                                     ~sADK_FieldControl ( );
};

#endif
