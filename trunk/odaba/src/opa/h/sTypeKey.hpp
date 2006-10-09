/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    TypeKey

\brief    


\date     $Date: 2006/08/24 20:21:01,67 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TypeKey_HPP
#define   TypeKey_HPP

class     TypeKey;

#define  TYPEKEY                                   sizeof(TypeKey)
class     DBHandle;
class     Dictionary;
#include  <sInstance.hpp>
#include  <sKeyClass.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
class  TypeKey
{
public     :         char                                         sys_ident[40];                                             // 
public     :         int32                                        namespace_id;                                              // 

public     :
public     :                                        logical Exact ( );
public     :                                        int32 GetID ( );
public     :                  OPAImpExp             Key GetKey ( );
public     : static           OPAImpExp             char *__cdecl GetScopeName (char *scoped_name, char *string, uint16 len );
public     :                                        char *InitPropertyType (Dictionary *dictptr, char *scoped_name );
public     :                  OPAImpExp             logical Initialize (Dictionary *dictptr, char *scoped_name );
public     :                  OPAImpExp             logical Initialize (char *typenames, int32 nsid );
public     :                  OPAImpExp             logical Initialize (Dictionary *dictptr, char *scope_name, char *strnames );
public     :                  OPAImpExp             logical Initialize (DictionaryHandle &dicthdl_ref, char *scoped_name );
public     :                  OPAImpExp             logical Initialize (DictionaryHandle &dicthdl_ref, char *scope_name, char *strnames );
public     :                  OPAImpExp             logical Initialize (DatabaseHandle &res_dbhandle, char *scoped_name );
public     :                  OPAImpExp             logical Initialize (DatabaseHandle &res_dbhandle, char *scope_name, char *strnames );
public     :                                        logical Initialize_intern (Dictionary *dictptr, DBHandle *dbhandle, char *scoped_name );
public     :                                        logical Initialize_intern (Dictionary *dictptr, DBHandle *dbhandle, char *scope_name, char *strnames );
public     :                  OPAImpExp             logical IsEmpty ( );
public     :                                        int32 LookUp (Dictionary *dictptr );
public     :                  OPAImpExp             char *Name ( );
public     :                  OPAImpExp             char *Scope (Dictionary *dictptr, char *string, int32 leng );
public     :                  OPAImpExp             char *Scope (DictionaryHandle dicthdl, char *string, int32 leng );
public     :                  OPAImpExp             char *Scope (DatabaseHandle &res_dbhandle, char *string, int32 &rlen );
public     :                  OPAImpExp             char *ScopedName (Dictionary *dictptr, char *string, int32 leng );
public     :                  OPAImpExp             char *ScopedName (DictionaryHandle &dicthdl_ref, char *string, int32 leng );
public     :                  OPAImpExp             char *ScopedName (DatabaseHandle &res_dbhandle, char *string, int32 leng );
public     :                  OPAImpExp             void SetName (char *typenames );
public     :                  OPAImpExp             void SetNamespace (int32 nsid );
public     :                  OPAImpExp                  TypeKey (Dictionary *dictptr, char *scoped_name );
public     :                  OPAImpExp                  TypeKey (char *typenames, int32 nsid );
public     :                  OPAImpExp                  TypeKey ( );
public     :                  OPAImpExp                  TypeKey (Dictionary *dictptr, char *scope_name, char *strnames );
public     :                  OPAImpExp                  TypeKey (DictionaryHandle &dicthdl_ref, char *scoped_name );
public     :                  OPAImpExp                  TypeKey (DictionaryHandle &dicthdl_ref, char *scope_name, char *strnames );
public     :                  OPAImpExp                  TypeKey (DatabaseHandle &res_dbhandle, char *scoped_name );
public     :                  OPAImpExp                  TypeKey (DatabaseHandle &res_dbhandle, char *scope_name, char *strnames );
public     :                  OPAImpExp             NOTYPE operator bool ( );
public     :                  OPAImpExp             NOTYPE operator char* ( );
public     :                  OPAImpExp             logical operator! ( );
public     :                  OPAImpExp             logical operator!= (char *strnames );
public     :                  OPAImpExp             logical operator!= (TypeKey &tk_ref );
public     :                  OPAImpExp             logical operator== (char *strnames );
public     :                  OPAImpExp             logical operator== (TypeKey &tk_ref );
};

#endif
