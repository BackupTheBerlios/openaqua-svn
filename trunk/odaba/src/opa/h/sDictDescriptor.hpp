/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DictDescriptor

\brief    


\date     $Date: 2006/03/12 19:13:07,75 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DictDescriptor_HPP
#define   DictDescriptor_HPP

class     DictDescriptor;

#ifndef   DLL_SC_Dictionary_HPP
#define   DLL_SC_Dictionary_HPP
#include  <sSC_Dictionary.hpp>
#include  <sDLL.h>
#endif
#include  <cPIACC.h>
#pragma pack(8)

class  DictDescriptor
{
protected  :         char                                         path[256];                                                 
protected  :         DictionaryHandle                             dicthdl;                                                   
protected  :         DLL(SC_Dictionary)                           dict_clients;                                              
protected  :         uint16                                       version;                                                   
protected  :         PIACC                                        access_mode;                                               

public     :
                     char                                        *get_path() { return(path); }
                     DictionaryHandle                            &get_dicthdl() { return(dicthdl); }
                     DLL(SC_Dictionary)                          &get_dict_clients() { return(dict_clients); }
                     uint16                                       get_version() { return(version); }
                     PIACC                                        get_access_mode() { return(access_mode); }
public     :                                                             DictDescriptor ( );
public     :                                                             DictDescriptor (char *cpath, PIACC accopt, uint16 version_nr=CUR_VERSION );
public     :                                                             ~DictDescriptor ( );
};

#pragma pack()
#endif
