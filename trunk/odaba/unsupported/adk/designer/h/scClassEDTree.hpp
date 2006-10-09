/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassEDTree



\date     $Date: 2006/06/01 16:47:56,46 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassEDTree_HPP
#define   cClassEDTree_HPP

class     cClassEDTree;

#include  <sPropertyHandle.hpp>
#include  <scSDBResource_Base.hpp>
class  cClassEDTree :public cSDBResource_Base
{
protected  :         char                                         last_function[40];                                         
protected  :         PropertyHandle                               dependend_object;                                          

public     :
                     char                                        *get_last_function() { return(last_function); }
public     :                                        logical AfterInsertImpClass (PropertyHandle *class_ph );
public     :                                        logical AfterInsertPFunction (PropertyHandle *funct_ph );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                int8 DoAfterDeleteData ( );
public     : virtual                                int8 DoAfterInsertData ( );
public     : virtual                                int8 DoAfterSelect ( );
public     :                                        int8 DoBeforeClose ( );
public     : virtual          DesignerImpExp        int8 DoBeforeDataSet ( );
public     :                                        int8 DoBeforeDeleteData ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetClassName ( );
public     :                                        PropertyHandle *GetClassPH ( );
public     :                                        logical InsertOverloadFunction ( );
public     :                                        void SetApplicationTitle ( );
public     :                                        void SetPFunctionNotInit ( );
public     :                                             cClassEDTree ( );
public     :                                             ~cClassEDTree ( );
};

#endif
