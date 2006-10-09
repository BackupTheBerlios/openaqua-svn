/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierarchyTable

\brief    


\date     $Date: 2006/03/12 19:21:44,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "HierarchyTable"

#include  <pdefault.h>
#include  <sHierarchyTable.hpp>


/******************************************************************************/
/**
\brief  AppendHEntry

\return indx -

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AppendHEntry"

int16 HierarchyTable :: AppendHEntry (char *names )
{
  short       indx = GetCount()+1;
BEGINSEQ
  HierarchyEntry  hentry(names,0);
  if ( AddEntry(indx,&hentry) )                      ERROR
RECOVER
  indx = 0;
ENDSEQ
  return(indx);
}

/******************************************************************************/
/**
\brief  FindHEntry

\return indx -

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindHEntry"

int16 HierarchyTable :: FindHEntry (char *names )
{
  short            indx = 0;
  HierarchyEntry  *hentry;
  char             name[ID_SIZE];
BEGINSEQ
  gvtxstb(name,names,ID_SIZE);
  
  while ( hentry = GetEntry(++indx) )
    if ( !memcmp(name,hentry->get_name(),ID_SIZE) )       LEAVESEQ

  ERROR
RECOVER
  indx = 0;
ENDSEQ
  return(indx);
}

/******************************************************************************/
/**
\brief  HierarchyTable

-------------------------------------------------------------------------------
\brief i0


\param  names - Name
\param  maxe -
\param  expand -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierarchyTable"

                        HierarchyTable :: HierarchyTable (char *names, int32 maxe, logical expand )
                     : GSRT(HierarchyEntry) 
(maxe,sizeof(HierarchyEntry),UNDEF,UNDEF,UNDEF,expand),
  current(AUTO)
{

  gvtxstb(name,names,sizeof(name));

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierarchyTable"

                        HierarchyTable :: HierarchyTable ( )
                     : GSRT(HierarchyEntry) 
(20,sizeof(HierarchyEntry),UNDEF,UNDEF,UNDEF,YES),
  current(AUTO)
{

  memset(name,' ',sizeof(name));

}

/******************************************************************************/
/**
\brief  InsertHEntry

\return indx -

\param  indx -
\param  names - Name
\param  lev -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertHEntry"

int16 HierarchyTable :: InsertHEntry (int16 indx, char *names, int16 lev )
{

  HierarchyEntry  hentry(names,lev);
  return ( AddEntry(indx,&hentry) );

}


