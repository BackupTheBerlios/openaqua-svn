/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    LDictionary

\brief    Dictionary
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/04/09 19:48:17,98 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   LDictionary_HPP
#define   LDictionary_HPP

class     LDictionary;

#define  STRING_EXPR                               local_expression
#define  TEMP_MAIN                                 254
class     ACObject;
class     DBHandle;
class     LDictionary;
class     SDB_Attribute;
class     SDB_BaseStruct;
class     SDB_Key;
class     SDB_Reference;
class     SDB_Relationship;
#include  <cPIACC.h>
#include  <sDictionary.hpp>
#include  <sLDBHandle.hpp>
#pragma pack(8)

class  LDictionary :public Dictionary,
public LDBHandle
{

public     :
public     : virtual OPAImpExp                   DBHandle *CreateDBHandle (char *cpath, PIACC accopt, logical netopt, uint16 version_nr=CUR_VERSION, char sysenv=NO );
public     : virtual OPAImpExp                   DBHandle *CreateDBHandle ( );
public     : virtual OPAImpExp                   DBHandle *CreateDBHandle (char *cpath, int32 dasize=0 );
public     : virtual OPAImpExp                   DBExtend *CreateExtentDef (TypeKey &tkey );
public     : virtual OPAImpExp                   DBStructDef *CreateStructDef (TypeKey &tkey, DBStructDef *strdef );
public     : static  OPAImpExp                   logical __cdecl DictDisplay (char *cpath, char *ppath );
public     : virtual                             int16 GetLastStructureID ( );
public     : virtual                             LDictionary *GetLocalDictionary ( );
public     : virtual                             ACObject *GetOBHandle (uint16 version_nr=CUR_VERSION );
public     :                                                             LDictionary (char *cpath, PIACC accopt, logical w_netopt=NO, uint16 version_nr=CUR_VERSION, char sysenv=NO, logical is_server=NO );
public     :                                                             LDictionary ( );
public     :                                                             LDictionary (DBHandle *dbhandle );
public     :                                     logical SaveExtList ( );
public     : virtual                             logical UpdateVersion ( );
public     : virtual                                                     ~LDictionary ( );
};

#pragma pack()
#endif
