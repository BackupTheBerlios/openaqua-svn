/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ADK_Class



\date     $Date: 2006/05/23 13:05:18,25 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc1_ADK_Class"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc1_ADK_Class.hpp>


/******************************************************************************/
/**
\brief  InitResourceDB

\return term - 

\param  clsnames
\param  source_class
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResourceDB"

logical pc1_ADK_Class :: InitResourceDB (char *clsnames, pc1_ADK_Class &source_class )
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
\brief  pc1_ADK_Class - Konstruktor



\param  obhandle
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc1_ADK_Class"

     pc1_ADK_Class :: pc1_ADK_Class (DBObjectHandle &obhandle, PIACC accopt )
                     : PropertyHandle (obhandle,"ADK_Class",accopt),
  controls(GPH("controls"))
{
}


