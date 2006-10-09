/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FieldSource

\brief    


\date     $Date: 2006/03/12 19:13:22,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FieldSource_HPP
#define   FieldSource_HPP

class     FieldSource;

#include  <sExpressionReference.hpp>
#include  <sFieldSource.hpp>
class  FieldSource :public ExpressionReference
{
protected  :         char                                         order[41];                                                 

public     :
                     char                                        *get_order() { return(order); }
public     :                                                             FieldSource (char *expression, char *key_name );
public     :                                                             FieldSource (FieldSource &fld_source_ref );
public     :                                                             FieldSource ( );
public     :                                     char *GetOrder ( );
};

#endif
