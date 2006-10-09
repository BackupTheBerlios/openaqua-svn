/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ADK_Resource



\date     $Date: 2006/05/23 13:07:07,01 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_ADK_Resource"

#include  <pdesign.h>
#include  <spc1_ADK_Resource.hpp>
#include  <spc1_ADK_Resource.hpp>


/******************************************************************************/
/**
\brief  InitResourceDB

\return term - 

\param  source_resource
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pc1_ADK_Resource :: InitResourceDB (pc1_ADK_Resource &source_resource )
{
  int32                   indx0 = 0;
  logical                 term  = NO;
  while ( source_resource.Get(indx0++) )
    if ( source_resource.get_sys_resource().IsTrue() )
      Copy(source_resource,REPL_none);
  return(term);
}

/******************************************************************************/
/**
\brief  pc1_ADK_Resource - Konstruktor



\param  obhandle
\param  clsnames
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ADK_Resource"

     pc1_ADK_Resource :: pc1_ADK_Resource (DBObjectHandle &obhandle, char *clsnames, PIACC accopt )
                     : PropertyHandle (obhandle,clsnames,accopt),
  sys_resource(GPH("sys_resource"))
{
}


