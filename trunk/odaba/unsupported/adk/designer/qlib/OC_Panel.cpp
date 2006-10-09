/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF) - Context that communicates with the output area
\class    OC_Panel

\brief    


\date     $Date: 2006/03/31 18:32:36,82 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OC_Panel"

#include  <pdesign.h>
#include  <cactp.h>
#include  <iCtxIncl.h>
#include  <sOC_Panel.hpp>


/******************************************************************************/
/**
\brief  OC_Panel - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OC_Panel"

                        OC_Panel :: OC_Panel ( )
                     : datasource(),
  extents()
{

// comment


}

/******************************************************************************/
/**
\brief  Open - 


\return 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical OC_Panel :: Open ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ~OC_Panel - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OC_Panel"

                        OC_Panel :: ~OC_Panel ( )
{

  extents.Close();
  datasource.Close();

}


