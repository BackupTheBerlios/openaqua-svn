/********************************* Class Declaration ***************************/
/**
\package  OPI - 
\class    ExtentListEntry

\brief    


\date     $Date: 2006/08/26 11:51:46,54 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExtentListEntry_HPP
#define   ExtentListEntry_HPP
#include "copadll.h"

class     ExtentListEntry;

#pragma pack(8)

class  ExtentListEntry
{
protected  :         int64                                        identity;                                                  // 
protected  :         char                                         extent_name[40];                                           // 
protected  :         int32                                        namespace_id;                                              // 

public     :
                     int32                                        get_namespace_id() { return(namespace_id); }
public     :                  OPIImpExp             char *get_extent_name ( );
public     :                  OPIImpExp             int16 get_main_base ( );
};

#pragma pack()
#endif
