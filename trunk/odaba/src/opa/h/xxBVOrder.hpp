/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBVOrder

\brief    Order defintion for a view collection


\date     $Date: 2006/03/12 19:13:05,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBVOrder_HPP
#define   DBVOrder_HPP

class     DBVOrder;

class     node;
#pragma pack(8)

class  DBVOrder
{
protected  :         char                                        *prop_path;                                                 // Property path
protected  :         char                                         sort_key[40];                                              // Sort key name

public     :
                     char                                        *get_prop_path() { return(prop_path); }
                     char                                        *get_sort_key() { return(sort_key); }
public     :                                                             DBVOrder (char *property_path, char *sort_key_name );
public     :                                     logical SetOrder (node *nodeptr );
public     :                                                             ~DBVOrder ( );
};

#pragma pack()
#endif
