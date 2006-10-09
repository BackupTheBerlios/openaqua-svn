/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ViewSource

\brief    Source definition for a view collection


\date     $Date: 2006/03/13 21:30:14,12 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ViewSource_HPP
#define   SDB_ViewSource_HPP

class     SDB_ViewSource;

#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  SDB_ViewSource :public SDB_Resource
{
protected  :         char                                         order[40] ATTR_ALIGN(4);                                   // Key name
protected  :         PI(mem)                                      path;                                                      // Source definition

public     :
                     char                                        *get_order() { return(order); }
                     PI(mem)                                     &get_path() { return(path); }
};

#pragma pack()
#endif
