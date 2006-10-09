/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ODE_Helper



\date     $Date: 2006/05/23 13:52:46,40 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODE_Helper_HPP
#define   ODE_Helper_HPP

class     ODE_Helper;

class     BNFData;
class     ODE_Project;
class     PropertyHandle;
class     pc1_ODC_ImpClass;
#include  <sDictionaryHandle.hpp>
class  ODE_Helper
{
protected  :         DictionaryHandle                             dictionary;                                                
protected  :         ODE_Project                                 *projects;                                                  

public     :
                     DictionaryHandle                            &get_dictionary() { return(dictionary); }
                     ODE_Project                                 *get_projects() { return(projects); }
public     :                                        void Deinitialize ( );
public     :                                        PropertyHandle *GetAccPathType (TypeKey &type_key, BNFData *bdata, char &lookup_type );
public     :                                        PropertyHandle *GetListHandle (TypeKey &type_key, BNFData *bdata, char &lookup_type );
public     :                                        PropertyHandle *GetListHandle (TypeKey &type_key, char *accpath, char &lookup_type );
public     :                                        PropertyHandle *GetMember (PropertyHandle *class_ph, char *memnames, char search_type );
public     : static                                 char *__cdecl GetPath (char *codestring, int32 textpos, char &lookup_type );
public     :                                        PropertyHandle *GetTargetClass (TypeKey &type_key, char *accpath, char &lookup_type );
public     :                                        PropertyHandle *GetTargetFunction (TypeKey &type_key, char *accpath, char &lookup_type );
public     :                                        logical Initialize (DictionaryHandle &dict_handle );
public     :                                        logical Initialize (ODE_Project *ode_project );
public     :                                             ODE_Helper ( );
public     :                                             ~ODE_Helper ( );
};

#endif
