/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FunctLink

\brief    


\date     $Date: 2006/03/12 19:17:35,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FunctLink"

#include  <popa7.h>
#include  <ccctp.h>
#include  <coctp.h>
#ifndef   DPA_PropertyHandle_HPP
#define   DPA_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sDPA.h>
#endif
#include  <sACObject.hpp>
#include  <sDLL_Handle.hpp>
#include  <sDictionary.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <svcls.hpp>
#include  <sFunctLink.hpp>


/******************************************************************************/
/**
\brief  Check - 


\return term - Termination code

\param  return_value -
\param  co -
\param  parameters -
\param  convopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical FunctLink :: Check (PropertyHandle *return_value, PropertyHandle *co, ParmList *parameters, logical convopt )
{
  logical                 term = NO;
BEGINSEQ
  if ( flnkfct == NULL && flnkcfct == NULL )         ERROR
    
// soll Funktion mit 'Initialize' zum initialisieren des retval aufrufen!
  if ( return_value )
    term = Execute(co,return_value,parameters,NULL,ET_Initialize);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Execute - 


\return term - Termination code

\param  co -
\param  retval -
\param  parameters -
\param  implname -
\param  exectype -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical FunctLink :: Execute (PropertyHandle *co, PropertyHandle *retval, ParmList *parameters, char *implname, ExecutionTypes exectype )
{

  if ( flnkcfct )
    return( (*flnkcfct)(co,retval,parameters,implname,exectype) );
  
  if ( vclsptr )
    return( (vclsptr->*flnkfct)(co,retval,parameters,implname,exectype) );
  
#if defined (WIN32) || defined (__unix__)
  return( (vcls().*flnkfct)(co,retval,parameters,implname,exectype) );
#else
  return( (vcls()->*flnkfct)(co,retval,parameters,implname,exectype) );
#endif

}

/******************************************************************************/
/**
\brief  FunctLink - 


-------------------------------------------------------------------------------
\brief i0


\param  fctptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FunctLink"

                        FunctLink :: FunctLink (OCTP fctptr )
                     : vclsptr(NULL),
  flnkfct(fctptr),
  flnkcfct(NULL)
{



}

/******************************************************************************/
/**
\brief i02


\param  cfctptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FunctLink"

                        FunctLink :: FunctLink (CCTP cfctptr )
                     : vclsptr(NULL),
  flnkfct(NULL),
  flnkcfct(cfctptr)
{



}

/******************************************************************************/
/**
\brief i03


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FunctLink"

                        FunctLink :: FunctLink ( )
                     : vclsptr(NULL),
  flnkfct(NULL),
  flnkcfct(NULL)
{



}

/******************************************************************************/
/**
\brief i1


\param  flink -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FunctLink"

                        FunctLink :: FunctLink (FunctLink &flink )
                     : vclsptr(NULL),
  flnkfct(flink.flnkfct),
  flnkcfct(flink.flnkcfct)
{



}

/******************************************************************************/
/**
\brief  SetFunctionPtr - 


\return term - Termination code

\param  dicthdl -
\param  co_type -
\param  fname -
\param  check_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFunctionPtr"

logical FunctLink :: SetFunctionPtr (DictionaryHandle dicthdl, char *co_type, char *fname, logical check_opt )
{
  Dictionary             *dictptr = NULL;
  char                    dll_path[256];
  char                    dllname[65];
  char                    string[129];
  logical                 term = NO;
BEGINSEQ
  strcat(strcpy(dllname,"_if_"),(gvtxbts(string,co_type,ID_SIZE)));
  
  if ( dicthdl.IsOpened() )
    dictptr = dicthdl.get_dictionary();
  
  dictptr->GetDLLPath(dll_path,dllname);
//  if ( filchck(dll_path,'F') )                       ERROR

//  if ( !(*((void **)&flnkfct) = DLLHandle()->GetFunctionPtr(dll_path,fname)) )
//  if ( !(*((void **)&flnkcfct) = DLLHandle()->GetFunctionPtr(dll_path,fname)) )
  if ( !(flnkcfct = (CCTP)DLLHandle()->GetFunctionPtr(dll_path,fname,check_opt)) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetInstance - 



\param  vclsinst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

void FunctLink :: SetInstance (vcls *vclsinst )
{

  vclsptr = vclsinst;

}

/******************************************************************************/
/**
\brief  ~FunctLink - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~FunctLink"

                        FunctLink :: ~FunctLink ( )
{



}


