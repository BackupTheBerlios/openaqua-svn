/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierarchyEntry

\brief    


\date     $Date: 2006/03/12 19:21:43,96 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "HierarchyEntry"

#include  <pdefault.h>
#include  <sHierarchyEntry.hpp>


/******************************************************************************/
/**
\brief  HierarchyEntry

-------------------------------------------------------------------------------
\brief i0


\param  names - Name
\param  lev -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierarchyEntry"

                        HierarchyEntry :: HierarchyEntry (char *names, int16 lev )
                     :   level(lev)
{

  gvtxstb(name,names,sizeof(name));

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HierarchyEntry"

                        HierarchyEntry :: HierarchyEntry ( )
                     :   level(0)
{

  memset(name,' ',sizeof(name));

}

/******************************************************************************/
/**
\brief  set_level


\param  lev -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_level"

void HierarchyEntry :: set_level (int16 lev )
{

  level = lev;

}


