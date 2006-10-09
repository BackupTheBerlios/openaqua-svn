/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBVFilter

\brief    Filter definition for the view


\date     $Date: 2006/03/12 19:13:04,96 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBVFilter_HPP
#define   DBVFilter_HPP

class     DBVFilter;

#pragma pack(8)

class  DBVFilter
{
protected  :         char                                        *prop_path;                                                 // Property path
protected  :         char                                        *expression;                                                // Filter expression

public     :
                     char                                        *get_prop_path() { return(prop_path); }
                     char                                        *get_expression() { return(expression); }
public     :                                                             DBVFilter (char *property_path, char *expression );
public     :                                     logical SetFilter (node *nodeptr );
public     :                                                             ~DBVFilter ( );
};

#pragma pack()
#endif
