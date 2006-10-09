/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    BNFExpData

\brief    Expression BNF data
          This  class is used to add additional functionality for Expression BNF
          data trees.

\date     $Date: 2006/06/16 12:01:48,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFExpData_HPP
#define   BNFExpData_HPP

class     BNFExpData;

class     ACObject;
class     BNFExpData;
class     DBStructDef;
class     Dictionary;
class     OperEnvironment;
class     fmcb;
class     smcb;
#include  <cODC_Privilege.h>
#include  <cPathTypes.h>
#include  <sBNFData.hpp>
#include  <sNString.hpp>
#pragma pack(8)

class  BNFExpData :public BNFData
{

public     :
public     :                                        BNFExpData *GetAccessPath ( );
public     : static                                 BNFExpData *__cdecl GetBNFExpData (BNFData *bnf_data );
public     :                                        int32 GetDimension (int32 &indx_ref );
public     :                                        BNFExpData *GetElement (int32 index0 );
public     :                                        BNFExpData *GetElement (char *symbol );
public     :                                        int16 GetElementCount ( );
public     :                                        BNFData *GetElementaryView ( );
public     :                                        int32 GetIntegerConstant ( );
public     :                                        BNFData *GetOperand ( );
public     :                                        int16 GetOperandCount ( );
public     :                                        int16 GetParmCount ( );
public     :                                        BNFExpData *GetParmList ( );
public     :                                        fmcb *GetPathElement (Dictionary *dictptr, BNFData *bnf_data, smcb *smcbptr, OperEnvironment *operenv, FunctionTypes &var_type, int8 &path_opt_ref, int32 &autopos, char **autokey );
public     :                                        PathTypes GetPathType (ACObject *obhandle, DBStructDef *structdef );
public     :                  OPAImpExp             ODC_Privilege GetPrivilege ( );
public     :                                        int32 GetReferenceLevel (int32 &indx_ref );
public     :                                        char *GetScopeName (char *scope_name );
public     :                                        BNFExpData *GetSimpleOp ( );
public     :                                        char *GetStringConstant ( );
public     :                  OPAImpExp             logical GetTypeSpec (char *type_name, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref );
public     :                  OPAImpExp             logical GetTypeSpec (char *type_name, char *generic_type, uint32 &size_ref, int32 &dim_ref, int16 &prec_ref, logical unicode_ref, ODC_Privilege &priv_ref, logical &virt_ref, logical &stat_ref, logical &trans_ref, logical &coll_ref );
public     :                                        logical IsBlock ( );
public     :                                        logical IsExpression ( );
public     :                                        logical IsPropertyPath (ACObject *obhandle, smcb *smcbptr, OperEnvironment *operenv, FunctionTypes &path_type, int8 &path_opt_ref );
public     :                                        logical IsPropertyPath (smcb *smcbptr, Dictionary *dictptr, OperEnvironment *operenv, FunctionTypes &path_type, int8 &path_opt_ref );
};

#pragma pack()
#endif
