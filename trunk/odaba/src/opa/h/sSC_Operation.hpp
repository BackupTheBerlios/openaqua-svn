/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    SC_Operation

\brief    Server operation
          This  class  runs  an  operation  on  the  server side and returns the
          result.

\date     $Date: 2006/03/12 19:13:50,40 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_Operation_HPP
#define   SC_Operation_HPP

class     SC_Operation;

class     CSInstanceList;
class     ParmList;
#include  <sOperation.hpp>
#include  <sSC_Handle.hpp>
#include  <sSC_Property.hpp>
#pragma pack(8)

class  SC_Operation :public SC_Handle,
public Operation
{
protected  :         SC_Property                                 *calling_property ATTR_ALIGN(4);                            

public     :
                     SC_Property                                 *get_calling_property() { return(calling_property); }
public     :                                     logical Close ( );
public     :                                     logical Execute (ParmList *parmlist );
public     :                                     void FillResult (CSInstanceList *result, logical term );
public     :                                     void ForceClose ( );
public     : virtual                             char *GetName ( );
public     : virtual                             char *GetTypeName ( );
public     :                                     logical ProvideExpression (char *expression );
public     :                                     logical ReopenProperty (char *expression, logical own_opt );
public     :                                                             SC_Operation (SC_Property *sc_property, int64 client_handle );
public     : virtual                                                     ~SC_Operation ( );
};

#pragma pack()
#endif
