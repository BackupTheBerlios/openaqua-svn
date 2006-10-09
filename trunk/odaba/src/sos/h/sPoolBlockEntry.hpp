/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    PoolBlockEntry



\date     $Date: 2006/03/12 19:20:10,43 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PoolBlockEntry_HPP
#define   PoolBlockEntry_HPP

class     PoolBlockEntry;

#pragma pack(8)

class  PoolBlockEntry
{
protected  :         char                                         area;                                                      

public     :
                     char                                         get_area() { return(area); }
};

#pragma pack()
#endif
