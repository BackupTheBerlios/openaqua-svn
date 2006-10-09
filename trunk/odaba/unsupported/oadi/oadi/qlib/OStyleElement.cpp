/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OStyleElement



\date     $Date: 2006/04/28 16:41:23,67 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OStyleElement"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sODataSource.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOResource.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sOStyleElement.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OStyleElement :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"OStyleElement") ? this
           : !strcmp(typenames,"OContextStyle") ? (OContextStyle *)this
                                                : OResource::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  GetTitle

\return text

\param  pODataSource
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTitle"

char *OStyleElement :: GetTitle (ODataSource *pODataSource )
{
  char       *text = NULL;
BEGINSEQ
  if ( !LabelPosition()->HasShowLabel() )            LEAVESEQ
    
  text = (char *)textDefinitions.GetTitle();
  
  if ( !text || !*text && pODataSource ) 
    text = (char *)pODataSource->GetPath();



ENDSEQ
  return(text);
}

/******************************************************************************/
/**
\brief  OStyleElement

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStyleElement"

     OStyleElement :: OStyleElement ( )
                     : OResource (),
OContextStyle ()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOResource
\param  bcOContextStyle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OStyleElement"

     OStyleElement :: OStyleElement (OResource bcOResource, OContextStyle bcOContextStyle )
                     :  OResource(bcOResource)
,OContextStyle(bcOContextStyle)
{
/* 
  "OStyleElement("
  +      + ADK_Resource::Generate()
  + ", " + ADK_ContextStyle::Generate()
  + ")";
*/
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OStyleElement :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OResource::Read(ph);
  OContextStyle::Read(ph);
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OStyleElement :: Reset ( )
{
  OResource::Reset();
  OContextStyle::Reset();
}

/******************************************************************************/
/**
\brief  UpdateStyleElement

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateStyleElement"

logical OStyleElement :: UpdateStyleElement (PropertyHandle *ph )
{
  long       save_res_id       = res_id;
  char       save_ctxcl[ID_SIZE+1];
  logical    save_docking_area = docking_area;
  logical    term   = NO;
  memcpy(save_ctxcl,contextClass,ID_SIZE);
  
  OResource::Reset();
  OResource::Read(ph);
  OContextStyle::Read(ph);
  
  docking_area = save_docking_area;
  
  if ( !res_id || *contextClass <= ' ' ) // ausschalten des fieldcontrol-contextes am field durch Angabe von CTX_Control!
  {
    strcpy(contextClass,save_ctxcl);
    res_id = save_res_id;
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ~OStyleElement


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OStyleElement"

     OStyleElement :: ~OStyleElement ( )
{

  if ( !Deleting() )
    Reset();

}


