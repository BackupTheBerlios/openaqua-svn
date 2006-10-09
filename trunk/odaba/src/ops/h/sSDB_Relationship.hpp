/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Relationship

\brief    Relationship
          Relationships  are  defined  for  referring  to  instances  form other
          collections  or extents. A relationship may  also own the instances in
          the  collection. Relationships  define several  properties for setting
          different  types  of  dependencies,  inverse  relationships  and  base
          collections.

\date     $Date: 2006/05/11 16:10:42,45 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Relationship_HPP
#define   SDB_Relationship_HPP

class     SDB_Relationship;

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
#ifndef   P_SDB_Relationship_HPP
#define   P_SDB_Relationship_HPP
#include  <sPI.hpp>
class       SDB_Relationship;
PI_dcl     (SDB_Relationship)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#include  <cTYP_TYPES.h>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Relationship.hpp>
#pragma pack(8)

class  SDB_Relationship :public SDB_Reference
{
protected  :         logical                                      ddesecr;                                                   // Secondary relationship
protected  :         logical                                      dderlog;                                                   // Logical relationship
protected  :         logical                                      autodelete;                                                // Automatic deletion
protected  :         char                                         ddeinv[40];                                                // Inverse relationship
protected  :         char                                         ddeext[129];                                               // Base collection
protected  :         PI(mem)                                      event_list;                                                // reserved for future
protected  :         PI(SDB_Relationship)                         inverse;                                                   // Inverse relationship
protected  :         PI(SDB_Relationship)                         inverse_ref;                                               // References as inverse relationship

public     :
                     logical                                      get_ddesecr() { return(ddesecr); }
                     logical                                      get_dderlog() { return(dderlog); }
                     logical                                      get_autodelete() { return(autodelete); }
                     char                                        *get_ddeinv() { return(ddeinv); }
                     char                                        *get_ddeext() { return(ddeext); }
                     PI(mem)                                     &get_event_list() { return(event_list); }
                     PI(SDB_Relationship)                        &get_inverse() { return(inverse); }
                     PI(SDB_Relationship)                        &get_inverse_ref() { return(inverse_ref); }
public     :                  OPSImpExp             logical Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes, uint16 dim, char *inverse, logical secrefr );
public     :                  OPSImpExp             void Initialize ( );
public     :                  OPSImpExp                  SDB_Relationship (SDB_Reference sdbref, logical secrefr, logical logrefr, char *irefname, logical depopt, char *extnames );
public     :                  OPSImpExp                  SDB_Relationship (const SDB_Relationship &dbp_refc );
public     :                  OPSImpExp                  SDB_Relationship ( );
public     :                  OPSImpExp                  ~SDB_Relationship ( );
};

#pragma pack()
#endif
