/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBViewGroup

\brief    GroupBy Clause
          A  group  clause  consists  either  of an expression defining the view
          value  domain  or  an  explicite  domain  definition  by  using  case 
          expressions,  i.e.  assigning  the  first  value  from  a  list, which
          returns true for the case condition.

\date     $Date: 2006/03/12 19:13:06,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBViewGroup_HPP
#define   DBViewGroup_HPP

class     DBViewGroup;

#ifndef   DPA_DBViewGroupCase_HPP
#define   DPA_DBViewGroupCase_HPP
#include  <sDBViewGroupCase.hpp>
#include  <sDPA.h>
#endif
class     PropertyHandle;
class  DBViewGroup
{
protected  :         DBStructDef                                 *struct_def;                                                
protected  :         char                                        *source;                                                    // Grouping domain
protected  :         DPA(DBViewGroupCase)                         case_list;                                                 // Case list

public     :
                     char                                        *get_source() { return(source); }
                     DPA(DBViewGroupCase)                        &get_case_list() { return(case_list); }
public     :                                                             DBViewGroup (DBStructDef *strdef, PropertyHandle *vl_ph );
public     :                                                             DBViewGroup (DBStructDef *strdef, BNFData *bnf_data );
public     :                                                             DBViewGroup (DBStructDef *strdef );
public     :                                     logical Initialize (BNFData *bnf_data );
public     :                                     logical Initialize (PropertyHandle *vl_ph );
public     :                                                             ~DBViewGroup ( );
};

#endif
