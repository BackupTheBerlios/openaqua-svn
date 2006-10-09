/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    sODC_Variable

\brief    


\date     $Date: 2006/06/04 10:33:42,25 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sODC_Variable"

#include  <pfmodel.h>
#include  <sCTX_Structure.hpp>
#include  <spc_ODC_Variable.hpp>
#include  <ssODC_Variable.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  CTX_Structure_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sODC_Variable :: Create (CTX_Structure **CTX_Structure_ptrp )
{

  *CTX_Structure_ptrp = new sODC_Variable();
  return(NO);


}

/******************************************************************************/
/**
\brief  DataTypeCString - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataTypeCString"

logical sODC_Variable :: DataTypeCString ( )
{
  PropertyHandle  *ph       = GetPropertyHandle();
  NString          nstring;
  logical          term     = NO;

BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_Variable   var_pc(ph); 
  SetResult(var_pc.DataTypeCString(nstring));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical sODC_Variable :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("DataTypeCString",ALINK(this,sODC_Variable,DataTypeCString)),
                           cfte("GetCastType",ALINK(this,sODC_Variable,GetCastType)),
                           cfte("ParmTypeCString",ALINK(this,sODC_Variable,ParmTypeCString)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = sSDB_Member_base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCastType - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCastType"

logical sODC_Variable :: GetCastType ( )
{
  PropertyHandle  *ph      = GetPropertyHandle();
  NString          nstring;
  logical          term    = NO;

BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_Variable   var_pc(ph); 
  SetResult(var_pc.GetCastType(nstring));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ParmTypeCString - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParmTypeCString"

logical sODC_Variable :: ParmTypeCString ( )
{
  PropertyHandle  *ph       = GetPropertyHandle();
  char            *prototyp = Parm(1);
  NString          nstring;
  logical          term     = NO;

BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_Variable   var_pc(ph); 
  SetResult(var_pc.ParmTypeCString(nstring,prototyp && *prototyp == 'Y' ? YES : NO));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaultsForSpecialType - 


\return term - 

\param  dbhandle - 
\param  propnames - 
\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultsForSpecialType"

logical sODC_Variable :: SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;

  pc_ODC_Variable   var_pc(ph); 
  term = var_pc.Fill(propnames,typenames);
  return(term);
}

/******************************************************************************/
/**
\brief  sODC_Variable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sODC_Variable"

     sODC_Variable :: sODC_Variable ( )
                     : sSDB_Member_base ()
{



}

/******************************************************************************/
/**
\brief  ~sODC_Variable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sODC_Variable"

     sODC_Variable :: ~sODC_Variable ( )
{



}


