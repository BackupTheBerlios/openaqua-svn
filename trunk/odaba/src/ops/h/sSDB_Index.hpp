/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Index

\brief    Index definition
          The  index definition provides the key name and some index options for
          the  collection  index.  Indexes  can  be defined for local and global
          collections.   The   collection   should   be   a  typed or weak-typed
          collection.  For untypical collections, only  the __IDENTITY index can
          be  defined, which  orders the  collection by local object identifiers
          (LOID).

\date     $Date: 2006/05/11 15:25:15,73 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Index_HPP
#define   SDB_Index_HPP

class     SDB_Index;

#ifndef   P_CAU_simpleAction_HPP
#define   P_CAU_simpleAction_HPP
#include  <sPI.hpp>
class       CAU_simpleAction;
PI_dcl     (CAU_simpleAction)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#include  <cSDB_SET.h>
#include  <sCAU_simpleAction.hpp>
#pragma pack(8)

class  SDB_Index
{
protected  :         char                                         skdname[40];                                               // Key name for the index
protected  :         SDB_SET                                      skdtype;                                                   // Collection type
protected  :         logical                                      skdunique;                                                 // Unique index
protected  :         logical                                      skdtemp;                                                   // Temporary index
protected  :         logical                                      case_sensitive;                                            // Reserved
protected  :         logical                                      no_empty;                                                  // Not storing empty keys or attributes
protected  :         int32                                        skdmax;                                                    // Maximum number of entries in the index
protected  :         CAU_simpleAction                             compare;                                                   // Compare function for the index
protected  :         logical                                      main_index;                                                // Main index

public     :
                     char                                        *get_skdname() { return(skdname); }
                     SDB_SET                                      get_skdtype() { return(skdtype); }
                     logical                                      get_skdunique() { return(skdunique); }
                     logical                                      get_skdtemp() { return(skdtemp); }
                     logical                                      get_case_sensitive() { return(case_sensitive); }
                     logical                                      get_no_empty() { return(no_empty); }
                     int32                                        get_skdmax() { return(skdmax); }
                     CAU_simpleAction                            &get_compare() { return(compare); }
                     logical                                      get_main_index() { return(main_index); }
public     :                  OPSImpExp             logical Check (PI(SDB_Structure) &dbs_pi, char *strname );
public     :                  OPSImpExp             void Initialize (char *idxnames, int16 settype, logical uniopt, logical sensiopt );
public     :                  OPSImpExp                  SDB_Index (char *keynams, SDB_SET settyp, logical uniopt, logical tempopt, logical case_sensopt, logical empopt, int16 maxcount );
};

#pragma pack()
#endif
