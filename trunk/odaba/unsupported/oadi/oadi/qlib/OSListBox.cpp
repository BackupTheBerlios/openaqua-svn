/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSListBox



\date     $Date: 2006/04/28 16:55:14,70 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSListBox"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sPropertyHandle.hpp>
#include  <sOSListBox.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSListBox :: CastPointer (char *typenames )
{

  return (   !typenames                     ? NULL
           : !strcmp(typenames,"OSListBox") ? this
                                            : OStyle::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OSListBox :: CreateInstance (void **instptrp )
{
  *instptrp = new OSListBox();
  return(0);
}

/******************************************************************************/
/**
\brief  GetObjectType

\return typenames

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectType"

char *OSListBox :: GetObjectType ( )
{

  return("OSListBox");

}

/******************************************************************************/
/**
\brief  OSListBox

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSListBox"

     OSListBox :: OSListBox ( )
                     : OStyle (),
  drop(NO),
  edit(NO),
  hscrol(NO),
  vscrol(NO),
  sorted(NO),
  multisel(NO),
  multi_column(NO),
  check_box(NO),
  tree(NO),
  transposed(NO),
  table_grid(NO),
  fast_list(NO)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  drop
\param  edit
\param  hscroll
\param  vscroll
\param  sorted
\param  multisel
\param  multi_column
\param  check_box
\param  tree
\param  transposed
\param  table_grid
\param  fast_list
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSListBox"

     OSListBox :: OSListBox (OStyle bcOStyle, logical drop, logical edit, logical hscroll, logical vscroll, logical sorted, logical multisel, logical multi_column, logical check_box, logical tree, logical transposed, logical table_grid, logical fast_list )
                     : OStyle (bcOStyle),
  drop(drop),
  edit(edit),
  hscrol(hscroll),
  vscrol(vscroll),
  sorted(sorted),
  multisel(multisel),
  multi_column(multi_column),
  check_box(check_box),
  tree(tree),
  transposed(transposed),
  table_grid(table_grid),
  fast_list(fast_list)
{
/*
  "OSListBox("
  + ADK_Style::Generate()
  + ", " + drop
  + ", " + edit
  + ", " + hscrol
  + ", " + vscrol
  + ", " + sorted
  + ", " + multisel
  + ", " + multi_column
  + ", " + check_box
  + ", " + tree
  + ", " + transposed
  + ", " + table_grid
  + ", " + fast_list
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

logical OSListBox :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  edit         = ph->GetInt("edit");
  drop         = ph->GetInt("drop");
  hscrol       = ph->GetInt("hscrol");
  vscrol       = ph->GetInt("vscrol");
  sorted       = ph->GetInt("sorted");
  multisel     = ph->GetInt("multisel");
  multi_column = ph->GetInt("multi_column");
  check_box    = ph->GetInt("check_box");
  tree         = ph->GetInt("tree");
  transposed   = ph->GetInt("transposed");
  table_grid   = ph->GetInt("table_grid");
  fast_list    = ph->GetInt("fast_list");
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSListBox :: Reset ( )
{

  OStyle::Reset();

}

/******************************************************************************/
/**
\brief  ~OSListBox


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSListBox"

     OSListBox :: ~OSListBox ( )
{

  if ( !Deleting() )
    Reset();

}


