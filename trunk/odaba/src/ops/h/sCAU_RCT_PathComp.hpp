/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_RCT_PathComp

\brief    Path component
          Should be removed

\date     $Date: 2006/03/13 21:30:06,25 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CAU_RCT_PathComp_HPP
#define   CAU_RCT_PathComp_HPP

class     CAU_RCT_PathComp;

#pragma pack(8)

class  CAU_RCT_PathComp
{
protected  :         char                                         prop_name[40];                                             // Property name
protected  :         logical                                      path_up;                                                   //
protected  :         logical                                      path_opt1;                                                 //
protected  :         logical                                      active;                                                    //

public     :
                     char                                        *get_prop_name() { return(prop_name); }
                     logical                                      get_path_up() { return(path_up); }
                     logical                                      get_path_opt1() { return(path_opt1); }
                     logical                                      get_active() { return(active); }
};

#pragma pack()
#endif
