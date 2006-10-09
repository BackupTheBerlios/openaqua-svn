/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    eb_ClusterPool

\brief    


\date     $Date: 2006/03/12 19:14:14,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   eb_ClusterPool_HPP
#define   eb_ClusterPool_HPP

class     eb_ClusterPool;

#ifndef   GSRT_CPE_HPP
#define   GSRT_CPE_HPP
#include  <sCPE.hpp>
#include  <sGSRT.h>
#endif
class     CPE;
class     EBI;
class     acb;
class     eb_MainBase;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  eb_ClusterPool :public GSRT(CPE)
{
protected  :         eb_MainBase                                 *mb_handle ATTR_ALIGN(4);                                   

public     :
                     eb_MainBase                                 *get_mb_handle() { return(mb_handle); }
public     :                                     logical AddClusterEntry (acb *acbptr );
public     :                                     logical Clear ( );
public     :                                     logical DelClusterEntry (acb *acbptr );
public     :                                     logical Flush ( );
public     :                                     logical FlushCluster (acb *acbptr );
public     :                                     CPE *GetCluster (acb *acbptr );
public     :                                     int32 GetClusterEntry (acb *acbptr, int32 entlen );
public     :                                     int32 GetEntryLength (acb *acbptr );
public     :                                     logical PutClusterEntry (acb *acbptr, int32 entlen, int32 offset );
public     :                                     logical ReleaseCluster (acb *acbptr );
public     :                                     void SetMainBase (eb_MainBase *mainbase );
public     :                                     logical UseCluster (acb *acbptr );
public     :                                                             eb_ClusterPool (eb_MainBase *mbhandle );
public     :                                                             ~eb_ClusterPool ( );
};

#pragma pack()
#endif
