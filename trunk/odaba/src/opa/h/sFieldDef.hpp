/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FieldDef

\brief    Internal ODABA2 field definition
          Based   on   this   class   ODABA2   field   definitions  (see {\b {.r
          DBFieldDef}})  are provided  in the  main storage.  The base class {\b
          {.r  fmcb}}  provides  basic  information  about  a data field and its
          structure.

\date     $Date: 2006/03/12 19:13:22,57 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FieldDef_HPP
#define   FieldDef_HPP

class     FieldDef;

class     SDB_Member;
class     SDB_Property;
#include  <cSDB_RLEV.h>
#include  <sFieldDef.hpp>
#include  <sfmcb.hpp>
#pragma pack(8)

class  FieldDef :public fmcb
{

public     :
public     :                                     logical Check (SDB_Member *dbmptr, logical transient );
public     :                                     logical Check (PropertyHandle &ph, logical transient );
public     :                                     logical Check (FieldDef &temp_field );
public     :                                     SDB_RLEV FMCBRefLevel (SDB_RLEV fldreflev, logical transopt );
public     :                                                             FieldDef (fmcb *fmcbptr );
public     :                                                             FieldDef ( );
public     :                                                             FieldDef (char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim );
public     :                                     logical Fill (SDB_Member *dbmptr, logical transient );
public     :                                     logical FillMember (PropertyHandle &ph, logical transient );
public     :                                     logical IsFilled ( );
public     :         opa7ImpExp                  SDB_RLEV ReferenceLevel ( );
public     :                                     void TraceGenError ( );
};

#pragma pack()
#endif
