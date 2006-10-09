/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADK_Class_

\brief    


\date     $Date: 2006/03/12 19:37:37,03 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ADK_Class_"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_Class_.hpp>


/******************************************************************************/
/**
\brief  InitResourceDB - 


\return term -

\param  clsnames -
\param  source_class -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pc_ADK_Class_ :: InitResourceDB (char *clsnames, pc_ADK_Class_ &source_class )
{
  PropertyHandle   clsname(clsnames);
  int32            indx0 = 0;
  logical          term = NO;
BEGINSEQ
  if ( !source_class.Get(clsname) )                ERROR

  if ( !Provide(clsname) )
  {
    SDBCERR
    ERROR
  }

  while ( source_class.get_controls().Get(indx0++) )
    controls.InitResourceDB(source_class.get_controls());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ADK_Class_ - Konstruktor



\param  obhandle -
\param  accopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ADK_Class_"

                        pc_ADK_Class_ :: pc_ADK_Class_ (DBObjectHandle &obhandle, PIACC accopt )
                     : PropertyHandle (obhandle,"ADK_Class",accopt),
  controls(GPH("controls"))
{



}


