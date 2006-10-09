/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Dataset

\brief    Dataset definition


\date     $Date: 2006/03/13 21:30:08,35 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Dataset_HPP
#define   SDB_Dataset_HPP

class     SDB_Dataset;

#pragma pack(8)

class  SDB_Dataset
{
protected  :         char                                         path[256];                                                 // Path for dataset
protected  :         char                                         reserve[256];                                              

public     :
                     char                                        *get_path() { return(path); }
                     char                                        *get_reserve() { return(reserve); }
};

#pragma pack()
#endif
