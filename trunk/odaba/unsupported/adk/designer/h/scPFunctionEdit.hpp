/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cPFunctionEdit

\brief    


\date     $Date: 2006/06/03 15:05:23,90 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cPFunctionEdit_HPP
#define   cPFunctionEdit_HPP

class     cPFunctionEdit;

class     PropertyHandle;
class  cPFunctionEdit :public CTX_Control
{
protected  :         int64                                        not_init_objid;                                            // 

public     :
public     :                                        logical Changed ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoBeforeFillData ( );
public     :                                        logical ExecSearchReplace ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        CTX_Control *GetImplEditContext ( );
public     :                                        CTX_Control *GetImplHeadlineContext ( );
public     :                                        logical SetNotInit ( );
public     :                                             cPFunctionEdit ( );
public     : virtual                                     ~cPFunctionEdit ( );
};

#endif
