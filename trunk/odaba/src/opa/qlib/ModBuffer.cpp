/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ModBuffer

\brief    


\date     $Date: 2006/03/12 19:17:57,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ModBuffer"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sLACObject.hpp>
#include  <sexd.hpp>
#include  <sModBuffer.hpp>


/******************************************************************************/
/**
\brief  AddEntry - 


\return term - Termination code

\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEntry"

logical ModBuffer :: AddEntry (exd *exdarea )
{
  EB_Number  entnr = exdarea->get_exdebsn();
  logical    term  = NO;
BEGINSEQ
  if ( Get((char *)&entnr,YES) )                     SDBERR(99)
  if ( Add(exdarea->get_exdebsn(),exdarea) )         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Clear - 


\return term - Termination code

\param  marksave -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical ModBuffer :: Clear (logical marksave )
{
  exd       *exdarea;
  logical    term = NO;
  Cancel();
  while ( exdarea = (exd *)GetPrevious() )
  {
    if ( marksave )
      exdarea->stsssav();
    if ( ob_handle->Write(exdarea) )
      term = YES;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ModBuffer - 



\param  lobhandle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ModBuffer"

                        ModBuffer :: ModBuffer (LACObject *lobhandle )
                     : exdBuffer (lobhandle,50,UNDEF,UNDEF,UNDEF)
{



}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical ModBuffer :: Reset ( )
{
  exd       *exdarea;
  logical    term = NO;
  Cancel();
  while ( exdarea = (exd *)GetPrevious() )
  {
    exdarea->stssold();
    if ( exdarea->Read(exdarea->get_exdacb()->get_entry_length()) )
      term = YES;
    Delete(exdarea);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ~ModBuffer - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ModBuffer"

                        ModBuffer :: ~ModBuffer ( )
{

  Clear(NO);

}


