/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstancePool

\brief    


\date     $Date: 2006/03/12 19:13:26,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   InstancePool_HPP
#define   InstancePool_HPP

class     InstancePool;

class     EBI;
class     ObjectEntryList;
class     acb;
class     eb_RootBase;
class     ieh;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  InstancePool
{
protected  :         uint32                                       max_size;                                                  //
protected  :         uint32                                       used_size;                                                 //
protected  :         eb_RootBase                                 *root_base;                                                 //
protected  :         acb                                         *work_acb;                                                  //
protected  :         uint32                                       max_inst_size;                                             //
protected  :         ObjectEntryList                             *object_entries;                                            //

public     :
                     uint32                                       get_max_size() { return(max_size); }
                     uint32                                       get_used_size() { return(used_size); }
                     eb_RootBase                                 *get_root_base() { return(root_base); }
                     acb                                         *get_work_acb() { return(work_acb); }
                     uint32                                       get_max_inst_size() { return(max_inst_size); }
public     :                                     ieh *CreateInstance (ieh *iehptr, ieh *oldieh, logical no_data );
public     :                                                             InstancePool (ObjectEntryList *object_list, uint32 maxi_size=100*1024*1024 );
public     :                                     logical RemoveInstance (ieh *iehptr );
public     :                                     logical StoreInstance (EB_Number entnr, EBI *ebiptr, ieh *iehptr, int32 cluster_number );
public     :                                     logical UpdateInstance (ieh *oldieh, char newieh );
public     :                                                             ~InstancePool ( );
};

#pragma pack()
#endif
