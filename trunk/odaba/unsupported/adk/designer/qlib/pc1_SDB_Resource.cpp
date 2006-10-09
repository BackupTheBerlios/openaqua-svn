/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_SDB_Resource



\date     $Date: 2006/05/23 13:11:51,92 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_SDB_Resource"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc1_SDB_Resource.hpp>


/******************************************************************************/
/**
\brief  GetContextType

\return base_context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

char *pc1_SDB_Resource :: GetContextType ( )
{
  char         *base_context = NULL;
BEGINSEQ
  if ( !Exist() )                                    ERROR
 
  if ( Inherits("SDB_Type") )
    base_context = "CTX_Structure";
  else if ( Inherits("SDB_Member") )
    base_context = "CTX_Property";
  else if ( Inherits("ADK_Project") )
    base_context = "CTX_Project";
  else if ( Inherits("ADK_Application") )
    base_context = "CTX_Application";
  else if ( Inherits("ADK_StyleElement") )
    base_context = "CTX_Control";
RECOVER
ENDSEQ
  return(base_context);
}

/******************************************************************************/
/**
\brief  pc1_SDB_Resource - Konstruktor



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_SDB_Resource"

     pc1_SDB_Resource :: pc1_SDB_Resource (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{
}


