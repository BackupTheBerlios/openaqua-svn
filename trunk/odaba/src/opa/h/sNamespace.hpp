/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    Namespace



\date     $Date: 2006/05/14 11:52:53,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Namespace_HPP
#define   Namespace_HPP

class     Namespace;

#ifndef   DLL_Namespace_HPP
#define   DLL_Namespace_HPP
#include  <sNamespace.hpp>
#include  <sDLL.h>
#endif
class     Dictionary;
class     Namespace;
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTypeKey.hpp>
class  Namespace :public TypeKey
{
protected  :         Namespace                                   *parent;                                                    
protected  :         DLL(Namespace)                               children;                                                  
protected  :         int32                                        ns_id;                                                     
protected  :         PropertyHandle                               name_spaces;                                               
protected  :         Dictionary                                  *dict;                                                      
protected  :         logical                                      active;                                                    

public     :
                     Namespace                                   *get_parent() { return(parent); }
                     DLL(Namespace)                              &get_children() { return(children); }
                     int32                                        get_ns_id() { return(ns_id); }
                     PropertyHandle                              &get_name_spaces() { return(name_spaces); }
                     Dictionary                                  *get_dict() { return(dict); }
                     logical                                      get_active() { return(active); }
public     :                                        void CloseNamespace ( );
public     :                                        logical Fill (PropertyHandle &ph );
public     :                                        Namespace *Find (char *ns_name );
public     :                                        int32 GetNSID (char *scope_name );
public     :                                        char *GetScope (char *string, int32 &rlen );
public     :                                        logical GetScopeName (NString &nstring );
public     :                                        Namespace *Locate (char *scope_name );
public     :                                             Namespace (Dictionary *dictptr, Namespace *parent_ns, int32 nsid );
public     :                                             ~Namespace ( );
};

#endif
