/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_BaseStruct

\brief    Base structure
          Base  structures implement the generic part  of a complex data type. A
          structure  may  be  derived  from  any number of base structures. Base
          structures  can  be  defined  as  shared or exclusive base structures.
          Shared  base  structures  allow  deriving any number of instances from
          one  base instance. Exclusive base  structure instances can be derived
          to  maximum  one  instance  and  exist as long as the derived instance
          exists.

\date     $Date: 2006/05/11 16:11:17,96 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_BaseStruct_HPP
#define   SDB_BaseStruct_HPP

class     SDB_BaseStruct;

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
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
class     DBFieldDef;
#include  <cTYP_TYPES.h>
#include  <sDatabaseHandle.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Relationship.hpp>
#pragma pack(8)

class  SDB_BaseStruct :public SDB_Relationship
{
protected  :         logical                                      smcedom;                                                   // not used

public     :
                     logical                                      get_smcedom() { return(smcedom); }
public     :                  OPSImpExp             logical Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes, char *inverse );
public     :                  OPSImpExp                  SDB_BaseStruct (SDB_Relationship sdbrel, logical domopt );
public     :                  OPSImpExp                  ~SDB_BaseStruct ( );
};

#pragma pack()
#endif
