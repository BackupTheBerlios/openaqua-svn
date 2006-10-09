/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ExtentList

\brief    


\date     $Date: 2006/03/12 19:09:59,81 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExtentList_HPP
#define   ExtentList_HPP

class     ExtentList;

#pragma pack(8)

class  ExtentList
{
protected  :         int64                                        identity;                                                  //
protected  :         char                                         extent_name[40];                                           //

public     :
public     :         OPI7ImpExp                  char *get_extent_name ( );
public     :         OPI7ImpExp                  int16 get_main_base ( );
};

#pragma pack()
#endif
