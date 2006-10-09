/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    eb_MainBase

\brief    


\date     $Date: 2006/03/12 19:14:15,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   eb_MainBase_HPP
#define   eb_MainBase_HPP

class     eb_MainBase;

#ifndef   INTERVAL_short_HPP
#define   INTERVAL_short_HPP
#include  <sINTERVAL.h>
#endif
class     EBRootBase;
class     EB_Header;
class     acb;
class     eb_ClusterPool;
class     eb_DataArea;
class     srt;
#include  <sEBI.hpp>
#include  <sEB_MBHeader.hpp>
#include  <sEB_Number.hpp>
#include  <sRessourceLock.hpp>
#include  <seb_MainBase.hpp>
#include  <seb_SubBase.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  eb_MainBase
{
protected  :         RessourceLock                                mb_lock;                                                   
protected  :         EB_MBHeader                                 *mb_header;                                                 //
protected  :         int16                                        mb_number;                                                 //
protected  :         eb_SubBase                                  *sub_bases;                                                 //
protected  :         int16                                        number_sb;                                                 //
protected  :         eb_ClusterPool                              *cluster_pool;                                              //
protected  :         logical                                      sys_application;                                           //
protected  :         logical                                      mb_outopt;                                                 //
protected  :         logical                                      mb_netopt;                                                 
protected  :         logical                                      pif;                                                       

public     :
                     RessourceLock                               &get_mb_lock() { return(mb_lock); }
                     EB_MBHeader                                 *get_mb_header() { return(mb_header); }
                     int16                                        get_mb_number() { return(mb_number); }
                     eb_SubBase                                  *get_sub_bases() { return(sub_bases); }
                     int16                                        get_number_sb() { return(number_sb); }
                     eb_ClusterPool                              *get_cluster_pool() { return(cluster_pool); }
                     logical                                      get_sys_application() { return(sys_application); }
                     logical                                      get_mb_netopt() { return(mb_netopt); }
                     logical                                      get_pif() { return(pif); }
public     :                                     logical Add (acb *acbptr );
public     :                                     logical Append (acb *acbptr );
public     :                                     logical CheckEBI (acb *acbptr );
public     :                                     uint8 Check_WProtect (acb *acbptr );
public     :                                     logical ClearEBI (acb *acbptr );
public     :                                     logical Close ( );
public     :                                     logical Copy (eb_MainBase *sourcemain, logical consol_appl );
public     :                                     logical CopyPrevious (eb_MainBase *sourcemain, acb *acbptr, int64 previous );
public     :                                     EB_Number Create (uint16 sbnumber, EB_Number clnumb, uint16 version_nr=CUR_VERSION );
public     :                                     EB_Number Create (acb *acbptr );
public     :                                     logical CreateNewVersion (acb *acbptr, int32 entlen, uint16 version_nr=CUR_VERSION );
public     :                                     logical Delete (acb *acbptr );
public     :                                     logical DeleteVersion (acb *acbptr, uint16 version_nr=CUR_VERSION );
public     :                                     logical ExistEBI (acb *acbptr );
public     :                                     logical Flush ( );
public     :                                     logical FlushCluster (acb *acbptr );
public     :                                     logical FlushClusterPool ( );
public     :                                     int16 GetDataVersion ( );
public     :                                     logical GetEBI (acb *acbptr, logical real=NO );
public     :                                     EB_Number GetNewEBNumber ( );
public     :                                     EB_Number GetNextEBNumber (EB_Number entnr );
public     :                                     logical GetPrevInstance (acb *acbptr, uint16 version_nr=CUR_VERSION );
public     :                                     eb_SubBase *GetSubBase (int32 indx0 );
public     :                                     int32 GetVersionNumber (acb *acbptr );
public     :                                     int32 Get_Length (acb *acbptr );
public     :                                     uint16 Get_Mod (acb *acbptr );
public     :                                     logical InitHeader (uint16 sbnumber, EB_Header *pheader, char *filename );
public     :                                     void *Locate (acb *acbptr, int32 entlen );
public     :                                     logical Lock (acb *acbptr, logical wait );
public     :                                     logical LockInternal (acb *acbptr, logical wait );
public     :                                     EB_Number MBNtoRBN (EB_Number entnr );
public     :                                     logical Open (EB_MBHeader *mbheader, char *path, logical outopt, logical netopt, char sysenv=NO, logical pif_opt=NO );
public     :                                     logical OpenTemp (int16 mbnumber, logical pif_opt=NO );
public     :                                     logical PrintMessage (acb *acbptr );
public     :                                     logical PutEBI (acb *acbptr );
public     :                                     EB_Number RBNtoMBN (EB_Number entnr );
public     :                                     logical ReleaseCluster (acb *acbptr );
public     :                                     logical Remove (acb *acbptr );
public     :                                     logical Reserve (acb *acbptr, logical wait );
public     :                                     logical ResetSize (int32 sb_number );
public     :                                     logical SaveBuffer ( );
public     :                                     logical SetNetOpt (logical netopt );
public     :                                     logical TraceLock (acb *acbptr, logical lock_opt );
public     :                                     logical Undelete (acb *acbptr );
public     :                                     logical Unlock (acb *acbptr );
public     :                                     logical UnlockInternal (acb *acbptr );
public     :                                     logical Update (acb *acbptr, int32 entlen, int32 offset );
public     :                                     logical UseCluster (acb *acbptr );
public     :                                     logical ValidateEBI (EBI *ebiptr );
public     :                                     logical Version1 ( );
public     :                                     logical Version2 ( );
public     :                                     logical Version3 ( );
public     :                                     logical VersionCheck ( );
public     :                                     uint64 WriteInitial (EBRootBase *rbentry, int32 length );
public     :                                                             eb_MainBase ( );
public     :                                     logical ebscdel (acb *acbptr );
public     :                                     logical ebseupd (acb *acbptr, int32 entlen, int32 offset );
public     :                                     logical ebsprv (acb *acbptr, logical real=NO );
public     :                                     void ebstwerr ( );
public     :                                     eb_MainBase &operator= (eb_MainBase &rmainbase );
public     :                                                             ~eb_MainBase ( );
public     :                                     eb_DataArea *GetDataArea0 ( ){

  return (sub_bases->get_data_areas());

}

public     :                                     logical IsOpened ( ){


  return ( number_sb ? YES : NO );
}

};

#pragma pack()
#endif
