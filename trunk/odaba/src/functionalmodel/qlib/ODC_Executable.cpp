/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_Executable

\brief    


\date     $Date: 2006/03/13 21:30:39,07 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_Executable"

#include  <pfmodel.h>
#include  <sODC_Executable.hpp>


/******************************************************************************/
/**
\brief  GetDocFileName - 


\return filnames
/******************************************************************************/
/**
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *ODC_Executable :: GetDocFileName ( )
{
  static char   filnames[DEF_BUFLEN+1];
  return ( strcat(gvtxbts(filnames,sys_ident,ID_SIZE),".cpp") );

}


