/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    PropAllocation

\brief    Property allocation vor view


\date     $Date: 2006/03/12 19:13:46,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PropAllocation_HPP
#define   PropAllocation_HPP

class     PropAllocation;

class     DBFieldDef;
class     node;
#include  <cADT_Types.h>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  PropAllocation
{
protected  :         char                                         name[40];                                                  
protected  :         PropertyHandle                               source_pi;                                                 
protected  :         PropertyHandle                               target_pi;                                                 
protected  :         PropertyHandle                               source_inst;                                               
protected  :         ADT_Types                                    type;                                                      
protected  :         OperationHandle                              operation;                                                 
protected  :         logical                                      is_reference;                                              
protected  :         int32                                        size;                                                      
protected  :         char                                        *expression;                                                
protected  :         logical                                      transient;                                                 

public     :
                     char                                        *get_name() { return(name); }
                     PropertyHandle                              &get_source_pi() { return(source_pi); }
                     PropertyHandle                              &get_target_pi() { return(target_pi); }
                     ADT_Types                                    get_type() { return(type); }
                     OperationHandle                             &get_operation() { return(operation); }
                     logical                                      get_is_reference() { return(is_reference); }
                     int32                                        get_size() { return(size); }
                     char                                        *get_expression() { return(expression); }
public     :                                     logical Get ( );
public     :                                     DBFieldDef *GetSourceFieldDef ( );
public     :                                                             PropAllocation (node *source_node, node *target_node, char *prop_name, char *source_path, ADT_Types source_type=ADT_PropertyPath, int32 size_w=UNDEF );
public     :                                     logical Put ( );
public     :                                     logical SetTarget (node *nodeptr );
public     :                                                             ~PropAllocation ( );
};

#pragma pack()
#endif
