/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/10|23:48:19,31}|(REF)
\class    ExtentList



\date     $Date: 2006/04/15 18:56:43,03 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExtentList"

#include  <poql.h>
#include  <sExtentList.hpp>


/******************************************************************************/
/**
\brief  Add


\param  ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void ExtentList :: Add (PropertyHandle &ph )
{

  if ( &ph )
    AddTail(&ph);

}

/******************************************************************************/
/**
\brief  ExtentList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtentList"

                        ExtentList :: ExtentList ( )
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

void ExtentList :: Remove (PropertyHandle &ph )
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

void ExtentList :: Reset ( )
{
  PropertyHandle       *ph;
  GoTop();
  while ( ph = GetNext() )
    ph->ToTop();

}

/******************************************************************************/
/**
\brief  ~ExtentList


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ExtentList"

                        ExtentList :: ~ExtentList ( )
{



}


