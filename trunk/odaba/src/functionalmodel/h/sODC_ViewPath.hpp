/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_ViewPath

\brief    


\date     $Date: 2006/03/13 21:30:34,95 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_ViewPath_HPP
#define   ODC_ViewPath_HPP

class     ODC_ViewPath;

#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  ODC_ViewPath :public SDB_Resource
{
protected  :         char                                         path[256] ATTR_ALIGN(4);                                   // Path definition
protected  :         char                                         structure[40];                                             
protected  :         char                                         order[40];                                                 

public     :
                     char                                        *get_path() { return(path); }
                     char                                        *get_structure() { return(structure); }
                     char                                        *get_order() { return(order); }
};

#pragma pack()
#endif
