/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    IFClass

\brief    


\date     $Date: 2006/03/12 19:13:24,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   IFClass_HPP
#define   IFClass_HPP

class     IFClass;

class     CSInstanceList;
class     CS_Connection;
class     IFFunction;
class     SC_Handle;
#pragma pack(8)

class  IFClass
{
protected  :         IFFunction                                  *function_table;                                            
protected  :         int16                                        function_count;                                            

public     :
                     IFFunction                                  *get_function_table() { return(function_table); }
public     :         opa7ImpExp                  logical Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Connection *connection, void *cso_ptr, CSInstanceList *cparms, CSInstanceList *result );
public     :         opa7ImpExp                                          IFClass (IFFunction *if_fct_table, int16 if_fct_count );
};

#pragma pack()
#endif
