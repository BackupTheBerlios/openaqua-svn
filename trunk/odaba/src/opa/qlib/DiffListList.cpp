/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListList

\brief    


\date     $Date: 2006/03/12 19:17:23,15 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DiffListList"

#include  <popa7.h>
#include  <sDiffListListEntry.hpp>
#include  <sDifferenceList.hpp>
#include  <sLACObject.hpp>
#include  <sTABuffer.hpp>
#include  <sDiffListList.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return indx -

\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

int32 DiffListList :: Add (DifferenceList *dlist_ptr )
{
  DiffListListEntry  dle_temp(dlist_ptr);
  int32               indx = 0;
BEGINSEQ
  if ( !(indx = AddEntry(&dle_temp)) )                 ERROR

RECOVER

ENDSEQ
  return(indx);
}

/******************************************************************************/
/**
\brief  Clear - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

logical DiffListList :: Clear ( )
{
  DifferenceList  *dlist_ptr;
  while ( srtecnt )
  {
    dlist_ptr = Delete(srtecnt);
    delete dlist_ptr;
  }

  return(NO);
}

/******************************************************************************/
/**
\brief  Delete - 


\return dlist_ptr -

\param  lindex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

DifferenceList *DiffListList :: Delete (int32 lindex )
{
  DifferenceList    *dlist_ptr = NULL;
BEGINSEQ
  if ( lindex )
  {
    if ( lindex > srtecnt )                           ERROR
    dlist_ptr = GetEntry(lindex)->get_diff_list();
    DeleteEntry(lindex);
  }

RECOVER

ENDSEQ
  return(dlist_ptr);
}

/******************************************************************************/
/**
\brief  DiffListList - 



\param  lobhandle -
\param  tabuffer -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DiffListList"

                        DiffListList :: DiffListList (LACObject *lobhandle, TABuffer *tabuffer )
                     : GSRT(DiffListListEntry)(20,
             sizeof(DiffListListEntry),4,1,'I',YES),
  ob_handle(lobhandle),
  transaction(tabuffer)
{

BEGINSEQ
  if ( SOSERROR )                               SDBERR(95)
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Locate - 


\return dlist_ptr -
-------------------------------------------------------------------------------
\brief i0


\param  entnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

DifferenceList *DiffListList :: Locate (EB_Number entnum )
{
  DifferenceList    *dlist_ptr = NULL;
  int32               index;
  index = srtbsr((char *)&entnum);
  if ( index && !stscerr() )
    dlist_ptr = Locate(index);

  return(dlist_ptr);
}

/******************************************************************************/
/**
\brief i01


\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Locate"

DifferenceList *DiffListList :: Locate (int16 indx )
{

  return( GetEntry(indx)->get_diff_list() );


}

/******************************************************************************/
/**
\brief  Provide_vielleicht

\return dlistptr -

\param  dlist_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Provide_vielleicht"

DifferenceList *DiffListList :: Provide_vielleicht (DifferenceList *dlist_ptr )
{
  EB_Number          entnr = dlist_ptr->GetEBINumber();
  DifferenceList    *dlistptr = NULL;
BEGINSEQ
  if ( dlistptr = Locate(entnr) )                    LEAVESEQ
  
  dlistptr = new DifferenceList(dlist_ptr);
  Add(dlist_ptr);
ENDSEQ
  return(dlistptr);
}

/******************************************************************************/
/**
\brief  ~DiffListList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DiffListList"

                        DiffListList :: ~DiffListList ( )
{

  Clear();

}


