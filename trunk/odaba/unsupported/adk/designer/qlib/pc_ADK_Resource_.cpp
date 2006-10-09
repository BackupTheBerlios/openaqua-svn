/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADK_Resource_

\brief    


\date     $Date: 2006/03/12 19:37:38,03 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_Resource_"

#include  <pdesign.h>
#include  <spc_ADK_Resource_.hpp>
#include  <spc_ADK_Resource_.hpp>


/******************************************************************************/
/**
\brief  InitResourceDB - 


\return term -

\param  source_resource -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pc_ADK_Resource_ :: InitResourceDB (pc_ADK_Resource_ &source_resource )
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
\brief  pc_ADK_Resource_ - Konstruktor



\param  obhandle -
\param  clsnames -
\param  accopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Resource_"

                        pc_ADK_Resource_ :: pc_ADK_Resource_ (DBObjectHandle &obhandle, char *clsnames, PIACC accopt )
                     : PropertyHandle (obhandle,clsnames,accopt),
  sys_resource(GPH("sys_resource"))
{



}


