/********************************* Class Declaration ***************************/
/**
\package  OPI - 
\class    DictionaryHandle

\brief    Dictionary Handle
          The  dictionary handle  is used  for providing schema definitions from
          the  dictionary.  The  dictionary  creates  internal  images  from the
          externally  stored schema definitions. These  internal images ({\b {.r
          DBStructDef}}) can be provided by means of dictionary functions.  
          Because  the dictionary  is a  database handle  {\b {.r DBHandle}} you
          can access schema information also directly via PI functions.

\date     $Date: 2006/06/25 17:15:35,48 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DictionaryHandle_HPP
#define   DictionaryHandle_HPP
#include "copadll.h"

class     DictionaryHandle;

class     BNFData;
class     BNFParser;
class     DBExtend;
class     DBFieldDef;
class     DBObjectHandle;
class     DBStructDef;
class     Dictionary;
#include  <cPIACC.h>
#include  <cPIREPL.h>
#include  <cResourceTypes.h>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODABAClient.hpp>
#pragma pack(8)

class  DictionaryHandle :public DatabaseHandle
{

public     :
public     :                  OPIImpExp             int32 BaseType (char *strnames );
public     :                  OPIImpExp             logical CheckExpression (char *expression, DBObjectHandle &dbobj_handle, char *clsnames );
public     :                  OPIImpExp             logical CheckExpression (DBObjectHandle &resobj, char *clsnames, char *exprnames, char *implnames );
public     :                  OPIImpExp             logical CheckExtentDef (char *extname, int32 namespace_id );
public     :                  OPIImpExp             logical CheckExtentDef (char *scoped_name );
public     :                  OPIImpExp             logical CheckValueSet (char *extname, int32 namespace_id );
public     :                  OPIImpExp             logical CheckValueSet (char *scoped_name );
public     :                  OPIImpExp             logical Close ( );
public     :                  OPIImpExp             logical CopyCodeset (DictionaryHandle &srce_dicthandle, char *strname, int32 namespace_id, char *newnames=NULL, PIREPL db_replace=REPL_none, logical retainSID=NO, logical retain_schemav=NO );
public     :                  OPIImpExp             logical CopyExtentDef (DictionaryHandle &srce_dicthandle, char *extentname, char *newnames=NULL, char *targ_struct=NULL, logical transaction=NO, logical retain_schemav=NO );
public     :                  OPIImpExp             logical CopyStructure (DictionaryHandle &srce_dicthandle, char *strname, int32 namespace_id, char *newnames=NULL, char *topname=NULL, PIREPL db_replace=REPL_none, logical retainSID=NO, logical retain_schemav=NO );
public     :                  OPIImpExp             logical CopyType (DictionaryHandle &srce_dicthandle, char *strnames, char *newnames=NULL, char *topname=NULL, PIREPL db_replace=REPL_none, logical retainSID=NO, logical transaction=NO, logical retain_schemav=NO );
public     :                  OPIImpExp             logical CreateEnum (char *enum_name, char *basetype );
public     :                  OPIImpExp             PropertyHandle *CreateGlobalVariable (PropertyHandle &prophdl, char *var_name );
public     :                  OPIImpExp             BNFParser *CreateParser ( );
public     :                  OPIImpExp             char *CreateTempExtent (char *strnames, char *extnames_w=NULL, char *key_name_w=NULL, char *baseexts_w=NULL, logical weak_opt_w=NO, logical own_opt_w=NO );
public     :                  OPIImpExp             char *CreateTempExtent (DBFieldDef *field_def, char *extnames_w=NULL );
public     :                  OPIImpExp             logical DeleteEnum (char *enum_name );
public     :                  OPIImpExp                  DictionaryHandle (ODABAClient &odaba_client, char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic, logical sysenv=NO );
public     :                  OPIImpExp                  DictionaryHandle ( );
public     :                  OPIImpExp                  DictionaryHandle (Dictionary *_dictionary );
public     :                  OPIImpExp                  DictionaryHandle (const DictionaryHandle &dictionary_refc );
public     :                  OPIImpExp                  DictionaryHandle (DatabaseHandle &db_handle );
public     :                  OPIImpExp             char *EnumToString (char *enumeration, int32 enum_val, char *string, int32 len );
public     :                  OPIImpExp             char *EnumToString (char *enumeration, PropertyHandle &ph, char *string, int32 len );
public     :                  OPIImpExp             DBExtend *GetExtentDef (char *extname, int32 namespace_id );
public     :                  OPIImpExp             DBExtend *GetExtentDef (char *scoped_name );
public     :                  OPIImpExp             PropertyHandle *GetGlobalVariable (char *var_name );
public     :                  OPIImpExp             int16 GetID_SIZE ( );
public     :                                        uint16 GetLastSchemaVersion ( );
public     :                  OPIImpExp             DBStructDef *GetStructDef (char *strnames );
public     :                  OPIImpExp             char *GetTempName (char *extnames );
public     :                  OPIImpExp             logical IsBasicType (char *typenames );
public     :                  OPIImpExp             DBExtend *LocateExtentDef (char *extname, int32 namespace_id );
public     :                  OPIImpExp             DBExtend *LocateExtentDef (char *scoped_name );
public     :                  OPIImpExp             logical Open (ODABAClient &odaba_client, char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic, logical sysenv=NO );
public     :                  OPIImpExp             logical Open (DatabaseHandle &db_handle );
public     :                  OPIImpExp             logical OpenDictionary (ODABAClient &odaba_client, char *cpath, PIACC accopt, logical w_netopt, uint16 version_nr=CUR_VERSION, ResourceTypes local_ressources=RES_automatic, logical sysenv=NO );
public     :                  OPIImpExp             BNFData *ParseExpression (char *expression, char *symbol=NULL );
public     :                  OPIImpExp             BNFData *ParseFile (char *cpath, char *symbol=NULL );
public     :                  OPIImpExp             DBExtend *ProvideExtentDef (char *scoped_name );
public     :                  OPIImpExp             DBExtend *ProvideExtentDef (char *extnames, int32 namespace_id );
public     :                  OPIImpExp             DBStructDef *ProvideStructureDef (char *scoped_name );
public     :                  OPIImpExp             DBStructDef *ProvideStructureDef (char *strnames, int32 namespace_id );
public     :                                        void SetLastSchemaVersion (uint16 schema_version );
public     :                  OPIImpExp             int32 StringToEnum (char *enumeration, char *enum_string );
public     :                  OPIImpExp             int32 StringToEnum (char *enumeration, PropertyHandle &ph );
public     :                                        logical UpdateVersion ( );
public     :                                        Dictionary *get_dictionary ( );
public     :                  OPIImpExp             NOTYPE operator bool ( ) const;
public     :                                        Dictionary *operator-> ( );
public     :                  OPIImpExp             DictionaryHandle &operator= (const DictionaryHandle &dictionary_refc );
public     :                  OPIImpExp             logical operator== (const DictionaryHandle &dictionary_refc );
public     :                  OPIImpExp                  ~DictionaryHandle ( );
};

#pragma pack()
#endif
