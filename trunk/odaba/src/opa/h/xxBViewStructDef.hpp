/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBViewStructDef

\brief    


\date     $Date: 2006/03/12 19:13:06,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBViewStructDef_HPP
#define   DBViewStructDef_HPP

class     DBViewStructDef;

#ifndef   DLL_DBViewPath_HPP
#define   DLL_DBViewPath_HPP
#include  <sDBViewPath.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_char_HPP
#define   DLL_char_HPP
#include  <sDLL.h>
#endif
class     BNFData;
class     DBViewGroup;
class     Dictionary;
class     ODC_View;
#include  <sDBStructDef.hpp>
class  DBViewStructDef
{
protected  :         DBStructDef                                 *struct_def;                                                //
protected  :         DLL(DBViewPath)                              from;                                                      //
protected  :         char                                        *where;                                                     //
protected  :         char                                        *having;                                                    //
protected  :         DBViewGroup                                 *group_by;                                                  //

public     :
                     DLL(DBViewPath)                             &get_from() { return(from); }
                     char                                        *get_where() { return(where); }
                     char                                        *get_having() { return(having); }
public     :                                                             DBViewStructDef (DBStructDef *strdef, PropertyHandle &ph );
public     :                                                             DBViewStructDef (DBStructDef *strdef, BNFData *bnf_data );
public     :                                                             DBViewStructDef (DBStructDef *strdef );
public     :                                     logical Initialize (PropertyHandle &ph );
public     :                                     logical Initialize (BNFData *bnf_data );
public     :                                                             ~DBViewStructDef ( );
};

#endif
