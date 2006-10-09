/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    IFFunction

\brief    


\date     $Date: 2006/03/12 19:13:24,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   IFFunction_HPP
#define   IFFunction_HPP

class     IFFunction;

class     CSInstanceList;
class     CS_Connection;
#pragma pack(8)

class  IFFunction
{
protected  :         CS_FCTP                                      function_ptr;                                              

public     :
public     :         opa7ImpExp                  logical Execute (CS_Connection *connection, void *cso_ptr, CSInstanceList *cparms, CSInstanceList *result );
public     :         opa7ImpExp                                          IFFunction (CS_FCTP cs_execute );
};

#pragma pack()
#endif
