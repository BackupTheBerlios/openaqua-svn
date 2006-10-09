/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstanceDescriptor

\brief    


\date     $Date: 2006/03/12 19:13:25,67 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   InstanceDescriptor_HPP
#define   InstanceDescriptor_HPP

class     InstanceDescriptor;

class     InstanceDescriptor;
class     acb;
class     eb_RootBase;
class     ieh;
#include  <sEBI.hpp>
#include  <sEB_Number.hpp>
#pragma pack(8)

class  InstanceDescriptor
{
protected  :         EBI                                          ebi;                                                       
protected  :         ieh                                         *ext_inst;                                                  
protected  :         InstanceDescriptor                          *prev_version;                                              
protected  :         EB_Number                                    cluster_number;                                            

public     :
                     EBI                                         &get_ebi() { return(ebi); }
                     ieh                                         *get_ext_inst() { return(ext_inst); }
                     InstanceDescriptor                          *get_prev_version() { return(prev_version); }
                     EB_Number                                   &get_cluster_number() { return(cluster_number); }
public     :                                     int32 GetLength ( );
public     :                                     InstanceDescriptor *GetOldInstance (eb_RootBase *erootbase, acb *acbptr );
public     :                                     InstanceDescriptor *GetVersionInst (uint16 version_nr=CUR_VERSION );
public     :                                     void Initialize (acb *acbptr );
public     :                                                             InstanceDescriptor ( );
public     :                                     void *Locate (acb *acbptr, int32 entlen, logical pif );
public     :                                     ieh *SetArea (ieh *iehptr );
public     :                                                             ~InstanceDescriptor ( );
};

#pragma pack()
#endif
