/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    StructDef

\brief    Internal ODABA2 type definition
          Based   on   this   class   ODABA2   type   definitions   (see {\b {.r
          DBStructDef}})  are provided in the  main storage dictionary. The case
          class  {\b {.r smcb}} provides basic information about a data type and
          its structure.
          The  class itself has no information or functionallity of interest for
          an ODABA2 application programer.

\date     $Date: 2006/04/13 12:38:29,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   StructDef_HPP
#define   StructDef_HPP

class     StructDef;

class     DBStructDef;
class     Dictionary;
#include  <cSDB_ST.h>
#include  <cTYP_TYPES.h>
#include  <sTypeKey.hpp>
#include  <sacc.hpp>
#include  <ssmcb.hpp>
#pragma pack(8)

class  StructDef :public acc,
public smcb
{

public     :
public     :                                     DBStructDef *GetDBStruct ( );
public     :                                     logical Setup (Dictionary *dictionary );
public     :                                                             StructDef (char *strname, int32 nsid, int16 strsid, int32 intlen, TYP_TYPES metatype, SDB_ST strtype );
public     : virtual                                                     ~StructDef ( );
};

#pragma pack()
#endif
