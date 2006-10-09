/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    CDictionary

\brief    Dictionary
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/07/24 18:36:24,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CDictionary_HPP
#define   CDictionary_HPP

class     CDictionary;

#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
class     CClient;
class     CDictionary;
class     DBExtend;
class     DBFieldDef;
class     DBHandle;
class     DBResource;
class     DBStructDef;
class     DataSourceHandle;
class     ODABAClient;
class     TypeKey;
class     kcb;
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <cResourceTypes.h>
#include  <sCDBHandle.hpp>
#include  <sDictionary.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  CDictionary :public CDBHandle,
public Dictionary
{

public     :
public     :                                             CDictionary (CClient *odaba_client, char *cpath, PIACC accopt, logical w_netopt=NO, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic, char sysenv=NO );
public     :                                             CDictionary ( );
public     :                                             CDictionary (DBHandle *dbhandle );
public     : virtual                                void CloseDictionary ( );
public     : virtual                                logical CreateEnum (char *enum_name, char *basetype );
public     : virtual                                DBExtend *CreateExtentDef (TypeKey &tkey );
public     : virtual                                DBStructDef *CreateStructDef (TypeKey &tkey, DBStructDef *strdef );
public     : virtual                                char *CreateTempExtent (char *strnames, char *extnames_w=NULL, char *key_name_w=NULL, char *baseexts_w=NULL, logical weak_opt_w=NO, logical own_opt_w=NO );
public     : virtual                                char *CreateTempExtent (DBFieldDef *field_def, char *extnames_w=NULL );
public     :                  OPAImpExp             logical DeleteEnum (char *enum_name );
public     : virtual                                CDictionary *GetClientDictionary ( );
public     : virtual          OPAImpExp             char *GetTempName (char *extnames );
public     :                                        DBExtend *SetupDBExtent (int32 &rindx0 );
public     :                                        DBExtend *SetupDBExtent ( );
public     :                                        logical SetupDBFieldDef (DBFieldDef *fielddef, int32 &rindx0 );
public     :                                        logical SetupDBIndex (DBFieldDef *fielddef, int32 &rindx0 );
public     :                                        logical SetupDBKeyComponent (kcb *kcbptr, int32 &rindx0 );
public     :                                        logical SetupDBKeyDef (DBStructDef *strdef, int32 &rindx0 );
public     :                                        logical SetupDBResource (DBResource *dbresource, int32 &rindx0 );
public     :                                        DBStructDef *SetupDBStructDef (TypeKey &tkey, DBStructDef *strdef );
public     :                                        DBStructDef *SetupDBStructDef (TypeKey &tkey, DBStructDef *strdef, int32 &rindx0 );
public     :                                        logical SetupDBValue (ENUM_Value *csentry, int32 &rindx0 );
public     : virtual                                     ~CDictionary ( );
};

#pragma pack()
#endif
