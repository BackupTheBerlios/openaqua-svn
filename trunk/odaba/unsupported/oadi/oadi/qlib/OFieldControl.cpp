/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    OFieldControl

\brief    


\date     $Date: 2006/07/17 13:48:05,43 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OFieldControl"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOElementStyle.hpp>
#include  <sOField.hpp>
#include  <sOFrameStyle.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControl.hpp>
#include  <sOFieldControl.hpp>


/******************************************************************************/
/**
\brief  CastPointer - 



\return pointer - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OFieldControl :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"OFieldControl") ? this
                                                : OStyleAction::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance - 



\return rc - 

\param  instptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OFieldControl :: CreateInstance (void **instptrp )
{

  *instptrp = new OFieldControl();
  return(0);

}

/******************************************************************************/
/**
\brief  FieldByName - 



\return term - 

\param  rcdsName - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldByName"

OField *OFieldControl :: FieldByName (const DString &rcdsName )
{
  OField *   term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  OFieldControl - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFieldControl"

     OFieldControl :: OFieldControl ( )
                     : OStyleAction (),
  length(0),
  cache(NO),
  reserved(NO),
  output(NO),
  dynamic(NO),
  class_name(),
  grid_size(),
  field_margin(),
  inner_distance(0)
{

  memset(this->class_name,0,sizeof(this->class_name));


}

/******************************************************************************/
/**
\brief  i01 - 



\param  bcOStyleAction - 
\param  length - 
\param  output - 
\param  dynamic - 
\param  class_name - 
\param  grid_size - 
\param  dm_field_margin - 
\param  inner_distance - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFieldControl"

     OFieldControl :: OFieldControl (OStyleAction bcOStyleAction, int32 length, logical output, logical dynamic, char *class_name, DSize grid_size, DMargin dm_field_margin, int16 inner_distance )
                     : OStyleAction (bcOStyleAction),
  length(length),
  output(output),
  dynamic(dynamic),
  class_name(), // strcpy
  grid_size(grid_size),
  field_margin(dm_field_margin),
  inner_distance(inner_distance)
{

  gvtxstb(this->class_name,class_name?class_name:"",ID_SIZE);
  if (grid_size.Width==AUTO && grid_size.Height==AUTO)
  {
    DSize ds(align.get_horiCells(),align.get_vertCells());
    this->grid_size = ds;
  }
  if (inner_distance==AUTO) 
    this->inner_distance = distance;

/*
  "OFieldControl("
  +        ADK_StyleAction::Generate()
  + ", " + length
  + ", " + output
  + ", " + virtual
  + ", \"" + ??class_name + "\""
  + ", DSize(AUTO,AUTO)" // from style action
  + ", DMargin(0,0,0,0)"
  + ", AUTO
  + ")";
*/

}

/******************************************************************************/
/**
\brief  Read - 



\return term - 

\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OFieldControl :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyleAction::Read(ph);
  
  length  = ph->GetInt("length");
  cache   = ph->GetInt("cache");
//reserved  ist noch frei
  output  = ph->GetInt("output");
  dynamic = ph->GetInt("virtual");
  grid_size = DSize(align.get_horiCells(),align.get_vertCells());

  inner_distance = distance;
  
  memset(class_name,' ',ID_SIZE);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OFieldControl :: Reset ( )
{

  length    = 0;
  output    = NO;
  grid_size = DSize();

  OStyleAction::Reset();


}

/******************************************************************************/
/**
\brief  SetClassName - 




\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetClassName"

void OFieldControl :: SetClassName (char *string )
{

  gvtxstb(class_name,string ? string : "",ID_SIZE);

}

/******************************************************************************/
/**
\brief  SetInnerDistance - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInnerDistance"

void OFieldControl :: SetInnerDistance ( )
{

  inner_distance = distance;

}

/******************************************************************************/
/**
\brief  ~OFieldControl - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OFieldControl"

     OFieldControl :: ~OFieldControl ( )
{

  if ( !Deleting() )
    Reset();

}


