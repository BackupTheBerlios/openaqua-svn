/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    OqlExtentList



\date     $Date: 2006/04/15 18:56:43,03 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OqlExtentList"

#include  <poql.h>
#include  <sOqlExtentList.hpp>


/******************************************************************************/
/**
\brief  Add


\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void OqlExtentList :: Add (PropertyHandle &ph )
{

  if ( &ph )
    AddTail(&ph);

}

/******************************************************************************/
/**
\brief  OqlExtentList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OqlExtentList"

                        OqlExtentList :: OqlExtentList ( )
                     : DLL(PropertyHandle)()
{



}

/******************************************************************************/
/**
\brief  Remove


\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void OqlExtentList :: Remove (PropertyHandle &ph )
{

  if ( &ph )
    QuList::Remove(&ph);

}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OqlExtentList :: Reset ( )
{
  PropertyHandle       *ph;
  GoTop();
  while ( ph = GetNext() )
    ph->ToTop();

}

/******************************************************************************/
/**
\brief  ~OqlExtentList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OqlExtentList"

                        OqlExtentList :: ~OqlExtentList ( )
{



}


