/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_PersonBase

\brief    


\date     $Date: 2006/07/18 12:28:05,18 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_PersonBase"

#include  <pVGKbase.h>
#include  <spc_PersonBase.hpp>


/******************************************************************************/
/**
\brief  GetEmail - 



\return string - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEmail"

char *pc_PersonBase :: GetEmail ( )
{
  char         *string = "";
BEGINSEQ
  if ( !IsPositioned() )                            ERROR
  
  string = GPH("email")->GetString();
RECOVER

ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  pc_PersonBase - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_PersonBase"

     pc_PersonBase :: pc_PersonBase (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


