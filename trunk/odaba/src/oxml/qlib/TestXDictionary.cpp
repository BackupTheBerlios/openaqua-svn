/******************************** main Function Code *****************************************************/
/**
\class TestXDictionary

\brief 

\date $Date: 2006/06/05 15:36:16,26 $
\dbsource l:\opa\opa.dev - ODABA Version 9.0

 */
/*************************************************************************************/
#define    OBJ_ID  "TestXDictionary"

#include  <popa7.h>
#include  <sXDictionary.hpp>


/******************************************************************************/
/**
\brief  TestXDictionary - 


\return rc - 

\param  argc - 
\param  argv[] - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TestXDictionary"

int32 __cdecl main (int32 argc, char *argv[] )
{
  XDictionary      xdict;
  char            *cpath = "Dictionary.xsl";
  char            *xs_prefix = "xs";
  char            *oxs_prefix = "oxs";
  logical          rc = 0;
BEGINSEQ
  if ( argc > 1 )  cpath = argv[1];
  if ( argc > 2 )  xs_prefix = argv[2];
  if ( argc > 3 )  xs_prefix = argv[3];

  if ( xdict.Open(cpath,xs_prefix,oxs_prefix) )     ERROR
RECOVER
  rc = 1;
ENDSEQ
  return(rc);
}

