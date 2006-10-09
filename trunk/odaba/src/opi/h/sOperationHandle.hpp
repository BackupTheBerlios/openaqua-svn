/********************************* Class Declaration ***************************/
/**
\package  OPI - 
\class    OperationHandle

\brief    Operation Handle
          Operation  handles can be used for executing operations as expressions
          or  function  calls.  Usually,  an  operation  is  associated  with  a
          property  handle defining the instance that is passed to the operation
          as calling object.

\date     $Date: 2006/06/13 17:59:44,57 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OperationHandle_HPP
#define   OperationHandle_HPP

class     OperationHandle;
#include "copadll.h"

class     BNFData;
class     Operation;
class     ParmList;
#include  <sDBObjectHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sInstance.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  OperationHandle
{
protected  :         Operation                                   *operation;                                                 // 

public     :
                     Operation                                   *get_operation() { return(operation); }
public     :                  OPIImpExp             logical CheckExpression (DictionaryHandle &dictptr, char *expression, DBObjectHandle &obhandle, char *clsnames );
public     :                  OPIImpExp             logical CheckExpression (DictionaryHandle &dictptr, DBObjectHandle &resobj, char *clsnames, char *exprnames, char *impnames );
public     :                  OPIImpExp             logical Execute (ParmList *parameters );
public     :                  OPIImpExp             logical Execute ( );
public     :                  OPIImpExp             logical Execute (PropertyHandle &call_object, ParmList *parameters );
public     :                  OPIImpExp             int32 GetDimension ( );
public     :                  OPIImpExp             PropertyHandle &GetResult ( );
public     :                  OPIImpExp             int32 GetSize ( );
public     :                                        logical IsValid ( );
public     :                  OPIImpExp             logical Open (PropertyHandle &prophdl_ref );
public     :                  OPIImpExp                  OperationHandle (PropertyHandle &prophdl_ref );
public     :                  OPIImpExp                  OperationHandle ( );
public     :                  OPIImpExp             logical ProvideExpression (DictionaryHandle &dictionary, DBObjectHandle &resobj, DBObjectHandle &obhandle, char *expression );
public     :                  OPIImpExp             logical ProvideExpression (DictionaryHandle &dictionary, DBObjectHandle &resobj, DBObjectHandle &obhandle, char *class_names, char *expr_names, ParmList *parameters, logical refresh_opt=NO );
public     :                  OPIImpExp             logical ProvideExpression (DictionaryHandle &dictionary, DBObjectHandle &resobj, DBObjectHandle &obhandle, BNFData *expr_data );
public     :                  OPIImpExp             logical ProvideExpression (char *expression );
public     :                  OPIImpExp             void Reset ( );
public     :                  OPIImpExp                  ~OperationHandle ( );
};

#pragma pack()
#endif
