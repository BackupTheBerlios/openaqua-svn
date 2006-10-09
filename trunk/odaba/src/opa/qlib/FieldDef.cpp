/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FieldDef

\brief    Internal ODABA2 field definition
          Based   on   this   class   ODABA2   field   definitions  (see {\b {.r
          DBFieldDef}})  are provided  in the  main storage.  The base class {\b
          {.r  fmcb}}  provides  basic  information  about  a data field and its
          structure.

\date     $Date: 2006/03/12 19:17:34,31 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FieldDef"

#include  <popa7.h>
#include  <sSDB_Member.hpp>
#include  <sSDB_Property.hpp>
#include  <sfmcb.hpp>
#include  <sFieldDef.hpp>


/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  dbmptr -
\param  transient -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical FieldDef :: Check (SDB_Member *dbmptr, logical transient )
{
  FieldDef   temp_field;
  logical    term        = NO;
BEGINSEQ
  temp_field.Fill(dbmptr,transient);
    
  if ( Check(temp_field) )                           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  ph -
\param  transient -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical FieldDef :: Check (PropertyHandle &ph, logical transient )
{
  FieldDef   temp_field;
  logical    term        = NO;
BEGINSEQ
  temp_field.FillMember(ph,transient);
    
  if ( Check(temp_field) )                           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i02


\param  temp_field
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical FieldDef :: Check (FieldDef &temp_field )
{
  int8       max_aligned = 1;
  logical    term        = NO;
BEGINSEQ
  if ( memcmp(fmcbname,temp_field.fmcbname,sizeof(fmcbname)) ||
       memcmp(fmcbtype,temp_field.fmcbtype,sizeof(fmcbtype))    )
                                                     ERROR
  
  if ( fmcbrlev < 0 )                                LEAVESEQ
  
  temp_field.fmcbityp = fmcbityp;
  temp_field.fmcbesu(fmcbsmcb,fmcbposn,AUTO,max_aligned);
  if ( fmcbbyte != temp_field.fmcbbyte )             ERROR 
  


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FMCBRefLevel - 


\return reflevel

\param  fldreflev - Property reference level
\param  transopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FMCBRefLevel"

SDB_RLEV FieldDef :: FMCBRefLevel (SDB_RLEV fldreflev, logical transopt )
{

  switch ( fldreflev )
  {
    case RL_reference : fmcbrlev = R_REFR;             break;
    case RL_generic   : fmcbrlev = R_GENERIC;          break;
    case RL_direct    : fmcbrlev = transopt ? R_INTERN : R_DIRECT;
                                                       break;
    case RL_1         :
    case RL_2         :
    case RL_3         :
    default           : fmcbrlev = fldreflev;
  }

//  if ( transopt )
//    fmcbrlev = R_INTERN;
  return((SDB_RLEV)fmcbrlev);
}

/******************************************************************************/
/**
\brief  FieldDef - 


-------------------------------------------------------------------------------
\brief i0


\param  fmcbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldDef"

                        FieldDef :: FieldDef (fmcb *fmcbptr )
                     : fmcb (*fmcbptr)
{



}

/******************************************************************************/
/**
\brief i02


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldDef"

                        FieldDef :: FieldDef ( )
                     : fmcb ()
{



}

/******************************************************************************/
/**
\brief i1


\param  fldnames - Property name
\param  fldtypes - Property type
\param  fldnsid
\param  fldreflev - Property reference level
\param  fldsize - Size of property
\param  fldprec - Precision of property
\param  flddim - Dimension of property
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldDef"

                        FieldDef :: FieldDef (char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim )
                     : fmcb (fldnames,fldtypes,fldnsid,FMCBRefLevel(fldreflev,NO),fldsize,fldprec,flddim)
{



}

/******************************************************************************/
/**
\brief  Fill - 


\return term - Termination code

\param  dbmptr -
\param  transient -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical FieldDef :: Fill (SDB_Member *dbmptr, logical transient )
{
  logical    chk        = IsFilled();
  int16      old_revlev = fmcbrlev;
  logical    term       = NO;

BEGINSEQ
  if ( chk )
  {
    if ( Check(dbmptr,transient) )                   ERROR
    LEAVESEQ
  }

  fmcbini();
  memcpy(fmcbname,dbmptr->get_sys_ident(),ID_SIZE);
  memcpy(fmcbtype,dbmptr->get_ddetype(),ID_SIZE);

  fmcbsize = dbmptr->get_ddesize();
  fmcbdim  = *dbmptr->get_ddedim();
  fmcbprec = dbmptr->get_ddeprec();
  fmcbstat = dbmptr->get_ddestat();
  fmcbvirt = dbmptr->get_ddevirt();
  fmcbempty= dbmptr->get_empty();
  
  FMCBRefLevel(dbmptr->get_reference_level(),transient);
  
  if ( fmcbrlev != R_GENERIC && fmcbrlev <= 0 )   //
    if ( fmcbdim == 0 && fmcbsize == 0 )          // 12.11.98
      fmcbrlev = R_REFR;                          //
RECOVER
  term = YES;  

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  FillMember

\return term - Termination code

\param  ph -
\param  transient -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillMember"

logical FieldDef :: FillMember (PropertyHandle &ph, logical transient )
{
  logical    chk        = IsFilled();
  int16      old_revlev = fmcbrlev;
  logical    term       = NO;
BEGINSEQ
  if ( chk ) 
  {
    if ( Check(ph,transient) )                     ERROR
    LEAVESEQ
  }

  fmcbini();
  memcpy(fmcbname,ph.GetArea("sys_ident"),ID_SIZE);
  memcpy(fmcbtype,ph.GetArea("ddetype"),ID_SIZE);

  fmcbsize = ph.GetInt("ddesize");
  fmcbdim  = ph.GetInt("ddedim");
  fmcbprec = ph.GetInt("ddeprec");
  fmcbstat = ph.IsTrue("ddestat");
  fmcbvirt = ph.IsTrue("ddevirt");
  fmcbempty= ph.IsTrue("empty");
  
  FMCBRefLevel((SDB_RLEV)ph.GetInt("reference_level"),transient);
  
  if ( fmcbrlev != R_GENERIC && fmcbrlev <= 0 )   //
    if ( fmcbdim == 0 && fmcbsize == 0 )          // 12.11.98
      fmcbrlev = R_REFR;                          //
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsFilled - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFilled"

logical FieldDef :: IsFilled ( )
{

  return ( this && *fmcbname > ' ' ? YES : NO );

}

/******************************************************************************/
/**
\brief  ReferenceLevel - Provide level, data is referenced
        The  function provides the reference level  for the field data as ODABA2
        typed value.

\return reflevel

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReferenceLevel"

SDB_RLEV FieldDef :: ReferenceLevel ( )
{
  SDB_RLEV       reflevel = RL_undefined;
  switch ( fmcbrlev )
  {
    case R_INTERN     :
    case R_DIRECT     : reflevel = RL_direct;          break;
    case R_GENERIC    : reflevel = RL_generic;         break;
    case R_REFR       : reflevel = RL_reference;       break;
    default           : reflevel = (SDB_RLEV)fmcbrlev;
  }
  return(reflevel);
}

/******************************************************************************/
/**
\brief  TraceGenError - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TraceGenError"

void FieldDef :: TraceGenError ( )
{
  char   strnames[41];
  char   propnames[41];

  strncpy(strnames,SDBError().get_err_var1(),sizeof(strnames));
  gvtxbts(propnames,fmcbname,sizeof(fmcbname));
  
  SDBError().TraceMessage("Structure: '",strnames,"' Property: '",propnames,
                      "' illegal changes for generated property");

  SDBSET(400)
  SDBRESET

}


