/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HierarchyEntry

\brief    


\date     $Date: 2006/03/12 19:20:03,07 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   HierarchyEntry_HPP
#define   HierarchyEntry_HPP

class     HierarchyEntry;

#pragma pack(8)

class  HierarchyEntry
{
protected  :         char                                         name[40];                                                  //
protected  :         int16                                        level;                                                     //

public     :
                     char                                        *get_name() { return(name); }
                     int16                                        get_level() { return(level); }
public     :         SOS7ImpExp                                          HierarchyEntry (char *names, int16 lev );
public     :         SOS7ImpExp                                          HierarchyEntry ( );
public     :         SOS7ImpExp                  void set_level (int16 lev );
};

#pragma pack()
#endif
