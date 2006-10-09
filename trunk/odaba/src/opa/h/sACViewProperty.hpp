/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACViewProperty

\brief    


\date     $Date: 2006/03/12 19:12:20,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACViewProperty_HPP
#define   ACViewProperty_HPP

class     ACViewProperty;

class     CTX_Base;
class     DBFieldDef;
class     OperEnvironment;
class     node;
#include  <cADT_Types.h>
#include  <cPIACC.h>
#include  <sACViewProperty.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbnode.hpp>
#pragma pack(8)

class  ACViewProperty :public bnode
{
protected  :         PropertyHandle                               target ATTR_ALIGN(4);                                      //
protected  :         PropertyHandle                               source;                                                    //
protected  :         void                                        *expression;                                                //
protected  :         OperationHandle                              operation;                                                 //
protected  :         ADT_Types                                    source_type;                                               //
protected  :         OperEnvironment                             *oper_env;                                                  //

public     :
                     PropertyHandle                              &get_target() { return(target); }
                     PropertyHandle                              &get_source() { return(source); }
                     void                                        *get_expression() { return(expression); }
                     OperationHandle                             &get_operation() { return(operation); }
                     ADT_Types                                    get_source_type() { return(source_type); }
                     OperEnvironment                             *get_oper_env() { return(oper_env); }
public     :                                                             ACViewProperty (node *nodeptr, DBFieldDef *dbfield_ptr, CTX_Base *highctx, void *instptr, PIACC accopt, OperEnvironment *operenv );
public     :                                                             ACViewProperty (ACViewProperty &viewattr_ref );
public     : virtual                             PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     :                                     logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                     node *CreateCopyNode ( );
public     : virtual                             PIACC GetMaxMode ( );
public     :                                     node *GetNode (logical autoini=NO );
public     : virtual opa7ImpExp                  logical IsAttribute ( );
public     : virtual opa7ImpExp                  logical IsCollection ( );
public     : virtual opa7ImpExp                  logical IsReadOnly ( );
public     :                                     logical Read ( );
public     :                                     logical Save (logical switchopt );
public     :                                     void SetIsCollection ( );
public     :                                     logical SetSource ( );
public     :                                     void SetTarget ( );
public     :                                     logical SetupAttribute ( );
public     :                                     logical SetupFieldDef ( );
public     :                                     logical SetupReference (void *instptr );
public     :                                     logical Store ( );
public     :                                                             ~ACViewProperty ( );
};

#pragma pack()
#endif
