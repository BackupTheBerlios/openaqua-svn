/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSDBStructure_edit

\brief    


\date     $Date: 2006/06/03 15:05:24,56 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cSDBStructure_edit_HPP
#define   cSDBStructure_edit_HPP

class     cSDBStructure_edit;

#include  <scSDBResourceNotifyHigh.hpp>
class  cSDBStructure_edit :public cSDBResourceNotifyHigh
{

public     :
public     :                                        logical Check ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             cSDBStructure_edit ( );
public     : virtual                                     ~cSDBStructure_edit ( );
};

#endif
