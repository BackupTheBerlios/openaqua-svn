/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_SDB_Resource

\brief    


\date     $Date: 2006/03/12 19:37:45,31 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Resource"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc_SDB_Resource.hpp>


/******************************************************************************/
/**
\brief  GetContextType - 


\return base_context -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

char *pc_SDB_Resource :: GetContextType ( )
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
\brief  pc_SDB_Resource - Konstruktor



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Resource"

                        pc_SDB_Resource :: pc_SDB_Resource (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}


