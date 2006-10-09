/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    SystemInput

\brief    


\date     $Date: 2006/08/26 20:43:46,85 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SystemInput"

#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <sSystemInput.hpp>


/******************************************************************************/
/**
\brief  Read - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

char *SystemInput :: Read ( )
{
  char          *string = NULL;
BEGINSEQ
  nstring = "";
  if ( context )
    context->Input(nstring);
  else
  {
    if ( !gets(nstring) )                           ERROR
    string = nstring;
  }
RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  SystemInput - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemInput"

     SystemInput :: SystemInput ( )
                     : SystemIO()
{



}

/******************************************************************************/
/**
\brief  ~SystemInput - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SystemInput"

     SystemInput :: ~SystemInput ( )
{



}


