/********************************* Class Declaration ***************************/
/**
\package  OPS
\class    SDB_Attribute

\brief    Attribute definition
          Attribute  definitions are used to define the attributes for a complex
          data type (structure).

\date     $Date: 2006/05/11 16:06:10,96 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Attribute_HPP
#define   SDB_Attribute_HPP

class     SDB_Attribute;

#ifndef   P_SDB_CodeSet_HPP
#define   P_SDB_CodeSet_HPP
#include  <sPI.hpp>
class       SDB_CodeSet;
PI_dcl     (SDB_CodeSet)
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
#include  <sSDB_Member.hpp>
#include  <sSDB_Property.hpp>
#pragma pack(8)

class  SDB_Attribute :public SDB_Property
{

public     :
public     :                  OPSImpExp             logical Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes );
public     :                  OPSImpExp                  SDB_Attribute (SDB_Member sdbmem, logical transopt, uint8 ver );
public     :                  OPSImpExp                  SDB_Attribute ( );
};

#pragma pack()
#endif
