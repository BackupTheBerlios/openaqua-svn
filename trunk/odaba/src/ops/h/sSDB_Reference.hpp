/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Reference

\brief    References
          References  are  used  to  describe any sort of reference collections.
          Thus,  the  reference  definition  is  the  base  for  defining  local
          collections (references or relationships) as well as extents.

\date     $Date: 2006/05/11 16:09:54,40 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Reference_HPP
#define   SDB_Reference_HPP

class     SDB_Reference;

#ifndef   P_SDB_CodeSet_HPP
#define   P_SDB_CodeSet_HPP
#include  <sPI.hpp>
class       SDB_CodeSet;
PI_dcl     (SDB_CodeSet)
#endif
#ifndef   P_SDB_Extend_HPP
#define   P_SDB_Extend_HPP
#include  <sPI.hpp>
class       SDB_Extend;
PI_dcl     (SDB_Extend)
#endif
#ifndef   P_SDB_Index_HPP
#define   P_SDB_Index_HPP
#include  <sPI.hpp>
class       SDB_Index;
PI_dcl     (SDB_Index)
#endif
#ifndef   P_SDB_InternalAct_HPP
#define   P_SDB_InternalAct_HPP
#include  <sPI.hpp>
class       SDB_InternalAct;
PI_dcl     (SDB_InternalAct)
#endif
#ifndef   P_SDB_NameSpace_HPP
#define   P_SDB_NameSpace_HPP
#include  <sPI.hpp>
class       SDB_NameSpace;
PI_dcl     (SDB_NameSpace)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#ifndef   P_SDB_ViewExtent_HPP
#define   P_SDB_ViewExtent_HPP
#include  <sPI.hpp>
class       SDB_ViewExtent;
PI_dcl     (SDB_ViewExtent)
#endif
class     DBFieldDef;
class     DBIndex;
class     SDB_Index;
#include  <cSDB_AT.h>
#include  <cTYP_TYPES.h>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_Property.hpp>
#include  <sSDB_Reference.hpp>
#pragma pack(8)

class  SDB_Reference :public SDB_Property
{
protected  :         logical                                      owning;                                                    // Owning collections
protected  :         logical                                      create;                                                    // Not allow creating new instances
protected  :         logical                                      clustered;                                                 // Build clustered instances
protected  :         logical                                      depend;                                                    
protected  :         int16                                        mb_number;                                                 // Mainbase number
protected  :         logical                                      week_typed;                                                // Weak typed collections
protected  :         logical                                      update;                                                    // Updateable reference
protected  :         logical                                      multikey;                                                  // Enable multiple index feature
protected  :         SDB_AT                                       ddeatyp;                                                   // Access type
protected  :         int32                                        namespace_id;                                              
protected  :         PI(SDB_Index)                                ddeindx;                                                   // Order keys
protected  :         PI(SDB_Extend)                               extent_ref;                                                
protected  :         PI(SDB_ViewExtent)                           view_extents;                                              
protected  :         PI(SDB_NameSpace)                            name_space;                                                

public     :
                     logical                                      get_owning() { return(owning); }
                     logical                                      get_create() { return(create); }
                     logical                                      get_clustered() { return(clustered); }
                     logical                                      get_depend() { return(depend); }
                     int16                                        get_mb_number() { return(mb_number); }
                     logical                                      get_week_typed() { return(week_typed); }
                     logical                                      get_update() { return(update); }
                     logical                                      get_multikey() { return(multikey); }
                     SDB_AT                                       get_ddeatyp() { return(ddeatyp); }
                     int32                                        get_namespace_id() { return(namespace_id); }
                     PI(SDB_Index)                               &get_ddeindx() { return(ddeindx); }
                     PI(SDB_Extend)                              &get_extent_ref() { return(extent_ref); }
                     PI(SDB_ViewExtent)                          &get_view_extents() { return(view_extents); }
                     PI(SDB_NameSpace)                           &get_name_space() { return(name_space); }
public     :                  OPSImpExp             logical Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes, uint16 dim );
public     :                                        logical GetAlignInfo (char *propname, int16 &size_info, int16 &offset_info );
public     :                  OPSImpExp             logical Initialize ( );
public     :                  OPSImpExp             logical Initialize (DatabaseHandle &dbhandle, char *strname );
public     :                  OPSImpExp                  SDB_Reference (SDB_Member sdbmem, logical transopt, uint8 ver, logical ownopt, logical create_opt, logical cluster_opt, int16 mbnumber, logical week_opt, SDB_Index *dbilistptr=NULL, int16 dbicount=0, logical update_opt=NO, logical mkey_opt=NO, logical glob_identity=NO );
public     :                  OPSImpExp                  SDB_Reference (const SDB_Reference &dbr_refc );
public     :                  OPSImpExp                  SDB_Reference ( );
public     :                  OPSImpExp             void set_create (logical create_opt );
public     :                  OPSImpExp             void set_ddeatyp (SDB_AT acctype );
public     :                  OPSImpExp             void set_owning (logical owning_opt );
public     :                  OPSImpExp                  ~SDB_Reference ( );
};

#pragma pack()
#endif
