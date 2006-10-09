/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierarchyTable

\brief    


\date     $Date: 2006/03/12 19:20:03,21 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   HierarchyTable_HPP
#define   HierarchyTable_HPP

class     HierarchyTable;

#ifndef   GSRT_HierarchyEntry_HPP
#define   GSRT_HierarchyEntry_HPP
#include  <sHierarchyEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <sHierarchyEntry.hpp>
#pragma pack(8)

class  HierarchyTable :public GSRT(HierarchyEntry)
{
protected  :         char                                         name[40] ATTR_ALIGN(4);                                    //
protected  :         int16                                        current;                                                   //

public     :
                     char                                        *get_name() { return(name); }
                     int16                                        get_current() { return(current); }
public     :         SOS7ImpExp                  int16 AppendHEntry (char *names );
public     :         SOS7ImpExp                  int16 FindHEntry (char *names );
public     :         SOS7ImpExp                                          HierarchyTable (char *names, int32 maxe, logical expand );
public     :         SOS7ImpExp                                          HierarchyTable ( );
public     :         SOS7ImpExp                  int16 InsertHEntry (int16 indx, char *names, int16 lev );
};

#pragma pack()
#endif
