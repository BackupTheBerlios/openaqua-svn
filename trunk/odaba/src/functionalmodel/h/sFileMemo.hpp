/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    FileMemo



\date     $Date: 2006/05/10 19:51:12,10 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FileMemo_HPP
#define   FileMemo_HPP

class     FileMemo;

#pragma pack(8)

class  FileMemo
{
protected  :         char                                         file_name[8];                                              
protected  :         char                                         file_ext[3];                                               
protected  :         char                                         file_path[65];                                             
protected  :         logical                                      internal;                                                  
protected  :         PI(mem)                                      file_memo;                                                 

public     :
                     char                                        *get_file_name() { return(file_name); }
                     char                                        *get_file_ext() { return(file_ext); }
                     char                                        *get_file_path() { return(file_path); }
                     logical                                      get_internal() { return(internal); }
                     PI(mem)                                     &get_file_memo() { return(file_memo); }
};

#pragma pack()
#endif
