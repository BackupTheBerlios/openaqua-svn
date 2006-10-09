/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    ObjectCommander

\brief    


\date     $Date: 2006/03/12 19:36:10,56 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ObjectCommander_HPP
#define   ObjectCommander_HPP

class     ObjectCommander;

#include  <sOC_Panel.hpp>
#pragma pack(8)

class  ObjectCommander
{
protected  :         OC_Panel                                     left;                                                      //
protected  :         OC_Panel                                     right;                                                     //
protected  :         char                                         command[513];                                              //

public     :
                     OC_Panel                                    &get_left() { return(left); }
                     OC_Panel                                    &get_right() { return(right); }
                     char                                        *get_command() { return(command); }
public     :                                                             ObjectCommander ( );
public     :                                                             ~ObjectCommander ( );
};

#pragma pack()
#endif
